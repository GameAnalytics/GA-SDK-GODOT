#!/usr/bin/env python3
"""Check the Android wrapper against the GameAnalytics Android SDK it will actually run on.

Two rules, both derived from real failures:

1. The pinned SDK version agrees everywhere. build.gradle governs how the Godot plugin
   aar is compiled; _get_android_dependencies() in export_plugin.gd governs what an
   exported game resolves at runtime. These drifted silently (7.0.1 vs 7.1.0), and it is
   the export_plugin value that decides whether a class exists on the device.

2. Every Java name and descriptor the wrapper looks up exists in that artifact.
   check_jni.py proves a descriptor is well formed; it cannot tell you the method exists.
   A perfectly formed descriptor for a method that is not there passes that lint, compiles,
   and then fails at runtime - which is exactly how an IAP validation port built against
   a ReceiptInfo that has no no-arg constructor would have shipped.

Needs network (the GameAnalytics Maven repo) and javap from any JDK.
"""
import re
import subprocess
import sys
import tempfile
import time
import urllib.request
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "src/android/GAWrapperAndroid.cpp"

GRADLE = "android/godotgameanalytics/build.gradle"
EXPORT_PLUGINS = ["addons/GameAnalytics/export_plugin.gd",
                  "example/addons/GameAnalytics/export_plugin.gd"]

# classes from the GameAnalytics SDK artifact. Anything else the wrapper looks up
# (java/lang/String, our own godotgameanalytics plugin classes) is not in this jar.
SDK_PREFIX = "com/gameanalytics/sdk/"

failures = []


def read(rel):
    p = ROOT / rel
    if not p.exists():
        failures.append("missing file: %s" % rel)
        return ""
    return p.read_text(encoding="utf-8")


# ---- rule 1: the pinned version agrees everywhere -----------------------------------
PIN = re.compile(r'com\.gameanalytics\.sdk:gameanalytics-android:([0-9][0-9.]*)')

pins = {}
m = PIN.search(read(GRADLE))
if m:
    pins[GRADLE] = m.group(1)
else:
    failures.append("no gameanalytics-android pin found in %s" % GRADLE)

for rel in EXPORT_PLUGINS:
    m = PIN.search(read(rel))
    if m:
        pins[rel] = m.group(1)
    else:
        failures.append("no gameanalytics-android pin found in %s" % rel)

for rel, v in pins.items():
    print("%-48s %s" % (rel, v))

if len(set(pins.values())) > 1:
    failures.append("the gameanalytics-android pins disagree: %s" % pins)
    print("\nFAILED:")
    for f in failures:
        print("  - %s" % f)
    sys.exit(1)

if not pins:
    print("\nFAILED:")
    for f in failures:
        print("  - %s" % f)
    sys.exit(1)

# the runtime pin is the one that decides what exists on the device
version = pins.get(EXPORT_PLUGINS[0]) or next(iter(pins.values()))
print("\nchecking JNI usage against gameanalytics-android %s\n" % version)

# ---- fetch the artifact -------------------------------------------------------------
repo = "https://maven.gameanalytics.com/release"
m = re.search(r'PackedStringArray\(\["(https://[^"]+)"\]\)', read(EXPORT_PLUGINS[0]))
if m:
    repo = m.group(1).rstrip("/")

url = "%s/com/gameanalytics/sdk/gameanalytics-android/%s/gameanalytics-android-%s.aar" % (
    repo, version, version)

tmp = Path(tempfile.mkdtemp())
aar = tmp / "ga.aar"
# every build job waits on static-checks, so a transient network blip here would block
# the whole run. Retry a few times before giving up, but still fail rather than skip:
# a check that quietly passes when it cannot verify anything is worse than no check.
err = None
for attempt in range(3):
    try:
        with urllib.request.urlopen(url, timeout=60) as r, open(aar, "wb") as f:
            f.write(r.read())
        err = None
        break
    except Exception as e:
        err = e
        if attempt < 2:
            print("  download attempt %d failed (%s), retrying..." % (attempt + 1, e))
            time.sleep(5)
if err is not None:
    print("FAILED: could not download %s\n  %s" % (url, err))
    sys.exit(1)

with zipfile.ZipFile(aar) as z:
    z.extract("classes.jar", tmp)
jar = tmp / "classes.jar"

with zipfile.ZipFile(jar) as z:
    jar_classes = {n[:-6] for n in z.namelist() if n.endswith(".class")}


def members(cls):
    """{(name, descriptor)} for a class, via javap. '<init>' for constructors."""
    out = subprocess.run(["javap", "-classpath", str(jar), "-s", "-p", cls.replace("/", ".")],
                         capture_output=True, text=True)
    if out.returncode != 0:
        return None
    found, name = set(), None
    for line in out.stdout.splitlines():
        s = line.strip()
        d = re.match(r'descriptor:\s*(\S+)', s)
        if d and name:
            found.add((name, d.group(1)))
            continue
        m2 = re.match(r'.*?\b([A-Za-z_$][\w$]*)\s*\(', s)
        if m2:
            name = m2.group(1)
            if cls.rsplit("/", 1)[-1] == name:
                name = "<init>"
    return found


# ---- rule 2: every looked-up name and descriptor exists -----------------------------
text = read(SRC)
lines = text.splitlines()


def resolve(expr, upto=None):
    """A string literal, or the nearest preceding constexpr const char* with that name.

    The constants are function-local and reuse the same name, so the search has to run
    backwards from the use site. Matching the first declaration in the file instead
    silently attributes every lookup to whichever function happens to come first.
    """
    expr = expr.strip()
    if expr.startswith('"'):
        return expr.strip('"')
    var = expr.replace(".c_str()", "").strip()
    decl = re.compile(r'const char\*\s*' + re.escape(var) + r'\s*=\s*"([^"]+)"')
    for j in range((len(lines) - 1) if upto is None else upto, -1, -1):
        m2 = decl.search(lines[j])
        if m2:
            return m2.group(1)
    return None


# jclass variable -> class name, from FindClass / GetGameAnalyticsClass
var_class = {}
for idx, line in enumerate(lines):
    m2 = re.search(r'jclass\s+(\w+)\s*=\s*env->FindClass\(\s*([^)]+?)\s*\)', line)
    if m2:
        c = resolve(m2.group(2), idx)
        if c:
            var_class[m2.group(1)] = c
    if re.search(r'jclass\s+(\w+)\s*=\s*GetGameAnalyticsClass\(\)', line):
        var_class[re.search(r'jclass\s+(\w+)', line).group(1)] = "com/gameanalytics/sdk/GameAnalytics"

# every class the wrapper resolves out of the SDK must exist
checked_classes, unresolved = set(), []
for idx, line in enumerate(lines):
  for raw in re.findall(r'env->FindClass\(\s*([^)]+?)\s*\)', line):
    c = resolve(raw, idx)
    if c is None:
        unresolved.append("FindClass(%s)" % raw)
    elif c.startswith(SDK_PREFIX):
        checked_classes.add(c)

for c in sorted(checked_classes):
    if c not in jar_classes:
        failures.append("class not in gameanalytics-android %s: %s" % (version, c))
    else:
        print("  class ok  %s" % c)

# method and constructor lookups
cache, n_checked = {}, 0
pattern = re.compile(r'env->Get(Static)?MethodID\(\s*(\w+)\s*,\s*([^,]+?)\s*,\s*"([^"]*)"\s*\)')
for i, line in enumerate(lines, 1):
    m2 = pattern.search(line)
    if not m2:
        continue
    _static, cls_var, name_expr, desc = m2.groups()
    cls = var_class.get(cls_var)
    name = resolve(name_expr, i - 1)
    if cls is None or name is None:
        unresolved.append("%s:%d  %s(...,%s)" % (SRC.name, i, cls_var, name_expr))
        continue
    if not cls.startswith(SDK_PREFIX):
        continue
    if cls not in cache:
        cache[cls] = members(cls)
    have = cache[cls]
    if have is None:
        failures.append("could not javap %s" % cls)
        continue
    n_checked += 1
    if (name, desc) not in have:
        same = sorted(d for (n, d) in have if n == name)
        detail = ("\n      available: " + "\n      available: ".join(same)) if same else \
                 "\n      no method of that name on the class"
        failures.append("%s:%d  %s.%s%s does not exist%s" % (SRC.name, i, cls, name, desc, detail))

# CallStringMethod(name) resolves its method at runtime; check the literals passed to it
for name in sorted(set(re.findall(r'CallStringMethod\("([^"]+)"\)', text))):
    cls = "com/gameanalytics/sdk/GameAnalytics"
    if cls not in cache:
        cache[cls] = members(cls)
    n_checked += 1
    if (name, "()Ljava/lang/String;") not in (cache[cls] or set()):
        failures.append("CallStringMethod(\"%s\") has no matching ()Ljava/lang/String; on %s" % (name, cls))

print("\nchecked %d classes and %d method lookups" % (len(checked_classes), n_checked))
for u in unresolved:
    print("  skipped (not a literal): %s" % u)

if failures:
    print("\nFAILED:")
    for f in failures:
        print("  - %s" % f)
    sys.exit(1)

print("\nok: every JNI lookup exists in gameanalytics-android %s" % version)

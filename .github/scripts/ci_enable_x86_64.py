#!/usr/bin/env python3
"""Point the example project at an x86_64 build and the Android smoke scene.

CI-only, and never committed: the shipped addon stays arm64. A standard GitHub runner
emulates x86_64, and this job is about the JNI contract - class names, descriptors, the
dependency the export resolves - which is identical on both architectures.

A script rather than sed because the two differ on the one-line `a` form, and this is
testable on a developer machine.
"""
import re
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXAMPLE = ROOT / "example"
ADDON = EXAMPLE / "addons/GameAnalytics"

SO = "bin/android/x86_64/libGodotGameAnalytics.so"
SMOKE = "res://tests/android_smoke.tscn"


def fail(msg):
    print("FAIL: %s" % msg)
    sys.exit(1)


# ---- the built library ---------------------------------------------------------------
src = ROOT / "bin/android/release/libGodotGameAnalytics.so"
if not src.exists():
    fail("no x86_64 build at %s" % src)
dst = ADDON / SO
dst.parent.mkdir(parents=True, exist_ok=True)
shutil.copyfile(src, dst)
print("copied %s -> %s" % (src.relative_to(ROOT), dst.relative_to(ROOT)))

# ---- declare the x86_64 library, under [libraries] ------------------------------------
gde = ADDON / "GameAnalytics.gdextension"
lines = gde.read_text(encoding="utf-8").splitlines()

keys = ["android.debug.x86_64", "android.release.x86_64"]
lines = [l for l in lines if not any(l.startswith(k) for k in keys)]

anchor = next((i for i, l in enumerate(lines) if l.startswith("android.release.arm64")), None)
if anchor is None:
    fail("no android.release.arm64 in %s to anchor to" % gde.name)

# anchored to the arm64 key so these cannot land in [dependencies] at the end of the file
lines[anchor + 1:anchor + 1] = ['%s = "%s"' % (k, SO) for k in keys]
gde.write_text("\n".join(lines) + "\n", encoding="utf-8")
print("declared %s in %s" % (", ".join(keys), gde.name))

# ---- export only x86_64 ---------------------------------------------------------------
presets = EXAMPLE / "export_presets.cfg"
text = presets.read_text(encoding="utf-8")
for key, want in (("armeabi-v7a", "false"), ("arm64-v8a", "false"), ("x86_64", "true"), ("x86", "false")):
    pat = re.compile(r'^architectures/%s=(true|false)$' % re.escape(key), re.M)
    if not pat.search(text):
        fail("no architectures/%s entry in export_presets.cfg" % key)
    text = pat.sub("architectures/%s=%s" % (key, want), text, count=1)
presets.write_text(text, encoding="utf-8")
print("export preset set to x86_64 only")

# ---- run the smoke scene instead of the demo -------------------------------------------
project = EXAMPLE / "project.godot"
text = project.read_text(encoding="utf-8")
pat = re.compile(r'^run/main_scene=".*"$', re.M)
if not pat.search(text):
    fail("no run/main_scene in project.godot")
if not (EXAMPLE / "tests/android_smoke.tscn").exists():
    fail("the smoke scene is missing: example/tests/android_smoke.tscn")
project.write_text(pat.sub('run/main_scene="%s"' % SMOKE, text, count=1), encoding="utf-8")
print("main scene set to %s" % SMOKE)

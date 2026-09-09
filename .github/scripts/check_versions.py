#!/usr/bin/env python3
"""Assert the GDExtension API version is declared consistently.

build_ios.sh builds godot-cpp from inside the submodule, so it never sees SConstruct's
default and carries its own copy of the value. compatibility_minimum is a promise to the
engine about which versions can load the extension. If these drift, one platform is
silently built against a different API than the rest - which is exactly how the Android
build ended up restarting into a process with no plugin.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
failures = []


def read(rel):
    p = ROOT / rel
    if not p.exists():
        failures.append("missing file: %s" % rel)
        return ""
    return p.read_text(encoding="utf-8")


def find(pattern, text, label):
    m = re.search(pattern, text)
    if not m:
        failures.append("could not find %s" % label)
        return None
    return m.group(1)


scons = find(r'ARGUMENTS\.setdefault\(\s*"api_version"\s*,\s*"([\d.]+)"',
             read("SConstruct"), "api_version in SConstruct")
ios = find(r'API_VERSION="\$\{API_VERSION:-([\d.]+)\}"',
           read("build_ios.sh"), "API_VERSION in build_ios.sh")

gdext_versions = {}
for rel in ("addons/GameAnalytics/GameAnalytics.gdextension",
            "example/addons/GameAnalytics/GameAnalytics.gdextension"):
    v = find(r'compatibility_minimum\s*=\s*([\d.]+)', read(rel), "compatibility_minimum in %s" % rel)
    if v:
        gdext_versions[rel] = v

print("SConstruct    api_version           = %s" % scons)
print("build_ios.sh  API_VERSION           = %s" % ios)
for rel, v in gdext_versions.items():
    print("%-13s compatibility_minimum = %s" % (Path(rel).parts[0], v))

if scons and ios and scons != ios:
    failures.append("SConstruct api_version (%s) != build_ios.sh API_VERSION (%s)" % (scons, ios))

for rel, v in gdext_versions.items():
    if scons and v != scons:
        failures.append("%s compatibility_minimum (%s) != api_version (%s)" % (rel, v, scons))

# the two .gdextension files are copies of one another
if len(set(gdext_versions.values())) > 1:
    failures.append("the .gdextension files disagree: %s" % gdext_versions)

if failures:
    print("\nFAILED:")
    for f in failures:
        print("  - %s" % f)
    sys.exit(1)

print("\nok: all API version declarations agree")

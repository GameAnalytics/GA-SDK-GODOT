#!/usr/bin/env python3
"""Bundle the addon into a release zip.

    python bundle_release.py                 # version taken from plugin.cfg
    python bundle_release.py --version 3.1.1
    python bundle_release.py --out dist/

Produces GameAnalytics-Godot-<version>.zip laid out as the Asset Store and the
editor both expect:

    addons/GameAnalytics/...     <- extracts straight into a project
    LICENSE                      <- required at the zip root

Verifies before writing: the version matches plugin.cfg and GA_VERSION, every
platform binary declared in the .gdextension is present, and no stray build
output or source is carried along.
"""
import argparse
import os
import re
import sys
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent
ADDON = ROOT / "example" / "addons" / "GameAnalytics"
LICENSE = ROOT / "LICENSE"

# never ship these, whatever happens to be lying around in the working tree
EXCLUDE_NAMES = {".DS_Store", "Thumbs.db", ".gdignore"}
EXCLUDE_SUFFIXES = {".o", ".os", ".d", ".obj", ".pdb", ".ilk", ".exp", ".log"}
EXCLUDE_DIRS = {"__pycache__", ".godot", ".import"}


def fail(msg):
    print("ERROR: %s" % msg, file=sys.stderr)
    sys.exit(1)


def plugin_version():
    cfg = (ADDON / "plugin.cfg").read_text(encoding="utf-8")
    m = re.search(r'version\s*=\s*"([^"]+)"', cfg)
    if not m:
        fail("could not read version from plugin.cfg")
    return m.group(1)


def ga_version():
    src = (ROOT / "src" / "gameanalytics" / "GameAnalytics.cpp").read_text(encoding="utf-8")
    m = re.search(r'#define\s+GA_VERSION\s+"godot\s+([0-9.]+)"', src)
    return m.group(1) if m else None


def declared_binaries():
    """Every library path the .gdextension points at."""
    text = (ADDON / "GameAnalytics.gdextension").read_text(encoding="utf-8")
    paths = set()
    in_libraries = False
    for line in text.splitlines():
        s = line.strip()
        if s.startswith("["):
            in_libraries = s.lower() == "[libraries]"
            continue
        if in_libraries and "=" in s:
            m = re.search(r'"([^"]+)"', s)
            if m:
                paths.add(m.group(1))
    return sorted(paths)


def should_skip(path: Path):
    if path.name in EXCLUDE_NAMES or path.suffix in EXCLUDE_SUFFIXES:
        return True
    return any(part in EXCLUDE_DIRS for part in path.parts)


def main():
    ap = argparse.ArgumentParser(description="Bundle the GameAnalytics addon into a release zip.")
    ap.add_argument("--version", help="release version (default: read from plugin.cfg)")
    ap.add_argument("--out", default=".", help="output directory (default: repo root)")
    ap.add_argument("--skip-checks", action="store_true", help="package even if verification fails")
    args = ap.parse_args()

    if not ADDON.is_dir():
        fail("addon not found: %s" % ADDON)
    if not LICENSE.is_file():
        fail("LICENSE not found at the repo root (the Asset Store requires it)")

    cfg_version = plugin_version()
    version = args.version or cfg_version
    problems = []

    # the version in the filename should not disagree with what the addon reports
    if version != cfg_version:
        problems.append("requested version %s != plugin.cfg %s" % (version, cfg_version))
    gav = ga_version()
    if gav and gav != cfg_version:
        problems.append("plugin.cfg %s != GA_VERSION %s (binaries report the latter)" % (cfg_version, gav))

    # a missing binary means the extension silently fails to load on that platform
    missing = [p for p in declared_binaries() if not (ADDON / p).exists()]
    for p in missing:
        problems.append("declared in .gdextension but not present: %s" % p)

    if problems:
        print("Verification problems:")
        for p in problems:
            print("  - %s" % p)
        if not args.skip_checks:
            fail("refusing to package (use --skip-checks to override)")
        print("  ...packaging anyway (--skip-checks)\n")

    out_dir = Path(args.out).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)
    zip_path = out_dir / ("GameAnalytics-Godot-%s.zip" % version)

    count = 0
    with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as z:
        for path in sorted(ADDON.rglob("*")):
            if path.is_dir() or should_skip(path.relative_to(ADDON)):
                continue
            # addons/GameAnalytics/... so it extracts straight into a project
            z.write(path, Path("addons/GameAnalytics") / path.relative_to(ADDON))
            count += 1
        z.write(LICENSE, "LICENSE")
        count += 1

    size_mb = zip_path.stat().st_size / (1024 * 1024)
    print("%s" % zip_path)
    print("  version : %s" % version)
    print("  files   : %d" % count)
    print("  size    : %.1f MB%s" % (size_mb, "  (Asset Store limit is 1 GB)" if size_mb < 1024 else "  OVER THE 1 GB LIMIT"))
    print("  layout  : addons/GameAnalytics/... + LICENSE at root")


if __name__ == "__main__":
    main()

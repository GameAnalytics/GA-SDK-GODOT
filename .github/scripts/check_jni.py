#!/usr/bin/env python3
"""Lint the JNI usage in the Android wrapper.

Two rules, both derived from real failures:

1. Every type descriptor must be a valid JNI descriptor. "()L" is not - L introduces an
   object type and must be followed by a class name and a semicolon. The malformed
   descriptor made getElapsedSessionTime fail on every call.

2. Every failed lookup must clear the pending exception. JNI leaves a NoSuchMethodError
   pending after a failed GetStaticMethodID, and the *next* JNI call aborts the process
   with SIGABRT. One wrong method name killed the whole app ~20s after launch.

This does not verify the names exist on the SDK class - that needs the Maven artifact.
See CI_TESTING.md section 1.2 for that check.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "src/android/GAWrapperAndroid.cpp"

# a JNI descriptor: (args)return, where each type is primitive, array, or Lclass;
TYPE = r'(?:\[*(?:[ZBCSIJFD]|L[^;]+;))'
DESCRIPTOR = re.compile(r'^\(%s*\)(?:%s|V)$' % (TYPE, TYPE))

failures = []

if not SRC.exists():
    print("missing %s" % SRC)
    sys.exit(1)

text = SRC.read_text(encoding="utf-8")
lines = text.splitlines()

# ---- rule 1: descriptors are well formed -------------------------------------------
descriptors = re.findall(r'Get(?:Static)?MethodID\([^,]+,\s*[^,]+,\s*"([^"]*)"\)', text)
print("checked %d JNI descriptors" % len(descriptors))
for d in sorted(set(descriptors)):
    if not DESCRIPTOR.match(d):
        failures.append('malformed JNI descriptor: "%s"' % d)

# ---- rule 2: failed lookups clear the pending exception ------------------------------
# every "Failed to find method/class" log site must have an ExceptionClear nearby
log_sites = [i for i, l in enumerate(lines)
             if re.search(r'Failed to find (method|class)', l)]
unguarded = []
for i in log_sites:
    window = "\n".join(lines[max(0, i - 3):i + 4])
    if "ExceptionClear" not in window:
        unguarded.append(i + 1)

print("checked %d lookup-failure sites" % len(log_sites))
if unguarded:
    failures.append("lookup failures without ExceptionClear at lines: %s"
                    % ", ".join(str(n) for n in unguarded))

# a blunt backstop: never fewer clears than lookups
lookups = len(re.findall(r'Get(?:Static)?MethodID\(', text))
clears = len(re.findall(r'ExceptionClear\(\)', text))
print("lookups=%d exception-clears=%d" % (lookups, clears))
if clears < lookups:
    failures.append("fewer ExceptionClear() calls (%d) than JNI lookups (%d)" % (clears, lookups))

if failures:
    print("\nFAILED:")
    for f in failures:
        print("  - %s" % f)
    sys.exit(1)

print("\nok: JNI descriptors valid and all lookup failures guarded")

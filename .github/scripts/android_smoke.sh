#!/usr/bin/env bash
# Install the exported APK on the running emulator, drive the smoke scene and assert
# on logcat. Called from the emulator job, which supplies a booted device.
#
# CheckJNI is forced on: it turns the mistakes this is meant to catch - a null
# jmethodID, a bad descriptor, an unhandled pending exception - into an immediate
# abort rather than a silent no-op.
set -euo pipefail

APK="${1:-build/smoke.apk}"
PKG="com.gameanalytics.godottest"
ACTIVITY="$PKG/com.godot.game.GodotAppLauncher"
LOG="logcat.txt"

echo "::group::install"
adb wait-for-device
adb install -r -g "$APK"
echo "::endgroup::"

adb shell setprop debug.checkjni 1
adb shell am force-stop "$PKG" || true
adb logcat -c

echo "::group::run"
adb shell am start -W -n "$ACTIVITY"
# the scene quits itself; give it room on a cold start under software rendering
adb shell sleep 45
adb logcat -d > "$LOG"
echo "::endgroup::"

echo "::group::logcat (GameAnalytics)"
grep -aE "GA_SMOKE|GameAnalytics|godot " "$LOG" | head -60 || true
echo "::endgroup::"

fail=0

if ! grep -aq "Late-enabling -Xcheck:jni" "$LOG"; then
  echo "WARNING: CheckJNI was not enabled; JNI misuse would not abort"
fi

if ! grep -aq "GA_SMOKE DONE ok=true" "$LOG"; then
  echo "FAIL: the smoke scene did not run to completion"
  echo "      (no 'GA_SMOKE DONE ok=true' in logcat - the app crashed, or never started)"
  fail=1
fi

# our own wrapper logs these loudly when a class, method or constructor is missing
if grep -aqE "Failed to find (class|method|the)" "$LOG"; then
  echo "FAIL: the wrapper could not resolve something over JNI:"
  grep -aE "Failed to find (class|method|the)" "$LOG" | sed 's/^/      /'
  fail=1
fi

# ART complaints: a bad descriptor or a pending exception
if grep -aqE "JNI DETECTED ERROR|NoSuchMethodError|NoSuchFieldError|ClassNotFoundException" "$LOG"; then
  echo "FAIL: the runtime reported a JNI error:"
  grep -aE "JNI DETECTED ERROR|NoSuchMethodError|NoSuchFieldError|ClassNotFoundException" "$LOG" | sed 's/^/      /'
  fail=1
fi

if grep -aqE "FATAL EXCEPTION|signal 6 \(SIGABRT\)|signal 11 \(SIGSEGV\)" "$LOG"; then
  echo "FAIL: the process crashed:"
  grep -aE "FATAL EXCEPTION|signal 6 \(SIGABRT\)|signal 11 \(SIGSEGV\)" "$LOG" | sed 's/^/      /'
  fail=1
fi

if [ "$fail" -ne 0 ]; then
  exit 1
fi

echo "ok: the wrapper resolved every JNI call and the smoke scene completed"

#!/bin/bash

GDB_BIN="libs/arm64-v8a/gdbserver"
APP_ID="com.beatgames.beatsaber"
APP_ACTIVITY="${APP_ID}/com.unity3d.player.UnityPlayerActivity"
APP_PWD_DIR="/data/data/${APP_ID}"
APP_APK_DIR="$(adb shell pm path "${APP_ID}" | cut -d':' -f2)"
APP_APK_DIR="$(dirname "${APP_APK_DIR}")"
APP_PID="$(adb shell pidof "${APP_ID}")"
TARGET_DIR="obj/local/arm64-v8a"
PULL_FILES=(
  "/system/bin/app_process64"
  "/system/bin/linker64"
  "/system/lib64/libc.so"
  "/system/lib64/libm.so"
  "/system/lib64/libdl.so"
  "${APP_APK_DIR}/lib/arm64/libil2cpp.so"
  "${APP_APK_DIR}/lib/arm64/libmain.so"
  "${APP_APK_DIR}/lib/arm64/libunity.so"
)

echo "[*] App is at ${APP_APK_DIR}"

echo "[*] Pushing GDB binary"

adb push "${GDB_BIN}" "/sdcard/gdbserver"

echo "[*] Starting ${APP_ACTIVITY} in debug mode..."

adb shell am start -n "${APP_ACTIVITY}"

sleep 2

APP_PID="$(adb shell pidof "${APP_ID}")"

echo "[*] ${APP_ID} launched with pid ${APP_PID}"
echo "[*] Configuring device..."

adb shell setprop debug.debuggerd.wait_for_debugger true
adb forward tcp:8700 "jdwp:$APP_PID"
adb forward tcp:2345 tcp:2345
adb shell run-as com.beatgames.beatsaber cp "/sdcard/gdbserver" "${APP_PWD_DIR}/gdbserver"
adb shell run-as com.beatgames.beatsaber chmod +x "${APP_PWD_DIR}/gdbserver"

sleep 2

#echo "[*] Running JDB...resuming process..."
#jdb -attach localhost:8700  -sourcepath . &
#JDB_PID=$!
#sleep 1
#kill $JDB_PID

echo "[*] Pulling required files..."
for file in "${PULL_FILES[@]}"
do
  dest_file="${TARGET_DIR}/$(basename "$file")"
  if [ ! -f "$dest_file" ]; then
    echo "[*] Pulling $file to $dest_file..."
    adb pull "$file" "$dest_file"
  fi
done

echo "[*] Starting gdbserver in the background..."
adb shell run-as com.beatgames.beatsaber killall gdbserver
adb shell run-as com.beatgames.beatsaber "${APP_PWD_DIR}/gdbserver" --attach 0.0.0.0:2345 "$APP_PID"

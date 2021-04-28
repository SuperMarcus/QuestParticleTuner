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

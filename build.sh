#!/bin/bash

PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DEBUG_FLAG=0

if [[ "$CI_BUILD_TARGET" = "Debug" ]]; then
  DEBUG_FLAG=1
fi

NDK_DEBUG=$DEBUG_FLAG ndk-build NDK_PROJECT_PATH="${PROJECT_DIR}" APP_BUILD_SCRIPT="${PROJECT_DIR}/Android.mk" NDK_APPLICATION_MK="${PROJECT_DIR}/Application.mk" "$@"

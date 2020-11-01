#!/bin/bash

PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

ndk-build NDK_PROJECT_PATH="${PROJECT_DIR}" APP_BUILD_SCRIPT="${PROJECT_DIR}/Android.mk" NDK_APPLICATION_MK="${PROJECT_DIR}/Application.mk"

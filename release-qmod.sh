#!/bin/bash

#TMP_DIR=`mktemp -d -t questmod`

PKG_NAME=ParticleTuner.qmod

if [[ ! -z "$CI_BUILD_TARGET" ]]; then
  PKG_NAME="ParticleTuner.${CI_BUILD_TARGET}.qmod"
fi

rm -f "$PKG_NAME"

# Build normal package
zip -j "$PKG_NAME" mod.json cover.gif

find ./libs/arm64-v8a \
  ! -name 'libmodloader.so' \
  ! -name 'libcodegen*.so' \
  ! -name 'libcustom-types.so' \
  ! -name 'questui.so' \
  ! -name 'gdb*' \
  -type f -exec zip -j "$PKG_NAME" {} +

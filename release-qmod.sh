#!/bin/bash

#TMP_DIR=`mktemp -d -t questmod`

PKG_NAME=ParticleTuner.qmod

if [[ "$NDK_DEBUG" = 1 ]]; then
  PKG_NAME=ParticleTuner.Debug.qmod
fi

rm -f "$PKG_NAME"

# Build normal package
zip -j "$PKG_NAME" mod.json cover.gif

find ./libs/arm64-v8a \
  ! -name 'libmodloader.so' \
  ! -name 'libcodegen_*.so' \
  ! -name 'gdb*' \
  -type f -exec zip -j "$PKG_NAME" {} +

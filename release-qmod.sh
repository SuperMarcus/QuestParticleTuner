#!/bin/bash

#TMP_DIR=`mktemp -d -t questmod`

rm -f ParticleTuner.qmod

# Build normal package
zip -j ParticleTuner.qmod mod.json

find ./libs/arm64-v8a \
  ! -name 'libmodloader.so' \
  ! -name 'libcodegen_*.so' \
  ! -name 'gdb*' \
  -type f -exec zip -j ParticleTuner.qmod {} +

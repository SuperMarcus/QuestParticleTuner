#!/bin/bash

TMP_DIR=`mktemp -d -t questmod`

# Build standalone package
rm -f ParticleTuner.qmod ParticleTuner.standalone.qmod
cp mod.standalone.json "${TMP_DIR}/mod.json"
zip -j ParticleTuner.standalone.qmod "${TMP_DIR}/mod.json"
find ./libs/arm64-v8a \
  ! -name 'libmodloader.so' \
  -type f -exec zip -j ParticleTuner.standalone.qmod {} +

# Build normal package
zip -j ParticleTuner.qmod mod.json ./libs/arm64-v8a/libparticletuner.so

# Cleanup
rm -rf "${TMP_DIR}"

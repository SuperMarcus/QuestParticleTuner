#!/bin/bash

rm -f ParticleTuner.qmod
zip -j ParticleTuner.qmod mod.json
find ./libs/arm64-v8a \
  ! -name 'libmodloader.so' \
  -type f -exec zip -j ParticleTuner.qmod {} +

#!/bin/bash

rm -f ParticleTuner.zip
zip -j ParticleTuner.zip bmbfmod.json cover.gif
find ./libs/arm64-v8a ! -name 'libmodloader.so' ! -name 'libcodegen_*.so' -type f -exec zip -j ParticleTuner.zip {} +

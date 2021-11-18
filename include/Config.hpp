#pragma once

#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#define PT_DEFAULT_SPARKLE_MULTIPLIER       1.0
#define PT_DEFAULT_EXPLOSION_MULTIPLIER     1.0
#define PT_DEFAULT_LIFETIME_MULTIPLIER      1.0
#define PT_DEFAULT_PARTICLE_OPACITY         0.5

#define PT_PRESET_NONE      { "None", 0.0, 0.0, 0.0, 0.0, true, true, true, false }
#define PT_PRESET_NORMAL    { "Normal", 1.0, 1.0, 1.0, 0.5, false, false, false, false }
#define PT_PRESET_FANCY     { "Fantasy", 12.0, 0.1, 5.0, 1.0, false, false, true, true }
#define PT_PRESET_TOO_MUCH  { "Insane", 100.0, 10.0, 10.0, 1.0, false, false, false, true }
#define PT_NUMBER_OF_PRESETS 4

#define PT_DISCOVERY_MAX_ITERATIONS 5 

struct PTPreset {
    std::string name;
    float sparkleMultiplier;
    float explosionMultiplier;
    float lifetimeMultiplier;
    float particleOpacity;

    bool reduceCoreParticles;
    bool reduceClashParticles;
    bool reduceDustParticles;
    bool rainbowParticles;
};

class ConfigClass {
public:
    float sparkleMultiplier;
    float explosionMultiplier;
    float lifetimeMultiplier;
    float particleOpacity;

    bool rainbowParticles;
    bool reduceCoreParticles;
    bool reduceClashParticles;
    bool reduceDustParticles;

    void load();
    void store();

    ConfigClass(Configuration&);

private:
    Configuration& _storage;
};

ConfigClass& getConfig();

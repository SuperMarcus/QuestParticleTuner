#pragma once

#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#define PT_DEFAULT_SPARKLE_MULTIPLIER       1.0
#define PT_DEFAULT_EXPLOSION_MULTIPLIER     1.0
#define PT_DEFAULT_LIFETIME_MULTIPLIER      1.0

#define PT_PRESET_NONE      { "None", 0.0, 0.0, 0.0, true }
#define PT_PRESET_NORMAL    { "Normal", 1.0, 1.0, 1.0, false }
#define PT_PRESET_FANCY     { "Fancy", 5.0, 5.0, 2.0, false }
#define PT_PRESET_TOO_MUCH  { "Too Much", 100.0, 100.0, 10.0, false }
#define PT_NUMBER_OF_PRESETS 4

struct PTPreset {
    std::string name;
    float sparkleMultiplier;
    float explosionMultiplier;
    float lifetimeMultiplier;
    bool reduceCoreParticles;
};

class ConfigClass {
public:
    float sparkleMultiplier;
    float explosionMultiplier;
    float lifetimeMultiplier;
    bool rainbowParticles;
    bool reduceCoreParticles;

    void load();
    void store();

    ConfigClass(Configuration&);

private:
    Configuration& _storage;
};

ConfigClass& getConfig();

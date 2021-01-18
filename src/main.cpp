#include "modloader.hpp"
#include "particletune_private.hpp"
#include "particletune.hpp"
#include "Config.hpp"
#include "PTModSettings.hpp"
#include "UnityInternalCalls.hpp"

static ModInfo modInfo;

Logger& getLogger() {
    static auto logger = new Logger(modInfo);
    return *logger;
}

ConfigClass& getConfig() {
    static Configuration raw(modInfo);
    static ConfigClass config(raw);
    return config;
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Setting up ParticleTuner.");
}

extern "C" void load() {
    getLogger().info("Loading ParticleTuner...");
    PTRegisterTypes();
    ParticleTuner::icall_functions::resolve_icalls();
    PTInstallHooks();
    PTRegisterUI(modInfo);
    getLogger().info("Finished loading ParticleTuner.");
}

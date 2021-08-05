#include "UnityInternalCalls.hpp"
#include "utils/il2cpp-functions.hpp"
#include "particletune.hpp"
#include "particletune_private.hpp"

#define DECLARE_I(a) decltype(a) a
#define RESOLVE_I(a, name) \
    a = reinterpret_cast<decltype(a)>(il2cpp_functions::resolve_icall((name))); \
    if (a) getLogger().debug("Resolved icall pointer for: \"%s\" = %p", (name), (a)); \
    else getLogger().error("Failed to resolve icall function pointer for \"%s\"", (#a))

using namespace ParticleTuner::icall_functions;

DECLARE_I(ParticleSystem_MainModule::set_startLifetimeMultiplier_Injected);
DECLARE_I(ParticleSystem_MainModule::get_startLifetimeMultiplier_Injected);
DECLARE_I(ParticleSystem_ColorOverLifetimeModule::set_enabled_Injected);
DECLARE_I(ParticleSystem_ColorOverLifetimeModule::get_enabled_Injected);
DECLARE_I(ParticleSystem_ColorOverLifetimeModule::set_color_Injected);
DECLARE_I(ParticleSystem_ColorOverLifetimeModule::get_color_Injected);
DECLARE_I(ParticleSystem_ColorBySpeedModule::set_enabled_Injected);

void ParticleTuner::icall_functions::resolve_icalls() {
    getLogger().info("Resolving internal calls...");

    // Thanks Lillie#1010 for teaching me how to make icalls :)
    
    RESOLVE_I(
        ParticleSystem_MainModule::set_startLifetimeMultiplier_Injected,
        "UnityEngine.ParticleSystem/MainModule::set_startLifetimeMultiplier_Injected"
    );

    RESOLVE_I(
        ParticleSystem_MainModule::get_startLifetimeMultiplier_Injected,
        "UnityEngine.ParticleSystem/MainModule::get_startLifetimeMultiplier_Injected"
    );

    RESOLVE_I(
        ParticleSystem_ColorOverLifetimeModule::get_enabled_Injected,
        "UnityEngine.ParticleSystem/ColorOverLifetimeModule::get_enabled_Injected"
    );

    RESOLVE_I(
        ParticleSystem_ColorOverLifetimeModule::set_enabled_Injected,
        "UnityEngine.ParticleSystem/ColorOverLifetimeModule::set_enabled_Injected"
    );

    RESOLVE_I(
        ParticleSystem_ColorOverLifetimeModule::get_color_Injected,
        "UnityEngine.ParticleSystem/ColorOverLifetimeModule::get_color_Injected"
    );

    RESOLVE_I(
        ParticleSystem_ColorOverLifetimeModule::set_color_Injected,
        "UnityEngine.ParticleSystem/ColorOverLifetimeModule::set_color_Injected"
    );

    RESOLVE_I(
        ParticleSystem_ColorBySpeedModule::set_enabled_Injected,
        "UnityEngine.ParticleSystem/ColorBySpeedModule::set_enabled_Injected"
    );
}

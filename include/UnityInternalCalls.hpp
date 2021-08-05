#pragma once

#include "UnityEngine/ParticleSystem_MainModule.hpp"

namespace ParticleTuner::icall_functions {
    class ParticleSystem_MainModule {
    public:
        static void (*set_startLifetimeMultiplier_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self, float value);
        static float (*get_startLifetimeMultiplier_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self);
    };

    class ParticleSystem_ColorOverLifetimeModule {
    public:
        // They have the same layout so using the main module to fake the ColorOverLifetimeModule should be fine...
        static void (*set_enabled_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self_fake, bool value);
        static bool (*get_enabled_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self_fake);
        static void (*set_color_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self_fake, UnityEngine::ParticleSystem::MinMaxGradient *value);
        static void (*get_color_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self_fake, UnityEngine::ParticleSystem::MinMaxGradient *value);
    };

    class ParticleSystem_ColorBySpeedModule {
    public:
        static void (*set_enabled_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self_fake, bool value);
    };

    void resolve_icalls();
}

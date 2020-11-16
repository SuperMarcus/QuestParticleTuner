#pragma once

#include "UnityEngine/ParticleSystem_MainModule.hpp"

namespace ParticleTuner::icall_functions {
    class ParticleSystem_MainModule {
    public:
        static void (*set_startLifetimeMultiplier_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self, float value);
        static float (*get_startLifetimeMultiplier_Injected)(UnityEngine::ParticleSystem::MainModule* _unity_self);
    };

    void resolve_icalls();
}

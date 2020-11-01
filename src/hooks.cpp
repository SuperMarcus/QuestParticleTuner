#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/ParticleSystem_MainModule.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/NoteCutParticlesEffect.hpp"
#include "UnityEngine/Random.hpp"
#include "particletune.hpp"
#include "particletune_private.hpp"
#include "Config.hpp"

MAKE_HOOK_OFFSETLESS(NoteCutParticlesEffect_SpawnParticles, void,
                     GlobalNamespace::NoteCutParticlesEffect* self, Vector3 pos, Vector3 cutNormal,
                     Vector3 saberDir, Vector3 moveVec, Color32 color,
                     int sparkleParticlesCount, int explosionParticlesCount,
                     float lifetimeMultiplier)
{
    auto& currentConfig = getConfig();
    int newSparkleCount = static_cast<int>(sparkleParticlesCount * currentConfig.sparkleMultiplier);
    int newExplosionCount = static_cast<int>(explosionParticlesCount * currentConfig.explosionMultiplier);
    float newLifetimeMultiplier = lifetimeMultiplier * currentConfig.lifetimeMultiplier;

    auto sparklesPS = self->sparklesPS;
    auto explosionPS = self->explosionPS;
    auto corePS = self->explosionCorePS;

    sparklesPS->get_main().set_maxParticles(INT_MAX);
    explosionPS->get_main().set_maxParticles(INT_MAX);

    if (currentConfig.rainbowParticles) {
        auto randomColor = UnityEngine::Random::ColorHSV();
        color.a = static_cast<uint8_t>(randomColor.a * 255);
        color.r = static_cast<uint8_t>(randomColor.r * 255);
        color.g = static_cast<uint8_t>(randomColor.g * 255);
        color.b = static_cast<uint8_t>(randomColor.b * 255);
    }

    NoteCutParticlesEffect_SpawnParticles(self, pos, cutNormal, saberDir, moveVec, color, newSparkleCount, newExplosionCount, newLifetimeMultiplier);
}

void PTInstallHooks() {
    getLogger().info("Adding hooks...");
    INSTALL_HOOK_OFFSETLESS(NoteCutParticlesEffect_SpawnParticles, il2cpp_utils::FindMethodUnsafe("", "NoteCutParticlesEffect", "SpawnParticles", 8));
}

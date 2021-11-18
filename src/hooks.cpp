#include <algorithm>
#include <random>

#include "utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/ParticleSystem_MainModule.hpp"
#include "UnityEngine/ParticleSystem_MinMaxGradient.hpp"
#include "UnityEngine/Gradient.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "GlobalNamespace/NoteCutParticlesEffect.hpp"
#include "GlobalNamespace/SaberClashEffect.hpp"
#include "UnityEngine/Random.hpp"
#include "particletune.hpp"
#include "particletune_private.hpp"
#include "PTScenePSController.hpp"
#include "Config.hpp"
#include "UnityInternalCalls.hpp"

using namespace ParticleTuner;

MAKE_HOOK_MATCH(NoteCutParticlesEffect_SpawnParticles, &GlobalNamespace::NoteCutParticlesEffect::SpawnParticles, void,
                GlobalNamespace::NoteCutParticlesEffect *self, UnityEngine::Vector3 cutPoint,
                UnityEngine::Vector3 cutNormal, UnityEngine::Vector3 saberDir, float saberSpeed,
                UnityEngine::Vector3 noteMovementVec, UnityEngine::Color32 color, int sparkleParticlesCount,
                int explosionParticlesCount, float lifetimeMultiplier)
{
    auto &currentConfig = getConfig();
    int newSparkleCount = static_cast<int>(static_cast<float>(sparkleParticlesCount) * currentConfig.sparkleMultiplier);
    int newExplosionCount = static_cast<int>(static_cast<float>(explosionParticlesCount) * currentConfig.explosionMultiplier);
    float newLifetimeMultiplier = lifetimeMultiplier * currentConfig.lifetimeMultiplier;

    auto sparklesPS = self->sparklesPS;
    auto explosionPS = self->explosionPS;
    auto corePS = self->explosionCorePS;

    auto sparklesMain = sparklesPS->get_main();
    auto explosionMain = explosionPS->get_main();
    auto coreMain = corePS->get_main();

    sparklesMain.set_maxParticles(INT_MAX);
    explosionMain.set_maxParticles(INT_MAX);

    icall_functions::ParticleSystem_MainModule::set_startLifetimeMultiplier_Injected(
        &explosionMain,
        currentConfig.lifetimeMultiplier);

    icall_functions::ParticleSystem_ColorBySpeedModule::set_enabled_Injected(&sparklesMain, currentConfig.rainbowParticles);

    icall_functions::ParticleSystem_ColorOverLifetimeModule::set_enabled_Injected(&sparklesMain, currentConfig.rainbowParticles);

    if (currentConfig.reduceCoreParticles)
    {
        icall_functions::ParticleSystem_MainModule::set_startLifetimeMultiplier_Injected(
            &coreMain,
            0.0f);
        coreMain.set_maxParticles(0);
    }

    // getLogger().debug("Original color R,G,B,A: %d, %d, %d, %d", color.r, color.g, color.b, color.a);

    if (currentConfig.rainbowParticles)
    {
        const int color_value = 127; // color value of the HSV color code. 127 equals to 0.5f
        int rgb_variable = rand();
        int color_hue = rgb_variable % 256;
        rgb_variable >>= 8;
        int rgb_zero = rgb_variable & 1;
        rgb_variable >>= 1;
        rgb_variable %= 3;
        rgb_zero = (rgb_variable + 1 + rgb_zero) % 3;
        int rgb_fixed = 3 - rgb_variable - rgb_zero;

        switch (rgb_variable)
        {
        case 0:
            color.r = color_hue;
            break;
        case 1:
            color.g = color_hue;
            break;
        case 2:
            color.b = color_hue;
            break;
        }

        switch (rgb_zero)
        {
        case 0:
            color.r = 0;
            break;
        case 1:
            color.g = 0;
            break;
        case 2:
            color.b = 0;
            break;
        }

        switch (rgb_fixed)
        {
        case 0:
            color.r = color_value;
            break;
        case 1:
            color.g = color_value;
            break;
        case 2:
            color.b = color_value;
            break;
        }
    }

    // Set alpha channel
    color.a = static_cast<uint8_t>(std::clamp(currentConfig.particleOpacity * 255.0f, 0.0f, 255.0f));

    getLogger().debug("Processed color R,G,B,A: %d, %d, %d, %d", color.r, color.g, color.b, color.a);

    //    auto updatedColor = toColor(color);
    //    auto newGradient = new UnityEngine::ParticleSystem::MinMaxGradient(updatedColor);
    //    icall_functions::ParticleSystem_ColorOverLifetimeModule::set_color_Injected(&sparklesMain, newGradient);
    //

    NoteCutParticlesEffect_SpawnParticles(
        self, cutPoint, cutNormal, saberDir, saberSpeed, noteMovementVec, color,
        newSparkleCount, newExplosionCount, newLifetimeMultiplier);
}

MAKE_HOOK_MATCH(SaberClashEffect_LateUpdate, &GlobalNamespace::SaberClashEffect::LateUpdate, void,
                GlobalNamespace::SaberClashEffect *self)
{
    auto &currentConfig = getConfig();

    auto glowPS = self->glowParticleSystem;
    auto sparklePS = self->sparkleParticleSystem;

    glowPS->get_main().set_maxParticles(currentConfig.reduceClashParticles ? 0 : INT_MAX);
    sparklePS->get_main().set_maxParticles(currentConfig.reduceClashParticles ? 0 : INT_MAX);

    SaberClashEffect_LateUpdate(self);
}

MAKE_HOOK_MATCH(SceneManager_Internal_ActiveSceneChanged,
                &UnityEngine::SceneManagement::SceneManager::Internal_ActiveSceneChanged, void,
                UnityEngine::SceneManagement::Scene oldScene, UnityEngine::SceneManagement::Scene newScene)
{
    static std::vector<std::string> sensitiveScenes = {
        "Init", "MenuViewControllers", "GameCore", "Credits"};

    SceneManager_Internal_ActiveSceneChanged(oldScene, newScene);

    auto sceneNameCs = newScene.get_name();

    if (sceneNameCs)
    {
        auto sceneName = to_utf8(csstrtostr(newScene.get_name()));
        // getLogger().info("Transitioning to scene: %s", sceneName.data());

        if (std::find(sensitiveScenes.begin(), sensitiveScenes.end(), sceneName) != sensitiveScenes.end())
        {
            getLogger().info("Starting PTScenePSDiscoveryAgent...");
            auto discoveryAgent = THROW_UNLESS(il2cpp_utils::New<PTScenePSDiscoveryAgent *>());
            GlobalNamespace::SharedCoroutineStarter::get_instance()
                ->StartCoroutine(reinterpret_cast<System::Collections::IEnumerator *>(discoveryAgent));
        }
    }
}

void PTInstallHooks()
{
    auto &logger = getLogger();
    logger.info("Adding hooks...");
    INSTALL_HOOK(logger, NoteCutParticlesEffect_SpawnParticles);
    INSTALL_HOOK(logger, SaberClashEffect_LateUpdate);
    INSTALL_HOOK(logger, SceneManager_Internal_ActiveSceneChanged);
    srand(std::chrono::system_clock::now().time_since_epoch().count());
}

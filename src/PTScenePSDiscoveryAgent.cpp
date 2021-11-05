#include "particletune_private.hpp"
#include "PTScenePSController.hpp"
#include "Config.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "QuestUI.hpp"
#include "BeatSaberUI.hpp"
#include "CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/WaitForSeconds.hpp"

using namespace ParticleTuner;

DEFINE_TYPE(::ParticleTuner, PTScenePSDiscoveryAgent); // NOLINT(cert-err58-cpp)

bool PTScenePSDiscoveryAgent::MoveNext()
{
    if (dustPS == nullptr)
    {
        getLogger().info("PTScenePSDiscoveryAgent discovery iteration %d", iterations);

        auto particleSystems = UnityEngine::Object::FindObjectsOfType<UnityEngine::ParticleSystem *>();
        auto particleSystemsLen = particleSystems->Length();

        for (auto i = 0; i < particleSystemsLen; ++i)
        {
            auto ps = particleSystems->values[i];
            auto psName = ps->get_name();

            if (to_utf8(csstrtostr(psName)) == "DustPS")
            {
                getLogger().info("PTScenePSDiscoveryAgent found new DustPS.");
                dustPS = ps;
                UpdateDustPSSettings();
                break;
            }
        }

        if (dustPS == nullptr)
        {
            if (iterations < PT_DISCOVERY_MAX_ITERATIONS)
            {
                currentOp = UnityEngine::WaitForSeconds::New_ctor(0.5f);
                iterations++;
                return true;
            }
            else
            {
                getLogger().info("PTScenePSDiscoveryAgent discovery exceeded maximum iterations. Aborting...");
            }
        }
    }

    // Reset yield
    currentOp = nullptr;
    return false;
}

void PTScenePSDiscoveryAgent::UpdateDustPSSettings()
{
    if (dustPS)
    {
        auto &currentConfig = getConfig();
        dustPS->get_gameObject()->SetActive(!currentConfig.reduceDustParticles);
    }
}

Il2CppObject *PTScenePSDiscoveryAgent::get_Current()
{
    return currentOp;
}

void PTScenePSDiscoveryAgent::Reset()
{
    getLogger().info("Resetting PTScenePSDiscoveryAgent...");
    dustPS = nullptr;
    currentOp = nullptr;
    iterations = 0;
}

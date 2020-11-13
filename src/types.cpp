#include "QuestUI.hpp"
#include "modloader.hpp"
#include "particletune_private.hpp"
#include "particletune.hpp"
#include "PTScenePSController.hpp"
#include "PTModSettings.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

using namespace ParticleTuner;
using namespace custom_types;

void PTRegisterTypes() {
    getLogger().info("Registering ParticleTuner Types...");
    QuestUI::Init();
    Register::RegisterType<PTModSettingsViewController>();
    Register::RegisterType<PTScenePSDiscoveryAgent>();
    Register::RegisterType<PTPresetData>();
}

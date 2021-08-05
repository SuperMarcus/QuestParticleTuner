#include "QuestUI.hpp"
#include "particletune_private.hpp"
#include "PTModSettings.hpp"

using namespace ParticleTuner;
using namespace custom_types;

void PTRegisterTypes() {
    getLogger().info("Registering ParticleTuner Types...");
    il2cpp_functions::Init();
    QuestUI::Init();
    custom_types::Register::AutoRegister();
}

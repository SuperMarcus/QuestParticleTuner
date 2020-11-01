#include "particletune_private.hpp"
#include "PTModSettings.hpp"
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

using namespace ParticleTuner;

DEFINE_CLASS(PTModSettingsViewController);
DEFINE_CLASS(PTPresetData);

static PTPreset presetsRawList[] = {
    PT_PRESET_NONE,
    PT_PRESET_NORMAL,
    PT_PRESET_FANCY,
    PT_PRESET_TOO_MUCH
};
static PTPresetData* presetDataList[PT_NUMBER_OF_PRESETS];

void PTModSettingsApplyPreset(PTPresetData * presetData) {
    auto* vc = presetData->parent;
    auto& preset = presetsRawList[presetData->preset];
    auto& currentConfig = getConfig();

    if (vc) {
        getLogger().info("Selecting preset %s", preset.name.c_str());
        currentConfig.sparkleMultiplier = preset.sparkleMultiplier;
        currentConfig.explosionMultiplier = preset.explosionMultiplier;
        currentConfig.lifetimeMultiplier = preset.lifetimeMultiplier;
        vc->UpdateUIComponents();
    }
}

void PTModSettingsOnSparkleMultChange(PTModSettingsViewController* parent, float newValue) {
    if (newValue < 0) {
        parent->sparklesMultInc->CurrentValue = 0.0;
        parent->sparklesMultInc->UpdateValue();
    } else {
        getConfig().sparkleMultiplier = newValue;
        getLogger().info("Set sparkleMultiplier=%f", newValue);
    }
}

void PTModSettingsOnExplosionMultChange(PTModSettingsViewController* parent, float newValue) {
    if (newValue < 0) {
        parent->explosionsMultInc->CurrentValue = 0.0;
        parent->explosionsMultInc->UpdateValue();
    } else {
        getConfig().explosionMultiplier = newValue;
        getLogger().info("Set explosionMultiplier=%f", newValue);
    }
}

void PTModSettingsOnLifetimeMultChange(PTModSettingsViewController* parent, float newValue) {
    if (newValue < 0) {
        parent->lifetimeMultInc->CurrentValue = 0.0;
        parent->lifetimeMultInc->UpdateValue();
    } else {
        getConfig().lifetimeMultiplier = newValue;
        getLogger().info("Set lifetimeMultiplier=%f", newValue);
    }
}

void PTModSettingsOnRainbowToggle(PTModSettingsViewController* parent, bool newValue) {
    getConfig().rainbowParticles = newValue;
    getLogger().info("Set rainbowParticles=%d", newValue);
}

void PTModSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (firstActivation && addedToHierarchy) {
        getLogger().info("Adding mod settings UI components...");

        auto rootLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_rectTransform());
        rootLayout->get_gameObject()->AddComponent<QuestUI::Backgroundable*>()->ApplyBackground(
            il2cpp_utils::createcsstr("round-rect-panel")
        );
        rootLayout->set_padding(UnityEngine::RectOffset::New_ctor(16, 16, 8, 8));

        constexpr auto rootLayoutPreferredWidth = 128;
        auto rootLayoutElement = rootLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        rootLayoutElement->set_preferredWidth(rootLayoutPreferredWidth);
        rootLayoutElement->set_preferredHeight(40);
        
        auto sparkleChangeDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*),
            this, PTModSettingsOnSparkleMultChange
        );
        auto explosionChangeDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*),
            this, PTModSettingsOnExplosionMultChange
        );
        auto lifetimeChangeDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*),
            this, PTModSettingsOnLifetimeMultChange
        );
        auto rainbowToggleDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
            classof(UnityEngine::Events::UnityAction_1<bool>*),
            this, PTModSettingsOnRainbowToggle
        );

        auto &currentConfig = getConfig();
        
        // Configs
        sparklesMultInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            rootLayout->get_rectTransform(),
            "Sparkles Multiplier",
            1, 0.2,
            currentConfig.sparkleMultiplier,
            sparkleChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(sparklesMultInc->get_gameObject(), "Tune the amount of sparkles generated after a slash. Set to 0 to disable sparkles.");

        explosionsMultInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            rootLayout->get_rectTransform(),
            "Explosions Multiplier",
            1, 0.2,
            currentConfig.explosionMultiplier,
            explosionChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(explosionsMultInc->get_gameObject(), "Tune the amount of explosions generated after a slash. Set to 0 to disable explosions.");

        lifetimeMultInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            rootLayout->get_rectTransform(),
            "Lifetime Multiplier",
            1, 0.2,
            currentConfig.lifetimeMultiplier,
            lifetimeChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(lifetimeMultInc->get_gameObject(), "Tune the lifetime of particles. Lifetime determines how long the particles stay on the screen.");

        rainbowParticlesToggle = QuestUI::BeatSaberUI::CreateToggle(
            rootLayout->get_rectTransform(),
            "Rainbow Particles",
            rainbowToggleDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(rainbowParticlesToggle->get_gameObject(), "Randomizes the color of particles!");

        // Presets
        auto presetsLayout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(rootLayout->get_rectTransform());
        presetsLayout->set_spacing(1);

        auto presetsLayoutElement = presetsLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        presetsLayoutElement->set_preferredHeight(8);
        
        for (int i = 0; i < PT_NUMBER_OF_PRESETS; ++i) {
            if (!presetDataList[i]) {
                auto object = CRASH_UNLESS(il2cpp_utils::New<PTPresetData*>());
                object->preset = i;
                presetDataList[i] = object;
            }

            auto *presetData = presetDataList[i];
            auto *preset = &presetsRawList[i];
            presetData->parent = this;
            auto presetBtnDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
                classof(UnityEngine::Events::UnityAction*),
                presetData, PTModSettingsApplyPreset
            );
            QuestUI::BeatSaberUI::CreateUIButton(
                presetsLayout->get_rectTransform(),
                preset->name,
                "OkButton",
                presetBtnDelegate
            );
        }
    }
}

void PTModSettingsViewController::DidDeactivate(bool removedFromHierarchy, bool systemScreenDisabling) {
    getLogger().info("Deactivated PTModSettingsViewController.");
    getConfig().store();
}

void PTModSettingsViewController::UpdateUIComponents() {
    auto& currentConfig = getConfig();

    sparklesMultInc->CurrentValue = currentConfig.sparkleMultiplier;
    explosionsMultInc->CurrentValue = currentConfig.explosionMultiplier;
    lifetimeMultInc->CurrentValue = currentConfig.lifetimeMultiplier;

    sparklesMultInc->UpdateValue();
    explosionsMultInc->UpdateValue();
    lifetimeMultInc->UpdateValue();
}

void PTRegisterUI(ModInfo& modInfo) {
    getLogger().info("Registering ParticleTune UI...");
    QuestUI::Init();
    custom_types::Register::RegisterType<PTModSettingsViewController>();
    custom_types::Register::RegisterType<PTPresetData>();
    QuestUI::Register::RegisterModSettingsViewController<PTModSettingsViewController*>(modInfo, "Particle Tuner");
    memset(presetDataList, 0, sizeof(presetDataList));
}

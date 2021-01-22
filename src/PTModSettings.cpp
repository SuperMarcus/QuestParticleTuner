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
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "PTScenePSController.hpp"

using namespace ParticleTuner;

DEFINE_CLASS(PTModSettingsViewController);
DEFINE_CLASS(PTPresetData);

static PTPreset presetsRawList[] = {
    PT_PRESET_NONE,
    PT_PRESET_NORMAL,
    PT_PRESET_FANCY,
    PT_PRESET_TOO_MUCH
};

void PTModSettingsApplyPreset(PTPresetData * presetData) {
    auto* vc = presetData->parent;
    auto& preset = presetsRawList[presetData->preset];
    auto& currentConfig = getConfig();

    if (vc) {
        getLogger().info("Selecting preset %s", preset.name.c_str());
        currentConfig.sparkleMultiplier = preset.sparkleMultiplier;
        currentConfig.explosionMultiplier = preset.explosionMultiplier;
        currentConfig.lifetimeMultiplier = preset.lifetimeMultiplier;
        currentConfig.particleOpacity = preset.particleOpacity;
        currentConfig.reduceCoreParticles = preset.reduceCoreParticles;
        currentConfig.reduceClashParticles = preset.reduceClashParticles;
        currentConfig.reduceDustParticles = preset.reduceDustParticles;
        currentConfig.boostSaturation = preset.boostSaturation;
        currentConfig.rainbowParticles = preset.rainbowParticles;
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

void PTModSettingsOnParticleOpacityChange(PTModSettingsViewController* parent, float newValue) {
    if (newValue < 0.0f) {
        parent->particleOpacityInc->CurrentValue = 0.0f;
        parent->particleOpacityInc->UpdateValue();
    } else if (newValue > 1.0f) {
        parent->particleOpacityInc->CurrentValue = 1.0f;
        parent->particleOpacityInc->UpdateValue();
    } else {
        getConfig().particleOpacity = newValue;
        getLogger().info("Set particleOpacity=%f", newValue);
    }
}

void PTModSettingsOnReduceCoreParticlesToggle(PTModSettingsViewController* parent, bool newValue) {
    getConfig().reduceCoreParticles = newValue;
    getLogger().info("Set reduceCoreParticles=%d", newValue);
}

void PTModSettingsOnRainbowToggle(PTModSettingsViewController* parent, bool newValue) {
    getConfig().rainbowParticles = newValue;
    getLogger().info("Set rainbowParticles=%d", newValue);
}

void PTModSettingsOnReduceClashParticlesToggle(PTModSettingsViewController* parent, bool newValue) {
    getConfig().reduceClashParticles = newValue;
    getLogger().info("Set reduceClashParticles=%d", newValue);
}

void PTModSettingsOnReduceDustParticlesToggle(PTModSettingsViewController* parent, bool newValue) {
    getConfig().reduceDustParticles = newValue;

    auto dustPSAgent = reinterpret_cast<PTScenePSDiscoveryAgent*>(parent->dustPSAgent);
    if (dustPSAgent) {
        dustPSAgent->UpdateDustPSSettings();
    }

    getLogger().info("Set reduceDustParticles=%d", newValue);
}

//void PTModSettingsOnBoostSaturationToggle(PTModSettingsViewController* parent, bool newValue) {
//    getConfig().boostSaturation = newValue;
//    getLogger().info("Set boostSaturation=%d", newValue);
//}

void PTModSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (firstActivation && addedToHierarchy) {
        getLogger().info("Adding mod settings UI components...");

        auto sectionBackgroundName = il2cpp_utils::createcsstr("round-rect-panel");
        auto sectionPadding = UnityEngine::RectOffset::New_ctor(4, 4, 4, 4);

        // Root Layout
        auto rootLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_rectTransform());
        rootLayout->set_spacing(4);

        // Layout - Section Container
        auto sectionContainerLayout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(rootLayout->get_rectTransform());
        sectionContainerLayout->set_spacing(4);

        auto leftTogglesLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(sectionContainerLayout->get_rectTransform());
        leftTogglesLayout->get_gameObject()
            ->AddComponent<QuestUI::Backgroundable*>()
            ->ApplyBackground(sectionBackgroundName);
        leftTogglesLayout->set_padding(sectionPadding);
        
        auto leftTogglesLayoutElement = leftTogglesLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        // leftTogglesLayoutElement->set_flexibleHeight(0);
        // leftTogglesLayoutElement->set_preferredHeight(45);
        leftTogglesLayoutElement->set_preferredWidth(60);

        // auto leftSpacingLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(leftSectionLayout->get_rectTransform());
        // auto leftSpacingLayoutElement = leftSpacingLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        // leftSpacingLayoutElement->set_preferredWidth(60);

        // Layout - Center Container
        auto centerContainerLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(sectionContainerLayout->get_rectTransform());
        centerContainerLayout->set_spacing(4);

        // auto centerContainerLayoutElement = centerContainerLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        // centerContainerLayoutElement->set_preferredWidth(80);
        // centerContainerLayoutElement->set_preferredHeight(45);

        // Layout - Center Multipliers
        auto centerSectionLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(centerContainerLayout->get_rectTransform());
        centerSectionLayout->get_gameObject()
            ->AddComponent<QuestUI::Backgroundable*>()
            ->ApplyBackground(sectionBackgroundName);
        centerSectionLayout->set_padding(sectionPadding);
        centerSectionLayout->set_spacing(4);
        auto centerSectionLayoutElement = centerSectionLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        centerSectionLayoutElement->set_preferredWidth(110);
        // centerSectionLayoutElement->set_preferredHeight(60);

        // Layout - Presets Container
        auto presetContainerLayout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(centerContainerLayout->get_rectTransform());
        presetContainerLayout->set_spacing(4);
        presetContainerLayout->set_padding(UnityEngine::RectOffset::New_ctor(2, 2, 0, 0));
        auto presetContainerLayoutElement = presetContainerLayout
            ->GetComponent<UnityEngine::UI::LayoutElement*>();
        presetContainerLayoutElement->set_preferredHeight(8);
        // presetContainerLayoutElement->set_preferredWidth(100);
        // presetContainerLayoutElement->set_flexibleWidth(0);

        // Layout - Right
        // auto rightSectionLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(sectionContainerLayout->get_rectTransform());
        // rightSectionLayout->get_gameObject()
        //     ->AddComponent<QuestUI::Backgroundable*>()
        //     ->ApplyBackground(sectionBackgroundName);
        // rightSectionLayout->set_padding(sectionPadding);
        // auto rightSectionLayoutElement = rightSectionLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        // rightSectionLayoutElement->set_preferredWidth(60);
        // rightSectionLayoutElement->set_preferredHeight(45);
        
        // Delegates
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
        auto particleOpacityChangeDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<float>*>(
            classof(UnityEngine::Events::UnityAction_1<float>*),
            this, PTModSettingsOnParticleOpacityChange
        );
        auto reduceCoreParticlesToggleDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
            classof(UnityEngine::Events::UnityAction_1<bool>*),
            this, PTModSettingsOnReduceCoreParticlesToggle
        );
        auto reduceClashParticlesToggleDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
            classof(UnityEngine::Events::UnityAction_1<bool>*),
            this, PTModSettingsOnReduceClashParticlesToggle
        );
        auto reduceDustParticlesToggleDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
            classof(UnityEngine::Events::UnityAction_1<bool>*),
            this, PTModSettingsOnReduceDustParticlesToggle
        );
//        auto boostSaturationToggleDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
//            classof(UnityEngine::Events::UnityAction_1<bool>*),
//            this, PTModSettingsOnBoostSaturationToggle
//        );
        auto rainbowToggleDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction_1<bool>*>(
            classof(UnityEngine::Events::UnityAction_1<bool>*),
            this, PTModSettingsOnRainbowToggle
        );

        auto &currentConfig = getConfig();

        // Left Panel Configs
        reduceCoreParticlesToggle = QuestUI::BeatSaberUI::CreateToggle(
            leftTogglesLayout->get_rectTransform(),
            "Reduce Core Particles",
            currentConfig.reduceCoreParticles,
            reduceCoreParticlesToggleDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(reduceCoreParticlesToggle->get_gameObject(), "Remove the core particle effects from slicing a block.");

        reduceClashParticlesToggle = QuestUI::BeatSaberUI::CreateToggle(
            leftTogglesLayout->get_rectTransform(),
            "Reduce Clash Effects",
            currentConfig.reduceClashParticles,
            reduceClashParticlesToggleDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(reduceClashParticlesToggle->get_gameObject(), "Remove saber clash effects.");

        reduceDustParticlesToggle = QuestUI::BeatSaberUI::CreateToggle(
            leftTogglesLayout->get_rectTransform(),
            "Reduce Dust",
            currentConfig.reduceDustParticles,
            reduceDustParticlesToggleDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(reduceDustParticlesToggle->get_gameObject(), "Remove the particles floating in the air.");

//        boostSaturationToggle = QuestUI::BeatSaberUI::CreateToggle(
//            leftTogglesLayout->get_rectTransform(),
//            "Boost Saturation",
//            currentConfig.boostSaturation,
//            boostSaturationToggleDelegate
//        );
//        QuestUI::BeatSaberUI::AddHoverHint(boostSaturationToggle->get_gameObject(), "Make the note slash particle more vibrant.");

        rainbowParticlesToggle = QuestUI::BeatSaberUI::CreateToggle(
            leftTogglesLayout->get_rectTransform(),
            "Rainbow Particles",
            currentConfig.rainbowParticles,
            rainbowToggleDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(rainbowParticlesToggle->get_gameObject(), "Make slash particles rainbow!");

        // Center Panel Configs
        sparklesMultInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            centerSectionLayout->get_rectTransform(),
            "Sparkles Multiplier",
            1, 0.2,
            currentConfig.sparkleMultiplier,
            sparkleChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(sparklesMultInc->get_gameObject(), "Tune the amount of sparkles generated after a slash. Set to 0 to disable sparkles.");

        explosionsMultInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            centerSectionLayout->get_rectTransform(),
            "Explosions Multiplier",
            1, 0.2,
            currentConfig.explosionMultiplier,
            explosionChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(explosionsMultInc->get_gameObject(), "Tune the amount of explosions generated after a slash. Set to 0 to disable explosions.");

        lifetimeMultInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            centerSectionLayout->get_rectTransform(),
            "Lifetime Multiplier",
            1, 0.2,
            currentConfig.lifetimeMultiplier,
            lifetimeChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(lifetimeMultInc->get_gameObject(), "Tune the lifetime of particles. Lifetime determines how long the particles stay on the screen.");

        particleOpacityInc = QuestUI::BeatSaberUI::CreateIncrementSetting(
            centerSectionLayout->get_rectTransform(),
            "Particle Opacity",
            1, 0.1,
            currentConfig.particleOpacity,
            particleOpacityChangeDelegate
        );
        QuestUI::BeatSaberUI::AddHoverHint(particleOpacityInc->get_gameObject(), "Adjust the opacity of the slash particle.");

        for (int i = 0; i < PT_NUMBER_OF_PRESETS; ++i) {
            auto *preset = &presetsRawList[i];
            auto *presetData = CRASH_UNLESS(il2cpp_utils::New<PTPresetData*>());
            presetData->preset = i;
            presetData->parent = this;

            auto presetBtnDelegate = il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(
                classof(UnityEngine::Events::UnityAction*),
                presetData, PTModSettingsApplyPreset
            );
            QuestUI::BeatSaberUI::CreateUIButton(
                presetContainerLayout->get_rectTransform(),
                preset->name,
                "OkButton",
                presetBtnDelegate
            );
        }

        // Start private DustPS discovery agent
        auto privateAgent = THROW_UNLESS(il2cpp_utils::New<PTScenePSDiscoveryAgent*>());
        dustPSAgent = reinterpret_cast<Il2CppObject*>(privateAgent);
        GlobalNamespace::SharedCoroutineStarter::get_instance()
            ->StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(privateAgent));
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
    particleOpacityInc->CurrentValue = currentConfig.particleOpacity;

    sparklesMultInc->UpdateValue();
    explosionsMultInc->UpdateValue();
    lifetimeMultInc->UpdateValue();
    particleOpacityInc->UpdateValue();

    rainbowParticlesToggle->set_isOn(currentConfig.rainbowParticles);
    reduceClashParticlesToggle->set_isOn(currentConfig.reduceClashParticles);
    reduceCoreParticlesToggle->set_isOn(currentConfig.reduceCoreParticles);
    reduceDustParticlesToggle->set_isOn(currentConfig.reduceDustParticles);
//    boostSaturationToggle->set_isOn(currentConfig.boostSaturation);
}

void PTRegisterUI(ModInfo& modInfo) {
    getLogger().info("Registering ParticleTuner UI...");
    QuestUI::Register::RegisterModSettingsViewController<PTModSettingsViewController*>(modInfo, "Particle Tuner");
}

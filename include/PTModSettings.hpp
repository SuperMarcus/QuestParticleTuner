#pragma once

#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "CustomTypes/Components/Settings/IncrementSetting.hpp"
#include "modloader.hpp"
#include "Config.hpp"

DECLARE_CLASS_CODEGEN(ParticleTuner, PTModSettingsViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, sparklesMultInc);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, explosionsMultInc);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, lifetimeMultInc);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, particleOpacityInc);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, reduceCoreParticlesToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, reduceClashParticlesToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, reduceDustParticlesToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, rainbowParticlesToggle);
//    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, boostSaturationToggle);
    DECLARE_INSTANCE_FIELD(Il2CppObject*, dustPSAgent);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);

    DECLARE_METHOD(void, UpdateUIComponents);

    REGISTER_FUNCTION(PTModSettingsViewController,
        REGISTER_FIELD(sparklesMultInc);
        REGISTER_FIELD(explosionsMultInc);
        REGISTER_FIELD(lifetimeMultInc);
        REGISTER_FIELD(particleOpacityInc);
        REGISTER_FIELD(reduceCoreParticlesToggle);
        REGISTER_FIELD(reduceClashParticlesToggle);
        REGISTER_FIELD(reduceDustParticlesToggle);
        REGISTER_FIELD(rainbowParticlesToggle);
//        REGISTER_FIELD(boostSaturationToggle);
        REGISTER_FIELD(dustPSAgent);

        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
        REGISTER_METHOD(UpdateUIComponents);
    )
)

DECLARE_CLASS_CODEGEN(ParticleTuner, PTPresetData, Il2CppObject,
    DECLARE_INSTANCE_FIELD(PTModSettingsViewController*, parent);
    DECLARE_INSTANCE_FIELD(int, preset);

    REGISTER_FUNCTION(PTPresetData,
        REGISTER_FIELD(parent);
        REGISTER_FIELD(preset);
    )
)

#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "readability-const-return-type"

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
    DECLARE_INSTANCE_FIELD_DEFAULT(QuestUI::IncrementSetting*, sparklesMultInc, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(QuestUI::IncrementSetting*, explosionsMultInc, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(QuestUI::IncrementSetting*, lifetimeMultInc, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(QuestUI::IncrementSetting*, particleOpacityInc, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(UnityEngine::UI::Toggle*, reduceCoreParticlesToggle, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(UnityEngine::UI::Toggle*, reduceClashParticlesToggle, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(UnityEngine::UI::Toggle*, reduceDustParticlesToggle, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(UnityEngine::UI::Toggle*, rainbowParticlesToggle, nullptr);
//    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, boostSaturationToggle);
    DECLARE_INSTANCE_FIELD_DEFAULT(Il2CppObject*, dustPSAgent, nullptr);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);

    DECLARE_INSTANCE_METHOD(void, UpdateUIComponents);
)

DECLARE_CLASS_CODEGEN(ParticleTuner, PTPresetData, Il2CppObject,
    DECLARE_INSTANCE_FIELD_DEFAULT(PTModSettingsViewController*, parent, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, preset, 0);
)

#pragma clang diagnostic pop
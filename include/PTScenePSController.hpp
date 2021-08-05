#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-sizeof-expression"
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "readability-const-return-type"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "CustomTypes/Components/Settings/IncrementSetting.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "UnityEngine/ParticleSystem.hpp"
#include "modloader.hpp"
#include "Config.hpp"

DECLARE_CLASS_INTERFACES(ParticleTuner, PTScenePSDiscoveryAgent,
    "System", "Object", sizeof(Il2CppObject),
    { il2cpp_utils::GetClassFromName("System.Collections", "IEnumerator") },

    DECLARE_INSTANCE_FIELD_DEFAULT(Il2CppObject*, currentOp, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(UnityEngine::ParticleSystem*, dustPS, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, iterations, 0);

    DECLARE_OVERRIDE_METHOD(Il2CppObject*, get_Current, il2cpp_utils::FindMethod("System.Collections", "IEnumerator", "get_Current"));
    DECLARE_OVERRIDE_METHOD(bool, MoveNext, il2cpp_utils::FindMethod("System.Collections", "IEnumerator", "MoveNext"));
    DECLARE_OVERRIDE_METHOD(void, Reset, il2cpp_utils::FindMethod("System.Collections", "IEnumerator", "Reset"));

    DECLARE_INSTANCE_METHOD(void, UpdateDustPSSettings);
)

#pragma clang diagnostic pop

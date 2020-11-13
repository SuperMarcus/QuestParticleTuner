#pragma once

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
    il2cpp_utils::GetClassFromName("System.Collections", "IEnumerator"),

    DECLARE_INSTANCE_FIELD(Il2CppObject*, currentOp);
    DECLARE_INSTANCE_FIELD(UnityEngine::ParticleSystem*, dustPS);
    DECLARE_INSTANCE_FIELD(int, iterations);

    DECLARE_OVERRIDE_METHOD(Il2CppObject*, get_Current, il2cpp_utils::FindMethod("System.Collections", "IEnumerator", "get_Current"));
    DECLARE_OVERRIDE_METHOD(bool, MoveNext, il2cpp_utils::FindMethod("System.Collections", "IEnumerator", "MoveNext"));
    DECLARE_OVERRIDE_METHOD(void, Reset, il2cpp_utils::FindMethod("System.Collections", "IEnumerator", "Reset"));

    DECLARE_METHOD(void, UpdateDustPSSettings);

    REGISTER_FUNCTION(PTScenePSDiscoveryAgent,
        REGISTER_FIELD(currentOp);
        REGISTER_FIELD(dustPS);
        REGISTER_FIELD(iterations);

        REGISTER_METHOD(MoveNext);
        REGISTER_METHOD(get_Current);
        REGISTER_METHOD(Reset);
        REGISTER_METHOD(UpdateDustPSSettings);
    )
)

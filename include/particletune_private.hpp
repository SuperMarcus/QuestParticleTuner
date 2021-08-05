#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <string>

#include "utils/typedefs.h"
#include "utils/logging.hpp"

namespace UnityEngine {
    struct Color32;
    struct Color;
}

Logger& getLogger();

void PTInstallHooks();
void PTRegisterUI(struct ModInfo& modInfo);
void PTRegisterTypes();

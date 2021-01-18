#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <string>

#include "utils/typedefs.h"
#include "utils/logging.hpp"

typedef struct Color32 {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color32;

Logger& getLogger();

void PTInstallHooks();
void PTRegisterUI(struct ModInfo& modInfo);
void PTRegisterTypes();

#pragma once
#include <iostream>
#include <Windows.h>

#include "../../offsets/client.dll.hpp"
#include "../../offsets/offsets.hpp"
#include "../../utils/driver/Driver.hpp"

void glowToggle(HANDLE driver, std::uintptr_t client, bool& glow_toggle);
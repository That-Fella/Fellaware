#pragma once
#include <iostream>
#include <Windows.h>

#include "../../offsets/client.dll.hpp"
#include "../../offsets/offsets.hpp"
#include "../../offsets/buttons.hpp"
#include "../../utils/driver/Driver.hpp"

void bhopToggle(HANDLE driver, std::uintptr_t client, const std::uint32_t flags);

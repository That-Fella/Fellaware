#pragma once
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

#include "../../offsets/client.dll.hpp"
#include "../../offsets/offsets.hpp"
#include "../../utils/driver/Driver.hpp"

void checkAndShoot(HANDLE driver, std::uintptr_t client);
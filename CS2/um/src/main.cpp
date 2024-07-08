#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
#include <math.h>

#include "math/vector.h"
#include "utils/utils/Utilities.hpp"
#include "utils/driver/Driver.hpp"

#include "hacks/glow/glow.hpp"
#include "hacks/antiflash/antiflash.hpp"
#include "hacks/bhop/bhop.hpp"
#include "hacks/triggerbot/triggerbot.hpp"

bool glow_toggle = false;
bool bhop_toggle = false;
bool anti_flash_toggle = false;
bool triggerbot_toggle = false;

void PrintStates();

int main() {
	LaunchCS2();

	std::this_thread::sleep_for(std::chrono::seconds(15));

	const DWORD pid = get_process_id(L"cs2.exe");

	if (pid == 0)
	{
		std::cout << "Failed to find process\n";
		std::cin.get();
		return 1;
	}

	const HANDLE driver = CreateFile(L"\\\\.\\KernelDriver", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (driver == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to create driver handle\n";
		std::cin.get();
		return 1;
	}

	if (driver::attach_to_process(driver, pid) == true)
	{
		std::cout << "Attachment successful.\n";

		if (const std::uintptr_t client = get_module_base(pid, L"client.dll"); client != 0) {
			std::cout << "Client found.\n";

			while (true)
			{
				if (GetAsyncKeyState(VK_END))
					break;

				if (client == 0)
					break;

				const auto local_player_pawn = driver::read_memory<std::uintptr_t>(driver, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
				const auto entity_id = driver::read_memory<std::uintptr_t>(driver, local_player_pawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex);

				if (local_player_pawn == 0)
					continue;

				const auto flags = driver::read_memory<std::uint32_t>(driver, local_player_pawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);

				// glow
				if (GetAsyncKeyState(VK_NUMPAD1) & 1) 
				{
					glow_toggle = !glow_toggle;
					ClearConsole();
					PrintStates();
					Sleep(150);
				}

				glowToggle(driver, client, glow_toggle);

				// bhop
				if (GetAsyncKeyState(VK_NUMPAD2) & 1) 
				{
					bhop_toggle = !bhop_toggle;
					ClearConsole();
					PrintStates();
					Sleep(150);
				}
				if (bhop_toggle)
				{
					bhopToggle(driver, client, flags);
				}

				// antiflash
				if (GetAsyncKeyState(VK_NUMPAD3) & 1)
				{
					anti_flash_toggle = !anti_flash_toggle;
					ClearConsole();
					PrintStates();
					Sleep(150);
				}

				if (anti_flash_toggle)
				{
					antiflashToggle(driver, local_player_pawn);
				}

				// triggerbot
				if (GetAsyncKeyState(VK_NUMPAD4) & 1)
				{
					triggerbot_toggle = !triggerbot_toggle;
					ClearConsole();
					PrintStates();
					Sleep(150);
				}
			
				if (triggerbot_toggle)
				{
					checkAndShoot(driver, client);
				}
			}
		}
	}

	HANDLE cs2ProcessHandle = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (cs2ProcessHandle != NULL) {
		TerminateProcess(cs2ProcessHandle, 0); // Terminate cs2.exe
		CloseHandle(cs2ProcessHandle); // Close the handle to the process
	}

	CloseHandle(driver);

	return 0;
}

void PrintStates() {
	printf("Glow: %s    \n", glow_toggle ? "on" : "off");
	printf("Bhop: %s    \n", bhop_toggle ? "on" : "off");
	printf("Anti Flash: %s    \n", anti_flash_toggle ? "on" : "off");
	printf("Triggerbot: %s    \n", triggerbot_toggle ? "on" : "off");
	fflush(stdout);
}
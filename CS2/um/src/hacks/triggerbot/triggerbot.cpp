#include "triggerbot.hpp"

void checkAndShoot(HANDLE driver, std::uintptr_t client) {
	if (GetAsyncKeyState(VK_XBUTTON1) || GetAsyncKeyState(VK_XBUTTON2))
	{
		uintptr_t localplayer = driver::read_memory<uintptr_t>(driver, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
		int localteam = driver::read_memory<int>(driver, localplayer + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

		int entity_id = driver::read_memory<int>(driver, localplayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex);

		if (entity_id > 0)
		{
			uintptr_t entity_list = driver::read_memory<uintptr_t>(driver, client + cs2_dumper::offsets::client_dll::dwEntityList);

			uintptr_t ent_entry = driver::read_memory<uintptr_t>(driver, entity_list + 0x8 * (entity_id >> 9) + 0x10);
			uintptr_t entity = driver::read_memory<uintptr_t>(driver, ent_entry + 120 * (entity_id & 0x1FF));

			int team = driver::read_memory<int>(driver, entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
			int health = driver::read_memory<int>(driver, entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);

			if (team != localteam && health > 0)
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(10);
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
}
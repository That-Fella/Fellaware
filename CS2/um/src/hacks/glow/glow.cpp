#include "glow.hpp"


void glowToggle(HANDLE driver, std::uintptr_t client, bool& glow_toggle) {
	for (auto i = 0; i < 64; i++)
	{
		uintptr_t entity_list = driver::read_memory<uintptr_t>(driver, client + cs2_dumper::offsets::client_dll::dwEntityList);
		if (entity_list == 0)
			continue;
		uintptr_t list_entry = driver::read_memory<uintptr_t>(driver, entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
		if (list_entry == 0)
			continue;
		uintptr_t player = driver::read_memory<uintptr_t>(driver, list_entry + 120 * (i & 0x1FF));
		if (player == 0)
			continue;
		uint32_t player_pawn = driver::read_memory<uint32_t>(driver, player + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
		uintptr_t list_entry2 = driver::read_memory<uintptr_t>(driver, entity_list + 0x8 * ((player_pawn & 0x7FFF) >> 9) + 16);
		if (list_entry2 == 0)
			continue;
		uintptr_t p_cs_player_pawn = driver::read_memory<uintptr_t>(driver, list_entry2 + 120 * (player_pawn & 0x1FF));
		if (p_cs_player_pawn == 0)
			continue;
		if (glow_toggle)
		{
			// disable broken glow memory offset (idk what happened to the offsets, I think they got nuked from the game) driver::write_memory(driver, p_cs_player_pawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_flDetectedByEnemySensorTime, 100000.f);
		}
		else
		{
			// disable broken glow memory offset (idk what happened to the offsets, I think they got nuked from the game) driver::write_memory(driver, p_cs_player_pawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_flDetectedByEnemySensorTime, 0.f);
		}

	}
}

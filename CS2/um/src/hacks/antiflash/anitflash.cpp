#include "antiflash.hpp"

#include "../../offsets/client.dll.hpp"
#include "../../offsets/offsets.hpp"
#include "../../utils/driver/Driver.hpp"

void antiflashToggle(HANDLE driver, std::uintptr_t local_player_pawn)
{
    driver::write_memory<float>(driver, local_player_pawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_flFlashDuration, 0.0f);
}
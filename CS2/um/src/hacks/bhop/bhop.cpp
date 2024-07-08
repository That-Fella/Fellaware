#include "bhop.hpp"

void bhopToggle(HANDLE driver, std::uintptr_t client, const std::uint32_t flags)
{
	const bool in_air = flags & (1 << 0);
	const bool space_pressed = GetAsyncKeyState(VK_SPACE);
	const auto force_jump = driver::read_memory<DWORD>(driver, client + cs2_dumper::buttons::jump);

	if (space_pressed && in_air)
	{
		Sleep(5);
		driver::write_memory(driver, client + cs2_dumper::buttons::jump, 65537);
	}
	else if (space_pressed && !in_air)
	{
		driver::write_memory(driver, client + cs2_dumper::buttons::jump, 256);
	}
	else if (!space_pressed && force_jump == 65537)
	{
		driver::write_memory(driver, client + cs2_dumper::buttons::jump, 256);
	}
}


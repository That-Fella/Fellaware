#include "Utilities.hpp"

DWORD get_process_id(const wchar_t* process_name) {
	DWORD process_id = 0;

	HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (snap_shot == INVALID_HANDLE_VALUE)
		return process_id;

	PROCESSENTRY32W entry = {};
	entry.dwSize = sizeof(decltype(entry));

	if (Process32FirstW(snap_shot, &entry) == TRUE)
	{
		if (_wcsicmp(process_name, entry.szExeFile) == 0)
			process_id = entry.th32ProcessID;
		else
		{
			while (Process32NextW(snap_shot, &entry) == TRUE)
			{
				if (_wcsicmp(process_name, entry.szExeFile) == 0)
				{
					process_id = entry.th32ProcessID;
					break;
				}
			}
		}
	}

	CloseHandle(snap_shot);

	return process_id;
}

std::uintptr_t get_module_base(const DWORD pid, const wchar_t* module_name) {
	std::uintptr_t module_base = 0;

	HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	if (snap_shot == INVALID_HANDLE_VALUE)
		return module_base;

	MODULEENTRY32W entry = {};
	entry.dwSize = sizeof(decltype(entry));

	if (Module32FirstW(snap_shot, &entry) == TRUE)
	{
		if (wcsstr(module_name, entry.szModule) != nullptr)
			module_base = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
		else
		{
			while (Module32NextW(snap_shot, &entry) == TRUE)
			{
				if (wcsstr(module_name, entry.szModule) != nullptr)
				{
					module_base = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
					break;
				}
			}
		}
	}

	CloseHandle(snap_shot);

	return module_base;
}

void ClearConsole() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD count;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

	SetConsoleCursorPosition(hStdOut, coord);
}


bool LaunchCS2() 
{
	const LPCWSTR steamURL = L"steam://rungameid/730";

	HINSTANCE result = ShellExecute(NULL, L"open", steamURL, NULL, NULL, SW_SHOWNORMAL);

	if ((uintptr_t)result > 32) {
		std::cout << "CS2 Launched.\n";
		return true;
	}
	else {
		std::cout << "Failed to launch CS:GO. Error: " << (uintptr_t)result << "\n";
		return false;
	}
	return false;
}
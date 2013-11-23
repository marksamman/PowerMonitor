/*
 * Copyright (c) 2013 Mark Samman <https://github.com/marksamman/PowerMonitor>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <functional>

#include <Windows.h>
#include <TlHelp32.h>

#include "config.hpp"
#include "powermonitor.hpp"

void showBalloonTip(const wchar_t* message)
{
	NOTIFYICONDATA data;
	data.cbSize = sizeof(NOTIFYICONDATA);
	data.hIcon = nullptr;
	data.uTimeout = 1500;
	data.uFlags = NIF_INFO;
	data.dwInfoFlags = NIIF_INFO;
	wcscpy_s(data.szInfoTitle, L"PowerMonitor");
	wcscpy_s(data.szInfo, message);
	Shell_NotifyIcon(NIM_ADD, &data);
	Sleep(1500);
	Shell_NotifyIcon(NIM_DELETE, &data);
}

void processProcessList(const std::function<bool (wchar_t*)>& func)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		return;
	}

	Process32First(snapshot, &entry);
	do {
		if (func(entry.szExeFile)) {
			break;
		}
	} while (Process32Next(snapshot, &entry));
	CloseHandle(snapshot);
}

int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	PowerMonitor powerMonitor;
	powerMonitor.loadPowerSchemes();

	size_t highPowerSchemeIndex;
	if (!powerMonitor.getSchemeIndexByName(highPowerSchemeName, highPowerSchemeIndex)) {
		showBalloonTip(L"Error: high power scheme not found. Exiting.");
		return EXIT_FAILURE;
	}

	size_t defaultSchemeIndex;
	if (!powerMonitor.getSchemeIndexByName(defaultSchemeName, defaultSchemeIndex)) {
		showBalloonTip(L"Error: default power scheme not found. Exiting.");
		return EXIT_FAILURE;
	}

	size_t lowPowerSchemeIndex;
	if (!powerMonitor.getSchemeIndexByName(lowPowerSchemeName, lowPowerSchemeIndex)) {
		showBalloonTip(L"Error: low power scheme not found. Exiting.");
		return EXIT_FAILURE;
	}

	showBalloonTip(L"PowerMonitor is now running.");

	for (;;) {
		powerMonitor.updateActiveScheme();

		bool highPowerAppRunning = false;
		bool lowPowerAppRunning = false;
		processProcessList([&highPowerAppRunning, &lowPowerAppRunning](const wchar_t* processName) {
			for (const wchar_t* appName : highPowerAppNames) {
				if (wcscmp(appName, processName) == 0) {
					highPowerAppRunning = true;
					return true;
				}
			}

			for (const wchar_t* appName : lowPowerAppNames) {
				if (wcscmp(appName, processName) == 0) {
					lowPowerAppRunning = true;
				}
			}
			return false;
		});

		if (highPowerAppRunning) {
			if (powerMonitor.setPowerScheme(highPowerSchemeIndex)) {
				wchar_t tooltipMessage[171];
				wsprintf(tooltipMessage, L"Power scheme set to: %s", highPowerSchemeName);
				showBalloonTip(tooltipMessage);
			}
		} else if (lowPowerAppRunning) {
			if (powerMonitor.setPowerScheme(lowPowerSchemeIndex)) {
				wchar_t tooltipMessage[171];
				wsprintf(tooltipMessage, L"Power scheme set to: %s", lowPowerSchemeName);
				showBalloonTip(tooltipMessage);
			}
		} else {
			if (powerMonitor.setPowerScheme(defaultSchemeIndex)) {
				wchar_t tooltipMessage[171];
				wsprintf(tooltipMessage, L"Power scheme set to: %s", defaultSchemeName);
				showBalloonTip(tooltipMessage);
			}
		}
		Sleep(5000);
	}
	return EXIT_SUCCESS;
}

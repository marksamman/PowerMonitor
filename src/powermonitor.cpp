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

#include <Windows.h>
#include <powrprof.h>

#include "powermonitor.hpp"

void PowerMonitor::loadPowerSchemes()
{
	ULONG index = 0;
	GUID guid;
	DWORD guidSize = sizeof(GUID);
	UCHAR name[258];
	while (PowerEnumerate(nullptr, nullptr, nullptr, ACCESS_SCHEME, index++, reinterpret_cast<UCHAR*>(&guid), &guidSize) == ERROR_SUCCESS) {
		// Max length for power scheme name is 128 characters.
		// Each character in the name is 2 bytes (wchar), and
		// should also be terminated by two NULL bytes.
		//
		// (128 * 2) + 2 = 258
		DWORD nameSize = 258;
		if (PowerReadFriendlyName(nullptr, &guid, nullptr, nullptr, name, &nameSize) != ERROR_SUCCESS) {
			break;
		}
		schemes.emplace_back(guid, name, nameSize);
	}
}

void PowerMonitor::updateActiveScheme()
{
	PowerGetActiveScheme(nullptr, &activeScheme);
}

bool PowerMonitor::setPowerScheme(const size_t index)
{
	const PowerScheme& scheme = schemes[index];
	if (*activeScheme == scheme.guid) {
		return false;
	}

	PowerSetActiveScheme(nullptr, &scheme.guid);
	return true;
}

bool PowerMonitor::getSchemeIndexByName(const wchar_t* name, size_t& index)
{
	for (size_t i = 0, size = schemes.size(); i < size; ++i) {
		const PowerScheme& scheme = schemes[i];
		if (wcscmp(name, scheme.name) == 0) {
			index = i;
			return true;
		}
	}
	return false;
}

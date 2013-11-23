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

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

const wchar_t* highPowerAppNames[] = {
	L"Game.exe",
	L"dota.exe",
	L"csgo.exe",
	L"Isaac.exe",
	L"TeamViewer_Desktop.exe"
};
const wchar_t* lowPowerAppNames[] = {
	L"vlc.exe"
};

const wchar_t* highPowerSchemeName = L"High performance";
const wchar_t* defaultSchemeName = L"Balanced";
const wchar_t* lowPowerSchemeName = L"Power saver";

#endif

/*
	File: 3dsbrick.c
	Desc: A boot9strap firmware that will brick your 3DS
	Author: Arves100
	Date: 11-03-2019

	Copyright (C) 2019 Arves100.
	Released under GPL v2.0 license.

	https://www.z7games.altervista.org/bricoio/#3ds

	Based from Hourglass9 by d0k3 (https://github.com/d0k3/Hourglass9)
*/

#include "decryptor/nand.h"
#include "decryptor/keys.h"
#include "platform.h"

extern void repl(int argc, char** argv);

void crash_code()
{
	int* x = NULL;
	*x = 454;
}

void main(int argc, char** argv)
{
	int errorlevel = 0;
	// nand keys

	repl(argc, argv);

	if (SetupTwlKey0x03() != 0) // TWL KeyX / KeyY
            errorlevel = 2;
	if ((GetUnitPlatform() == PLATFORM_N3DS) && (SetupCtrNandKeyY0x05() != 0))
		errorlevel = 2; // N3DS CTRNAND KeyY
	if (LoadKeyFromFile(0x25, 'X', NULL)) // NCCH 7x KeyX
		errorlevel = (errorlevel < 1) ? 1 : errorlevel;
	if (LoadKeyFromFile(0x18, 'X', NULL)) // NCCH Secure3 KeyX
		errorlevel = (errorlevel < 1) ? 1 : errorlevel;
	if (LoadKeyFromFile(0x1B, 'X', NULL)) // NCCH Secure4 KeyX
		errorlevel = (errorlevel < 1) ? 1 : errorlevel;
	if (SetupAgbCmacKeyY0x24()) // AGBSAVE CMAC KeyY
		errorlevel = (errorlevel < 1) ? 1 : errorlevel;

	SetNand(false, false);
	BrickNand();
}
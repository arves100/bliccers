#include "common.h"

u8 top_screen = 0;
u8 bottom_screen = 0;

void repl(int argc, char** argv)
{
	    if(argc >= 2) {
        // newer entrypoints
        u8 **fb = (u8 **)(void *)argv[1];
        top_screen = fb[0];
        bottom_screen = fb[2];
    } else {
        // outdated entrypoints
        top_screen = (u8*)(*(u32*)0x23FFFE00);
        bottom_screen = (u8*)(*(u32*)0x23FFFE08);
	}
}

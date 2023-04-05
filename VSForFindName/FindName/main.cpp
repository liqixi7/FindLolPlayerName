#include <stdio.h>
#include "openfile.h"
#include <stdlib.h>
#include "main.h"
int main(void)
{
	int a = 0;
	(void)OpenBlackTxt();
#if USE_ENTER
	EnterRoomLog();
#elsif FROM_DESKTOP
	OpenRoomLog();
#else
	GetTheMostNewFileName();
	GetNameFromLog();
#endif
	CompareTwoFileName();
	system("PAUSE");
}
#include <stdio.h>
#include "openfile.h"
#include <stdlib.h>
int main(void)
{
	int a = 0;
	(void)OpenBlackTxt();
	OpenRoomLog();
	#if !FROM_DESKTOP
	GetTheMostNewFileName();
	GetNameFromLog();
	#endif
	CompareTwoFileName();
	system("PAUSE");
}
#ifndef OPEN_FILE_H
#define OPEN_FILE_H
bool OpenBlackTxt(void);
int GetFileNumber(char* addr);
bool OpenRoomLog(void);
bool CompareTwoFileName(void);
char* GetTheMostNewFileName(void);
char GetNameFromLog(void);
int Utf8ToANSI(char* argvin, char* argvout);
void cpfile(char* path_from, char* path_to);
char* UnicodeToANSI(const wchar_t* str);
void windows_cmd_support_utf8(void);
#endif
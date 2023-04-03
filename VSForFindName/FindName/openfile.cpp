#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openfile.h"
#include "main.h"
#include <windows.h> 
#include <locale.h> 
char OnlyNameBlack[255][1024] = { 0 };/*store name from lol.txt*/
char OnlyNameGame[5][1024] = { 0 };/*store name from roomname.txt*/
char NameAndGuilty[255][1024] = { 0 };
char NameFromLOLLog[10][1024] = { 0 };
bool OpenBlackTxt(void)
{
    FILE* fp = 0;
    int i = 0;
    unsigned long j = 0;
    char buff[255][1024] = { 0 };

    int FileNumber = 0;

    if ((fopen_s(&fp, "C:/Users/lhr07/Desktop/lol.txt", "r")) != 0)
    {
        printf("OPEN FAILED\n");
        return false;
    }
    char addrtemp[50] = "C:/Users/lhr07/Desktop/lol.txt";
    FileNumber = GetFileNumber(addrtemp);
    for (i = 0; i < FileNumber; i++)
    {
        fgets(&buff[i][0], 301, fp);
        for (j = 0; j < 1024; j++)
        {
            if ((buff[i][j]) == '/')
            {
                memcpy(&OnlyNameBlack[i][0], &buff[i][0], j + 1);
            }
            if ((buff[i][j]) == '*')
            {
                memcpy(&NameAndGuilty[i][0], &buff[i][0], j + 1);
            }
        }
        // printf("%s",&OnlyNameBlack[i][0]);
        // printf("\n");
    }


    fclose(fp);

    return true;
}
/*get lol.txt `s line numbers*/
int GetFileNumber(char* addr)
{
    FILE* fp = 0;
    if ((fopen_s(&fp, addr, "r")) != 0)
    {
        printf("OPEN FAILED\n");
        return 0;
    }
    int LineNumberFlag = 0, LineNumberRow = 0, LineNumberCount = 0;
    while (!feof(fp))
    {
        LineNumberFlag = fgetc(fp);
        if (LineNumberFlag == '\n')
            LineNumberCount++;
    }
    LineNumberRow = LineNumberCount + 1;

    fclose(fp);
    return LineNumberRow;
}
/*get player names from roomname.txt*/
bool OpenRoomLog(void)
{
    char buff[5][50] = { 0 };
    int i = 0;
    unsigned long j = 0;
    FILE* fp = 0;
    if ((fopen_s(&fp, "C:/Users/lhr07/Desktop/roomlog.txt", "r")) != 0)
    {
        printf("OPEN FAILED\n");
        return false;
    }
    for (i = 0; i < 5; i++)
    {
        fgets(&buff[i][0], 301, fp);
        for (j = 0; j < 50; j++)
        {
            //printf("%x\n", buff[i][j]);
            //if (((buff[i][j]) == 0xffffffbc) && ((buff[i][j + 1]) == 0xffffffd3) && ((buff[i][j + 2]) == 0xffffffc8) && ((buff[i][j + 3]) == 0xffffffeb))/*%bc%d3%c8%eb*/
            if (((buff[i][j]) == 0xffffffe5) && ((buff[i][j + 1]) == 0xffffff8a) && ((buff[i][j + 2]) == 0xffffffa0) && ((buff[i][j + 3]) == 0xffffffe5))
            {
                memcpy(&OnlyNameGame[i][0], &buff[i][0], j);
                OnlyNameGame[i][j] = '/';
            }
        }
    }
    fclose(fp);
}
bool CompareTwoFileName(void)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int FileNumber = 0;
    char addrtemp[50] = "C:/Users/lhr07/Desktop/lol.txt";
    FileNumber = GetFileNumber(addrtemp);
    int length1[255] = { 0 };
#if FROM_DESKTOP
    int length2[5] = { 0 };
#else
    int length2[10] = { 0 };
#endif
    char tblk[30];
    char tgame[30];
    int GuiltyFlag = 0;
    for (i = 0; i < FileNumber; i++)
    {
        for (j = 0; j <= 30; j++)
        {
            if (OnlyNameBlack[i][j] == '/')
            {
                length1[i] = j;
            }
#if FROM_DESKTOP
            if (i < 5)
#else
            if (i < 10)
#endif
            {
#if FROM_DESKTOP
                if (OnlyNameGame[i][j] == '/')
#else
                if (NameFromLOLLog[i][j] == '/')
#endif
                {
                    length2[i] = j;
                }
            }
        }
        // printf("%d,%d\n",length1,length2);
    }
    for (i = 0; i < FileNumber; i++)
    {
        memcpy(tblk, &OnlyNameBlack[i][0], length1[i]);
        tblk[length1[i]] = '\0';
#if FROM_DESKTOP
        for (j = 0; j < 5; j++)
#else
        for (j = 0; j < 10; j++)
#endif
        {
#if FROM_DESKTOP
            memcpy(tgame, &OnlyNameGame[j][0], length2[j]);
#else
            memcpy(tgame, &NameFromLOLLog[j][0], length2[j]);
#endif
            tgame[length2[j]] = '\0';
            if (length1[i] != length2[j])
            {
            }
            else
            {
                if (strcmp(tblk, tgame) == 0)
                {
                    printf("找到大恶人 :%s!\n", tblk);
                    printf("罪行为 :%s \n", &NameAndGuilty[i][0]);
                    GuiltyFlag = 1;
                }
                else
                {
                }
            }
        }
    }
    if (GuiltyFlag == 0)
    {
        printf("本局无内鬼，可以交易\n");
    }
    return 0;
}
/*get name from LOL file log(auto)*/
char GetNameFromLog(void)
{
    char* ptr = GetTheMostNewFileName();
    FILE* fp = 0;
    int i = 0;
    int j = 0;
    char FileAddr[255] = { 0 };
    for (i = 0; i < 255; i++)
    {
        if ((ptr[i] == '\n') || (ptr[i] == '\0'))
        {
            ptr[i] = '\0';
        }
        if (ptr[i] == '\\')
        {
            ptr[i] = '/';
        }
    }
    memcpy(FileAddr, ptr, 255);
    // printf("%s",FileAddr);

    // char ANSIFileAddr[255] = "D:/PyForFindLOLName/gamename/gamename.txt";
    // Utf8ToANSI(FileAddr,ANSIFileAddr);
    if ((fopen_s(&fp, FileAddr, "r")) != 0)
    {
        printf("OPEN FAILED\n");
        return 0;
    }
    int FileNumber = 0;
    FileNumber = GetFileNumber(FileAddr);
    char buff[255][1024] = { 0 };
    int startbyte = 0;
    int endbyte = 0;
    int count = 0;
    char* pTemp = 0;
    for (i = 0; i < FileNumber; i++)/*find line by line*/
    {
        fgets(&buff[i][0], 300, fp);
        for (j = 0; j < 255; j++)/*find byte by byte*/
        {
            if ((buff[i][j] == 'c') && (buff[i][j + 1] == 'o') && (buff[i][j + 2] == 'm') && (buff[i][j + 3] == 'p') && (buff[i][j + 4] == 'a'))
            {
                startbyte = j + 21;/*find start byte*/
            }
            else if ((buff[i][j] == ':') && (buff[i][j + 1] == ' ') && (buff[i][j + 2] == 'P') && (buff[i][j + 3] == 'e') && (buff[i][j + 4] == 't'))
            {
                endbyte = j - 1;/*find end byte*/
            }
            else if ((buff[i][j] == ':') && (buff[i][j + 1] == ' ') && (buff[i][j + 2] == 'M') && (buff[i][j + 3] == 'i') && (buff[i][j + 4] == 's'))
            {
                endbyte = j - 1;/*find end byte*/
            }
            if (endbyte != 0)
            {
                memcpy(&NameFromLOLLog[count][0], &buff[i][startbyte], (endbyte - startbyte + 1));
                NameFromLOLLog[count][endbyte - startbyte + 1] = '/';
                windows_cmd_support_utf8();
                // pTemp = UnicodeToANSI((const wchar_t*)&NameFromLOLLog[count][0]);
                endbyte = 0;
                count++;
                if (count > 9)
                {
                    i = FileNumber;
                }
                j = 255;
            }
        }
    }
}
/*get LOL file log`s file name*/
char* GetTheMostNewFileName(void)
{
    FILE* fp = 0;
    char buff[1024] = { 0 };
    char* ptr = buff;
    system("dir F:\\xunxian\\WeGameApps\\英雄联盟\\Game\\Logs\\GameLogs\\*.txt /s /b > a.log");
    if ((fopen_s(&fp, "a.log", "r")) != 0)
    {
        printf("OPEN FAILED\n");
        return 0;
    }
    while (fgets(buff, 300, fp) != NULL)
    {

    }
    // printf("%s \n", buff);
    return ptr;/*auto return the last file name*/
}
int Utf8ToANSI(char* argvin, char* argvout)
{
    setlocale(LC_ALL, "");

    FILE* in_file = 0;
    if ((fopen_s(&in_file, argvin, "r")) != 0)
    {
        printf("Error: could not open input file %!s(MISSING)\n", argvin);
        return 1;
    }

    FILE* out_file = 0;
    if ((fopen_s(&out_file, "D:/PyForFindLOLName/gamename/gamename.txt", "a+")) != 0)
    {
        printf("Error: could not open output file %!s(MISSING)\n", argvout);
        fclose(out_file);
        return 1;
    }

    int c;
    while ((c = fgetc(in_file)) != EOF) {
        fputc(c, out_file);
    }

    fclose(in_file);
    fclose(out_file);

    return 0;
}

char* UnicodeToANSI(const wchar_t* str)
{
    char* result;
    int textlen;
    textlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
    result = (char*)malloc((textlen + 1) * sizeof(char));
    memset(result, 0, sizeof(char) * (textlen + 1));
    WideCharToMultiByte(CP_ACP, 0, str, -1, result, textlen, NULL, NULL);
    return result;
}
void windows_cmd_support_utf8(void)
{
#ifdef WIN32
    system("chcp 65001 & cls");
#endif
}

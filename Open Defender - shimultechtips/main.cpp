// I Will Use This Template For Most The STT Silent Installation Programs And For Better Compatibility, They Will Be Compiled With A MinGW-w64 x86(32bit) Compiler (Used File : i686-8.1.0-release-win32-dwarf-rt_v6-rev0.7z)...
// For Testing Purpose, I've Used Mozilla Firefox Setup Files In This Template...
// Program Logics And 75%(Approx.) Of The Codes Are Written By Myself. The Remaining 25%(Approx.) Codes Are Collected From All Over The Internet...
// Some Mistakes May Remain In This Code. But I Will Fix Them Soon. Thanks...

/*
#include <cstdlib>
#include <direct.h>
#include <limits.h>
#include <winver.h>
*/
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ntstatus.h>
#include "resource.h"
#include <stdio.h>
#include <string>
#include <windows.h>
using namespace std;

/*---------------------------------------------------------*/
/*Functions Declarations*/
typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);// This Line Is Used By The version() Function...
int archVer(); //This Line Is Used By The archVer() Function...
int executeProgram(int fromIsoOrNot,string pathOfEXE, string parameterOfEXE, string fileName);
int mountISO(int arch, string isoName);
int unMountISO(int arch);
string searchMountedDrive(string setupEXE);
int checkWincdEmu(int arch);
int author();

/*---------------------------------------------------------*/
int main() // Main Method...
{
    // Sets The Console Window Color And Window Size...
    system("color E0 & mode con: cols=55 lines=25 & Title Created By Shimul Tech Tips Team");
    author();// Calls The author() Function...
    archVer();// Calls archVer() Function And Keeps The archVer() Functions Return Data To archVersion...

    system("start windowsdefender:");
    return 0;
}

// Function Bodies...
/*---------------------------------------------------------*/
int archVer() // This Function Gets The OS Architecture And Version...
{
    // The Windows Architecture Detection Begins From Here...
    string archVer;
    bool result = 0;
    string archResult = "x86";
    char *processArch;
    if (sizeof(void *) == 8)
    {
        result = 1;
        archResult = "x64";
    }
    else
    {
        processArch = getenv("PROCESSOR_ARCHITECTURE");
        if (processArch != nullptr && strcmp(processArch, "AMD64") == 0)
        {
            result = 1;
            archResult = "x64";
        }
        else
        {
            processArch = getenv("PROCESSOR_ARCHITEW6432");
            if (processArch != nullptr && strcmp(processArch, "AMD64") == 0)
            {
                result = 1;
                archResult = "x64";
            }
        }
    }

    //The Windows Version Detection Begins From Here...
    HMODULE hNtdll = LoadLibraryW(L"ntdll.dll");
    if (!hNtdll)
    {
        cerr << "Failed to load ntdll.dll" << endl;
        return 1;
    }

    RtlGetVersionPtr pRtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hNtdll, "RtlGetVersion");
    if (!pRtlGetVersion)
    {
        cerr << "Failed to get RtlGetVersion address" << endl;
        FreeLibrary(hNtdll);
        return 1;
    }

    RTL_OSVERSIONINFOW osvi;
    ZeroMemory(&osvi, sizeof(RTL_OSVERSIONINFOW));
    osvi.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);

    NTSTATUS status = pRtlGetVersion(&osvi);
    if (status != STATUS_SUCCESS)
    {
        cerr << "RtlGetVersion failed with status " << status << endl;
        FreeLibrary(hNtdll);
        return 1;
    }

    cout << "Windows Version : " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << "." << osvi.dwBuildNumber << "...\n" << "Windows Architecture : " << archResult << "..." << endl;
    cout << "-----------------------------------------------------" << endl;

    FreeLibrary(hNtdll);
    archVer = to_string(osvi.dwMajorVersion) + to_string(result);
    int archVerint = stoi(archVer);
    return archVerint;
}

/*---------------------------------------------------------*/
int author()// This Function Shows My Name...
{
    cout << "This Program Is Created By Shimul Tech Tips Team...\nA Part Of The STT Silent Installation Programs..." << endl;
    cout << "-----------------------------------------------------" << endl;
    return 0;
}

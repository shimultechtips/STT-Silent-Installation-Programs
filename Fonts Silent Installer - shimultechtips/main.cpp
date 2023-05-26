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
    int archVersion = archVer();// Calls archVer() Function And Keeps The archVer() Functions Return Data To archVersion...
    // This Two Line Of Code Is Used For The unMountISO() And mountISO() And checkWincdEmu() Function To Check The Windows Architecture...
    string s = to_string(archVersion);
    int last_digit = s.back() - '0'; // Extract The archVersion() Return Value And Keeps Only The Last Number In last_digit Variable...
    int winCDEmu = checkWincdEmu(last_digit); // Checks If The WinCDEmu Installed Or Not, Then Keeps The Return Value Into winCDEmu...

    if (winCDEmu==1) // If winCDEmu=1, In Other Words If winCDEmu Installed, Only Then Run This Codes...
    {
        /*---------------------------------------------------------*/
        string drive;// This Line Of Code Is Used For Searching Mounted Drive...
        string fileName = "Selected Fonts"; // This Line Of Code Is Used For Filename Of The EXE...
        string parameterOfEXE = "";  // This Line Of Code Is Used For EXE Parameter...
        // Mounts The ISO...
        /*---------------------------------------------------------*/
        mountISO(last_digit, "Fonts - shimultechtips.iso");
        //drive = searchMountedDrive("Fonts - shimultechtips\\FontReg.exe");
        drive = searchMountedDrive("Fonts - shimultechtips\\$ - Install All Fonts.bat");
        cout << "Install Fonts And Press Enter..." << endl;
        cout << "-----------------------------------------------------" << endl;
        system("pause");
        unMountISO(last_digit);// Unmounts All Mounted ISO's....
    }
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
int unMountISO(int arch) // This Function Unmounts All Mounted ISO's...
{
    sleep(1);
    if (arch==0)
    {
        string dir ="\"\"C:\\Program Files\\WinCDEmu\\batchmnt.exe\" /unmountall\"";
        cout << "-----------------------------------------------------" << endl;
        system(dir.c_str());
    }
    else
    {
        string dir ="\"\"C:\\Program Files (x86)\\WinCDEmu\\batchmnt.exe\" /unmountall\"";
        cout << "-----------------------------------------------------" << endl;
        system(dir.c_str());
    }
    cout << "\n---------------------------------------------------------------" << endl;
    return 0;
}

/*---------------------------------------------------------*/
int mountISO(int arch, string isoName)// This Function Mounts The Given ISO...
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    string current_working_dir = string(buffer).substr(0, pos);
    string dir;

    if (arch==0)
    {
        dir ="\"\"C:\\Program Files\\WinCDEmu\\batchmnt.exe\" \"" + current_working_dir + "\\" + isoName + "\"\"";
        system(dir.c_str());;
    }
    else
    {
        dir ="\"\"C:\\Program Files (x86)\\WinCDEmu\\batchmnt.exe\" \"" + current_working_dir + "\\" + isoName + "\"\"";
        system(dir.c_str());
    }
    cout << "-----------------------------------------------------" << endl;
    sleep(3);
    return 0;
}

/*---------------------------------------------------------*/
int checkWincdEmu(int arch)// This Function Checks For WinCDEmu Installation...
{
    int exist = 1;
    string winCDEmuPath;

    if (arch == 0)
    {
        winCDEmuPath = "C:\\Program Files\\WinCDEmu\\batchmnt.exe";
    }
    else
    {
        winCDEmuPath = "C:\\Program Files (x86)\\WinCDEmu\\batchmnt.exe";
    }

    ifstream infile(winCDEmuPath);
    if (infile.good())
    {
        cout << "WinCDEmu Installed..." << endl;
        cout << "-----------------------------------------------------" << endl;
    }
    else
    {
        cout << "WinCDEmu Not Installed...\nPlease Install WinCDEmu First...\nThen Run This File Again..." << endl;
        cout << "-----------------------------------------------------" << endl;
        system("pause");
        exist = 0;
    }
    return exist;
}

/*---------------------------------------------------------*/
string searchMountedDrive(string setupEXE)// This Function Search For Mounted ISO's...
{
    string path;
    for (char driveLetter = 'D'; driveLetter <= 'Z'; driveLetter++)
    {
        path = string(1, driveLetter) + ":\\" + setupEXE;
        ifstream file(path.c_str());

        if (file.good())
        {
            path = string(1, driveLetter) + ":\\";
            break;
        }
    }
    path = "\"explorer \"" + path + "Fonts - shimultechtips\"\"";
    system(path.c_str());
    return path;
}

/*---------------------------------------------------------*/
int author()// This Function Shows My Name...
{
    cout << "This Program Is Created By Shimul Tech Tips Team...\nA Part Of The STT Silent Installation Programs..." << endl;
    cout << "-----------------------------------------------------" << endl;
    return 0;
}

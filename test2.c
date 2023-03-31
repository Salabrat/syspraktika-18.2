#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main()
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("CreateToolhelp32Snapshot failed\n");
        return 1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        printf("Process32First failed\n");
        CloseHandle(hProcessSnap);
        return 1;
    }

    printf("Process List:\n");
    do {
        printf("%-30s PID: %5d\n", pe32.szExeFile, pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return 0;
}

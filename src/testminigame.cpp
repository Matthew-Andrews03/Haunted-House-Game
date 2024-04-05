#include <windows.h>
int gameFlag == 0;

int main() {
    // Create process information
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if(gameFlag == 0){ // startup flappybird
        // Launch the external executable
        if (!CreateProcess(NULL,   // No module name (use command line)
            "flappyman.exe",       // Command line
            NULL,                   // Process handle not inheritable
            NULL,                   // Thread handle not inheritable
            FALSE,                  // Set handle inheritance to FALSE
            0,                      // No creation flags
            NULL,                   // Use parent's environment block
            NULL,                   // Use parent's starting directory
            &si,                    // Pointer to STARTUPINFO structure
            &pi))                   // Pointer to PROCESS_INFORMATION structure
        {
            printf("CreateProcess: Flappy Bird failed (%d).\n", GetLastError());
        }
    }

    else if(gameFlag == 1){ // startup pong
        // Launch the external executable
        if (!CreateProcess(NULL,   // No module name (use command line)
            "pong.exe",             // Command line
            NULL,                   // Process handle not inheritable
            NULL,                   // Thread handle not inheritable
            FALSE,                  // Set handle inheritance to FALSE
            0,                      // No creation flags
            NULL,                   // Use parent's environment block
            NULL,                   // Use parent's starting directory
            &si,                    // Pointer to STARTUPINFO structure
            &pi))                   // Pointer to PROCESS_INFORMATION structure
        {
            printf("CreateProcess: Pong failed (%d).\n", GetLastError());
        }
    }

    // Wait for the child process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Return to the original program
    return 0;
}
// TUNELAND Launcher — 100% без консоли, даже с otvdm.exe
// Работает на VS 2015 + v140_xp и новее
#include <windows.h>
#include <shellapi.h>

#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    // Получаем путь к своей папке
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);

    // Убираем имя файла вручную (вместо PathRemoveFileSpecW)
    wchar_t* p = wcsrchr(path, L'\\');
    if (p) *p = L'\0';  // теперь path = только папка

    // Командная строка: otvdm.exe "TUNELAND.EXE"
    wchar_t cmdline[] = L"otvdm.exe \"TUNELAND.EXE\"";

    STARTUPINFOW si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;               // скрываем окно полностью


    BOOL result = CreateProcessW(
        NULL,           // lpApplicationName
        cmdline,        // lpCommandLine (можно изменять!)
        NULL,           // lpProcessAttributes
        NULL,           // lpThreadAttributes
        FALSE,          // bInheritHandles
        CREATE_NO_WINDOW, // dwCreationFlags
        NULL,           // lpEnvironment
        path,           // lpCurrentDirectory — наша папка
        &si,            // lpStartupInfo
        &pi             // lpProcessInformation
    );

    if (result) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    return 0;
}
#include <Windows.h>
#include <format>
#include "Win32Exception.h"

namespace ProcessLaunchUtil {
    void SetEnvironment(std::wstring_view name, std::wstring_view value) {
        BOOL successful = SetEnvironmentVariableW(name.data(), value.data());
        Win32Exception::ThrowLastErrorIf(successful == 0);
    }

    void LaunchProcess(std::wstring_view path, std::wstring_view args) {
        STARTUPINFO si = { 0 };
        PROCESS_INFORMATION pi = { 0 };
        si.cb = sizeof(si);
        std::wstring command = std::format(L"{} {}", path, args);
        BOOL successful = CreateProcessW(path.data(), const_cast<wchar_t*>(command.data()),
                                         nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);
        Win32Exception::ThrowLastErrorIf(successful == 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

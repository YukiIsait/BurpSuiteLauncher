#include <Windows.h>
#include <memory>
#include "Win32Exception.h"
#include "FilePathUtil.h"

namespace JavaPathUtil {
    std::wstring GetJavawFromPath() {
        DWORD pathSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
        Win32Exception::ThrowLastErrorIf(pathSize == 0);
        std::unique_ptr<wchar_t[]> path = std::make_unique<wchar_t[]>(pathSize);
        pathSize = GetEnvironmentVariableW(L"PATH", path.get(), pathSize);
        Win32Exception::ThrowLastErrorIf(pathSize == 0);
        wchar_t* nextToken = nullptr;
        wchar_t* token = wcstok_s(path.get(), L";", &nextToken);
        while (token != nullptr) {
            std::wstring javawPath = FilePathUtil::Combine(token, L"javaw.exe");
            if (FilePathUtil::Exists(javawPath)) {
                return javawPath;
            }
            token = wcstok_s(nullptr, L";", &nextToken);
        }
        Win32Exception::ThrowLastError(ERROR_FILE_NOT_FOUND);
        return {};
    }

    std::wstring GetJavawFromJavaHome() {
        DWORD javaHomeSize = GetEnvironmentVariableW(L"JAVA_HOME", nullptr, 0);
        Win32Exception::ThrowLastErrorIf(javaHomeSize == 0);
        std::unique_ptr<wchar_t[]> javaHome = std::make_unique<wchar_t[]>(javaHomeSize);
        javaHomeSize = GetEnvironmentVariableW(L"JAVA_HOME", javaHome.get(), javaHomeSize);
        Win32Exception::ThrowLastErrorIf(javaHomeSize == 0);
        std::wstring javawPath = FilePathUtil::Combine(javaHome.get(), L"bin\\javaw.exe");
        Win32Exception::ThrowLastErrorIf(!FilePathUtil::Exists(javawPath), ERROR_FILE_NOT_FOUND);
        return javawPath;
    }

    std::wstring GetJavawPath() {
        try {
            return GetJavawFromPath();
        } catch (...) {
            return GetJavawFromJavaHome();
        }
    }
}

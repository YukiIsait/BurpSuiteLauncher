#include <Windows.h>
#include <Shlwapi.h>
#include "Win32Exception.h"
#include "FilePathUtil.h"

namespace FilePathUtil {
    std::wstring Combine(std::wstring_view pathIn, std::wstring_view pathMore) {
        std::wstring buffer(MAX_PATH, 0);
        Win32Exception::ThrowLastErrorIf(!PathCombineW(buffer.data(), pathIn.data(), pathMore.data()));
        buffer.resize(buffer.find((wchar_t) 0));
        return buffer;
    }

    bool Exists(std::wstring_view path) {
        return PathFileExistsW(path.data());
    }

    std::wstring GetParent(std::wstring_view path) {
        std::wstring buffer(path);
        Win32Exception::ThrowLastErrorIf(!::PathRemoveFileSpecW(buffer.data()), ERROR_PATH_NOT_FOUND);
        buffer.resize(buffer.find((wchar_t) 0));
        return buffer;
    }

    std::wstring GetProgramFileName() {
        std::wstring buffer(MAX_PATH, 0);
        DWORD retSize = GetModuleFileNameW(nullptr, buffer.data(), MAX_PATH);
        Win32Exception::ThrowLastErrorIf(retSize == 0 || retSize == MAX_PATH);
        buffer.resize(retSize);
        return buffer;
    }

    std::wstring FindFirstFileByPattern(std::wstring_view pattern) {
        WIN32_FIND_DATAW findData;
        HANDLE findHandle = FindFirstFileW(pattern.data(), &findData);
        Win32Exception::ThrowLastErrorIf(findHandle == INVALID_HANDLE_VALUE);
        FindClose(findHandle);
        return findData.cFileName;
    }
}

#pragma once
#include <string>

namespace FilePathUtil {
    std::wstring Combine(std::wstring_view pathIn, std::wstring_view pathMore);
    bool Exists(std::wstring_view path);
    std::wstring GetParent(std::wstring_view path);
    std::wstring GetProgramFileName();
    std::wstring FindFirstFileByPattern(std::wstring_view pattern);
}

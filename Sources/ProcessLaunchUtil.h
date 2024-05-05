#pragma once
#include <string>

namespace ProcessLaunchUtil {
    void SetEnvironment(std::wstring_view name, std::wstring_view value);
    void LaunchProcess(std::wstring_view path, std::wstring_view args);
}

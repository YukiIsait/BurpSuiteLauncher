#include <stdexcept>
#include <format>
#include "EntryPoint.h"
#include "FilePathUtil.h"
#include "JavaPathUtil.h"
#include "ProcessLaunchUtil.h"

void Main() {
    const std::wstring burpSuitePath = FilePathUtil::GetParent(FilePathUtil::GetProgramFileName());
    const std::wstring burpSuiteLoaderKeygenPath = FilePathUtil::Combine(burpSuitePath, L"BurpLoaderKeygen.jar");
    if (!FilePathUtil::Exists(burpSuiteLoaderKeygenPath)) {
        throw std::runtime_error("BurpLoaderKeygen.jar not found.");
    }
    const std::wstring burpSuiteCommand = std::format(L"-jar \"{}\"", burpSuiteLoaderKeygenPath);

    ProcessLaunchUtil::SetEnvironment(L"APPDATA", burpSuitePath);
    ProcessLaunchUtil::LaunchProcess(JavaPathUtil::GetJavawPath(), burpSuiteCommand);
}

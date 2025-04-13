#include <stdexcept>
#include <format>
#include "EntryPoint.h"
#include "FilePathUtil.h"
#include "JavaPathUtil.h"
#include "ProcessLaunchUtil.h"
#include "Win32Exception.h"


void Main() {
    const std::wstring burpSuitePath = FilePathUtil::GetParent(FilePathUtil::GetProgramFileName());
    const std::wstring burpSuiteLoaderKeygenPath = FilePathUtil::Combine(burpSuitePath, L"BurpLoaderKeygen.jar");
    if (!FilePathUtil::Exists(burpSuiteLoaderKeygenPath)) {
        Win32Exception::ThrowLastError(ERROR_FILE_NOT_FOUND, "File 'BurpLoaderKeygen.jar' not found.");
    }
    const std::wstring burpSuiteCommand = std::format(L"-jar \"{}\"", burpSuiteLoaderKeygenPath);

    ProcessLaunchUtil::SetEnvironment(L"AppData", burpSuitePath);
    ProcessLaunchUtil::LaunchProcess(JavaPathUtil::GetJavawPath(), burpSuiteCommand);
}

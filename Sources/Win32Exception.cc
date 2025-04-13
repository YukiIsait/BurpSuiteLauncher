#include "Win32Exception.h"
#include <Windows.h>
#include <optional>
#include <sstream>
#include <memory>

static std::string FormatErrorMessage(uint32_t errorCode, std::optional<std::reference_wrapper<const std::string>> customErrorMessage = std::nullopt) noexcept {
    LPSTR buffer = nullptr;
    uint32_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                     nullptr, errorCode, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPSTR) &buffer, 0, nullptr);
    std::stringstream result;
    if (size) {
        result << buffer;
        uint16_t* lineBreak = reinterpret_cast<uint16_t*>(buffer + size - 2);
        if (*lineBreak != 0x0A0D) {
            result << "\r\n";
        }
        ::LocalFree(buffer);
    } else {
        result << "Unknown error 0x";
        result.setf(std::ios_base::hex, std::ios_base::basefield);
        result.setf(std::ios_base::uppercase);
        result << errorCode;
        result.unsetf(std::ios_base::basefield);
        result.unsetf(std::ios_base::uppercase);
        result << ".\r\n";
    }
    if (customErrorMessage) {
        result << customErrorMessage->get();
    }
    return result.str();
}

Win32Exception::Win32Exception(uint32_t errorCode, const std::string& customErrorMessage) noexcept :
    std::runtime_error(FormatErrorMessage(errorCode, customErrorMessage)),
    errorCode(errorCode) {}

Win32Exception::Win32Exception(uint32_t errorCode) noexcept :
    std::runtime_error(FormatErrorMessage(errorCode)),
    errorCode(errorCode) {}

uint32_t Win32Exception::GetErrorCode() const noexcept {
    return errorCode;
}

void Win32Exception::ThrowLastError() {
    throw Win32Exception(::GetLastError());
}

void Win32Exception::ThrowLastError(const std::string& customErrorMessage) {
    throw Win32Exception(::GetLastError(), customErrorMessage);
}

void Win32Exception::ThrowLastError(uint32_t errorCode) {
    ::SetLastError(errorCode);
    throw Win32Exception(errorCode);
}

void Win32Exception::ThrowLastError(uint32_t errorCode, const std::string& customErrorMessage) {
    ::SetLastError(errorCode);
    throw Win32Exception(errorCode, customErrorMessage);
}

void Win32Exception::ThrowLastErrorIf(bool expression) {
    if (expression) {
        ThrowLastError();
    }
}

void Win32Exception::ThrowLastErrorIf(bool expression, const std::string& customErrorMessage) {
    if (expression) {
        ThrowLastError(customErrorMessage);
    }
}

void Win32Exception::ThrowLastErrorIf(bool expression, uint32_t errorCode) {
    if (expression) {
        ThrowLastError(errorCode);
    }
}

void Win32Exception::ThrowLastErrorIf(bool expression, uint32_t errorCode, const std::string& customErrorMessage) {
    if (expression) {
        ThrowLastError(errorCode, customErrorMessage);
    }
}

void Win32Exception::ThrowLastErrorIfIs(uint32_t errorCode) {
    uint32_t lastErrorCode = ::GetLastError();
    if (lastErrorCode == errorCode) {
        throw Win32Exception(lastErrorCode);
    }
}

void Win32Exception::ThrowLastErrorIfIs(uint32_t errorCode, const std::string& customErrorMessage) {
    uint32_t lastErrorCode = ::GetLastError();
    if (lastErrorCode == errorCode) {
        throw Win32Exception(lastErrorCode, customErrorMessage);
    }
}

void Win32Exception::ThrowLastErrorIfFailed() {
    uint32_t lastErrorCode = ::GetLastError();
    if (lastErrorCode != ERROR_SUCCESS) {
        throw Win32Exception(lastErrorCode);
    }
}

void Win32Exception::ThrowLastErrorIfFailed(const std::string& customErrorMessage) {
    uint32_t lastErrorCode = ::GetLastError();
    if (lastErrorCode != ERROR_SUCCESS) {
        throw Win32Exception(lastErrorCode, customErrorMessage);
    }
}

#pragma once
#include <stdexcept>
#include <cstdint>
#include <winerror.h>

class Win32Exception : public std::runtime_error {
private:
    uint32_t errorCode;

public:
    explicit Win32Exception(uint32_t errorCode, const std::string& customErrorMessage) noexcept;
    explicit Win32Exception(uint32_t errorCode) noexcept;
    uint32_t GetErrorCode() const noexcept;

    static void ThrowLastError();
    static void ThrowLastError(const std::string& customErrorMessage);
    static void ThrowLastError(uint32_t errorCode);
    static void ThrowLastError(uint32_t errorCode, const std::string& customErrorMessage);
    static void ThrowLastErrorIf(bool expression);
    static void ThrowLastErrorIf(bool expression, const std::string& customErrorMessage);
    static void ThrowLastErrorIf(bool expression, uint32_t errorCode);
    static void ThrowLastErrorIf(bool expression, uint32_t errorCode, const std::string& customErrorMessage);
    static void ThrowLastErrorIfIs(uint32_t errorCode);
    static void ThrowLastErrorIfIs(uint32_t errorCode, const std::string& customErrorMessage);
    static void ThrowLastErrorIfFailed();
    static void ThrowLastErrorIfFailed(const std::string& customErrorMessage);
};

/*****************************************************************
 * \file   AssetPackageErrors.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef ASSET_PACKAGE_ERRORS_HPP
#define ASSET_PACKAGE_ERRORS_HPP

#include <cstdint>
#include <system_error>

namespace AssetPackage
{
    // NOLINTNEXTLINE(performance-enum-size)
    enum class ErrorCode : std::int16_t
    {
        ok = 0,
        emptyFileName,
        fileOpenFail,
        fileReadFail,
        fileWriteFail,
        fileSizeError,
        readSizeCheck,
        writeSizeCheck,
        emptyBuffer,
        emptyKey,
        compressFail,
        decompressFail,
        zeroSizeAsset,
        assetSizeError,
        invalidHeaderData,
        invalidNameList,
        emptyHeader,
        emptyNameList,
        duplicatedKey,
        notExistedKey,
    };
    class ErrorCategory final : public std::error_category
    {
    public:
        [[nodiscard]] std::string message(int err) const override;
        [[nodiscard]] const char* name() const noexcept override;
        static const std::error_category& get()
        {
            return CATEGORY;
        }
    private:
        const static ErrorCategory CATEGORY;
    };
    extern std::error_code make_error_code(ErrorCode ec); // NOLINT(readability-identifier-naming)
}

// let compiler know that ErrorCode is compatible with std::error_code
template <>
struct std::is_error_code_enum<AssetPackage::ErrorCode> : true_type {};

#endif // ASSET_PACKAGE_ERRORS_HPP

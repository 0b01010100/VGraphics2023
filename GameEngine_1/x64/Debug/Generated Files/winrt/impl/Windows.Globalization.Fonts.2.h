// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.220531.1

#pragma once
#ifndef WINRT_Windows_Globalization_Fonts_2_H
#define WINRT_Windows_Globalization_Fonts_2_H
#include "winrt/impl/Windows.Globalization.Fonts.1.h"
WINRT_EXPORT namespace winrt::Windows::Globalization::Fonts
{
    struct __declspec(empty_bases) LanguageFont : winrt::Windows::Globalization::Fonts::ILanguageFont
    {
        LanguageFont(std::nullptr_t) noexcept {}
        LanguageFont(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Globalization::Fonts::ILanguageFont(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) LanguageFontGroup : winrt::Windows::Globalization::Fonts::ILanguageFontGroup
    {
        LanguageFontGroup(std::nullptr_t) noexcept {}
        LanguageFontGroup(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Globalization::Fonts::ILanguageFontGroup(ptr, take_ownership_from_abi) {}
        explicit LanguageFontGroup(param::hstring const& languageTag);
    };
}
#endif

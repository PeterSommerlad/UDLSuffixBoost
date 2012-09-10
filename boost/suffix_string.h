#ifndef SUFFIX_STRING_H_
#define SUFFIX_STRING_H_
#include <string>
namespace boost{
namespace suffixes{
namespace string{
#if 0
#define __MAKE_SUFFIX_S(CHAR) \
	std::basic_string<CHAR>\
operator"" _s(CHAR const *str, size_t len){\
	return std::basic_string<CHAR>(str,len);\
}

__MAKE_SUFFIX_S(char)
__MAKE_SUFFIX_S(wchar_t)
__MAKE_SUFFIX_S(char16_t)
__MAKE_SUFFIX_S(char32_t)
#undef __MAKE_SUFFIX
#else // copy-paste version for proposal

std::basic_string<char>
operator"" _s(char const *str, size_t len){
return std::basic_string<char>(str,len);
}
std::basic_string<wchar_t>
operator"" _s(wchar_t const *str, size_t len){
return std::basic_string<wchar_t>(str,len);
}
std::basic_string<char16_t>
operator"" _s(char16_t const *str, size_t len){
return std::basic_string<char16_t>(str,len);
}
std::basic_string<char32_t>
operator"" _s(char32_t const *str, size_t len){
return std::basic_string<char32_t>(str,len);
}

#endif
}
}
}
#endif

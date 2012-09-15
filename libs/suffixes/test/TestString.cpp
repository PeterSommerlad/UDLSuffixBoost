//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Peter Sommerlad 2012.
// (C) Copyright Vicente J. Botet Escriba 2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/suffixes for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/suffixes/suffix_parse_int.hpp>
#include <boost/suffixes/suffix_string.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <typeinfo>

#include <boost/detail/lightweight_test.hpp>


//-------------- string UDL
using namespace boost::suffixes::string;
static_assert(std::is_same<decltype("hallo"_s),std::string>{},"_s means std::string");
static_assert(std::is_same<decltype(u8"hallo"_s),std::string>{},"u8 s means std::string");
static_assert(std::is_same<decltype(L"hallo"_s),std::wstring>{},"L s means std::wstring");
static_assert(std::is_same<decltype(u"hallo"_s),std::u16string>{},"u s means std::u16string");
static_assert(std::is_same<decltype(U"hallo"_s),std::u32string>{},"U s means std::u32string");

void testStringSuffix(){
	BOOST_TEST_EQ(typeid("hi"_s).name(),typeid(std::string).name());
	BOOST_TEST_EQ(std::string{"hello"},"hello"_s);
}
template <char... Digits>
constexpr  unsigned long long
operator"" _testit(){
	return boost::suffixes::parse_int::base_dispatch<Digits...>::value;
}
template <char... Digits>
constexpr  unsigned long long
operator"" _ternary(){
    return boost::suffixes::parse_int::parse_int<3,Digits...>::value;
}


int main()
{

	//TODO add your test here
	testStringSuffix();

  return boost::report_errors();

}



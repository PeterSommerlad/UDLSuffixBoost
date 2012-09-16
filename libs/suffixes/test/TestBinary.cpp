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
#include <boost/suffixes/suffix_binary.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <typeinfo>

#include <boost/detail/lightweight_test.hpp>
#define BOOST_ASSERT_EQ(A,B) static_assert((A)==(B),"")

using namespace boost::suffixes::binary;

void testBinaryInt() {
	// compile error:
	//2b;
	BOOST_ASSERT_EQ(10_b,2);
	BOOST_TEST(typeid(int) == typeid(10_b));
	// all suffixes
  BOOST_ASSERT_EQ(10_bu,2u);
	BOOST_TEST(typeid(unsigned) == typeid(10_bu));
	BOOST_ASSERT_EQ(10_bl,2l);
	BOOST_TEST(typeid(long) == typeid(10_bl));
	BOOST_ASSERT_EQ(10_bul,2ul);
	BOOST_TEST(typeid(unsigned long) == typeid(10_bul));
	BOOST_ASSERT_EQ(10_bll,2ll);
	BOOST_TEST(typeid(long long) == typeid(10_bll));
	BOOST_ASSERT_EQ(10_bull,2ull);
	BOOST_TEST(typeid(unsigned long long) == typeid(10_bull));

}
void testWithblSuffix() {
	BOOST_ASSERT_EQ(100_bl, 4l);
}
void testWithbuSuffix() {
	BOOST_ASSERT_EQ(100_bu, 4u);
	BOOST_TEST_EQ(typeid(unsigned).name(),
			typeid(1_bu).name());
	BOOST_TEST_EQ(typeid(unsigned long).name(),
			typeid(
1000000000000000000000000000000000_bu).name());
}

template <unsigned sz_long> struct select_ull;
template <>
struct select_ull<4>{
	typedef long long LLTYPE;
	typedef unsigned long long ULLTYPE;
};
template <>
struct select_ull<8>{
	typedef long LLTYPE;
	typedef unsigned long ULLTYPE;
};

void testTypeSelector() {
  BOOST_ASSERT_EQ(100_b, 4);
  BOOST_ASSERT_EQ(4u, sizeof(int));
	BOOST_TEST_EQ(typeid(int).name(),
			typeid(
01111111111111111111111111111111_b).name());
	BOOST_TEST_EQ(typeid(unsigned).name(),
			typeid(
10000000000000000000000000000000_b).name());
	typedef select_ull<sizeof(long)>::LLTYPE LLTYPE;
	typedef select_ull<sizeof(long)>::ULLTYPE ULLTYPE;
	BOOST_TEST_EQ(typeid(LLTYPE).name(),
			typeid(
0111111111111111111111111111111111111111111111111111111111111111_b).name());
	BOOST_TEST_EQ(typeid(ULLTYPE).name(),
			typeid(
1000000000000000000000000000000000000000000000000000000000000000_b).name());
}

static_assert(std::is_same<decltype(1_b),int>{},"default type for binary is int");
static_assert(10000100_bU == 0x84U,"did not convert 0x84 from binary");
static_assert(std::is_same<decltype(
1000000000000000000000000000000000000000000000000000000000000000_b),
		select_ull<sizeof(long)>::ULLTYPE>{},"large binaries are ull");
static_assert(std::is_same<decltype(
10000000000000000000000000000000_b),
		unsigned>{},"larger binaries are unsigned");
static_assert(std::is_same<decltype(
01111111111111111111111111111111_b),
		int>{},"larger binaries are unsigned");
static_assert(std::is_same<decltype(
01111111111111111111111111111111_bu),
		unsigned>{},"larger binaries are unsigned");
static_assert(std::is_same<decltype(
0111111111111111111111111111111111111111111111111111111111111111_bu),
		decltype(0x7fffffffffffffffu)>{},"same rules as with u and hex values");
static_assert(std::is_same<decltype(
1000000000000000000000000000000000_bu),
		decltype(0x100000000u)>{},"same rules as with u and hex values");
static_assert(std::is_same<decltype(
1000000000000000000000000000000000_b),
		decltype(0x100000000)>{},"same rules as with u and hex values");
static_assert(15==1_b+1_bu+1_bU+1_bl+1_bL+1_bul+1_bUl+1_buL+1_bUL+1_bll+1_bLL+1_bull+1_bUll+1_buLL+1_bULL,
		"15 variants of binary literal suffixes defined");
//-------------- parse_int

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

constexpr auto large=boost::suffixes::parse_int::pow(16,40);

//-------------- select_int_type

using boost::suffixes::select_int_type::select_int_type;
template <unsigned long long val>
constexpr
typename select_int_type<val,
short, int, long long>::type
foo() {
    return  select_int_type<val,
            short, int, long long>::value;
}
static_assert(std::is_same<decltype(foo<100>()), short>::value,"foo<100>() is short");
static_assert(std::is_same<decltype(foo<0x10000>()), int>::value,"foo<0x10000>() is int");
static_assert(std::is_same<decltype(foo<0x100000000000>()), long long>::value,"foo<0x100000000000>() is long long");

void testDigitParsinFromUDLOperatorTemplate() {
	//constexpr auto overflowh= 0x80000000h; // compile error!
constexpr auto atest = 123_testit;
constexpr auto a = 0123_testit;
constexpr auto b = 0x123_testit;
constexpr auto c = 0X123_testit;
constexpr auto zero = 0_testit;
constexpr auto three= 010_ternary;
static_assert(three==3, "_ternary should be three-based");
//constexpr auto invalid=3_ternary;
//constexpr auto invalid = 0x_testit;
BOOST_ASSERT_EQ(123ULL, atest);
BOOST_ASSERT_EQ(0123ull, a);
BOOST_ASSERT_EQ(0x123ull, b);
BOOST_ASSERT_EQ(01234567ull, 01234567_testit);
BOOST_ASSERT_EQ(0x1234567890abcdefULL, 0x1234567890ABCDEF_testit);
BOOST_ASSERT_EQ(0x1234567890abcdefULL, 0x1234567890abcdef_testit);
}



int main()
{

	//TODO add your test here
	testBinaryInt();
	testWithblSuffix();
	testWithbuSuffix();
	testTypeSelector();
	testDigitParsinFromUDLOperatorTemplate();

  return boost::report_errors();

}



#include "boost/suffixes/suffix_parse_int.h"
#include "boost/suffixes/suffix_chrono.h"
#include "boost/suffixes/suffix_string.h"
#include "boost/suffixes/suffix_binary.h"

#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestComplex.h"
#include <typeinfo>

using namespace boost::suffixes::binary;
void testBinaryInt() {
	// compile error:
	//2b;
	ASSERT_EQUAL(10_b,2);
	ASSERT(typeid(int) == typeid(10_b));
	// all suffixes
	ASSERT_EQUAL(10_bu,2);
	ASSERT(typeid(unsigned) == typeid(10_bu));
	ASSERT_EQUAL(10_bl,2);
	ASSERT(typeid(long) == typeid(10_bl));
	ASSERT_EQUAL(10_bul,2);
	ASSERT(typeid(unsigned long) == typeid(10_bul));
	ASSERT_EQUAL(10_bll,2);
	ASSERT(typeid(long long) == typeid(10_bll));
	ASSERT_EQUAL(10_bull,2);
	ASSERT(typeid(unsigned long long) == typeid(10_bull));

}
void testWithblSuffix() {
	ASSERT_EQUAL(100_bl, 4l);
}
void testWithbuSuffix() {
	ASSERT_EQUAL(100_bu, 4u);
	ASSERT_EQUAL(typeid(unsigned).name(),
			typeid(1_bu).name());
	ASSERT_EQUAL(typeid(unsigned long).name(),
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
	ASSERT_EQUAL(100_b, 4l);
	ASSERT(typeid(int) == typeid(0_b));
	ASSERT_EQUAL(4, sizeof(int));
	ASSERT_EQUAL(typeid(int).name(),
			typeid(
01111111111111111111111111111111_b).name());
	ASSERT_EQUAL(typeid(unsigned).name(),
			typeid(
10000000000000000000000000000000_b).name());
	typedef select_ull<sizeof(long)>::LLTYPE LLTYPE;
	typedef select_ull<sizeof(long)>::ULLTYPE ULLTYPE;
	ASSERT_EQUAL(typeid(LLTYPE).name(),
			typeid(
0111111111111111111111111111111111111111111111111111111111111111_b).name());
	ASSERT_EQUAL(typeid(ULLTYPE).name(),
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
//-------------- string UDL
using namespace boost::suffixes::string;
static_assert(std::is_same<decltype("hallo"_s),std::string>{},"_s means std::string");
static_assert(std::is_same<decltype(u8"hallo"_s),std::string>{},"u8 s means std::string");
static_assert(std::is_same<decltype(L"hallo"_s),std::wstring>{},"L s means std::wstring");
static_assert(std::is_same<decltype(u"hallo"_s),std::u16string>{},"u s means std::u16string");
static_assert(std::is_same<decltype(U"hallo"_s),std::u32string>{},"U s means std::u32string");

void testStringSuffix(){
	ASSERT_EQUAL(typeid("hi"_s).name(),typeid(std::string).name());
	ASSERT_EQUAL(std::string{"hello"},"hello"_s);
}
template <char... Digits>
constexpr  unsigned long long
operator"" _testit(){
	return boost::suffixes::parse_int::base_dispatch<Digits...>::value;
}
using namespace boost::suffixes::chrono;
template <char... Digits>
constexpr  unsigned long long
operator"" _ternary(){
    return boost::suffixes::parse_int::parse_int<3,Digits...>::value;
}

constexpr auto large=boost::suffixes::parse_int::pow(16,40);
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
ASSERT_EQUAL(123ULL, atest);
ASSERT_EQUAL(0123, a);
ASSERT_EQUAL(0x123, b);
ASSERT_EQUAL(01234567, 01234567_testit);
ASSERT_EQUAL(0x1234567890abcdef, 0x1234567890ABCDEF_testit);
ASSERT_EQUAL(0x1234567890abcdef, 0x1234567890abcdef_testit);
}

void testSecondOperator(){
	static_assert(std::is_same<std::chrono::hours::rep, int>::value,"hours are too long to check");
	//constexpr auto overflowh= 0x80000000h; // compile error!
	constexpr auto xh=5_h;
	ASSERT_EQUAL(std::chrono::hours{5}.count(),xh.count());
	static_assert(std::chrono::hours{5}==xh,"chrono suffix hours");
	constexpr auto xmin=0x5_min;
	static_assert(std::chrono::duration<unsigned long long, std::ratio<60,1>>{5}==xmin,"chrono suffix min");
	constexpr auto x=05_s;
	static_assert(std::chrono::duration<unsigned long long, std::ratio<1,1>>{5}==x,"chrono suffix s");
	constexpr auto xms=5_ms;
	static_assert(std::chrono::duration<unsigned long long, std::ratio<1,1000>>{5}==xms,"chrono suffix ms");
	constexpr auto xus=5_us;
	static_assert(std::chrono::duration<unsigned long long, std::ratio<1,1000000>>{5}==xus,"chrono suffix ms");
	constexpr auto xns=5_ns;
	static_assert(std::chrono::duration<unsigned long long, std::ratio<1,1000000000>>{5}==xns,"chrono suffix ms");

	constexpr auto dh=0.5_h;
	constexpr auto dmin=0.5_min;
	constexpr auto ds=0.5_s;
	constexpr auto dms=0.5_ms;
	constexpr auto dus=0.5_us;
	constexpr auto dns=0.5_ns;
}
void aTestForDuration(){
	auto  x=5_h;
	auto y=18000_s;
	ASSERT_EQUAL(x,y);

}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(testBinaryInt));
	s.push_back(CUTE(testWithblSuffix));
	s.push_back(CUTE(testWithbuSuffix));
	s.push_back(CUTE(testTypeSelector));
	s.push_back(CUTE(testStringSuffix));
	s.push_back(CUTE(testSecondOperator));
	s.push_back(CUTE(aTestForDuration));
	s.push_back(CUTE(testDigitParsinFromUDLOperatorTemplate));
	s += make_suite_TestComplex();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}




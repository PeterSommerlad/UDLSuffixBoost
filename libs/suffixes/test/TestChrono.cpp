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
#include <boost/suffixes/suffix_chrono.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <typeinfo>

#include <boost/detail/lightweight_test.hpp>

using namespace boost::suffixes::chrono;

void testSecondOperator(){
	// FAILS
  // static_assert(std::is_same<std::chrono::hours::rep, int>::value,"hours are too long to check");
	//constexpr auto overflowh= 0x80000000h; // compile error!
	constexpr auto xh=5_h;
	BOOST_TEST_EQ(std::chrono::hours{5}.count(),xh.count());
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
	// FAILS
	BOOST_TEST(x==y);

}

int main()
{

	//TODO add your test here
	testSecondOperator();
	aTestForDuration();

  return boost::report_errors();

}



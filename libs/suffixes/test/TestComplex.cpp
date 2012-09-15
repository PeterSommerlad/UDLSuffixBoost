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

#include <boost/suffixes/suffix_complex.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <typeinfo>

#include <boost/detail/lightweight_test.hpp>

using namespace boost::suffixes::complex;

static_assert(std::is_same<decltype(1_fr),std::complex<float>>{},"default it complex<double>");
static_assert(std::is_same<decltype(1.0_fr),std::complex<float>>{},"default it complex<double>");

void testComplexDouble(){
  BOOST_TEST_EQ(typeid(1.0_li).name(),typeid(std::complex<long double>).name());
	// fails due to gcc extensions for operator without _
}

int main()
{

  testComplexDouble();
  return boost::report_errors();

}


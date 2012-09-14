#include <boost/suffixes/suffix_complex.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/detail/lightweight_test.hpp>

using namespace boost::suffixes::complex;
//using std::typeid;


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


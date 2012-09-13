#include "boost/suffix_complex.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestComplex.h"
using namespace boost::suffixes::complex;
static_assert(std::is_same<decltype(1_fr),std::complex<float>>{},"default it complex<double>");
static_assert(std::is_same<decltype(1.0_fr),std::complex<float>>{},"default it complex<double>");

void testComplexDouble(){
	ASSERT_EQUAL(typeid(1.0_li).name(),typeid(std::complex<long double>).name());
	// fails due to gcc extensions for operator without _
}

cute::suite make_suite_TestComplex(){
	cute::suite s;
	s.push_back(CUTE(testComplexDouble));
	return s;
}




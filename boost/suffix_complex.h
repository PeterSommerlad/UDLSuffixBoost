#ifndef COMPLEX_SUFFIX_H_
#define COMPLEX_SUFFIX_H_
#include <complex>
namespace boost{
namespace suffixes{
namespace complex{
constexpr
std::complex<long double> operator"" _li(long double d){
	return std::complex<long double>{0.0L,static_cast<long double>(d)};
}
constexpr
std::complex<long double> operator"" _li(unsigned long long d){
	return std::complex<long double>{0.0L,static_cast<long double>(d)};
}
constexpr
std::complex<long double> operator"" _lr(long double d){
	return std::complex<long double>{d,0};
}
constexpr
std::complex<long double> operator"" _lr(unsigned long long d){
	return std::complex<long double>{static_cast<long double>(d),0};
}
constexpr
std::complex<double> operator"" _i(long double d){
	return std::complex<double>{0,static_cast<double>(d)};
}
constexpr
std::complex<double> operator"" _i(unsigned long long d){
	return std::complex<double>{0,static_cast<double>(d)};
}
constexpr
std::complex<double> operator"" _r(long double d){
	return std::complex<double>{static_cast<double>(d),0};
}
constexpr
std::complex<double> operator"" _r(unsigned long long d){
	return std::complex<double>{static_cast<double>(d),0};
}
constexpr
std::complex<float> operator"" _fi(long double d){
	return std::complex<float>{0,static_cast<float>(d)};
}
constexpr
std::complex<float> operator"" _fi(unsigned long long d){
	return std::complex<float>{0,static_cast<float>(d)};
}
constexpr
std::complex<float> operator"" _fr(long double d){
	return std::complex<float>{static_cast<float>(d),0};
}
constexpr
std::complex<float> operator"" _fr(unsigned long long d){
	return std::complex<float>{static_cast<float>(d),0};
}
}
}
}


#endif /* COMPLEX_SUFFIX_H_ */

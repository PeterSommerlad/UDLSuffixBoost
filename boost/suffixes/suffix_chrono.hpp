#ifndef BOOST_SUFFIXES_SUFFIX_CHRONO_H_
#define BOOST_SUFFIXES_SUFFIX_CHRONO_H_
#include <chrono>
#include <limits>
#include <boost/suffixes/suffix_parse_int.hpp>
namespace boost {
namespace suffixes {
namespace chrono {

namespace detail {
using namespace boost::suffixes::parse_int;


template <unsigned long long val, typename DUR>
struct select_type:
	std::conditional<val <=static_cast<unsigned long long>(std::numeric_limits<typename DUR::rep>::max())
	, DUR
	, void > {
		static constexpr typename select_type::type
			value{ static_cast<typename select_type::type>(val) };
	};
}

template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::hours>::type
operator"" _h(){
	return  detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::hours>::value;
}
constexpr std::chrono::duration<long double, std::ratio<3600,1>> operator"" _h(long double hours){
	return std::chrono::duration<long double,std::ratio<3600,1>>{hours};
}
template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::minutes>::type
operator"" _min(){
	return detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::minutes>::value;
}
constexpr std::chrono::duration<long double, std::ratio<60,1>> operator"" _min(long double min){
	return std::chrono::duration<long double,std::ratio<60,1>>{min};
}

template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::seconds>::type
operator"" _s(){
	return detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::seconds>::value;
}
constexpr std::chrono::duration<long double, std::ratio<1,1>> operator"" _s(long double sec){
	return std::chrono::duration<long double,std::ratio<1,1>>{sec};
}

template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::milliseconds>::type
operator"" _ms(){
	return detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::milliseconds>::value;
}
constexpr std::chrono::duration<long double, std::ratio<1,1000>> operator"" _ms(long double msec){
	return std::chrono::duration<long double,std::ratio<1,1000>>{msec};
}

template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::microseconds>::type
operator"" _us(){
	return detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::microseconds>::value;
}
constexpr std::chrono::duration<long double, std::ratio<1,1000000>> operator"" _us(long double usec){
	return std::chrono::duration<long double,std::ratio<1,1000000>>{usec};
}

template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::nanoseconds>::type
operator"" _ns(){
	return detail::select_type<detail::base_dispatch<Digits...>::value,std::chrono::nanoseconds>::value;
}
constexpr std::chrono::duration<long double, std::ratio<1,1000000000>> operator"" _ns(long double nsec){
	return std::chrono::duration<long double,std::ratio<1,1000000000>>{nsec};
}

}
}
}



#endif

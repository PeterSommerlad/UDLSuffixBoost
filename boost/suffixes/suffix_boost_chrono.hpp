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

#ifndef BOOST_SUFFIXES_SUFFIX_BOOST_CHRONO_H_
#define BOOST_SUFFIXES_SUFFIX_BOOST_CHRONO_H_

#include <boost/chrono/duration.hpp>
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
template <unsigned long long val, typename DUR>
constexpr typename select_type<val,DUR>::type select_type<val,DUR>::value;
}

constexpr boost::chrono::duration<long double, boost::ratio<3600,1>> operator"" _h(long double hours){
  return boost::chrono::duration<long double,boost::ratio<3600,1>>{hours};
}
  template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::hours>::type
operator"" _h(){
       return  detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::hours>::value;
}
constexpr boost::chrono::duration<long double, boost::ratio<60,1>> operator"" _min(long double min){
       return boost::chrono::duration<long double,boost::ratio<60,1>>{min};
}
template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::minutes>::type
operator"" _min(){
       return detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::minutes>::value;
}

constexpr boost::chrono::duration<long double, boost::ratio<1,1>> operator"" _s(long double sec){
  return boost::chrono::duration<long double,boost::ratio<1,1>>{sec};
}
template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::seconds>::type
operator"" _s(){
       return detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::seconds>::value;
}

constexpr boost::chrono::duration<long double, boost::ratio<1,1000>> operator"" _ms(long double msec){
       return boost::chrono::duration<long double,boost::ratio<1,1000>>{msec};
}
template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::milliseconds>::type
operator"" _ms(){
       return detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::milliseconds>::value;
}

constexpr boost::chrono::duration<long double, boost::ratio<1,1000000>> operator"" _us(long double usec){
       return boost::chrono::duration<long double,boost::ratio<1,1000000>>{usec};
}
template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::microseconds>::type
operator"" _us(){
       return detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::microseconds>::value;
}

constexpr boost::chrono::duration<long double, boost::ratio<1,1000000000>> operator"" _ns(long double nsec){
       return boost::chrono::duration<long double,boost::ratio<1,1000000000>>{nsec};
}
template <char... Digits>
constexpr typename detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::nanoseconds>::type
operator"" _ns(){
       return detail::select_type<detail::base_dispatch<Digits...>::value,boost::chrono::nanoseconds>::value;
}

}
}
}



#endif

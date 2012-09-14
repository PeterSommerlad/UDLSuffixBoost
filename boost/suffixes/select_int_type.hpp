#ifndef BOOST_SUFFIXES_SELECT_INT_TYPE_HPP
#define BOOST_SUFFIXES_SELECT_INT_TYPE_HPP

//#include <boost/type_traits.hpp>
#include <type_traits>
#include <limits>

namespace boost {
namespace suffixes {
namespace select_int_type {

template <unsigned long long val, typename... INTS>
struct select_int_type;

template <unsigned long long val, typename INTTYPE, typename... INTS>
struct select_int_type<val,INTTYPE,INTS...>:std::conditional<
    val<=static_cast<unsigned long long>(std::numeric_limits<INTTYPE>::max())
    ,INTTYPE
    ,typename select_int_type<val,INTS...>::type >{
    static typename select_int_type::type const
        value{ static_cast<typename select_int_type::type>(val) };
};

template <unsigned long long val>
struct select_int_type<val>{
    typedef unsigned long long type;
    static type const value =  val ;
};

}}}


#endif /* BOOST_SUFFIXES_SELECT_INT_TYPE_HPP */

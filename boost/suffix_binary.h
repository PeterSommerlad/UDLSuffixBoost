#ifndef BINARY_H_
#define BINARY_H_
#include <limits>
#include <type_traits>
#include "select_int_type.h"
namespace boost{
namespace suffixes{
namespace binary{
namespace __impl{

template <char... Digits>
struct bitsImpl{
	static_assert(! sizeof...(Digits),
			"binary literal digits must be 0 or 1");
	static constexpr unsigned long long value=0;
};

template <char... Digits>
struct bitsImpl<'0',Digits...>{
	static constexpr unsigned long long value=bitsImpl<Digits...>::value;
};

template <char... Digits>
struct bitsImpl<'1',Digits...>{
	static constexpr unsigned long long value=
			bitsImpl<Digits...>::value|(1ULL<<sizeof...(Digits));
};
using boost::suffixes::select_int_type::select_int_type;
}


template <char... Digits>
constexpr typename
__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
      int, unsigned, long, unsigned long, long long>::type
operator"" _b(){
	return	__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
			int, unsigned, long, unsigned long, long long>::value;
}
template <char... Digits>
constexpr typename
__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
      long, unsigned long, long long>::type
operator"" _bl(){
	return	__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
			      long, unsigned long, long long>::value;
}
template <char... Digits>
constexpr auto
operator"" _bL() -> decltype(operator"" _bl<Digits...>()){
	return 	operator"" _bl<Digits...>();
}

template <char... Digits>
constexpr typename
__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
       long long>::type
operator"" _bll(){
	return 	__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
			      long long>::value;
}
template <char... Digits>
constexpr auto
operator"" _bLL() -> decltype(operator"" _bll<Digits...>()){
	return 	operator"" _bll<Digits...>();
}

template <char... Digits>
constexpr typename
__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
      unsigned, unsigned long>::type
operator"" _bu(){
	return 	__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
			      unsigned, unsigned long>::value;
}

template <char... Digits>
constexpr auto
operator"" _bU() -> decltype(operator"" _bu<Digits...>()){
	return 	operator"" _bu<Digits...>();
}

template <char... Digits>
constexpr typename
__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
       unsigned long>::type
operator"" _bul(){
	return 	__impl::select_int_type<__impl::bitsImpl<Digits...>::value,
			      unsigned long>::value;
}
template <char... Digits>
constexpr auto
operator"" _bUL() -> decltype(operator"" _bul<Digits...>()){
	return 	operator"" _bul<Digits...>();
}
template <char... Digits>
constexpr auto
operator"" _buL() -> decltype(operator"" _bul<Digits...>()){
	return 	operator"" _bul<Digits...>();
}
template <char... Digits>
constexpr auto
operator"" _bUl() -> decltype(operator"" _bul<Digits...>()){
	return 	operator"" _bul<Digits...>();
}
template <char... Digits>
constexpr unsigned long long
operator"" _bull(){
	return __impl::bitsImpl<Digits...>::value;
}
template <char... Digits>
constexpr unsigned long long
operator"" _bULL(){
	return __impl::bitsImpl<Digits...>::value;
}
template <char... Digits>
constexpr unsigned long long
operator"" _buLL(){
	return __impl::bitsImpl<Digits...>::value;
}
template <char... Digits>
constexpr unsigned long long
operator"" _bUll(){
	return __impl::bitsImpl<Digits...>::value;
}


} // binary
} //suffixes
} // boost



#endif /* BINARY_H_ */

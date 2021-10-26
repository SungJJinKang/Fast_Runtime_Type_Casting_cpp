#pragma once

#include <type_traits>
#include <tuple>

#if defined(__GNUC__) || defined( __clang__)
#define __FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE __attribute__ ((always_inline))
#elif defined(_MSC_VER)
#define __FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE __forceinline
#endif

////////////////////////

#ifndef __FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T
#define __FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(POINTER_TYPE) std::remove_pointer_t<POINTER_TYPE>
#endif

#ifndef __FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE
#define __FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE(POINTER_TYPE) std::is_pointer_v<POINTER_TYPE>
#endif

#ifndef __FAST_RUNTIME_TYPE_CASTING_CONCAT
#define __FAST_RUNTIME_TYPE_CASTING_CONCAT(STR1, STR2) STR1##STR2
#endif

#ifndef __FAST_RUNTIME_TYPE_CASTING_MAKE_STRING
#define __FAST_RUNTIME_TYPE_CASTING_MAKE_STRING(STR) #STR
#endif

namespace __fast_runtime_type_casting_details
{
	template <typename... T>
	struct __FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT
	{
		constexpr static const size_t count = sizeof...(T);
	};

#ifndef __FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT
#define __FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT(...) __fast_runtime_type_casting_details::__FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT<__VA_ARGS__>::count
#endif

	template<int N, typename... Ts>
	using NthTypeOfParameterPack = typename std::tuple_element<N, std::tuple<Ts...>>::type;


	template <typename DERIVED_TYPE, typename... MULTIPLE_BASE_TYPE>
	struct __FAST_RUNTIME_TYPE_CASTING_CHECK_IS_BASE_OF_MULTIPLE
	{
		constexpr static const bool value = (std::is_base_of_v<MULTIPLE_BASE_TYPE, DERIVED_TYPE> || ...) && ((std::is_same_v<MULTIPLE_BASE_TYPE, DERIVED_TYPE> == false) && ...);
	};
}


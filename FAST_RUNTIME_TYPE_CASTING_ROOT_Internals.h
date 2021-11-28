#pragma once

#include <type_traits>
#include <tuple>

#if defined(__GNUC__) || defined( __clang__)
#define FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE __attribute__ ((always_inline))
#elif defined(_MSC_VER)
#define FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE __forceinline
#endif

////////////////////////

#ifndef FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T
#define FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(POINTER_TYPE) std::remove_pointer_t<POINTER_TYPE>
#endif

#ifndef FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE
#define FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE(POINTER_TYPE) std::is_pointer_v<POINTER_TYPE>
#endif

#ifndef FAST_RUNTIME_TYPE_CASTING_CONCAT
#define FAST_RUNTIME_TYPE_CASTING_CONCAT(STR1, STR2) STR1##STR2
#endif

#ifndef FAST_RUNTIME_TYPE_CASTING_MAKE_STRING
#define FAST_RUNTIME_TYPE_CASTING_MAKE_STRING(STR) #STR
#endif

namespace fast_runtime_type_casting_details
{
	template <typename... T>
	struct FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT_STRUCT
	{
		constexpr static const size_t count = sizeof...(T);
	};

#ifndef FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT
#define FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT(...) fast_runtime_type_casting_details::FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT_STRUCT<__VA_ARGS__>::count
#endif

	template<int N, typename... Ts>
	using NthTypeOfParameterPack = typename std::tuple_element<N, std::tuple<Ts...>>::type;


	template <typename DERIVED_TYPE, typename... MULTIPLE_BASE_TYPE>
	struct FAST_RUNTIME_TYPE_CASTING_CHECK_IS_BASE_OF_MULTIPLE
	{
		constexpr static const bool value = (std::is_base_of_v<MULTIPLE_BASE_TYPE, DERIVED_TYPE> || ...) && ((std::is_same_v<MULTIPLE_BASE_TYPE, DERIVED_TYPE> == false) && ...);
	};
}


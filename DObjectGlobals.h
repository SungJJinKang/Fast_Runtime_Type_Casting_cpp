#pragma once

#include <type_traits>

#include "DObject.h"

#include "CompilerMacros.h"
#include "DObjectMacros.h"

#define REMOVE_POINTER_T(POINTER_TYPE) std::remove_pointer_t<POINTER_TYPE>
#define IS_POINTER_TYPE(POINTER_TYPE) std::is_pointer_v<POINTER_TYPE>


#define CASTING_STATIC_ASSERT(CASTING_TYPE)																													\
static_assert(IS_POINTER_TYPE(CASTING_TYPE) == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(IS_DOBJECT_TYPE(REMOVE_POINTER_T(CASTING_TYPE)) == true, "Please Pass DObject's child Type as IsA function's template argument");		\

#define CASTING_STATIC_ASSERT_PAIR(FROM_CASTING_TYPE, TO_CASTING_TYPE)		\
		CASTING_STATIC_ASSERT(FROM_CASTING_TYPE);							\
		CASTING_STATIC_ASSERT(TO_CASTING_TYPE);								\
		static_assert( ( std::conditional<std::is_const_v<REMOVE_POINTER_T(FROM_CASTING_TYPE)>, std::is_const<REMOVE_POINTER_T(TO_CASTING_TYPE)>, std::bool_constant<true>>::type::value ) == true, "If FromCasting Type is const-qualified type, ToCasting type should be const-qualified type")

template <typename CompareType>
D_FORCE_INLINE bool IsA(const DObject* const dObject)
{
	static_assert(std::is_pointer_v<CompareType> == false, "Don't Pass Pointer Type as IsA function's template argument");						
	static_assert(IS_DOBJECT_TYPE(CompareType) == true, "Please Pass DObject's child Type as IsA function's template argument");		

	return (dObject != nullptr) && ( dObject->IsChildOf<CompareType>() );
}

template <typename CompareType>
D_FORCE_INLINE bool IsChildOf(const DObject* const dObject)
{
	return IsA<CompareType>(dObject);
}

namespace details
{
	template<typename ToCastingType, typename FromCastingType>
	D_FORCE_INLINE ToCastingType CastToImp(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		return (dObject != nullptr && IsA<REMOVE_POINTER_T(ToCastingType)>(dObject) == true) ? ( reinterpret_cast<ToCastingType>(dObject) ) : ( nullptr );
	}

	template<typename ToCastingType, typename FromCastingType>
	D_FORCE_INLINE ToCastingType CastToUncheckedImp(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		return reinterpret_cast<ToCastingType>(dObject);
	}
}


/// <summary>
/// Cast passed dObject to CastingType ( template argument )
///	This function support only up-down hierarchy
///	Cant cast to sibling class
///
///	This function do type check using TypeID at runtime ( faster than dynamic_cast )
///	If you ensure Casting will be success, Use CastToUnchecked
/// </summary>
/// <typeparam name="CastingType"></typeparam>
/// <param name="dObject"></param>
/// <returns></returns>
template<typename ToCastingType, typename FromCastingType>
D_FORCE_INLINE ToCastingType CastTo(FromCastingType dObject)
{
	CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

	if constexpr(std::is_base_of_v<REMOVE_POINTER_T(ToCastingType), REMOVE_POINTER_T(FromCastingType)> == true)
	{
		return details::CastToUncheckedImp<ToCastingType>(dObject);
	}
	else
	{
		return details::CastToImp<ToCastingType>(dObject);
	}
}

template<typename ToCastingType, typename FromCastingType>
D_FORCE_INLINE ToCastingType CastToUnchecked(FromCastingType dObject)
{
	CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

	return details::CastToUncheckedImp<ToCastingType>(dObject);
}

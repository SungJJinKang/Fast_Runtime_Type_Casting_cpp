#pragma once

#include <type_traits>

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_Internals.h"

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_Macros.h"

#include "MultipleInheritance/FastDynamicCast/fast_dynamic_cast.h"


#define CASTING_STATIC_ASSERT(CASTING_TYPE)																													\
static_assert(__FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE(CASTING_TYPE) == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(__FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(__FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(CASTING_TYPE)) == true, "Please Pass FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS's child Type as IsA function's template argument");		\

#define CASTING_STATIC_ASSERT_PAIR(FROM_CASTING_TYPE, TO_CASTING_TYPE)		\
		CASTING_STATIC_ASSERT(FROM_CASTING_TYPE);							\
		CASTING_STATIC_ASSERT(TO_CASTING_TYPE);								\
		static_assert( ( std::conditional<std::is_const_v<__FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(FROM_CASTING_TYPE)>, std::is_const<__FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(TO_CASTING_TYPE)>, std::bool_constant<true>>::type::value ) == true, "If FromCasting Type is const-qualified type, ToCasting type should be const-qualified type")


namespace fast_cast
{
	template <typename CompareType, typename FromType>
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE bool IsChildOf(const FromType* const dObject)
	{
		static_assert(std::is_pointer_v<CompareType> == false, "Don't Pass Pointer Type as IsA function's template argument");
		static_assert(std::is_pointer_v<FromType> == false, "Don't Pass Pointer Type as IsA function's template argument");
		static_assert(__FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(CompareType) == true, "Please Pass FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS's child Type as IsA function's template argument");
		static_assert(__FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(FromType) == true, "Please Pass FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS's child Type as IsA function's template argument");

		if constexpr ( std::is_base_of_v<CompareType, FromType> == true)
		{
			return dObject != nullptr;
		}
		else
		{

			return (dObject != nullptr) && (dObject->IsChildOf<CompareType>());
		}
	}
}




namespace __fast_runtime_type_casting_details
{
	template<typename ToCastingType, typename FromCastingType>
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastToImp(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);
		
		if(dObject->__FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() == false)
		{
			return (fast_cast::IsChildOf<__FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(ToCastingType)>(dObject) == true) ? (reinterpret_cast<ToCastingType>(dObject)) : (nullptr); // reinterpret_cast is acceptable, because every root class has virtual table.
		}
		else
		{// use https://github.com/SungJJinKang/FastDynamicCast
			return fast_dcast::fast_dynamic_cast<ToCastingType>(dObject);
		}		
	}

	template<typename ToCastingType, typename FromCastingType>
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastToUncheckedImp(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		return reinterpret_cast<ToCastingType>(dObject); // reinterpret_cast is acceptable, because every root class has virtual table.
	}
}

namespace fast_cast
{
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
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastTo(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		ToCastingType castedType = nullptr;

		if(dObject != nullptr)
		{
			if (
				(std::is_base_of_v<__FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(ToCastingType), __FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(FromCastingType)> == true)
				&&
				(dObject->__FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() == false)
			)
			{
				castedType = __fast_runtime_type_casting_details::CastToUncheckedImp<ToCastingType>(dObject);
			}
			else
			{
				castedType = __fast_runtime_type_casting_details::CastToImp<ToCastingType>(dObject);
			}
		}

		return castedType;
	}

	template<typename ToCastingType, typename FromCastingType>
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastToUnchecked(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		return __fast_runtime_type_casting_details::CastToUncheckedImp<ToCastingType>(dObject);
	}
}
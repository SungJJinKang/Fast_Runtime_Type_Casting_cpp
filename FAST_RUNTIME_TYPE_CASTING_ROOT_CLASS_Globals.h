#pragma once

#include <type_traits>

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_Internals.h"

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_Macros.h"

#include "MultipleInheritance/FastDynamicCast/fast_dynamic_cast.h"


#define CASTING_STATIC_ASSERT(CASTING_TYPE)																													\
static_assert(FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE(CASTING_TYPE) == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(CASTING_TYPE)) == true, "Please Pass FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS's child Type as IsA function's template argument");		\

#define CASTING_STATIC_ASSERT_PAIR(FROM_CASTING_TYPE, TO_CASTING_TYPE)		\
		CASTING_STATIC_ASSERT(FROM_CASTING_TYPE);							\
		CASTING_STATIC_ASSERT(TO_CASTING_TYPE);								\
		static_assert( ( std::conditional<std::is_const_v<FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(FROM_CASTING_TYPE)>, std::is_const<FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(TO_CASTING_TYPE)>, std::bool_constant<true>>::type::value ) == true, "If FromCasting Type is const-qualified type, ToCasting type should be const-qualified type")


namespace fast_cast
{
	template <typename COMPARE_TYPE, typename FromType>																																				
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE bool IsChildOf(const FromType* const dObject)																												
	{
		static_assert(std::is_pointer_v<COMPARE_TYPE> == false, "Don't Pass Pointer Type as IsA function's template argument");
		static_assert(std::is_pointer_v<FromType> == false, "Don't Pass Pointer Type as IsA function's template argument");
		static_assert(FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(COMPARE_TYPE) == true, "Please Pass FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS's child Type as IsA function's template argument");
		static_assert(FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(FromType) == true, "Please Pass FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS's child Type as IsA function's template argument");

		if(dObject == nullptr)
		{
			return false;
		}
		else
		{
			if constexpr (std::is_base_of_v<COMPARE_TYPE, FromType> == true)
			{
				return true;
			}
			else
			{
				const bool is_multiple_inheritance = dObject->FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE();
				if (std::is_same_v<COMPARE_TYPE, FromType> == true && is_multiple_inheritance == false)
				{
					return true;
				}
				else if (is_multiple_inheritance == false)
				{
					const fast_runtime_type_casting_details::BaseChain& this_base_chain = dObject->__FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN();
					const bool isChild = (this_base_chain.mChainCount >= COMPARE_TYPE::FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()) && (this_base_chain.mChainData[this_base_chain.mChainCount - COMPARE_TYPE::FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()] == COMPARE_TYPE::FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC());
					return isChild;
				}
				else
				{
					return fast_dcast::fast_dynamic_cast<COMPARE_TYPE*>(dObject) != nullptr;
				}
			}
			
		}

		
	}


}




namespace fast_runtime_type_casting_details
{
	template<typename ToCastingType, typename FromCastingType>
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastToImp(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);
		
		if(dObject->FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() == false)
		{
			return (fast_cast::IsChildOf<FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(ToCastingType)>(dObject) == true) ? (reinterpret_cast<ToCastingType>(dObject)) : (nullptr); // reinterpret_cast is acceptable, because every root class has virtual table.
		}
		else
		{// use https://github.com/tobspr/FastDynamicCast
			return fast_dcast::fast_dynamic_cast<ToCastingType>(dObject);
		}		
	}

	template<typename ToCastingType, typename FromCastingType>
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastToUncheckedImp(FromCastingType dObject)
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
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastTo(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		ToCastingType castedType = nullptr;

		if(dObject != nullptr)
		{
			if (
				(std::is_base_of_v<FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(ToCastingType), FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(FromCastingType)> == true)
				&&
				(dObject->FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() == false)
			)
			{
				castedType = fast_runtime_type_casting_details::CastToUncheckedImp<ToCastingType>(dObject);
			}
			else
			{
				castedType = fast_runtime_type_casting_details::CastToImp<ToCastingType>(dObject);
			}
		}

		return castedType;
	}

	template<typename ToCastingType, typename FromCastingType>
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE ToCastingType CastToUnchecked(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		return fast_runtime_type_casting_details::CastToUncheckedImp<ToCastingType>(dObject);
	}
}
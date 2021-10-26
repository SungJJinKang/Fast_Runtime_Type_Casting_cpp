#pragma once

#include <type_traits>
#include <array>
#include <stddef.h>

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_Internals.h"


#ifndef __FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP

#define __FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)																				\
		public:																																	\
		constexpr static const char* const __FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID = #CURRENT_CLASS_TYPE;										\
		public:																																	\
		__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* __FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC() {										\
			return __FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;																					\
		}																																		\
        virtual const char* __FAST_RUNTIME_TYPE_CASTING_GET_CLASS_TYPE_ID() const {																\
		static_assert(std::is_same_v<std::decay<decltype(*this)>::type, CURRENT_CLASS_TYPE> == true, "Wrong Current ClassType is passed ");		\
		return CURRENT_CLASS_TYPE::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC(); }	

#endif



/////////////////////////////////


namespace __fast_runtime_type_casting_details
{
	//!!!!!!!!!!!!
	//Never change static to extern. static give hint to compiler that this definition is used only in source file(.cpp)
	//								 Then Compiler remove this functions definition from compiler if it is called only at compile time
	template <typename BASE_TYPE_CLASS>
	static constexpr void BASE_CHAIN_HILLCLIMB_COUNT(size_t& base_chain_count)
	{
		base_chain_count++;
		if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_TYPE_CLASS::template __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(base_chain_count);
		}
	}

	template <typename BASE_TYPE_CLASS>
	static constexpr size_t BASE_CHAIN_HILLCLIMB_COUNT()
	{
		size_t base_chain_count = 1;

		if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false)
		{
			if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
			{
				BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_TYPE_CLASS::template __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(base_chain_count);
			}
		}

		return base_chain_count;
	}

	template <typename BASE_TYPE_CLASS, size_t COUNT>
	static constexpr void BASE_CHAIN_HILLCLIMB_DATA(size_t& count, std::array<const char*, COUNT>& chain_data)
	{
		chain_data[count] = BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
		count++;
		if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_TYPE_CLASS::template __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(count, chain_data);
		}
	}

	template <typename BASE_TYPE_CLASS, size_t COUNT>
	static constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
	{
		std::array<const char*, COUNT> chain_data{};

		if constexpr(BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false)
		{
			chain_data[0] = BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
			if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
			{
				size_t count = 1;
				BASE_CHAIN_HILLCLIMB_DATA<typename BASE_TYPE_CLASS::template __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(count, chain_data);
			}
		}
		else
		{
			static_assert(COUNT == 1);
			chain_data[0] = nullptr;
		}
		
		return chain_data;
	}

	template <typename BASE_TYPE_CLASS>
	static constexpr void BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE(bool& have_multiple_inheritance)
	{
		if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_COUNT > 1)
		{
			have_multiple_inheritance = true;
		}
		else if constexpr (BASE_TYPE_CLASS::template __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>::__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE<BASE_TYPE_CLASS::template __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(have_multiple_inheritance);
		}
	}

	template <typename BASE_TYPE_CLASS>
	static constexpr bool BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE()
	{
		bool have_multiple_inheritance = false;

		if constexpr (BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE<BASE_TYPE_CLASS>(have_multiple_inheritance);
		}

		return have_multiple_inheritance;
	}

	struct BaseChain
	{
		const size_t mChainCount;
		const char* const* mChainData;

		constexpr BaseChain(const size_t _chainCount, const char* const* _chainData)
			: mChainCount(_chainCount), mChainData(_chainData)
		{

		}
	};
}


#ifndef __FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN

#define __FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN(...)													\
	public:																									\
	constexpr static const size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_COUNT = __FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT(__VA_ARGS__);	\
	constexpr static const bool	__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS = false;							\
	template <size_t TYPE_INDEX>																			\
	using __FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE = __fast_runtime_type_casting_details::NthTypeOfParameterPack<TYPE_INDEX, __VA_ARGS__>;						\
	constexpr static const bool __FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE>();		\
	private:																								\
	constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_COUNT<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE>();		\
	constexpr static const std::array<const char*, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT> __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_DATA<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT>();			\
	constexpr static const __fast_runtime_type_casting_details::BaseChain __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN{ __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA.data() };		\
	public:																									\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()			\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainCount;											\
	}																										\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* const * __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainData;											\
	}																										\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_STATIC()\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN;														\
	}																										\
	virtual size_t __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }	\
	virtual const char* const * __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const {					\
	static_assert(__fast_runtime_type_casting_details::__FAST_RUNTIME_TYPE_CASTING_CHECK_IS_BASE_OF_MULTIPLE<std::decay<decltype(*this)>::type, __VA_ARGS__>::value == true, "Current Class Type is not derived from Passed Base ClassType is passed");	\
	return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }											\
	virtual const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_STATIC(); }	\
	virtual bool __FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() const { return __FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE; }								\

#endif

/////////////////////////////////

#ifndef FAST_RUNTIME_TYPE_CASTING_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(CURRENT_CLASS_TYPE, ...)						\
		public:																				\
		using __FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = CURRENT_CLASS_TYPE;				\
		__FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)							\
		__FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN(__VA_ARGS__)							\
		private:

#endif


#ifndef FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY(TYPE_NAME)																													\
public:																																											\
	using __FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = TYPE_NAME;																													\
	__FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(TYPE_NAME)																															\
private:																																										\
	constexpr static const __fast_runtime_type_casting_details::BaseChain __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN{ 1, nullptr };													\
public:																																											\
	constexpr static const bool	__FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS = true;																								\
	constexpr static const bool	__FAST_RUNTIME_TYPE_CASTING_IS_INHERITING_ROOT_CLASS = true;																					\
	constexpr static const bool __FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE = false;																					\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()														\
	{																																											\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainCount;																												\
	}																																											\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* const* __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()											\
	{																																											\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainData;																												\
	}																																											\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA()				\
	{																																											\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN;																															\
	}																																											\
	virtual size_t __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }									\
	virtual const char* const* __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }							\
	virtual const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA(); }	\
	virtual bool __FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() const { return false; }																			\
	template <typename BASE_TYPE>																																				\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE bool IsChildOf() const																												\
	{																																											\
		const bool is_multiple_inheritance = __FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE();																	\
		if ( std::is_same_v<BASE_TYPE, std::decay<decltype(*this)>::type> == true && is_multiple_inheritance == false ) { return true; }										\
		else if(is_multiple_inheritance == false){																																\
		const __fast_runtime_type_casting_details::BaseChain& this_base_chain = __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN();													\
		const bool isChild = (this_base_chain.mChainCount >= BASE_TYPE::__FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()) && (this_base_chain.mChainData[this_base_chain.mChainCount - BASE_TYPE::__FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC());	\
		return isChild; }																																						\
		else { return fast_dcast::fast_dynamic_cast<BASE_TYPE*>(this) != nullptr ; }																							\
	}																																											\
private:																																										\

#endif


#ifndef __FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS
#define __FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(TYPE_NAME) (TYPE_NAME::__FAST_RUNTIME_TYPE_CASTING_IS_INHERITING_ROOT_CLASS == true)
#endif
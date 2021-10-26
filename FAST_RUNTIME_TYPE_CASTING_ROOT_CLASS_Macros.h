#pragma once

#include <type_traits>
#include <array>
#include <stddef.h>

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_Internals.h"

class FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS;

#define IS_DERIVED_FROM_FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS(CURRENT_CLASS_TYPE) std::is_base_of_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, CURRENT_CLASS_TYPE>

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
		if constexpr (std::is_same_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_TYPE_CLASS> == false) {
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(base_chain_count);
		}
	}

	template <typename BASE_TYPE_CLASS>
	static constexpr size_t BASE_CHAIN_HILLCLIMB_COUNT()
	{
		size_t base_chain_count = 1;
		if constexpr (std::is_same_v <FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_TYPE_CLASS > == false) {
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(base_chain_count);
		}
		return base_chain_count;
	}

	template <typename BASE_TYPE_CLASS, size_t COUNT>
	static constexpr void BASE_CHAIN_HILLCLIMB_DATA(size_t& count, std::array<const char*, COUNT>& chain_data)
	{
		chain_data[count] = BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
		count++;
		if constexpr (std::is_same_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_TYPE_CLASS> == false) {
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(count, chain_data);
		}
	}

	template <typename BASE_TYPE_CLASS, size_t COUNT>
	static constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
	{
		std::array<const char*, COUNT> chain_data{};
		chain_data[0] = BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
		if constexpr (std::is_same_v <FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_TYPE_CLASS > == false) {
			size_t count = 1;
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(count, chain_data);
		}
		return chain_data;
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




#define __FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN(BASE_TYPE_CLASS)							\
	static_assert(std::is_same_v<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE, BASE_TYPE_CLASS> == false);	\
	public:																										\
	using __FAST_RUNTIME_TYPE_CASTING_BASE_TYPE = BASE_TYPE_CLASS; /* alias base FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS Type Class */	\
	private:																									\
	constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_COUNT<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE>();		\
	constexpr static const std::array<const char*, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT> __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN_DATA = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_DATA<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT>();			\
	constexpr static const __fast_runtime_type_casting_details::BaseChain __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN{ __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT, __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN_DATA.data() };		\
	public:																									\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()			\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN.mChainCount;											\
	}																										\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* const * __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN.mChainData;											\
	}																										\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_STATIC()\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN;														\
	}																										\
	virtual size_t __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }	\
	virtual const char* const * __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const {					\
	static_assert(std::is_base_of_v<BASE_TYPE_CLASS, std::decay<decltype(*this)>::type> == true, "Current Class Type is not derived from Passed Base ClassType is passed");	\
	return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }											\
	virtual const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_STATIC(); }	\

/////////////////////////////////

#ifndef FAST_RUNTIME_TYPE_CASTING_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(CURRENT_CLASS_TYPE, BASE_CLASS_TYPE)			\
		public:																				\
		static_assert(std::is_base_of_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_CLASS_TYPE>, "Base ClassType is not derived from DObejct");	\
		using __FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = CURRENT_CLASS_TYPE;				\
		__FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)							\
		__FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN(BASE_CLASS_TYPE)						\
		private:

#endif


#ifndef FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY																																\
public:																																											\
	using __FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS;																						\
	__FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS)																								\
private:																																										\
	constexpr static const __fast_runtime_type_casting_details::BaseChain _BASE_CHAIN{ 1, nullptr };																			\
public:																																											\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()														\
	{																																											\
		return _BASE_CHAIN.mChainCount;																																			\
	}																																											\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* const* __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()											\
	{																																											\
		return _BASE_CHAIN.mChainData;																																			\
	}																																											\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA()				\
	{																																											\
		return _BASE_CHAIN;																																						\
	}																																											\
	virtual size_t __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }									\
	virtual const char* const* __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }							\
	virtual const __fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA(); }	\
	template <typename BASE_TYPE>																																				\
	__FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE bool IsChildOf() const																												\
	{																																											\
		static_assert(IS_DERIVED_FROM_FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS(BASE_TYPE));																							\
		const __fast_runtime_type_casting_details::BaseChain& this_base_chain = __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN();													\
		const bool isChild = (this_base_chain.mChainCount >= BASE_TYPE::__FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()) && (this_base_chain.mChainData[this_base_chain.mChainCount - BASE_TYPE::__FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC());	\
		return isChild;																																							\
	}																																											\
private:																																										\

#endif
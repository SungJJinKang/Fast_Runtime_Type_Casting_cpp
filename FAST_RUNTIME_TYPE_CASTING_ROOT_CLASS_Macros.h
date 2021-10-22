#pragma once

#include <type_traits>
#include <array>
#include <stddef.h>

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_Macros.h"

class FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS;

#define IS_DERIVED_FROM_FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS(CURRENT_CLASS_TYPE) std::is_base_of_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, CURRENT_CLASS_TYPE>


static_assert("TEST IF IDENTICAL LITERAL STRING IS ALLOCATED ONE TIME" == "TEST IF IDENTICAL LITERAL STRING IS ALLOCATED ONE TIME");

#ifndef __FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP

#define __FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)																				\
		public:																																	\
		constexpr static const char* const __FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID = #CURRENT_CLASS_TYPE;										\
		public:																																	\
		D_FORCE_INLINE constexpr static const char* __FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC() {										\
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
	template <typename BASE_DOBJECT_TYPE_CLASS>
	static constexpr void BASE_CHAIN_HILLCLIMB_COUNT(size_t& base_chain_count)
	{
		base_chain_count++;
		if constexpr (std::is_same_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_DOBJECT_TYPE_CLASS> == false) {
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(base_chain_count);
		}
	}

	template <typename BASE_DOBJECT_TYPE_CLASS>
	static constexpr size_t BASE_CHAIN_HILLCLIMB_COUNT()
	{
		size_t base_chain_count = 1;
		if constexpr (std::is_same_v <FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_DOBJECT_TYPE_CLASS > == false) {
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(base_chain_count);
		}
		return base_chain_count;
	}

	template <typename BASE_DOBJECT_TYPE_CLASS, size_t COUNT>
	static constexpr void BASE_CHAIN_HILLCLIMB_DATA(size_t& count, std::array<const char*, COUNT>& chain_data)
	{
		chain_data[count] = BASE_DOBJECT_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
		count++;
		if constexpr (std::is_same_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_DOBJECT_TYPE_CLASS> == false) {
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(count, chain_data);
		}
	}

	template <typename BASE_DOBJECT_TYPE_CLASS, size_t COUNT>
	static constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
	{
		std::array<const char*, COUNT> chain_data{};
		chain_data[0] = BASE_DOBJECT_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
		if constexpr (std::is_same_v <FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_DOBJECT_TYPE_CLASS > == false) {
			size_t count = 1;
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::__FAST_RUNTIME_TYPE_CASTING_BASE_TYPE>(count, chain_data);
		}
		return chain_data;
	}
}




#define __FAST_RUNTIME_TYPE_CASTING_DOBJECT_CLASS_BASE_CHAIN(BASE_DOBJECT_TYPE_CLASS)							\
	static_assert(std::is_same_v<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE, BASE_DOBJECT_TYPE_CLASS> == false);	\
	public:																										\
	using __FAST_RUNTIME_TYPE_CASTING_BASE_TYPE = BASE_DOBJECT_TYPE_CLASS; /* alias base FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS Type Class */	\
	private:																									\
	constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_COUNT<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE>();		\
	constexpr static const std::array<const char*, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT> __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN_DATA = __fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_DATA<__FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE, __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT>();			\
	public:																									\
	D_FORCE_INLINE constexpr static size_t __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()			\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT;												\
	}																										\
	D_FORCE_INLINE constexpr static const char* const * __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()\
	{																										\
		return __FAST_RUNTIME_TYPE_CASTING__BASE_CHAIN_DATA.data();											\
	}																										\
	virtual size_t __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const { return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }	\
	virtual const char* const * __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const {					\
	static_assert(std::is_base_of_v<BASE_DOBJECT_TYPE_CLASS, std::decay<decltype(*this)>::type> == true, "Current Class Type is not derived from Passed Base ClassType is passed");	\
	return __FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }

/////////////////////////////////

#ifndef FAST_RUNTIME_TYPE_CASTING_DOBJECT_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_DOBJECT_CLASS_BODY(CURRENT_CLASS_TYPE, BASE_CLASS_TYPE)	\
		public:																		\
		static_assert(std::is_base_of_v<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS, BASE_CLASS_TYPE>, "Base ClassType is not derived from DObejct");	\
		using __FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = CURRENT_CLASS_TYPE;				\
		__FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)							\
		__FAST_RUNTIME_TYPE_CASTING_DOBJECT_CLASS_BASE_CHAIN(BASE_CLASS_TYPE)

#endif


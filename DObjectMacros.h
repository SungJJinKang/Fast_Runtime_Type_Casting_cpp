#pragma once

#include <type_traits>
#include <array>
#include <stddef.h>


class DObject;

#define IS_DOBJECT_TYPE(TYPE) std::is_base_of_v<DObject, TYPE>


static_assert("TEST IF IDENTICAL LITERAL STRING IS ALLOATED ONE TIME" == "TEST IF IDENTICAL LITERAL STRING IS ALLOATED ONE TIME");

#ifndef TYPE_ID_IMP

#define TYPE_ID_IMP(CLASS_TYPE)																							\
		public:																											\
		constexpr static const char* const __CLASS_TYPE_ID = #CLASS_TYPE;												\
		public:																											\
		D_FORCE_INLINE constexpr static const char* CLASS_TYPE_ID_STATIC() {												\
			return __CLASS_TYPE_ID;																						\
		}																												\
        virtual const char* GetClassTypeID() const { return CLASS_TYPE::CLASS_TYPE_ID_STATIC(); }		

#endif



/////////////////////////////////


namespace details
{
	//!!!!!!!!!!!!
	//Never change static to extern. static give hint to compiler that this definition is used only in source file(.cpp)
	//								 Then Compiler remove this functions definition from compiler if it is called only at compile time
	template <typename BASE_DOBJECT_TYPE_CLASS>
	static constexpr void BASE_CHAIN_HILLCLIMB_COUNT(size_t& base_chain_count)
	{
		base_chain_count++;
		if constexpr (std::is_same_v<DObject, BASE_DOBJECT_TYPE_CLASS> == false) {
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::Base>(base_chain_count);
		}
	}

	template <typename BASE_DOBJECT_TYPE_CLASS>
	static constexpr size_t BASE_CHAIN_HILLCLIMB_COUNT()
	{
		size_t base_chain_count = 1;
		if constexpr (std::is_same_v <DObject, BASE_DOBJECT_TYPE_CLASS > == false) {
			BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::Base>(base_chain_count);
		}
		return base_chain_count;
	}

	template <typename BASE_DOBJECT_TYPE_CLASS, size_t COUNT>
	static constexpr void BASE_CHAIN_HILLCLIMB_DATA(size_t& count, std::array<const char*, COUNT>& chain_data)
	{
		chain_data[count] = BASE_DOBJECT_TYPE_CLASS::__CLASS_TYPE_ID;
		count++;
		if constexpr (std::is_same_v<DObject, BASE_DOBJECT_TYPE_CLASS> == false) {
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::Base>(count, chain_data);
		}
	}

	template <typename BASE_DOBJECT_TYPE_CLASS, size_t COUNT>
	static constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
	{
		std::array<const char*, COUNT> chain_data{};
		chain_data[0] = BASE_DOBJECT_TYPE_CLASS::__CLASS_TYPE_ID;
		if constexpr (std::is_same_v <DObject, BASE_DOBJECT_TYPE_CLASS > == false) {
			size_t count = 1;
			BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::Base>(count, chain_data);
		}
		return chain_data;
	}
}




#define DOBJECT_CLASS_BASE_CHAIN(BASE_DOBJECT_TYPE_CLASS)													\
	static_assert(std::is_same_v<Current, BASE_DOBJECT_TYPE_CLASS> == false);								\
	public:																									\
	using Base = BASE_DOBJECT_TYPE_CLASS; /* alias Base DObject Type Class */								\
	private:																								\
	constexpr static size_t _BASE_CHAIN_COUNT = details::BASE_CHAIN_HILLCLIMB_COUNT<Current>();		\
	constexpr static const std::array<const char*, _BASE_CHAIN_COUNT> _BASE_CHAIN_DATA = details::BASE_CHAIN_HILLCLIMB_DATA<Current, _BASE_CHAIN_COUNT>();			\
	public:																									\
	D_FORCE_INLINE constexpr static size_t BASE_CHAIN_COUNT_STATIC()											\
	{																										\
		return _BASE_CHAIN_COUNT;																			\
	}																										\
	D_FORCE_INLINE constexpr static const char* const * BASE_CHAIN_DATA_STATIC()								\
	{																										\
		return _BASE_CHAIN_DATA.data();																		\
	}																										\
	virtual size_t GetBaseChainCount() const { return BASE_CHAIN_COUNT_STATIC(); }							\
	virtual const char* const * GetBaseChainData() const { return BASE_CHAIN_DATA_STATIC(); }

/////////////////////////////////

#ifndef DOBJECT_CLASS_BODY

#define DOBJECT_CLASS_BODY(CLASS_TYPE)												\
		public:																		\
		using Current = CLASS_TYPE;													\
		TYPE_ID_IMP(CLASS_TYPE)														\

#endif


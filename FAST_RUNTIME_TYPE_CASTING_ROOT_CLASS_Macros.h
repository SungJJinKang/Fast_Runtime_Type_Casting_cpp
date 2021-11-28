#pragma once

#include <type_traits>
#include <array>
#include <stddef.h>

#include "FAST_RUNTIME_TYPE_CASTING_ROOT_Internals.h"

#include "MultipleInheritance/FastDynamicCast/fast_dynamic_cast.h"

#ifndef FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP

#define FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)																				\
		public:																																	\
		constexpr static const char* const FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID = #CURRENT_CLASS_TYPE;										\
		public:																																	\
		FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC() {										\
			return FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;																					\
		}																																		\
        virtual const char* __FAST_RUNTIME_TYPE_CASTING_GET_CLASS_TYPE_ID() const {																\
		static_assert(std::is_same_v<std::decay<decltype(*this)>::type, CURRENT_CLASS_TYPE> == true, "Wrong Current ClassType is passed ");		\
		return CURRENT_CLASS_TYPE::FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID_STATIC(); }	

#endif



/////////////////////////////////


namespace fast_runtime_type_casting_details
{
	//!!!!!!!!!!!!
	//Never change static to extern. static give hint to compiler that this definition is used only in source file(.cpp)
	//Then Compiler remove this functions definition from compiler because this function is called only at compile time
	template <typename BASE_TYPE_CLASS>
	static constexpr void BASE_CHAIN_HILLCLIMB_COUNT(size_t& base_chain_count)
	{
		base_chain_count++;
		if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_TYPE_CLASS::template FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(base_chain_count);
		}
	}

	template <typename BASE_TYPE_CLASS>
	static constexpr size_t BASE_CHAIN_HILLCLIMB_COUNT()
	{
		size_t base_chain_count = 1;

		if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false)
		{
			if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
			{
				fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_TYPE_CLASS::template FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(base_chain_count);
			}
		}

		return base_chain_count;
	}

	template <typename BASE_TYPE_CLASS, size_t COUNT>
	static constexpr void BASE_CHAIN_HILLCLIMB_DATA(size_t& count, std::array<const char*, COUNT>& chain_data)
	{
		chain_data[count] = BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
		count++;
		if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_DATA<typename BASE_TYPE_CLASS::template FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(count, chain_data);
		}
	}

	template <typename BASE_TYPE_CLASS, size_t COUNT>
	static constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
	{
		std::array<const char*, COUNT> chain_data{};

		if constexpr(BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false)
		{
			chain_data[0] = BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_CLASS_TYPE_ID;
			if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
			{
				size_t count = 1;
				fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_DATA<typename BASE_TYPE_CLASS::template FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(count, chain_data);
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
		if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_COUNT > 1)
		{
			have_multiple_inheritance = true;
		}
		else if constexpr (BASE_TYPE_CLASS::template FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>::FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE<typename BASE_TYPE_CLASS::template FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE<0>>(have_multiple_inheritance);
		}
	}

	template <typename BASE_TYPE_CLASS>
	static constexpr bool BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE()
	{
		bool have_multiple_inheritance = false;

		if constexpr (BASE_TYPE_CLASS::FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS == false)
		{
			fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE<BASE_TYPE_CLASS>(have_multiple_inheritance);
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


#ifndef FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN

#define FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN(...)													\
	public:																									\
	constexpr static const size_t FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_COUNT = FAST_RUNTIME_TYPE_CASTING_TYPE_COUNT(__VA_ARGS__);	\
	constexpr static const bool	FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS = false;							\
	template <size_t TYPE_INDEX>																			\
	using FAST_RUNTIME_TYPE_CASTING_BASE_CLASS_TYPE = fast_runtime_type_casting_details::NthTypeOfParameterPack<TYPE_INDEX, __VA_ARGS__>;						\
	constexpr static const bool FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE = fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_CHECK_MULTIPLE_INHERITANCE<FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE>();		\
	private:																								\
	constexpr static size_t FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT = fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_COUNT<FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE>();		\
	constexpr static const std::array<const char*, FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT> FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA = fast_runtime_type_casting_details::BASE_CHAIN_HILLCLIMB_DATA<FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE, FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT>();			\
	constexpr static const fast_runtime_type_casting_details::BaseChain FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN{ FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT, FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA.data() };		\
	public:																									\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static size_t FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()			\
	{																										\
		return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainCount;											\
	}																										\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* const * FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()\
	{																										\
		return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainData;											\
	}																										\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const fast_runtime_type_casting_details::BaseChain& FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_STATIC()\
	{																										\
		return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN;														\
	}																										\
	virtual size_t FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const override { return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }	\
	virtual const char* const * FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const override {			\
	static_assert(fast_runtime_type_casting_details::FAST_RUNTIME_TYPE_CASTING_CHECK_IS_BASE_OF_MULTIPLE<std::decay<decltype(*this)>::type, __VA_ARGS__>::value == true, "Current Class Type is not derived from Passed Base ClassType is passed");	\
	return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }											\
	virtual const fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN() const override { return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_STATIC(); }	\
	virtual bool FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() const override { return FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE; }								\

#endif

/////////////////////////////////

#ifndef FAST_RUNTIME_TYPE_CASTING_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(CURRENT_CLASS_TYPE, ...)						\
		public:																				\
		using FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = CURRENT_CLASS_TYPE;				\
		FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(CURRENT_CLASS_TYPE)							\
		FAST_RUNTIME_TYPE_CASTING_CLASS_BASE_CHAIN(__VA_ARGS__)							\
		private:

#endif




#ifndef FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY_BASE_CHAIN

#define FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY_BASE_CHAIN(TYPE_NAME)		\
public:																		\
	using FAST_RUNTIME_TYPE_CASTING_CURRENT_TYPE = TYPE_NAME;				\
private:																																										\
	constexpr static const fast_runtime_type_casting_details::BaseChain FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN{ 1, nullptr };													\
public:																																											\
	constexpr static const bool	FAST_RUNTIME_TYPE_CASTING_IS_ROOT_CLASS = true;																								\
	constexpr static const bool	__FAST_RUNTIME_TYPE_CASTING_IS_INHERITING_ROOT_CLASS = true;																					\
	constexpr static const bool FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE = false;																					\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static size_t FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC()														\
	{																																											\
	return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainCount;																												\
	}																																											\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const char* const* FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC()											\
	{																																											\
	return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN.mChainData;																												\
	}																																											\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE constexpr static const fast_runtime_type_casting_details::BaseChain& FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA()				\
	{																																											\
	return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN;																															\
	}																																											\
	virtual size_t FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_COUNT() const { return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_COUNT_STATIC(); }									\
	virtual const char* const* FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA() const { return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA_STATIC(); }							\
	virtual const fast_runtime_type_casting_details::BaseChain& __FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN() const { return FAST_RUNTIME_TYPE_CASTING_BASE_CHAIN_DATA(); }	\
	virtual bool FAST_RUNTIME_TYPE_CASTING_GET_IS_HAVE_MULTIPLE_INHERITANCE() const { return false; }																			\
	template <typename BASE_TYPE>																																				\
	FAST_RUNTIME_TYPE_CASTING_FORCE_INLINE bool IsChildOf() const																												\
	{																																											\
		return fast_cast::IsChildOf<BASE_TYPE>(this);																															\
	}																																											\
	private:

#endif

#ifndef FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS
#define FAST_RUNTIME_TYPE_CASTING_ASSERT_IS_INHERITING_ROOT_CLASS(TYPE_NAME) (TYPE_NAME::__FAST_RUNTIME_TYPE_CASTING_IS_INHERITING_ROOT_CLASS == true)
#endif

#ifndef FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY

#define FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY(TYPE_NAME)				\
	FAST_RUNTIME_TYPE_CASTING_TYPE_ID_IMP(TYPE_NAME)						\
	FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY_BASE_CHAIN(TYPE_NAME)			\

#endif

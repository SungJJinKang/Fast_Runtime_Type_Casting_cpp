#pragma once

#include "CompilerMacros.h"
#include "DObjectMacros.h"



class DObject
{
	DOBJECT_CLASS_BODY(DObject)

private:
	constexpr static size_t _BASE_CHAIN_COUNT = 1;
	constexpr static const std::array<const char*, 1> _BASE_CHAIN_DATA{ __CLASS_TYPE_ID };
public:
	D_FORCE_INLINE constexpr static size_t BASE_CHAIN_COUNT_STATIC()
	{
		return 1;
	}
	D_FORCE_INLINE constexpr static const char* const* BASE_CHAIN_DATA_STATIC()
	{
		return _BASE_CHAIN_DATA.data();
	}
	virtual size_t GetBaseChainCount() const { return BASE_CHAIN_COUNT_STATIC(); }
	virtual const char* const* GetBaseChainData() const { return BASE_CHAIN_DATA_STATIC(); }


public:

	template <typename BASE_TYPE>
	D_FORCE_INLINE bool IsChildOf() const
	{
		static_assert(IS_DOBJECT_TYPE(BASE_TYPE));

		const bool isChild = (GetBaseChainCount() >= BASE_TYPE::BASE_CHAIN_COUNT_STATIC()) && (GetBaseChainData()[GetBaseChainCount() - BASE_TYPE::BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::CLASS_TYPE_ID_STATIC());

		return isChild;
	}

};



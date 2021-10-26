#include <cassert>

#include "../FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS.h"
#include "../FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_Globals.h"

class B : public FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(B, FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS)
};

class C : public B
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(C, B)

public:
	virtual void Do(){}
};

class D : public C
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(D, C)
};

class E : public C
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(E, C)
};



int main()
{
	FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS* dObjectC = new C();
	C* cc = new C();
	FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS* dObjectD = new D();
	D* dd = new D();

	assert(dObjectC->IsChildOf<B>() == true);
	assert(dObjectC->IsChildOf<C>() == true);
	assert(dObjectC->IsChildOf<D>() == false);

	assert(fast_cast::IsChildOf<B>(dObjectC) == true);
	assert(fast_cast::IsChildOf<C>(dObjectC) == true);
	assert(fast_cast::IsChildOf<D>(dObjectC) == false);

	assert(cc->IsChildOf<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS>() == true);
	assert(cc->IsChildOf<B>() == true);

	assert(dObjectC->IsChildOf<D>() == false);
	assert(cc->IsChildOf<D>() == false);

	assert(fast_cast::CastTo<C*>(dObjectC) != nullptr);
	assert(fast_cast::CastTo<D*>(dObjectC) == nullptr);

	assert(fast_cast::CastTo<FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS*>(cc) != nullptr); // Be Cast at compile time
	assert(fast_cast::CastTo<C*>(cc) != nullptr); // Be Cast at compile time
	assert(fast_cast::CastTo<D*>(cc) == nullptr); 
	assert(fast_cast::CastTo<D*>(dd) != nullptr); // Be Cast at compile time
	
}
#include <cassert>

#include "../DObject.h"
#include "../DObjectGlobals.h"

class B : public DObject
{
	DOBJECT_CLASS_BODY(B)
	DOBJECT_CLASS_BASE_CHAIN(DObject)
};

class C : public B
{
	DOBJECT_CLASS_BODY(C)
	DOBJECT_CLASS_BASE_CHAIN(B)
};

class D : public C
{
	DOBJECT_CLASS_BODY(D)
	DOBJECT_CLASS_BASE_CHAIN(C)
};

int main()
{
	DObject* dObjectC = new C();
	C* cc = new C();
	DObject* dObjectD = new D();
	D* dd = new D();

	assert(dObjectC->IsChildOf<B>() == true);
	assert(dObjectC->IsChildOf<C>() == true);
	
	assert(cc->IsChildOf<DObject>() == true);
	assert(cc->IsChildOf<B>() == true);

	assert(dObjectC->IsChildOf<D>() == false);
	assert(cc->IsChildOf<D>() == false);

	assert(CastTo<C*>(dObjectC) != nullptr);
	assert(CastTo<D*>(dObjectC) == nullptr);

	assert(CastTo<DObject*>(cc) != nullptr); // Be Cast at compile time
	assert(CastTo<C*>(cc) != nullptr); // Be Cast at compile time
	assert(CastTo<D*>(cc) == nullptr); 
	assert(CastTo<D*>(dd) != nullptr); // Be Cast at compile time
	
}
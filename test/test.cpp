#include <cassert>

#include "../FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_Globals.h"

class B
{
	FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY(B)

};

class C : public B
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(C, B)

public:
	virtual void Do(){}
};

class D : public virtual C
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(D, C)
};

class E : public virtual C
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(E, C)
};

class F : public virtual D, public virtual E
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(F, D, E)
};

class G : public F
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(G, F)
};

int main()
{
	B* dObjectC = new C();
	C* cc = new C();
	B* dObjectD = new D();
	D* dd = new D();

	assert(dObjectC->IsChildOf<B>() == true);
	assert(dObjectC->IsChildOf<C>() == true);
	assert(dObjectC->IsChildOf<D>() == false);

	assert(fast_cast::IsChildOf<B>(dObjectC) == true);
	assert(fast_cast::IsChildOf<C>(dObjectC) == true);
	assert(fast_cast::IsChildOf<D>(dObjectC) == false);
	
	assert(cc->IsChildOf<B>() == true);

	assert(dObjectC->IsChildOf<D>() == false);
	assert(cc->IsChildOf<D>() == false);

	assert(fast_cast::CastTo<C*>(dObjectC) != nullptr);
	assert(fast_cast::CastTo<D*>(dObjectC) == nullptr);
	
	assert(fast_cast::CastTo<C*>(cc) != nullptr); // Be Cast at compile time
	assert(fast_cast::CastTo<D*>(cc) == nullptr); 
	assert(fast_cast::CastTo<D*>(dd) != nullptr); // Be Cast at compile time

	assert(fast_cast::CastTo<D*>(dd) != nullptr); // Be Cast at compile time

	static_assert(C::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false); // Be Cast at compile time
	static_assert(D::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false); // Be Cast at compile time
	static_assert(E::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == false); // Be Cast at compile time
	static_assert(F::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == true); // Be Cast at compile time
	static_assert(G::__FAST_RUNTIME_TYPE_CASTING_HAVE_MULTIPLE_INHERITANCE == true); // Be Cast at compile time


	D* dObjectD_multiple_inheritance = new G();
	assert(fast_cast::CastTo<G*>(dObjectD_multiple_inheritance) != nullptr); 
	assert(dObjectD_multiple_inheritance->__FAST_RUNTIME_TYPE_CASTING_GET_BASE_CHAIN_DATA()[0] == nullptr);
	assert(fast_cast::CastTo<G*>(dObjectD_multiple_inheritance) == dynamic_cast<G*>(dObjectD_multiple_inheritance)); 
	assert(dObjectD_multiple_inheritance->IsChildOf<F>() == true);
	assert(dObjectD_multiple_inheritance->IsChildOf<D>() == true);
	assert(dObjectD_multiple_inheritance->IsChildOf<E>() == true);
	assert(dObjectD_multiple_inheritance->IsChildOf<G>() == true);



	G* dObjectG_multiple_inheritance = new G();
	assert(fast_cast::CastTo<D*>(dObjectG_multiple_inheritance) != nullptr);
	assert(fast_cast::CastTo<D*>(dObjectG_multiple_inheritance) == dynamic_cast<D*>(dObjectG_multiple_inheritance)); 
	assert(dynamic_cast<C*>(dObjectG_multiple_inheritance));
}
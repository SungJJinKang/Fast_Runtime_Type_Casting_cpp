# Fast Runtime Type Casting

This library give you C++ Fast Runtime Type Casting faster than dynamic_cast ( inspired by Unreal Engine's Type Casting ).          

This library is for explaining algorithm.            
Template codes in this library may make build time slow. So I don't recommend using this library in your project.      

So I applied this algorithm to [my game engine project](https://github.com/SungJJinKang/DoomsEngine) using [reflection system](https://github.com/SungJJinKang/clReflect_ForDoomsEngine).            
It doesn't require template codes and bothersome macros.      
Reflection system automatically generate datas for this algorithm. ( ex. check "BASE_CHAIN_LIST" data https://github.com/SungJJinKang/clReflect_ForDoomsEngine/blob/doom_engine_version/src/clReflectScan/example/PlainComponent.reflection.h. if you have used unreal engine, you can see same thing in generated.h file )            

[한국어 블로그](https://sungjjinkang.github.io/computerscience/c++/2021/10/24/fast_dynamic_cast.html)

## Features

1. Fast Dynamic Cast
2. No Runtime Overhead for storing class hierarchy information. ( Class Hierarchy Information is evaluated at compile time and stored in exe, dll file ). 
3. Support multiple inheritance
4. No requirement for external tools.
5. Portable

( This library use a lot of template codes to generate datas for fast type casting. But Don't worry the template codes will be removed from object file. Because it's declared with internal linking option and it's called only at compile time ) 

## How Works


### If Class doesn't have multiple inheritance in its class hierarchy ( Best Case, Always fast )

1. Every Class's class hierarchy data is evaluated at compile time and stored as static variable in the class
```
1. Current Class's Hierarchy Depth ( ex) Root Class have value 1, Root Class's Child Class have value 2. ..... )
2. Current Class's Hierarchy Data Container ( Every class have this as static variable ) : [ Current Class TypeID ] [ Current Class's Parent Class TypeID ] [ Parent Class's Parent Class TypeID ] .... [ Root Class Type ID ]
```


2. At Run time, Use class hierarchy data to check if can type cast
```
Cast Object A's Pointer Type T ( Polymorphic ) to Type Q.

First. If Pointer Type T is child class type of Type Q or trying to same type, Cast it to Type Q without any checking mechanism ( at compile time )
Second. If not, check if " Object A's Hierarchy Depth ( get with virtual fucntion ) <( more deep ) Type Q's Hierarchy Depth ". If yes, Casting always fail and return nullptr.
Third. If not, Check if " Object A's Hierarchy Data Container[ Object A's Hierarchy Depth - Type Q's Hierarchy Depth ] == Type Q's TypeID. If yse, Casting success. Or Casting Fail and return nullptr.
```

### If Class has(!) multiple inheritance in its class hierarchy ( sometimes use dynamic_cast -> sometimes slow )

This algorithm is used [https://github.com/tobspr/FastDynamicCast](https://github.com/tobspr/FastDynamicCast)

## HOW TO USE
```
class A
{
	FAST_RUNTIME_TYPE_CASTING_ROOT_CLASS_BODY(A)
};

class B : public virtual A
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(B, A)
};

class C : public virtual A
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(C, A)
};

class D : public virtual B, public virtual C
{
	FAST_RUNTIME_TYPE_CASTING_CLASS_BODY(D, B, C)
};

A* object = new D();

D* Dobject = fast_cast::CastTo<D*>(object);
if(object->IsChildOf<D>() == true)
{
	~~
}
```

## Limitations

- Require at least C++17

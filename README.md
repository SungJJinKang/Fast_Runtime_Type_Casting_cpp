# Fast Runtime Type Casting

This Library give you C++ Fast Runtime Type Casting faster than dynamic_cast.         
You don't need RTTI compiler option.         
You can apply this library to your project with only two code lines for each class.        

[https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/DObject](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/DObject)

## Features

1. Fast Dynamic Cast ( similar to Unreal Engine's CastTo )
2. No Runtime Overhead for evaluating Class hierarchy information. ( Class Hierarchy Information is evaluated at compile time ) 

## How Works

1. At Compile time, Every Class evaluate class hierarchy data at compile time.
```
1. Current Class's Hierarchy Depth ( ex) Root Class have value 1, Root Class's Child Class have value 2. ..... )
2. Current Class's Hierarchy Data Container ( Every class have this as static variable ) : [ Current Class TypeID ] [ Current Class's Parent Class TypeID ] [ Parent Class's Parent Class TypeID ] .... [ Root Class Type ID ]
```


2. At Run time, Use this data for check if a object if child class of any class.
```
Cast Object A's Pointer Type T ( Polymorphic ) to Type Q.

First. If Pointer Type T is child class type of Type Q or trying to same type, Cast it to Type Q without any checking mechanism ( at compile time )
Second. If not, check if " Object A's Hierarchy Depth ( get with virtual fucntion ) <( more deep ) Type Q's Hierarchy Depth ". If yes, Casting always fail and return nullptr.
Third. If not, Check if " Object A's Hierarchy Data Container[ Object A's Hierarchy Depth - Type Q's Hierarchy Depth ] == Type Q's TypeID. If yse, Casting success. Or Casting Fail and return nullptr.

```

## HOW TO USE
```
class MeshCollider : public Collider3DComponent
{
	DOBJECT_CLASS_BODY(MeshCollider) <- Put Current Class Name
	DOBJECT_CLASS_BASE_CHAIN(Collider3DComponent) <- Put Parent Class Name
}

Collider3DComponent* object = ~~;
MeshCollider* meshCol = CastTo<MeshCollider*>(object);
if(meshCol != nullptr)
{
	~~
}
```

## Limitation

- This library require more than C++17.
- Every Class should be derived from one root class ( DObject ) ( similar to Unreal Engine's UObject )

[한국어 블로그](https://sungjjinkang.github.io/computerscience/2021/10/20/Reflection.html)

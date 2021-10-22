# Fast Runtime Type Casting

This Library give you C++ Fast Runtime Type Casting faster than dynamic_cast.         
You don't need RTTI compiler option.         
You can apply this library to your project with only two code lines for each class.        

## Features

1. Fast Dynamic Cast ( similar to Unreal Engine's CastTo )
2. No Runtime Overhead for evaluating Class hierarchy information. ( Class Hierarchy Information is evaluated at compile time ) 

## Performance

<img width="437" alt="20211023013700" src="https://user-images.githubusercontent.com/33873804/138491569-e507bfb8-be3b-4d3e-989e-54abe565a927.png">

Fast Runtime Type Casting is 2.0x faster than dynamic_cast.

## How Works

1. Every Class's class hierarchy data is evaluated at compile time.
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

## HOW TO USE
```
class Collider3DComponent : public DObject
{
	DOBJECT_CLASS_BODY(Collider3DComponent) <- Put Current Class Name
	DOBJECT_CLASS_BASE_CHAIN(DObject) <- Put Parent Class Name
}
class MeshCollider : public Collider3DComponent
{
	DOBJECT_CLASS_BODY(MeshCollider) <- Put Current Class Name
	DOBJECT_CLASS_BASE_CHAIN(Collider3DComponent) <- Put Parent Class Name
}

Collider3DComponent* object = new MeshCollider();

MeshCollider* meshCol = CastTo<MeshCollider*>(object);

if(object->IsChildOf<MeshCollider>() == true)
{
	~~
}
```

## Limitation

- This library require at least C++17.
- Every Class should be derived from one root class ( DObject ) ( similar to Unreal Engine's UObject )     
- Can do type cast only between classes derived from DObject root class   


[한국어 블로그](https://sungjjinkang.github.io/computerscience/2021/10/20/Reflection.html)

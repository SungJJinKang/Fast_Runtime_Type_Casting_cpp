# DoomsReflection_cpp

This Library give you C++ Reflection System.          
You can apply this library to your project with only two code lines

[https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/DObject](https://github.com/SungJJinKang/DoomsEngine/tree/main/Doom3/Source/Core/DObject)

## Features

1. All Reflection Datas is evaluated at Compile time! ( No Rumtime Overhead )
2. Fast Dynamic Cast ( similar to Unreal Engine's CastTo )


## Current 

## HOW TO USE
```
class MeshCollider : public Collider3DComponent
{
	DOBJECT_CLASS_BODY(MeshCollider) <- Put Current Class Name
	DOBJECT_CLASS_BASE_CHAIN(Collider3DComponent) <- Put Parent Class Name
}
```

## Limitation

Every Class should be derived from one root class ( DObject ) ( similar to Unreal Engine's UObject )

[한국어 블로그](https://sungjjinkang.github.io/computerscience/2021/10/20/Reflection.html)

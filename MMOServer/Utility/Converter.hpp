#pragma once

#include "generated/mmo/Protocol.gen.hpp"

class Converter
{
public:
	template<class T>
	static gen::mmo::Vector2 MakeVector(Vector2D<T> v)
	{
		gen::mmo::Vector2 t;
		t.x = static_cast<float>(v.x);
		t.y = static_cast<float>(v.y);
		return t;
	}
	template<class T>
	static Vector2D<T> MakeVector(gen::mmo::Vector2 v)
	{
		Vector2D<T> t;
		t.x = static_cast<T>(v.x);
		t.y = static_cast<T>(v.y);
		return t;
	}
	template<class T>
	static gen::mmo::Vector3 MakeVector(Vector3D<T> v)
	{
		gen::mmo::Vector3 t;
		t.x = static_cast<float>(v.x);
		t.y = static_cast<float>(v.y);
		t.z = static_cast<float>(v.z);
		return t;
	}
	template<class T>
	static Vector3D<T> MakeVector(gen::mmo::Vector3 v)
	{
		Vector3D<T> t;
		t.x = static_cast<T>(v.x);
		t.y = static_cast<T>(v.y);
		t.z = static_cast<T>(v.z);
		return t;

	}
};


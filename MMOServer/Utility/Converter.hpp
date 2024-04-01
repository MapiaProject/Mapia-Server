#pragma once

#include "generated/mmo/Protocol.gen.hpp"

class Converter
{
public:
	template<class T>
	static gen::mmo::Vector2 MakeVector(Vector2D<T> v)
	{
		gen::mmo::Vector2 t;
		t.x = v.GetX();
		t.y = v.GetY();
		return t;
	}
	template<class T>
	static Vector2D<T> MakeVector(gen::mmo::Vector2 v)
	{
		Vector2D<T> t;
		t.SetX(v.x);
		t.SetY(v.y);
		return t;
	}
	template<class T>
	static gen::mmo::Vector3 MakeVector(Vector3D<T> v)
	{
		gen::mmo::Vector3 t;
		t.x = v.GetX();
		t.y = v.GetY();
		t.z = v.GetZs();
		return t;
	}
	template<class T>
	static Vector3D<T> MakeVector(gen::mmo::Vector3 v)
	{
		Vector3D<T> t;
		t.SetX(v.x);
		t.SetY(v.y);
		t.SetZ(v.z);
		return t;

	}
};


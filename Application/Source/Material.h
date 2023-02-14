#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

struct Component
{
	float r, g, b;
	Component(float r, float g, float b) : r(0.1f), g(0.1f), b(0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
	Component& operator=(const Component& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		return *this;
	}

};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	unsigned size;


	Material() :
		kAmbient(0.0f, 0.0f, 0.0f), kDiffuse(0.0f, 0.0f, 0.0f), kSpecular(0.0f, 0.0f, 0.0f), kShininess(1.f), size(0)

	{
	}
	Material& operator=(const Material& rhs)
	{
		kAmbient = rhs.kAmbient;
		kDiffuse = rhs.kDiffuse;
		kSpecular = rhs.kSpecular;
		kShininess = rhs.kShininess;
		size = rhs.size;
		return *this;
	}
};


#endif

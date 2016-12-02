#pragma once

namespace JF
{
namespace Light
{

enum class LightType
{
	Directional,
	Point,
	Spot,
};

struct BasicLight
{
public:
	BasicLight() { ZeroMemory(this, sizeof(this)); }

public:
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
};

// Note: Make sure structure alignment agrees with HLSL structure padding rules. 
//   Elements are packed into 4D vectors with the restriction that an element
//   cannot straddle a 4D vector boundary.

struct DirectionalLight : BasicLight
{
public:
	DirectionalLight() { ZeroMemory(this, sizeof(this)); }
	
public:
	XMFLOAT3 Direction;
	float Pad; // Pad the last float so we can set an array of lights if we wanted.
};

struct PointLight : BasicLight
{
public:
	PointLight() { ZeroMemory(this, sizeof(this)); }

public:
	// Packed into 4D vector: (A0, A1, A2, Range)
	XMFLOAT3 Att;
	float Range;
};

struct SpotLight : BasicLight
{
public:
	SpotLight() { ZeroMemory(this, sizeof(this)); }

public:
	// Packed into 4D vector: (Direction, Spot)
	XMFLOAT3 Direction;
	float Spot;

	// Packed into 4D vector: (Att, Pad)
	XMFLOAT3 Att;
	float Range;
};

struct Material
{
	Material() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular; // w = SpecPower
	XMFLOAT4 Reflect;
};

}
}
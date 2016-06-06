#pragma once

namespace Jaraffe
{
namespace Vertex
{
	// Simple 24Byte Struct
	struct Simple
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	struct PosNormal
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
	};

	// Basic 32Byte Struct
	struct Basic32
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT3 Tex;
	};
}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC Simple[2];
	static const D3D11_INPUT_ELEMENT_DESC PosNormal[2];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* Simple;
	static ID3D11InputLayout* PosNormal;
};

}
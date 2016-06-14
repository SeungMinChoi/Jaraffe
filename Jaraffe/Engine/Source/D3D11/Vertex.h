#pragma once

namespace Jaraffe
{
namespace Vertex
{
	enum class VertexType
	{
		PosColor,
		PosNormalTex,
	};

	struct BasicVertex
	{
		BasicVertex(){}
	};

	// PosColor 24Byte Struct
	struct PosColor : BasicVertex
	{
		PosColor(XMFLOAT3 pos, XMFLOAT4 color)
			: BasicVertex()
		{
			Pos		= pos;
			Color	= color;
		}

		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	// Basic 32Byte Struct
	struct PosNormalTex : BasicVertex
	{
		PosNormalTex(XMFLOAT3 pos, XMFLOAT3 normal, XMFLOAT2 tex)
			: BasicVertex()
		{
			Pos		= pos;
			Normal	= normal;
			Tex		= tex;
		}

		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
	};
}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC PosColor[2];
	static const D3D11_INPUT_ELEMENT_DESC PosNormalTex[3];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* PosColor;
	static ID3D11InputLayout* PosNormalTex;
};

}
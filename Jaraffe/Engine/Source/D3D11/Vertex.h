#pragma once

namespace Jaraffe
{
namespace Vertex
{
	enum class VertexType
	{
		PosColor,
		PosNormal,
		PorNormalTex,
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

	struct PosNormal : BasicVertex
	{
		PosNormal(XMFLOAT3 pos, XMFLOAT3 normal)
			: BasicVertex()
		{
			Pos		= pos;
			Normal	= normal;
		}

		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
	};

	// Basic 32Byte Struct
	struct PorNormalTex : BasicVertex
	{
		PorNormalTex(XMFLOAT3 pos, XMFLOAT3 normal, XMFLOAT3 tex)
			: BasicVertex()
		{
			Pos		= pos;
			Normal	= normal;
			Tex		= tex;
		}

		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT3 Tex;
	};
}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC PosColor[2];
	static const D3D11_INPUT_ELEMENT_DESC PosNormal[2];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* PosColor;
	static ID3D11InputLayout* PosNormal;
};

}
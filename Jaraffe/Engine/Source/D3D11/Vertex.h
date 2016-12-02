#pragma once

namespace JF
{
namespace Vertex
{
	enum class VertexType
	{
		Position,
		PosColor,
		PosNormalTex,
		PosNormalTexTan,
	};

	struct BasicVertex
	{
		BasicVertex(){}
	};

	struct Position : BasicVertex
	{
		Position() : BasicVertex() {}
		Position(XMFLOAT3 pos)
			: BasicVertex(), Pos(pos) {}
		Position(float px, float py, float pz)
			: BasicVertex(), Pos(px, py, pz) {}

		XMFLOAT3 Pos;
	};

	// PosColor 24Byte Struct
	struct PosColor : BasicVertex
	{
		PosColor() : BasicVertex(){}
		PosColor(XMFLOAT3 pos, XMFLOAT4 color)
			: BasicVertex(), Pos(pos), Color(color){}
		PosColor(float px, float py, float pz,
				 float cr, float cg, float cb, float ca)
			: BasicVertex(), Pos(px, py, pz), Color(cr, cg, cb, ca) {}

		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	// Basic 32Byte Struct
	struct PosNormalTex : BasicVertex
	{
		PosNormalTex() : BasicVertex() {}
		PosNormalTex(XMFLOAT3 pos, XMFLOAT3 normal, XMFLOAT2 tex)
			: BasicVertex(),
			Pos(pos), Normal(normal), Tex(tex) {}
		PosNormalTex(XMFLOAT3& pos, XMFLOAT3& normal, XMFLOAT2& tex)
			: BasicVertex(),
			Pos(pos), Normal(normal), Tex(tex)	{}
		PosNormalTex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float u, float v)
			: BasicVertex(), 
			Pos(px, py, pz), Normal(nx, ny, nz), Tex(u, v) {}

		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
	};

	// Basic 48Byte Struct
	struct PosNormalTexTan : BasicVertex
	{
		PosNormalTexTan() : BasicVertex() {}
		PosNormalTexTan(XMFLOAT3 pos, XMFLOAT3 normal, XMFLOAT2 tex, XMFLOAT4 tan)
			: BasicVertex(),
			Pos(pos), Normal(normal), Tex(tex), Tan(tan) {}
		PosNormalTexTan(XMFLOAT3& pos, XMFLOAT3& normal, XMFLOAT2& tex, XMFLOAT4& tan)
			: BasicVertex(),
			Pos(pos), Normal(normal), Tex(tex), Tan(tan) {}
		PosNormalTexTan(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float u, float v,
			float tx, float ty, float tz, float tw)
			: BasicVertex(),
			Pos(px, py, pz), Normal(nx, ny, nz), Tex(u, v), Tan(tx, ty, tz, tw) {}

		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
		XMFLOAT4 Tan;
	};
}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC Position[1];
	static const D3D11_INPUT_ELEMENT_DESC PosColor[2];
	static const D3D11_INPUT_ELEMENT_DESC PosNormalTex[3];
	static const D3D11_INPUT_ELEMENT_DESC PosNormalTexTan[4];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* Position;
	static ID3D11InputLayout* PosColor;
	static ID3D11InputLayout* PosNormalTex;
	static ID3D11InputLayout* PosNormalTexTan;
};

}
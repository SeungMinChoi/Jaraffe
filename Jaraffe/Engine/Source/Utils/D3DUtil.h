#pragma once

namespace Jaraffe
{
namespace Util
{

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };

	XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
}

namespace Mesh
{
	static void CreateVertexBuffer(void* p_pVertices, UINT p_ByteWidth, ID3D11Buffer** p_pVB)
	{
		// Check
		assert(p_pVertices != nullptr);

		//
		D3D11_BUFFER_DESC vbd;
		vbd.Usage				= D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth			= p_ByteWidth;
		vbd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags		= 0;
		vbd.MiscFlags			= 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = p_pVertices;

		// Create
		HR(gRENDERER->GetDevice()->CreateBuffer(&vbd, &vinitData, p_pVB));
	}

	static void CreateIndexBuffer(void* p_pIndices, UINT p_ByteWidth, ID3D11Buffer** p_pIB)
	{
		assert(p_pIndices != nullptr);

		D3D11_BUFFER_DESC vbd;
		vbd.Usage				= D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth			= p_ByteWidth;
		vbd.BindFlags			= D3D11_BIND_INDEX_BUFFER;
		vbd.CPUAccessFlags		= 0;
		vbd.MiscFlags			= 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = p_pIndices;

		HR(gRENDERER->GetDevice()->CreateBuffer(&vbd, &vinitData, p_pIB));
	}
}

class MyDirectUtil
{
public:
	MyDirectUtil() {};
	virtual ~MyDirectUtil() {};
};

}
}
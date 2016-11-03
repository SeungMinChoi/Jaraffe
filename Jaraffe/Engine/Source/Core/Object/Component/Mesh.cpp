#include "stdafx.h"
#include "Mesh.h"

DECLARE_IDENTIFIER(Jaraffe::Component::Mesh);

Jaraffe::Component::Mesh::Mesh()
{

}

Jaraffe::Component::Mesh::~Mesh()
{

}

void Jaraffe::Component::Mesh::Init()
{
	float w2 = 0.5f*5.0f;
	float h2 = 0.5f*5.0f;
	float d2 = 0.5f*5.0f;

	// Temp Box
	Jaraffe::Vertex::PosNormalTex v[] =
	{
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, +h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, +h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, -h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f)),

		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, -h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, -h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, +h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, +h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),

		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, +h2, -d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, +h2, +d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, +h2, +d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, +h2, -d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f)),

		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, -h2, -d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, -h2, +d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, -h2, +d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)),

		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, -h2, +d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, +h2, +d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, +h2, -d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f)),

		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, -h2, -d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, +h2, -d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, +h2, +d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)),
		Jaraffe::Vertex::PosNormalTex(XMFLOAT3(+w2, -h2, +d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f))
	};

	m_pVertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	m_pIndices.assign(&i[0], &i[36]);

	// 1)
	m_VertexType	= Jaraffe::Vertex::VertexType::PosNormalTex;
	m_pInputLayout	= InputLayouts::PosNormalTex;
	m_Stride		= sizeof(Vertex::PosNormalTex);
	m_IndexCount	= 36;

	// 2) VertexBuffer Create
	Jaraffe::Util::Mesh::CreateVertexBuffer(&m_pVertices[0], m_Stride * 24, &m_pVB);

	// 3) Create Indices
	Jaraffe::Util::Mesh::CreateIndexBuffer(&m_pIndices[0], sizeof(UINT) * 36, &m_pIB);
}

void Jaraffe::Component::Mesh::Release()
{
	ReleaseCOM(m_pVB);
	ReleaseCOM(m_pIB);
}
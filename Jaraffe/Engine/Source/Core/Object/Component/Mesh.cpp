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
	// 1)
	m_pInputLayout	= InputLayouts::PosNormalTex;
	m_Stride		= sizeof(Vertex::PosNormalTex);
	m_VertexCount	= m_pVertices.size();
	m_IndexCount	= m_pIndices.size();

	// 2) VertexBuffer Create
	Jaraffe::Util::Mesh::CreateVertexBuffer(&m_pVertices[0], m_Stride * m_VertexCount, &m_pVB);

	// 3) Create Indices
	Jaraffe::Util::Mesh::CreateIndexBuffer(&m_pIndices[0], sizeof(UINT) * m_IndexCount, &m_pIB);
}

void Jaraffe::Component::Mesh::Release()
{
	ReleaseCOM(m_pVB);
	ReleaseCOM(m_pIB);
}
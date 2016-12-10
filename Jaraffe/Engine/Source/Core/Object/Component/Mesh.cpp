#include "stdafx.h"
#include "Mesh.h"

DECLARE_IDENTIFIER(JF::Component::Mesh);

JF::Component::Mesh::Mesh()
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&m_TexTransform, I);
}

JF::Component::Mesh::~Mesh()
{

}

void JF::Component::Mesh::Reset()
{
	// 1)
	m_pInputLayout	= InputLayouts::PosNormalTexTan;
	m_Stride		= sizeof(Vertex::PosNormalTexTan);
	m_VertexCount	= (UINT)m_pVertices.size();
	m_IndexCount	= (UINT)m_pIndices.size();

	// 2) VertexBuffer Create
	gRENDERER->CreateVertexBuffer(&m_pVertices[0], m_Stride * m_VertexCount, &m_pVB);

	// 3) Create Indices
	gRENDERER->CreateIndexBuffer(&m_pIndices[0], sizeof(UINT) * m_IndexCount, &m_pIB);
}

void JF::Component::Mesh::Release()
{
	ReleaseCOM(m_pVB);
	ReleaseCOM(m_pIB);
}
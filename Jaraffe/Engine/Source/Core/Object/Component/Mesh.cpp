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
	Jaraffe::Vertex::Simple v[] =
	{
		XMFLOAT3(-w2, -h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, +h2, -d2), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, +h2, -d2), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
		XMFLOAT3(+w2, -h2, -d2), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
													  
		XMFLOAT3(-w2, -h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, -h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, +h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, +h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
												  
		XMFLOAT3(-w2, +h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, +h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, +h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, +h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
												
		XMFLOAT3(-w2, -h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, -h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, -h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, -h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
												
		XMFLOAT3(-w2, -h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, +h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, +h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(-w2, -h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		
		XMFLOAT3(+w2, -h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, +h2, -d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, +h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(+w2, -h2, +d2), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
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

	// 1) VertexBuffer Create
	Jaraffe::Util::Mesh::CreateVertexBuffer<Jaraffe::Vertex::Simple>(&m_pVertices[0], 24, &m_VB);

	// 2) Create Indices
	Jaraffe::Util::Mesh::CreateIndexBuffer<UINT>(&m_pIndices[0], 36, &m_IB);
}

void Jaraffe::Component::Mesh::Update()
{
}

void Jaraffe::Component::Mesh::Render()
{
	Transform* transform = GetOwner()->GetComponent<Jaraffe::Component::Transform>();

	// Set Layout And Topology
	gRENDERER->GetDC()->IASetInputLayout(InputLayouts::Simple);
	gRENDERER->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = sizeof(Vertex::Simple);
	UINT offset = 0;
	gRENDERER->GetDC()->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset);
	gRENDERER->GetDC()->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0);

	// worldViewProj 행렬을 구한다.
	XMMATRIX world	= XMLoadFloat4x4(&transform->GetTransformMatrix());
	XMMATRIX view	= Camera::g_pMainCamera->GetView();
	XMMATRIX proj	= Camera::g_pMainCamera->GetProj();
	XMMATRIX worldViewProj = world * view * proj;

	// 셰이더에 상수값 설정.
	Effects::SimpleFX->SetWorldViewProj(worldViewProj);

	ID3DX11EffectTechnique* tech = Effects::SimpleFX->ColorTech;
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, gRENDERER->GetDC());

		// 색인 36개로 상자를 그린다.
		gRENDERER->GetDC()->DrawIndexed(36, 0, 0);
	}
}

void Jaraffe::Component::Mesh::Receve()
{

}

void Jaraffe::Component::Mesh::Release()
{
	ReleaseCOM(m_VB);
	ReleaseCOM(m_IB);
}
#include "stdafx.h"
#include "CubeMap.h"

DECLARE_IDENTIFIER(Jaraffe::Component::CubeMap);

Jaraffe::Component::CubeMap::CubeMap(float _skySphereRadius, Jaraffe::Texture* _pTexture)
{
	m_SkySphereRadius	= _skySphereRadius;
	m_pMainTexture		= _pTexture;
}

Jaraffe::Component::CubeMap::~CubeMap()
{
}

void Jaraffe::Component::CubeMap::Init()
{
	// 1)
	GeometryGenerator::CreateSphere(m_SkySphereRadius, 30, 30, m_pVertices, m_pIndices);

	// 2) Mesh Setting)
	Mesh::Init();
}

void Jaraffe::Component::CubeMap::Render()
{
	// Declear)
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// 
	Transform* cameraTranfrom = Camera::g_pMainCamera->GetOwner()->GetComponent<Jaraffe::Component::Transform>();
	if (cameraTranfrom == nullptr)
		return;

	// Set Layout And Topology
	gRENDERER->GetDC()->IASetInputLayout(m_pInputLayout);
	gRENDERER->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = m_Stride;
	UINT offset = 0;
	gRENDERER->GetDC()->IASetVertexBuffers(0, 1, &m_pVB, &stride, &offset);
	gRENDERER->GetDC()->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0);

	// center Sky about eye in world space
	XMFLOAT3 eyePos = cameraTranfrom->GetPosition();
	XMMATRIX T = XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z);

	XMMATRIX WVP = XMMatrixMultiply(T, Camera::g_pMainCamera->GetViewProj());
	Effects::CubeMapFX->SetWorldViewProj(WVP);
	Effects::CubeMapFX->SetCubeMap(m_pMainTexture->GetTexture());

	ID3DX11EffectTechnique* tech = Effects::CubeMapFX->SkyTech;
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, gRENDERER->GetDC());

		gRENDERER->GetDC()->DrawIndexed(m_IndexCount, 0, 0);
	}

	// 기본 랜더상태로 복원한다.
	gRENDERER->GetDC()->RSSetState(0);
	gRENDERER->GetDC()->OMSetBlendState(0, blendFactors, 0xffffffff);
}
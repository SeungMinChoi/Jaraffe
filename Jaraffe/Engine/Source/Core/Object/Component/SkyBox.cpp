#include "stdafx.h"
#include "SkyBox.h"

DECLARE_IDENTIFIER(JF::Component::SkyBox);

JF::Component::SkyBox::SkyBox(float _skySphereRadius, JF::Texture* _pTexture)
{
	m_SkySphereRadius	= _skySphereRadius;
	m_pMainTexture		= _pTexture;
}

JF::Component::SkyBox::~SkyBox()
{
}

void JF::Component::SkyBox::Reset()
{
	// 1)
	GeometryGenerator::CreateSphere(m_SkySphereRadius, 30, 30, m_pVertices, m_pIndices);

	// 2) Mesh Setting)
	Mesh::Reset();
}

void JF::Component::SkyBox::Render()
{
	// Declear)
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// 컴포넌트에 카메라가 없거나 메인카메라가 아니라면 패스.
	Camera* pCamera = GetOwner()->GetComponent<Camera>();
	if (pCamera == nullptr || Camera::g_pMainCamera != pCamera)
		return;

	// 
	Transform* pTransform = GetOwner()->GetComponent<Transform>();
	if (pTransform == nullptr)
		return;

	// Set Layout And Topology
	gRENDERER->DeviceContext()->IASetInputLayout(m_pInputLayout);
	gRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = m_Stride;
	UINT offset = 0;
	gRENDERER->DeviceContext()->IASetVertexBuffers(0, 1, &m_pVB, &stride, &offset);
	gRENDERER->DeviceContext()->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0);

	// center Sky about eye in world space
	XMFLOAT3 eyePos = pTransform->GetPosition();
	XMMATRIX T = XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z);

	XMMATRIX WVP = XMMatrixMultiply(T, pCamera->GetViewProj());
	Effects::CubeMapFX->SetWorldViewProj(WVP);
	Effects::CubeMapFX->SetCubeMap(m_pMainTexture->GetTexture());

	ID3DX11EffectTechnique* tech = Effects::CubeMapFX->SkyTech;
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, gRENDERER->DeviceContext());

		gRENDERER->DeviceContext()->DrawIndexed(m_IndexCount, 0, 0);
	}

	// 기본 랜더상태로 복원한다.
	gRENDERER->DeviceContext()->RSSetState(0);
	gRENDERER->DeviceContext()->OMSetBlendState(0, blendFactors, 0xffffffff);
}
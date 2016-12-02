#include "stdafx.h"
#include "MeshRenderer.h"

DECLARE_IDENTIFIER(JF::Component::MeshRenderer);

JF::Component::MeshRenderer::MeshRenderer()
{
}

JF::Component::MeshRenderer::~MeshRenderer()
{
}

void JF::Component::MeshRenderer::Init()
{

}

void JF::Component::MeshRenderer::Update(float t)
{

}

void JF::Component::MeshRenderer::Render()
{
	/*
	
	// Declear)
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};

	// Get)
	auto* pTransform	= GetOwner()->GetComponent<JF::Component::Transform>();
	auto* pMesh			= GetOwner()->GetComponent<JF::Component::Mesh>();
	auto* pMarerial		= GetMaterial(); 

	// Check)
	RETURN_IF(pTransform == nullptr,	);
	RETURN_IF(pMesh == nullptr,			);

	// Set Layout And Topology
	gRENDERER->DeviceContext()->IASetInputLayout(pMesh->m_pInputLayout);
	gRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = pMesh->m_Stride;
	UINT offset = 0;
	gRENDERER->DeviceContext()->IASetVertexBuffers(0, 1, &pMesh->m_pVB, &stride, &offset);
	gRENDERER->DeviceContext()->IASetIndexBuffer(pMesh->m_pIB, DXGI_FORMAT_R32_UINT, 0);

	// worldViewProj 행렬을 구한다.
	XMMATRIX world	= XMLoadFloat4x4(&pTransform->GetTransformMatrix());
	XMMATRIX view	= Camera::g_pMainCamera->GetView();
	XMMATRIX proj	= Camera::g_pMainCamera->GetProj();
	XMMATRIX worldViewProj = world * view * proj;

	XMMATRIX worldInvTranspose = JF::Util::MathHelper::InverseTranspose(world);

	// 셰이더에 상수값 설정.
	Effects::BasicFX->SetEyePosW(Camera::g_pMainCamera->GetEyePos());
	Effects::BasicFX->SetDirLights(JF::Component::Light::m_vLights[0]->GetDirectionalLight());		// TODO : 라이팅 리펙토링 1순위. 구조 생각중.

	Effects::BasicFX->SetWorldViewProj(worldViewProj);
	Effects::BasicFX->SetWorld(world);
	Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BasicFX->SetMaterial(pMarerial->m_Material);

	XMMATRIX I = XMMatrixIdentity();
	Effects::BasicFX->SetTexTransform(I);																// TODO : 요건 어디다가 둘지 생각중... 일단은 쓸일이 생기면 머트리얼에 넣을 생각.
	Effects::BasicFX->SetDiffuseMap(pMarerial->m_MainTexture->GetTexture());							// TODO : 텍스쳐 매니져도 아직 초기단계.
	if(pMarerial->m_BumpTexture != nullptr)
		Effects::BasicFX->SetNormalMap(pMarerial->m_BumpTexture->GetTexture());							// TODO : 텍스쳐 매니져도 아직 초기단계.
	Effects::BasicFX->SetTime(0.0f);																	// TODO : 아직 시간 매니져 안만듬.

	// 레스터라이즈 상태를 셋팅한다.
	if(pMarerial->m_RSState != nullptr)
		gRENDERER->DeviceContext()->RSSetState(pMarerial->m_RSState);

	// 블렌드 스테이트 상태를 셋팅한다.
	if(pMarerial->m_BlendState != nullptr)
		gRENDERER->DeviceContext()->OMSetBlendState(pMarerial->m_BlendState, blendFactors, 0xffffffff);

	// 
	ID3DX11EffectTechnique* tech = pMarerial->m_BumpTexture == nullptr ? Effects::BasicFX->Light1TexTech : Effects::BasicFX->Light1TexNorma;
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, gRENDERER->DeviceContext());

		// 색인 36개로 상자를 그린다.
		gRENDERER->DeviceContext()->DrawIndexed(pMesh->m_IndexCount, 0, 0);
	}

	// 기본 랜더상태로 복원한다.
	gRENDERER->DeviceContext()->RSSetState(0);
	gRENDERER->DeviceContext()->OMSetBlendState(0, blendFactors, 0xffffffff);
	*/
}

void JF::Component::MeshRenderer::Release()
{

}
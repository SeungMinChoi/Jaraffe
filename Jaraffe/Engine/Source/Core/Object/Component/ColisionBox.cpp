#include "stdafx.h"
#include "ColisionBox.h"

// Static Member DECLARE
DECLARE_IDENTIFIER(JF::Component::ColisionBox);

JF::Component::ColisionBox::ColisionBox(JF::JFCPhysXDevice* _pxDevice)
{
	m_Center	= XMFLOAT3(0, 0, 0);
	m_Size		= XMFLOAT3(1, 1, 1);

	m_pPXDevice = _pxDevice;
}

JF::Component::ColisionBox::~ColisionBox()
{
}

void JF::Component::ColisionBox::Reset()
{
	// 1) 
	auto* pTransform	= GetOwner()->GetComponent<JF::Component::Transform>();
	XMFLOAT4X4& rMatrix	= pTransform->GetTransformMatrix();

	assert(pTransform != nullptr);

	// 2) 
	m_pShape = m_pPXDevice->GetPhysics()->createShape(
		PxBoxGeometry(m_Size.x, m_Size.y, m_Size.z),
		*m_pPXDevice->GetMaterial());
	
	// 3)
	PxTransform localTm( PxMat44(
		PxVec4(rMatrix._11, rMatrix._12, rMatrix._13, rMatrix._14),
		PxVec4(rMatrix._21, rMatrix._22, rMatrix._23, rMatrix._24),
		PxVec4(rMatrix._31, rMatrix._32, rMatrix._33, rMatrix._34),
		PxVec4(rMatrix._41, rMatrix._42, rMatrix._43, rMatrix._44)
	));

	// 4)
	m_pRigidBody = m_pPXDevice->GetPhysics()->createRigidDynamic(localTm);
	m_pRigidBody->attachShape(*m_pShape);
	PxRigidBodyExt::updateMassAndInertia(*m_pRigidBody, 10.0f);
	m_pRigidBody->setLinearVelocity(PxVec3(0, 10, 2.0f));
	m_pPXDevice->GetScene()->addActor(*m_pRigidBody);

	// 5)
	float cX = 0.0f;
	float cY = 0.0f;
	float cZ = 0.0f;

	float eX = 1.0f;
	float eY = 1.0f;
	float eZ = 1.0f;

	// 정점 
	JF::Vertex::PosColor  vertices[] =
	{
		// 1, 1, 1	(0)
		{ XMFLOAT3(cX + eX, cY + eY, cZ + eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// 1, 1, -1	(1)
		{ XMFLOAT3(cX + eX, cY + eY, cZ + -eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// -1, 1, 1	(2)
		{ XMFLOAT3(cX + -eX, cY + eY, cZ + eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// -1, 1, -1 (3)
		{ XMFLOAT3(cX + -eX, cY + eY, cZ + -eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// 1, -1, 1 (4)
		{ XMFLOAT3(cX + eX, cY + -eY, cZ + eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// 1, -1, -1 (5)
		{ XMFLOAT3(cX + eX, cY + -eY, cZ + -eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// -1, -1, 1 (6)
		{ XMFLOAT3(cX + -eX, cY + -eY, cZ + eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// -1, -1, -1 (7)
		{ XMFLOAT3(cX + -eX, cY + -eY, cZ + -eZ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }
	};
	m_VertexSize = ARRAYSIZE(vertices);

	// 인덱스
	UINT indices[] =
	{
		// Top
		0,1, 1,3, 3,2, 0,2,
		// Bottom
		4,5, 5,7, 7,6, 6,4,
		// Top - Bottom
		0,4, 1,5, 2,6, 3,7
	};
	m_indexCnt = ARRAYSIZE(indices);

	// Create 
	gRENDERER->CreateVertexBuffer(&vertices[0], sizeof(JF::Vertex::PosColor) * m_VertexSize, &m_VertBuff);
	gRENDERER->CreateIndexBuffer(&indices[0], sizeof(UINT) * m_indexCnt, &m_IndexBuff);
}

void JF::Component::ColisionBox::Update(float t)
{

}

void JF::Component::ColisionBox::Render()
{
	// Declear)
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Get)
	auto* pTransform = GetOwner()->GetComponent<JF::Component::Transform>();

	// Check)
	RETURN_IF(pTransform == nullptr, );

	// Set Layout And Topology
	gRENDERER->DeviceContext()->IASetInputLayout(InputLayouts::PosColor);
	gRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = sizeof(JF::Vertex::PosColor);
	UINT offset = 0;
	gRENDERER->DeviceContext()->IASetVertexBuffers(0, 1, &m_VertBuff, &stride, &offset);
	gRENDERER->DeviceContext()->IASetIndexBuffer(m_IndexBuff, DXGI_FORMAT_R32_UINT, 0);

	// worldViewProj 행렬을 구한다.
	XMFLOAT3 rPosition	= XMFLOAT3(pTransform->GetPosition().x + m_Center.x, pTransform->GetPosition().y + m_Center.y, pTransform->GetPosition().z + m_Center.z);
	XMFLOAT3 rScale		= XMFLOAT3(pTransform->GetScale().x * m_Size.x, pTransform->GetScale().y * m_Size.y, pTransform->GetScale().z * m_Size.z);
	XMFLOAT4 rRotation	= pTransform->GetRotation();

	XMMATRIX scl, rot, tsl;
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&rScale));
	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&rRotation));
	tsl = XMMatrixTranslationFromVector(XMLoadFloat3(&rPosition));

	XMMATRIX world = scl*rot*tsl;
	XMMATRIX view = Camera::g_pMainCamera->GetView();
	XMMATRIX proj = Camera::g_pMainCamera->GetProj();
	XMMATRIX worldViewProj = world * view * proj;

	Effects::SimpleFX->SetWorldViewProj(worldViewProj);

	// 노말맵이 있는지에따라 FX Tech 설정 변경.
	ID3DX11EffectTechnique* Tech;
	Tech = Effects::SimpleFX->ColorTech;

	D3DX11_TECHNIQUE_DESC techDesc;
	Tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		Tech->GetPassByIndex(p)->Apply(0, gRENDERER->DeviceContext());
		gRENDERER->DeviceContext()->DrawIndexed(m_indexCnt, 0, 0);
	}

	// 기본 랜더상태로 복원한다.
	gRENDERER->DeviceContext()->RSSetState(0);
	gRENDERER->DeviceContext()->OMSetBlendState(0, blendFactors, 0xffffffff);
}

void JF::Component::ColisionBox::Release()
{
	ReleaseCOM(m_VertBuff);
	ReleaseCOM(m_IndexBuff);
}

void JF::Component::ColisionBox::SethalfExtents(XMFLOAT3 _vhalfExtents)
{
	// 1)
	m_Size = _vhalfExtents;

	// 2)
	if (m_pRigidBody != nullptr && m_pShape != nullptr)
	{
		m_pRigidBody->detachShape(*m_pShape);
		m_pShape->setGeometry(PxBoxGeometry(m_Size.x, m_Size.y, m_Size.z));
		m_pRigidBody->attachShape(*m_pShape);
	}
}

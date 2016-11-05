#include "stdafx.h"
#include "ColisionBox.h"

// Static Member DECLARE
DECLARE_IDENTIFIER(Jaraffe::Component::ColisionBox);

Jaraffe::Component::ColisionBox::ColisionBox()
{
}

Jaraffe::Component::ColisionBox::~ColisionBox()
{
}

void Jaraffe::Component::ColisionBox::Init()
{
	// 1) 
	auto* pTransform	= GetOwner()->GetComponent<Jaraffe::Component::Transform>();
	XMFLOAT4X4& rMatrix	= pTransform->GetTransformMatrix();

	assert(pTransform != nullptr);

	// 2) 
	m_pShape = PhysXDevice::GetInstance()->GetPhysics()->createShape(
		PxBoxGeometry(1.0f, 1.0f, 1.0f),
		*PhysXDevice::GetInstance()->GetMaterial());
	
	// 3)
	PxTransform localTm( PxMat44(
		PxVec4(rMatrix._11, rMatrix._12, rMatrix._13, rMatrix._14),
		PxVec4(rMatrix._21, rMatrix._22, rMatrix._23, rMatrix._24),
		PxVec4(rMatrix._31, rMatrix._32, rMatrix._33, rMatrix._34),
		PxVec4(rMatrix._41, rMatrix._42, rMatrix._43, rMatrix._44)
	));

	// 4)
	m_pRigidBody = PhysXDevice::GetInstance()->GetPhysics()->createRigidDynamic(localTm);
	m_pRigidBody->attachShape(*m_pShape);
	PxRigidBodyExt::updateMassAndInertia(*m_pRigidBody, 10.0f);
	m_pRigidBody->setLinearVelocity(PxVec3(0, 10, 5.0f));
	PhysXDevice::GetInstance()->GetScene()->addActor(*m_pRigidBody);

	// 5)
	float cX = 0.0f;
	float cY = 0.0f;
	float cZ = 0.0f;

	float eX = 1.0f;
	float eY = 1.0f;
	float eZ = 1.0f;

	// 정점 
	Jaraffe::Vertex::PosColor  vertices[] =
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
	Jaraffe::Util::Mesh::CreateVertexBuffer(&vertices[0], sizeof(Jaraffe::Vertex::PosColor) * m_VertexSize, &m_VertBuff);
	Jaraffe::Util::Mesh::CreateIndexBuffer(&indices[0], sizeof(UINT) * m_indexCnt, &m_IndexBuff);
}

void Jaraffe::Component::ColisionBox::Update()
{

}

void Jaraffe::Component::ColisionBox::Render()
{
	// Declear)
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Get)
	auto* pTransform = GetOwner()->GetComponent<Jaraffe::Component::Transform>();

	// Check)
	RETURN_IF(pTransform == nullptr, );

	// Set Layout And Topology
	gRENDERER->GetDC()->IASetInputLayout(InputLayouts::PosColor);
	gRENDERER->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = sizeof(Jaraffe::Vertex::PosColor);
	UINT offset = 0;
	gRENDERER->GetDC()->IASetVertexBuffers(0, 1, &m_VertBuff, &stride, &offset);
	gRENDERER->GetDC()->IASetIndexBuffer(m_IndexBuff, DXGI_FORMAT_R32_UINT, 0);

	// worldViewProj 행렬을 구한다.
	XMMATRIX world = XMLoadFloat4x4(&pTransform->GetTransformMatrix());
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
		Tech->GetPassByIndex(p)->Apply(0, gRENDERER->GetDC());
		gRENDERER->GetDC()->DrawIndexed(m_indexCnt, 0, 0);
	}

	// 기본 랜더상태로 복원한다.
	gRENDERER->GetDC()->RSSetState(0);
	gRENDERER->GetDC()->OMSetBlendState(0, blendFactors, 0xffffffff);
}

void Jaraffe::Component::ColisionBox::Release()
{
	ReleaseCOM(m_VertBuff);
	ReleaseCOM(m_IndexBuff);
}

void Jaraffe::Component::ColisionBox::SethalfExtents(XMFLOAT3 _vhalfExtents)
{
	ReleaseCOM(m_VertBuff);
	ReleaseCOM(m_IndexBuff);

	m_pShape->getGeometry().box().halfExtents = PxVec3(_vhalfExtents.x, _vhalfExtents.y, _vhalfExtents.z);

	// 5)
	float cX = 0.0f;
	float cY = 0.0f;
	float cZ = 0.0f;

	float eX = _vhalfExtents.x;
	float eY = _vhalfExtents.y;
	float eZ = _vhalfExtents.z;

	// 정점 
	Jaraffe::Vertex::PosColor  vertices[] =
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
	Jaraffe::Util::Mesh::CreateVertexBuffer(&vertices[0], sizeof(Jaraffe::Vertex::PosColor) * m_VertexSize, &m_VertBuff);
	Jaraffe::Util::Mesh::CreateIndexBuffer(&indices[0], sizeof(UINT) * m_indexCnt, &m_IndexBuff);
}

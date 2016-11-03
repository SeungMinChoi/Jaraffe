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
	//PxRigidBodyExt::updateMassAndInertia(*m_pRigidBody, 10.0f);
	m_pRigidBody->setLinearVelocity(PxVec3(0, 10, 5.0f));
	PhysXDevice::GetInstance()->GetScene()->addActor(*m_pRigidBody);
}

void Jaraffe::Component::ColisionBox::Update()
{

}

void Jaraffe::Component::ColisionBox::Render()
{

}

void Jaraffe::Component::ColisionBox::Release()
{
	
}

void Jaraffe::Component::ColisionBox::SethalfExtents(XMFLOAT3 _vhalfExtents)
{
	m_pShape->getGeometry().box().halfExtents = PxVec3(_vhalfExtents.x, _vhalfExtents.y, _vhalfExtents.z);
}

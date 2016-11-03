#include "stdafx.h"
#include "Transform.h"

DECLARE_IDENTIFIER(Jaraffe::Component::Transform);

Jaraffe::Component::Transform::Transform()
{
}

Jaraffe::Component::Transform::~Transform()
{
}

void Jaraffe::Component::Transform::SetPosition(float x, float y, float z)
{
	m_vPosition = XMFLOAT3(x, y, z);
}

void Jaraffe::Component::Transform::SetRotation(float x, float y, float z)
{
	m_vRotation = XMFLOAT3(x, y, z);
}

void Jaraffe::Component::Transform::SetScale(float x, float y, float z)
{
	m_vScale = XMFLOAT3(x, y, z);
}

XMFLOAT4X4& Jaraffe::Component::Transform::GetTransformMatrix()
{
	//
	Jaraffe::Component::Colision* pColision = GetOwner()->GetComponent<Jaraffe::Component::Colision>();
	if (pColision != nullptr && pColision->GetShape() != nullptr)
	{
		auto transform = pColision->GetRigidBody()->getGlobalPose();

		m_vPosition = XMFLOAT3(transform.p.x, transform.p.y, transform.p.z);
		//m_vRotation = XMFLOAT3(transform.q.x, transform.q.y, transform.q.z);
	}

	XMMATRIX scl, rot, tsl;
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&m_vScale));
	rot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_vRotation));
	tsl = XMMatrixTranslationFromVector(XMLoadFloat3(&m_vPosition));

	// worldMat = S*R*T
	XMStoreFloat4x4(&m_Transform, (scl*rot*tsl));

	return m_Transform;
}
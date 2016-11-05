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
	double t0 = cosf(z * 0.5f);
	double t1 = sinf(z * 0.5f);
	double t2 = cosf(x * 0.5f);
	double t3 = sinf(x * 0.5f);
	double t4 = cosf(y * 0.5f);
	double t5 = sinf(y * 0.5f);

	m_vRotation.w = t0 * t2 * t4 + t1 * t3 * t5;
	m_vRotation.x = t0 * t3 * t4 - t1 * t2 * t5;
	m_vRotation.y = t0 * t2 * t5 + t1 * t3 * t4;
	m_vRotation.z = t1 * t2 * t4 - t0 * t3 * t5;

	Jaraffe::Component::Colision* pColision = GetOwner()->GetComponent<Jaraffe::Component::Colision>();
	if (pColision != nullptr && pColision->GetShape() != nullptr)
	{
		auto transform = pColision->GetRigidBody()->getGlobalPose();
		transform.q.x = m_vRotation.x;
		transform.q.y = m_vRotation.y;
		transform.q.z = m_vRotation.z;
		transform.q.w = m_vRotation.w;
		pColision->GetRigidBody()->setGlobalPose(transform);
	}
}

void Jaraffe::Component::Transform::SetScale(float x, float y, float z)
{
	m_vScale = XMFLOAT3(x, y, z);
}

XMFLOAT4X4& Jaraffe::Component::Transform::GetTransformMatrix()
{
	// PhysX 는 오른손좌표계이다. DirextX 는 왼손좌표계이다.
	Jaraffe::Component::Colision* pColision = GetOwner()->GetComponent<Jaraffe::Component::Colision>();
	if (pColision != nullptr && pColision->GetShape() != nullptr)
	{
		auto transform = pColision->GetRigidBody()->getGlobalPose();
		m_vPosition = XMFLOAT3(transform.p.x, transform.p.y, transform.p.z);
		m_vRotation = XMFLOAT4(transform.q.x, transform.q.y, -transform.q.z, transform.q.w);
	}

	XMMATRIX scl, rot, tsl;
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&m_vScale));
	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_vRotation));
	tsl = XMMatrixTranslationFromVector(XMLoadFloat3(&m_vPosition));

	// worldMat = S*R*T
	XMStoreFloat4x4(&m_Transform, (scl*rot*tsl));

	return m_Transform;
}
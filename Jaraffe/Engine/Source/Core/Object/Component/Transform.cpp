#include "stdafx.h"
#include "Transform.h"

DECLARE_IDENTIFIER(JF::Component::Transform);

JF::Component::Transform::Transform()
{
}

JF::Component::Transform::~Transform()
{
}

XMFLOAT3 JF::Component::Transform::Forward()
{
	GetTransformMatrix();
	return JF::Util::MathHelper::ForwardVec(m_Transform);
}

XMFLOAT3 JF::Component::Transform::Back()
{
	GetTransformMatrix();
	return JF::Util::MathHelper::BackVec(m_Transform);
}

XMFLOAT3 JF::Component::Transform::Up()
{
	GetTransformMatrix();
	return JF::Util::MathHelper::UpVec(m_Transform);
}

XMFLOAT3 JF::Component::Transform::Down()
{
	GetTransformMatrix();
	return JF::Util::MathHelper::DownVec(m_Transform);
}

XMFLOAT3 JF::Component::Transform::Right()
{
	GetTransformMatrix();
	return JF::Util::MathHelper::RightVec(m_Transform);
}

XMFLOAT3 JF::Component::Transform::Left()
{
	GetTransformMatrix();
	return JF::Util::MathHelper::LeftVec(m_Transform);
}

void JF::Component::Transform::SetPosition(float x, float y, float z)
{
	m_vPosition = XMFLOAT3(x, y, z);

	if (GetOwner() != nullptr)
	{
		JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
		if (pColision != nullptr && pColision->GetShape() != nullptr)
		{
			auto transform = pColision->GetRigidBody()->getGlobalPose();
			transform.p.x = m_vPosition.x;
			transform.p.y = m_vPosition.y;
			transform.p.z = m_vPosition.z;
			pColision->GetRigidBody()->setGlobalPose(transform);
		}
	}
}

void JF::Component::Transform::SetRotation(float x, float y, float z)
{
	double t0 = cosf(z * 0.5f);	//yaw
	double t1 = sinf(z * 0.5f);
	double t2 = cosf(x * 0.5f); //roll
	double t3 = sinf(x * 0.5f);
	double t4 = cosf(y * 0.5f); //pitch
	double t5 = sinf(y * 0.5f);

	m_vRotation.w = float(t0 * t2 * t4 + t1 * t3 * t5);
	m_vRotation.x = float(t0 * t3 * t4 - t1 * t2 * t5);
	m_vRotation.y = float(t0 * t2 * t5 + t1 * t3 * t4);
	m_vRotation.z = float(t1 * t2 * t4 - t0 * t3 * t5);

	if (GetOwner() != nullptr)
	{
		JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
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
}

void JF::Component::Transform::SetScale(float x, float y, float z)
{
	m_vScale = XMFLOAT3(x, y, z);
}

XMFLOAT4X4& JF::Component::Transform::GetTransformMatrix()
{
	// PhysX 는 오른손좌표계이다. DirextX 는 왼손좌표계이다.
	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
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

void JF::Component::Transform::Strafe(float d)
{
	// mPosition += d*mRight
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&Right());
	XMVECTOR p = XMLoadFloat3(&m_vPosition);
	XMStoreFloat3(&m_vPosition, XMVectorMultiplyAdd(s, r, p));

	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
	if (pColision != nullptr && pColision->GetShape() != nullptr)
	{
		auto transform = pColision->GetRigidBody()->getGlobalPose();
		transform.p.x = m_vPosition.x;
		transform.p.y = m_vPosition.y;
		transform.p.z = m_vPosition.z;
		pColision->GetRigidBody()->setGlobalPose(transform);
	}
}

void JF::Component::Transform::Walk(float d)
{
	// mPosition += d*mLook
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR f = XMLoadFloat3(&Forward());
	XMVECTOR p = XMLoadFloat3(&m_vPosition);
	XMStoreFloat3(&m_vPosition, XMVectorMultiplyAdd(s, f, p));

	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
	if (pColision != nullptr && pColision->GetShape() != nullptr)
	{
		auto transform = pColision->GetRigidBody()->getGlobalPose();
		transform.p.x = m_vPosition.x;
		transform.p.y = m_vPosition.y;
		transform.p.z = m_vPosition.z;
		pColision->GetRigidBody()->setGlobalPose(transform);
	}
}

void JF::Component::Transform::Upper(float d)
{
	// mPosition += d*mLook
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR u = XMLoadFloat3(&Up());
	XMVECTOR p = XMLoadFloat3(&m_vPosition);
	XMStoreFloat3(&m_vPosition, XMVectorMultiplyAdd(s, u, p));

	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
	if (pColision != nullptr && pColision->GetShape() != nullptr)
	{
		auto transform = pColision->GetRigidBody()->getGlobalPose();
		transform.p.x = m_vPosition.x;
		transform.p.y = m_vPosition.y;
		transform.p.z = m_vPosition.z;
		pColision->GetRigidBody()->setGlobalPose(transform);
	}
}

void JF::Component::Transform::Pitch(float angle, bool _local)
{
	// Declear)
	XMFLOAT3 axis				= _local ? Right() : XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMVECTOR vRotation			= XMLoadFloat4(&m_vRotation);
	XMVECTOR pitchQuaternion	= XMQuaternionRotationNormal(XMLoadFloat3(&axis), angle);

	XMStoreFloat4(&m_vRotation, XMQuaternionMultiply(vRotation, pitchQuaternion));

	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
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

void JF::Component::Transform::Roll(float angle, bool _local)
{
	// Declear)
	XMFLOAT3 axis			= _local ? Up() : XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMVECTOR vRotation		= XMLoadFloat4(&m_vRotation);
	XMVECTOR rollQuaternion = XMQuaternionRotationNormal(XMLoadFloat3(&axis), angle);

	XMStoreFloat4(&m_vRotation, XMQuaternionMultiply(vRotation, rollQuaternion));

	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
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

void JF::Component::Transform::Yaw(float angle, bool _local)
{
	// Declear)
	XMFLOAT3 axis			= _local ? Forward() : XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMVECTOR vRotation		= XMLoadFloat4(&m_vRotation);
	XMVECTOR yawQuaternion	= XMQuaternionRotationNormal(XMLoadFloat3(&axis), angle);

	XMStoreFloat4(&m_vRotation, XMQuaternionMultiply(vRotation, yawQuaternion));
	
	JF::Component::Colision* pColision = GetOwner()->GetComponent<JF::Component::Colision>();
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

XMFLOAT4 JF::Component::Transform::EulerToQuaternion(float x, float y, float z)
{
	XMFLOAT4 q;

	double t0 = cosf(z * 0.5f);
	double t1 = sinf(z * 0.5f);
	double t2 = cosf(x * 0.5f);
	double t3 = sinf(x * 0.5f);
	double t4 = cosf(y * 0.5f);
	double t5 = sinf(y * 0.5f);

	q.w = float(t0 * t2 * t4 + t1 * t3 * t5);
	q.x = float(t0 * t3 * t4 - t1 * t2 * t5);
	q.y = float(t0 * t2 * t5 + t1 * t3 * t4);
	q.z = float(t1 * t2 * t4 - t0 * t3 * t5);

	return q;
}

XMFLOAT3 JF::Component::Transform::QuaternionToEuler(XMFLOAT4& q)
{
	XMFLOAT3 e;

	double ysqr = q.y * q.y;
	double t0 = -2.0f * (ysqr + q.z * q.z) + 1.0f;
	double t1 = +2.0f * (q.x * q.y - q.w * q.z);
	double t2 = -2.0f * (q.x * q.z + q.w * q.y);
	double t3 = +2.0f * (q.y * q.z - q.w * q.x);
	double t4 = -2.0f * (q.x * q.x + ysqr) + 1.0f;

	t2 = t2 > 1.0f ? 1.0f : t2;
	t2 = t2 < -1.0f ? -1.0f : t2;

	e.x = std::atan2(t3, t4);
	e.y = std::asin(t2);
	e.z = std::atan2(t1, t0);

	return e;
}
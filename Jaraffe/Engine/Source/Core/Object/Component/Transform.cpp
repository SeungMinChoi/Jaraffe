#include "stdafx.h"
#include "Transform.h"

DECLARE_IDENTIFIER(Jaraffe::Component::Transform);

Jaraffe::Component::Transform::Transform()
{
}

Jaraffe::Component::Transform::~Transform()
{
}

XMFLOAT4X4& Jaraffe::Component::Transform::GetTransformMatrix()
{
	XMMATRIX scl, rot, tsl;
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&m_vScale));
	rot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_vRotation));
	tsl = XMMatrixTranslationFromVector(XMLoadFloat3(&m_vPosition));

	// worldMat = S*R*T
	XMStoreFloat4x4(&m_Transform, (scl*rot*tsl));

	return m_Transform;
}

void Jaraffe::Component::Transform::Init()
{

}

void Jaraffe::Component::Transform::Release()
{
}

void Jaraffe::Component::Transform::Receve()
{

}
#pragma once

namespace Jaraffe
{
namespace Component
{

class Transform : public BaseComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Transform();
	virtual ~Transform();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(Transform, BaseComponent, true);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void Init();
	virtual void Release();
	virtual void Receve();

// ****************************************************************************
// Public Functions) 
// ----------------------------------------------------------------------------
public:
	// Get
	XMFLOAT3& GetPosition() { return m_vPosition; }
	XMFLOAT3& GetRotation() { return m_vRotation; }
	XMFLOAT3& GetScale()	{ return m_vScale; }

	// Set
	void SetPosition(float x, float y, float z) { m_vPosition = XMFLOAT3(x, y, z); }
	void SetRotation(float x, float y, float z) { m_vRotation = XMFLOAT3(x, y, z); }
	void SetScale(float x, float y, float z)	{ m_vScale = XMFLOAT3(x, y, z); }

	XMFLOAT4X4& GetTransformMatrix();

// ****************************************************************************
// Private Members) 
// ----------------------------------------------------------------------------
private:
	XMFLOAT3	m_vPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	m_vRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	m_vScale	= XMFLOAT3(1.0f, 1.0f, 1.0f);

	XMFLOAT4X4	m_Transform;
};

}
}
#pragma once

namespace JF
{
namespace Component
{

class Transform : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Transform();
	virtual ~Transform();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(Transform, BaseComponent, true);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void Reset()		{}
	virtual void Release()	{}

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	// Get
	const XMFLOAT3& GetPosition()	const	{ return m_vPosition; }
	const XMFLOAT4& GetRotation()	const	{ return m_vRotation; }
	const XMFLOAT3& GetScale()		const	{ return m_vScale; }

	XMFLOAT3 Forward();
	XMFLOAT3 Back();
	XMFLOAT3 Up();
	XMFLOAT3 Down();
	XMFLOAT3 Right();
	XMFLOAT3 Left();

	// Set
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	XMFLOAT4X4& GetTransformMatrix();

//=============================================================================
// Moveable) 
//=============================================================================
public:
	void Strafe(float d);
	void Walk(float d);
	void Upper(float d);

	void Pitch(float angle, bool _local = true);
	void Roll(float angle, bool _local = true);
	void Yaw(float angle, bool _local = true);

//=============================================================================
// Moveable) 
//=============================================================================
private:
	XMFLOAT4 EulerToQuaternion(float x, float y, float z);
	XMFLOAT3 QuaternionToEuler(XMFLOAT4& q);

//=============================================================================
// Private Members) 
//=============================================================================
private:
	XMFLOAT3	m_vPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4	m_vRotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT3	m_vScale	= XMFLOAT3(1.0f, 1.0f, 1.0f);

	XMFLOAT4X4	m_Transform;
};

}
}
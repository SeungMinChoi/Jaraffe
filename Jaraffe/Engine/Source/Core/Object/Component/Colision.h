#pragma once

namespace JF
{
namespace Component
{

class Colision : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Colision();
	virtual ~Colision();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(Colision, BaseComponent, true);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void	Reset()			{}
	virtual void	Update(float)	{}
	virtual void	Render()		{}
	virtual void	Release();

	void UseDebugMode(bool _bUse) { m_bUseDebugMode = _bUse; }

	physx::PxRigidBody* GetRigidBody()		{ return m_pRigidBody; }
	physx::PxShape* GetShape()				{ return m_pShape; }

//=============================================================================
// Private Members) 
//=============================================================================
protected:
	bool m_bUseDebugMode;

	physx::PxRigidBody*		m_pRigidBody	= nullptr;
	physx::PxShape*			m_pShape		= nullptr;

	XMFLOAT3 m_Center;
	XMFLOAT3 m_Size;
	
	ID3D11Buffer* m_VertBuff = nullptr;
	ID3D11Buffer* m_IndexBuff = nullptr;

	UINT m_VertexSize = 0;
	UINT m_indexCnt = 0;
};

}
}
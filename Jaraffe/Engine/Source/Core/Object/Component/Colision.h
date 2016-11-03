#pragma once

namespace Jaraffe
{
namespace Component
{

class Colision : public BaseComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Colision();
	virtual ~Colision();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(Colision, BaseComponent, true);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void	Init()		{}
	virtual void	Update()	{}
	virtual void	Render()	{}
	virtual void	Release();

	void UseDebugMode(bool _bUse) { m_bUseDebugMode = _bUse; }

	physx::PxRigidDynamic* GetRigidBody()	{ return m_pRigidBody; }
	physx::PxShape* GetShape()				{ return m_pShape; }

// ****************************************************************************
// Private Members) 
// ----------------------------------------------------------------------------
protected:
	bool m_bUseDebugMode;

	physx::PxRigidDynamic*	m_pRigidBody	= nullptr;
	physx::PxShape*			m_pShape		= nullptr;
};

}
}
#pragma once

namespace Jaraffe
{
class GameObject;

namespace Component
{
class BaseComponent : public Jaraffe::Object
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	BaseComponent();
	virtual ~BaseComponent();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(BaseComponent, null_t, false);

// ****************************************************************************
// Public Functions) 
// ----------------------------------------------------------------------------
public:
	GameObject* GetOwner()					{ return m_pOwner; }
	void		SetOwner(GameObject* rhs)	{ m_pOwner = rhs; }

// ****************************************************************************
// virtual Public Functions) 
// ----------------------------------------------------------------------------
public:
	virtual void Init()		{}
	virtual	void Update()	{}
	virtual void Release()	{}

	virtual void Receve()	{}

// ****************************************************************************
// private Values) 
// ----------------------------------------------------------------------------
private:
	GameObject*	m_pOwner;
};



}
}
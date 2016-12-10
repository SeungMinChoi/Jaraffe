#pragma once

namespace JF
{
class GameObject;

namespace Component
{
class BaseComponent : public JF::Object
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	BaseComponent();
	virtual ~BaseComponent();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(BaseComponent, null_t, false);

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	GameObject* GetOwner()					{ return m_pOwner; }
	void		SetOwner(GameObject* rhs)	{ m_pOwner = rhs; }

//=============================================================================
// virtual Public Functions) 
//=============================================================================
public:
	virtual void Reset()				{}
	virtual	void Update(float)		{}
	virtual void Release()			{}

//=============================================================================
// private Values) 
//=============================================================================
private:
	GameObject*	m_pOwner = nullptr;
};



}
}
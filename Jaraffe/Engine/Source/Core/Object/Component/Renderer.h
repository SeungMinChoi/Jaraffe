#pragma once

namespace Jaraffe
{
namespace Component
{

class Renderer : public BaseComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Renderer();
	virtual ~Renderer();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(Renderer, BaseComponent, true);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void Init()		{}
	virtual void Release()	{}
	virtual void Receve()	{}

// ****************************************************************************
// Public virtual Functions) 
// ----------------------------------------------------------------------------
public:
	virtual void Render()	{}

// ****************************************************************************
// Public Functions) 
// ----------------------------------------------------------------------------
	void SetMaterial(Jaraffe::Material* p_pMaterial);

protected:
	Jaraffe::Material* m_Material;
};

}
}
#pragma once

namespace JF
{
namespace Component
{

class Renderer : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Renderer();
	virtual ~Renderer();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(Renderer, BaseComponent, true);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void Init()		{}
	virtual void Release()	{}

//=============================================================================
// Public virtual Functions) 
//=============================================================================
public:
	virtual void Render()	{}

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	JF::Material* GetMaterial();
	void SetMaterial(JF::Material* p_pMaterial);

private:
	JF::Material* m_Material;
};

}
}
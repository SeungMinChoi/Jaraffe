#pragma once

namespace Jaraffe 
{
namespace Component
{

// TODO : 임시 셋팅.
class Material : public BaseComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Material();
	virtual ~Material();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(Material, BaseComponent, true);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void Init();
	virtual void Release();
	virtual void Receve();

// ****************************************************************************
// Public Members)
// ----------------------------------------------------------------------------
public:
	Jaraffe::Light::Material m_Material;
};

}
}
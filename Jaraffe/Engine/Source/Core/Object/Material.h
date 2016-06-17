#pragma once

namespace Jaraffe 
{

// TODO : 임시 셋팅.
class Material : public Jaraffe::Object
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Material();
	virtual ~Material();

// ****************************************************************************
// Public Members)
// ----------------------------------------------------------------------------
public:
	Jaraffe::Light::Material	m_Material;
	Jaraffe::Texture*			m_MainTexture;

// ****************************************************************************
// static Public Functions)
// ----------------------------------------------------------------------------
public:
	static Material* GetDefalutMaterial();

// ****************************************************************************
// static private Members)
// ----------------------------------------------------------------------------
private:
	static Material m_pDefalutMaterial;
};

}
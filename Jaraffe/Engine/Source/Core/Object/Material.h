#pragma once

namespace Jaraffe 
{

// TODO : 임시 셋팅.
class Material : public Jaraffe::Object
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Material();
	virtual ~Material();

//=============================================================================
// Public Members)
//=============================================================================
public:
	Jaraffe::Light::Material	m_Material;
	Jaraffe::Texture*			m_MainTexture	= nullptr;
	Jaraffe::Texture*			m_BumpTexture	= nullptr;

	ID3D11RasterizerState*		m_RSState		= nullptr;
	ID3D11BlendState*			m_BlendState	= nullptr;

//=============================================================================
// static Public Functions)
//=============================================================================
public:
	static Material* GetDefalutMaterial();

//=============================================================================
// static private Members)
//=============================================================================
private:
	static Material m_pDefalutMaterial;
};

}
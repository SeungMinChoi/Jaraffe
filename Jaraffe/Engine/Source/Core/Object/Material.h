#pragma once

namespace JF 
{

// TODO : 임시 셋팅.
class Material : public JF::Object
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
	JF::Light::Material			m_Material;
	JF::Texture*				m_MainTexture	= nullptr;
	JF::Texture*				m_BumpTexture	= nullptr;

	ID3D11RasterizerState*		m_RSState		= nullptr;
	ID3D11BlendState*			m_BlendState	= nullptr;

	bool						m_bAlphaClip	= false;
};

}
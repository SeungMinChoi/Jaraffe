#pragma once

//---------------------------------------------------------------------------------
// *SkyMap Component*
// 1. ī�޶� �����ϴ°����� ���������� ������Ʈ �̴�.
//---------------------------------------------------------------------------------
namespace JF
{
namespace Component
{

class SkyBox : public Mesh
{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
public:
	SkyBox(float _skySphereRadius, JF::Texture* _pTexture);
	virtual ~SkyBox();

	//=============================================================================
	// Component IDENTIFIER)
	//=============================================================================
public:
	COMPONENT_IDENTIFIER(SkyBox, Mesh, true);

	//=============================================================================
	// override) 
	//=============================================================================
public:
	virtual void Reset();
	virtual void Render();

	JF::Texture*		GetMainTexture()						{ return m_pMainTexture; }
	void				SetMainTexture(JF::Texture* _pTexture)	{ m_pMainTexture = _pTexture; }

private:
	float			m_SkySphereRadius;

	JF::Texture*	m_pMainTexture;
};

}
}

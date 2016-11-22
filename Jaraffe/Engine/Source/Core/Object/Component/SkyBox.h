#pragma once

//---------------------------------------------------------------------------------
// *SkyMap Component*
// 1. ī�޶� �����ϴ°����� ���������� ������Ʈ �̴�.
//---------------------------------------------------------------------------------
namespace Jaraffe
{
namespace Component
{

class SkyBox : public Mesh
{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
public:
	SkyBox(float _skySphereRadius, Jaraffe::Texture* _pTexture);
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
	virtual void Init();
	virtual void Render();

	void SetMainTexture(Jaraffe::Texture* _pTexture) { m_pMainTexture = _pTexture; }

private:
	float			m_SkySphereRadius;

	Jaraffe::Texture* m_pMainTexture;
};

}
}

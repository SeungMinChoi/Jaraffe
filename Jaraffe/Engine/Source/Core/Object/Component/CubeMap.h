#pragma once

namespace Jaraffe
{
namespace Component
{

class CubeMap : public Mesh
{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
public:
	CubeMap(float _skySphereRadius, Jaraffe::Texture* _pTexture);
	virtual ~CubeMap();

	//=============================================================================
	// Component IDENTIFIER)
	//=============================================================================
public:
	COMPONENT_IDENTIFIER(CubeMap, Mesh, true);

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

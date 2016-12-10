#pragma once

namespace JF
{
namespace Component
{

class ColisionBox : public Colision
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	ColisionBox(JF::JFCPhysXDevice* _pxDevice);
	virtual ~ColisionBox();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(ColisionBox, Colision, false);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void	Reset();
	virtual void	Update(float t);
	virtual void	Render();
	virtual void	Release();

	void SethalfExtents(XMFLOAT3 _vhalfExtents);

private:
	JF::JFCPhysXDevice* m_pPXDevice;
};

}
}
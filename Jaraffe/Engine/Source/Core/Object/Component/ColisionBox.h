#pragma once

namespace Jaraffe
{
namespace Component
{

class ColisionBox : public Colision
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	ColisionBox();
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
	virtual void	Init();
	virtual void	Update(float t);
	virtual void	Render();
	virtual void	Release();

	void SethalfExtents(XMFLOAT3 _vhalfExtents);
};

}
}
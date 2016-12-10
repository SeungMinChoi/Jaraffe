#pragma once

namespace JF 
{
namespace Component
{

class MeshRenderer : public Renderer
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	MeshRenderer();
	virtual ~MeshRenderer();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(MeshRenderer, Renderer, false);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void	Reset();
	virtual void	Update(float t);
	virtual void	Render();
	virtual void	Release();
};

}
}
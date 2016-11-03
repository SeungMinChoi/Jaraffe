#pragma once

namespace Jaraffe 
{
namespace Component
{

class MeshRenderer : public Renderer
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	MeshRenderer();
	virtual ~MeshRenderer();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(MeshRenderer, Renderer, false);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void	Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Release();
};

}
}
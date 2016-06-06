#pragma once

namespace Jaraffe 
{

namespace Component
{

// TODO: Temp Setting
class Mesh : public BaseComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Mesh();
	virtual ~Mesh();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(Mesh, BaseComponent, true);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void	Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Release();

	virtual void	Receve();

protected:
	ID3D11Buffer*		m_VB;				// Vertex Buffer
	ID3D11Buffer*		m_IB;				// Index Buffer

	std::vector<Jaraffe::Vertex::Simple>	m_pVertices;
	std::vector<UINT>						m_pIndices;
};

}

}
#pragma once

namespace Jaraffe
{
namespace Component
{

// TODO : Init Temp Setting
class Mesh : public BaseComponent
{
// ****************************************************************************
// friend class
// ----------------------------------------------------------------------------
	friend class MeshRenderer;

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
	virtual void Init();
	virtual void Release();
	virtual void Receve();

// ****************************************************************************
// protected Functions) 
// ----------------------------------------------------------------------------
public:
	void SetVertexType(Jaraffe::Vertex::VertexType p_VertexType);
	
	ID3D11InputLayout*	GetInputLayout()	{ return m_pInputLayout; }
	UINT				GetStride()			{ return m_Stride; }

	ID3D11Buffer*		GetVB()				{ return m_pVB; }
	ID3D11Buffer*		GetIB()				{ return m_pIB; }

// ****************************************************************************
// protected Members) 
// ----------------------------------------------------------------------------
protected:
	Jaraffe::Vertex::VertexType					m_VertexType;
	ID3D11InputLayout*							m_pInputLayout;
	UINT										m_Stride;
	UINT										m_IndexCount;

	std::vector<Jaraffe::Vertex::PosNormal>		m_pVertices;
	std::vector<UINT>							m_pIndices;

	ID3D11Buffer*								m_pVB;			// Vertex Buffer
	ID3D11Buffer*								m_pIB;			// Index Buffer
};

}
}
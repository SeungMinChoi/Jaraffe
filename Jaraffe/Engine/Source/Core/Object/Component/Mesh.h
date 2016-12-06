#pragma once

namespace JF
{
namespace Component
{

// TODO : Init Temp Setting
class Mesh : public BaseComponent
{
//=============================================================================
// friend class
//=============================================================================
	friend class MeshRenderer;

//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Mesh();
	virtual ~Mesh();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(Mesh, BaseComponent, true);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void Init();
	virtual void Release();

//=============================================================================
// public Functions) 
//=============================================================================
public:
	std::vector<JF::Vertex::PosNormalTexTan>&	GetVertices()	{ return m_pVertices; }
	std::vector<UINT>&							GetIndices()	{ return m_pIndices; }

	ID3D11InputLayout*	GetInputLayout()	{ return m_pInputLayout; }
	UINT				GetStride()			{ return m_Stride; }

	ID3D11Buffer*		GetVB()				{ return m_pVB; }
	ID3D11Buffer*		GetIB()				{ return m_pIB; }

	int					GetIndexCount()		{ return m_IndexCount; }

	XMFLOAT4X4&			GetTexTransform()	{ return m_TexTransform; }

//=============================================================================
// protected Members) 
//=============================================================================
protected:
	ID3D11InputLayout*								m_pInputLayout;
	UINT											m_Stride;
	UINT											m_VertexCount;
	UINT											m_IndexCount;

	std::vector<JF::Vertex::PosNormalTexTan>		m_pVertices;
	std::vector<UINT>								m_pIndices;

	ID3D11Buffer*									m_pVB;			// Vertex Buffer
	ID3D11Buffer*									m_pIB;			// Index Buffer

	XMFLOAT4X4										m_TexTransform;
};

}
}
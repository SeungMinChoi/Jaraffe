#pragma once

namespace Jaraffe
{

class RenderStates
{
//=============================================================================
// Public Functions)
//=============================================================================
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

//=============================================================================
// RasterizerStates)
//=============================================================================
public:
	static ID3D11RasterizerState* m_WireframeRS;
	static ID3D11RasterizerState* m_SolidRS;
	static ID3D11RasterizerState* m_BasicRS;

//=============================================================================
// BlendStates) TODO : ���̴����� �������� ���ø����̼� ���� ���������� �����.
//=============================================================================
	static ID3D11BlendState* m_AlphaToCoverageBS;
	static ID3D11BlendState* m_TransparentBS;
};

}
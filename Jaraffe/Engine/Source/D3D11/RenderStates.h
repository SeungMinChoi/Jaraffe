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
// BlendStates) TODO : 셰이더에서 정희할지 어플리케이션 에서 정의할지는 고민중.
//=============================================================================
	static ID3D11BlendState* m_AlphaToCoverageBS;
	static ID3D11BlendState* m_TransparentBS;
};

}
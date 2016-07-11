#include "stdafx.h"
#include "RenderStates.h"

// Staitc Values
ID3D11RasterizerState* Jaraffe::RenderStates::m_WireframeRS = 0;		// 와이어프레임 랜더링.
ID3D11RasterizerState* Jaraffe::RenderStates::m_SolidRS = 0;			// 일단 고형체 랜더링.

ID3D11BlendState*      Jaraffe::RenderStates::m_AlphaToCoverageBS = 0;	// 
ID3D11BlendState*      Jaraffe::RenderStates::m_TransparentBS = 0;		// 

void Jaraffe::RenderStates::InitAll(ID3D11Device * device)
{
	//
	// WireframeRS
	//
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode				= D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode				= D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable		= true;

	HR(device->CreateRasterizerState(&wireframeDesc, &m_WireframeRS));

	//
	// NoCullRS
	//
	D3D11_RASTERIZER_DESC noCullDesc;
	ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	noCullDesc.FillMode					= D3D11_FILL_SOLID;
	noCullDesc.CullMode					= D3D11_CULL_NONE;
	noCullDesc.FrontCounterClockwise	= false;
	noCullDesc.DepthClipEnable			= true;

	HR(device->CreateRasterizerState(&noCullDesc, &m_SolidRS));

	//
	// AlphaToCoverageBS
	//

	D3D11_BLEND_DESC alphaToCoverageDesc						= { 0 };
	alphaToCoverageDesc.AlphaToCoverageEnable					= true;
	alphaToCoverageDesc.IndependentBlendEnable					= false;
	alphaToCoverageDesc.RenderTarget[0].BlendEnable				= false;
	alphaToCoverageDesc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	HR(device->CreateBlendState(&alphaToCoverageDesc, &m_AlphaToCoverageBS));

	//
	// TransparentBS
	//

	D3D11_BLEND_DESC transparentDesc						= { 0 };
	transparentDesc.AlphaToCoverageEnable					= false;
	transparentDesc.IndependentBlendEnable					= false;

	transparentDesc.RenderTarget[0].BlendEnable				= true;
	transparentDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp					= D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_DEST_ALPHA;
	transparentDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	HR(device->CreateBlendState(&transparentDesc, &m_TransparentBS));
}

void Jaraffe::RenderStates::DestroyAll()
{
	ReleaseCOM(m_WireframeRS);
	ReleaseCOM(m_SolidRS);
	ReleaseCOM(m_AlphaToCoverageBS);
	ReleaseCOM(m_TransparentBS);
}

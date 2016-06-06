#include "stdafx.h"
#include "RenderStates.h"

// Staitc Values
ID3D11RasterizerState* Jaraffe::RenderStates::m_WireframeRS = 0;	// 와이어프레임 랜더링.
ID3D11RasterizerState* Jaraffe::RenderStates::m_SolidRS = 0;	// 일단 고형체 랜더링.

void Jaraffe::RenderStates::InitAll(ID3D11Device * device)
{
	//
	// WireframeRS
	//
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	HR(device->CreateRasterizerState(&wireframeDesc, &m_WireframeRS));

	//
	// NoCullRS
	//
	D3D11_RASTERIZER_DESC noCullDesc;
	ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	noCullDesc.FillMode = D3D11_FILL_SOLID;
	noCullDesc.CullMode = D3D11_CULL_NONE;
	noCullDesc.FrontCounterClockwise = false;
	noCullDesc.DepthClipEnable = true;

	HR(device->CreateRasterizerState(&noCullDesc, &m_SolidRS));
}

void Jaraffe::RenderStates::DestroyAll()
{
}

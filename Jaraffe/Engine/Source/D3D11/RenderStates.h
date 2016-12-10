#pragma once

namespace JF
{

class BlendStates;
class SamplerStates;
class RasterizerStates;
class DepthStencilStates;
class RenderStates
{
//=============================================================================
// Public Functions)
//=============================================================================
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

public:
	static BlendStates*			GetBlendStates()			{ return m_BlendStates; }
	static SamplerStates*		GetSamplerStates()			{ return m_SamplerStates; }
	static RasterizerStates*	GetRasterizerStates()		{ return m_ResterizerStates; }
	static DepthStencilStates*	GetDepthStencilStates()		{ return m_DepthStencilStates; }

protected:
	static BlendStates*			m_BlendStates;
	static SamplerStates*		m_SamplerStates;
	static RasterizerStates*	m_ResterizerStates;
	static DepthStencilStates*	m_DepthStencilStates;
};

class BlendStates
{
public:
	void Initialize(ID3D11Device* device);

	ID3D11BlendState* BlendDisabled()			{ return m_BlendDisabled; }
	ID3D11BlendState* AdditiveBlend()			{ return m_AdditiveBlend; }
	ID3D11BlendState* AlphaBlend()				{ return m_AlphaBlend; }
	ID3D11BlendState* PreMultipliedAlphaBlend() { return m_PreMultipliedAlphaBlend; }
	ID3D11BlendState* ColorWriteDisabled()		{ return m_NoColor; }

protected:
	D3D11_BLEND_DESC BlendDisabledDesc();
	D3D11_BLEND_DESC AdditiveBlendDesc();
	D3D11_BLEND_DESC AlphaBlendDesc();
	D3D11_BLEND_DESC PreMultipliedAlphaBlendDesc();
	D3D11_BLEND_DESC ColorWriteDisabledDesc();

protected:
	ID3D11BlendStatePtr m_BlendDisabled;
	ID3D11BlendStatePtr m_AdditiveBlend;
	ID3D11BlendStatePtr m_AlphaBlend;
	ID3D11BlendStatePtr m_PreMultipliedAlphaBlend;
	ID3D11BlendStatePtr m_NoColor;
};


class RasterizerStates
{
public:
	void Initialize(ID3D11Device* device);

	ID3D11RasterizerState* NoCull()			{ return m_NoCull; }
	ID3D11RasterizerState* BackFaceCull()	{ return m_CullBackFaces; }
	ID3D11RasterizerState* FrontFaceCull()	{ return m_CullFrontFaces; }
	ID3D11RasterizerState* NoCullNoMS()		{ return m_NoCullNoMS; }
	ID3D11RasterizerState* NoCullScissor()	{ return m_NoCullScissor; }

protected:
	D3D11_RASTERIZER_DESC NoCullDesc();
	D3D11_RASTERIZER_DESC FrontFaceCullDesc();
	D3D11_RASTERIZER_DESC BackFaceCullDesc();
	D3D11_RASTERIZER_DESC NoCullNoMSDesc();
	D3D11_RASTERIZER_DESC NoCullScissorDesc();

protected:
	ID3D11RasterizerStatePtr m_NoCull;
	ID3D11RasterizerStatePtr m_CullBackFaces;
	ID3D11RasterizerStatePtr m_CullFrontFaces;
	ID3D11RasterizerStatePtr m_NoCullNoMS;
	ID3D11RasterizerStatePtr m_NoCullScissor;
};


class DepthStencilStates
{
public:
	void Initialize(ID3D11Device* device);

	ID3D11DepthStencilState* EqualsDSS()				{ return m_EqualsDSS; }
	ID3D11DepthStencilState* DepthDisabled()			{ return m_DepthDisabled; }
	ID3D11DepthStencilState* DepthEnabled()				{ return m_DepthEnabled; }
	ID3D11DepthStencilState* ReverseDepthEnabled()		{ return m_RevDepthEnabled; }
	ID3D11DepthStencilState* DepthWriteEnabled()		{ return m_DepthWriteEnabled; }
	ID3D11DepthStencilState* ReverseDepthWriteEnabled() { return m_RevDepthWriteEnabled; }
	
protected:
	D3D11_DEPTH_STENCIL_DESC EqualsDSSDesc();
	D3D11_DEPTH_STENCIL_DESC DepthDisabledDesc();
	D3D11_DEPTH_STENCIL_DESC DepthEnabledDesc();
	D3D11_DEPTH_STENCIL_DESC ReverseDepthEnabledDesc();
	D3D11_DEPTH_STENCIL_DESC DepthWriteEnabledDesc();
	D3D11_DEPTH_STENCIL_DESC ReverseDepthWriteEnabledDesc();

protected:
	ID3D11DepthStencilStatePtr m_EqualsDSS;
	ID3D11DepthStencilStatePtr m_DepthDisabled;
	ID3D11DepthStencilStatePtr m_DepthEnabled;
	ID3D11DepthStencilStatePtr m_RevDepthEnabled;
	ID3D11DepthStencilStatePtr m_DepthWriteEnabled;
	ID3D11DepthStencilStatePtr m_RevDepthWriteEnabled;
};


class SamplerStates
{
public:
	void Initialize(ID3D11Device* device);

	ID3D11SamplerState* Linear()		{ return m_Linear; }
	ID3D11SamplerState* Point()			{ return m_Point; }
	ID3D11SamplerState* Anisotropic()	{ return m_Anisotropic; }
	ID3D11SamplerState* ShadowMap()		{ return m_ShadowMap; }
	ID3D11SamplerState* ShadowMapPCF()	{ return m_ShadowMapPCF; }

protected:
	D3D11_SAMPLER_DESC LinearDesc();
	D3D11_SAMPLER_DESC PointDesc();
	D3D11_SAMPLER_DESC AnisotropicDesc();
	D3D11_SAMPLER_DESC ShadowMapDesc();
	D3D11_SAMPLER_DESC ShadowMapPCFDesc();

protected:
	ID3D11SamplerStatePtr m_Linear;
	ID3D11SamplerStatePtr m_Point;
	ID3D11SamplerStatePtr m_Anisotropic;
	ID3D11SamplerStatePtr m_ShadowMap;
	ID3D11SamplerStatePtr m_ShadowMapPCF;
};

}
#include "stdafx.h"
#include "RenderStates.h"

namespace JF
{
	BlendStates*		RenderStates::m_BlendStates;
	SamplerStates*		RenderStates::m_SamplerStates;
	RasterizerStates*	RenderStates::m_ResterizerStates;
	DepthStencilStates*	RenderStates::m_DepthStencilStates;

	void RenderStates::InitAll(ID3D11Device* device)
	{
		// 1) วาด็.
		m_BlendStates			= new BlendStates();
		m_SamplerStates			= new SamplerStates();
		m_ResterizerStates		= new RasterizerStates();
		m_DepthStencilStates	= new DepthStencilStates();

		// 2) Reset
		m_BlendStates->Initialize(device);
		m_SamplerStates->Initialize(device);
		m_ResterizerStates->Initialize(device);
		m_DepthStencilStates->Initialize(device);
	}

	void RenderStates::DestroyAll()
	{
		SafeDelete(m_BlendStates);
		SafeDelete(m_SamplerStates);
		SafeDelete(m_ResterizerStates);
		SafeDelete(m_DepthStencilStates);
	}

	void BlendStates::Initialize(ID3D11Device* device)
	{
		device->CreateBlendState(&BlendDisabledDesc(), &m_BlendDisabled);
		device->CreateBlendState(&AdditiveBlendDesc(), &m_AdditiveBlend);
		device->CreateBlendState(&AlphaBlendDesc(), &m_AlphaBlend);
		device->CreateBlendState(&PreMultipliedAlphaBlendDesc(), &m_PreMultipliedAlphaBlend);
		device->CreateBlendState(&ColorWriteDisabledDesc(), &m_NoColor);
	}

	D3D11_BLEND_DESC BlendStates::BlendDisabledDesc()
	{
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		for (UINT i = 0; i < 8; ++i)
		{
			blendDesc.RenderTarget[i].BlendEnable = false;
			blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		}

		return blendDesc;
	}

	D3D11_BLEND_DESC BlendStates::AdditiveBlendDesc()
	{
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		for (UINT i = 0; i < 8; ++i)
		{
			blendDesc.RenderTarget[i].BlendEnable = true;
			blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		}

		return blendDesc;
	}

	D3D11_BLEND_DESC BlendStates::AlphaBlendDesc()
	{
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		for (UINT i = 0; i < 8; ++i)
		{
			blendDesc.RenderTarget[i].BlendEnable = true;
			blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		}

		return blendDesc;
	}

	D3D11_BLEND_DESC BlendStates::PreMultipliedAlphaBlendDesc()
	{
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		for (UINT i = 0; i < 8; ++i)
		{
			blendDesc.RenderTarget[i].BlendEnable = false;
			blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		}

		return blendDesc;
	}

	D3D11_BLEND_DESC BlendStates::ColorWriteDisabledDesc()
	{
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		for (UINT i = 0; i < 8; ++i)
		{
			blendDesc.RenderTarget[i].BlendEnable = false;
			blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = 0;
			blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		}

		return blendDesc;
	}

	void RasterizerStates::Initialize(ID3D11Device* device)
	{
		device->CreateRasterizerState(&NoCullDesc(), &m_NoCull);
		device->CreateRasterizerState(&FrontFaceCullDesc(), &m_CullFrontFaces);
		device->CreateRasterizerState(&BackFaceCullDesc(), &m_CullBackFaces);
		device->CreateRasterizerState(&NoCullNoMSDesc(), &m_NoCullNoMS);
		device->CreateRasterizerState(&NoCullScissorDesc(), &m_NoCullScissor);
	}

	D3D11_RASTERIZER_DESC RasterizerStates::NoCullDesc()
	{
		D3D11_RASTERIZER_DESC rastDesc;

		rastDesc.AntialiasedLineEnable = FALSE;
		rastDesc.CullMode = D3D11_CULL_NONE;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0f;
		rastDesc.DepthClipEnable = TRUE;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.MultisampleEnable = true;
		rastDesc.ScissorEnable = false;
		rastDesc.SlopeScaledDepthBias = 0;

		return rastDesc;
	}

	D3D11_RASTERIZER_DESC RasterizerStates::FrontFaceCullDesc()
	{
		D3D11_RASTERIZER_DESC rastDesc;

		rastDesc.AntialiasedLineEnable = FALSE;
		rastDesc.CullMode = D3D11_CULL_FRONT;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0f;
		rastDesc.DepthClipEnable = TRUE;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.MultisampleEnable = true;
		rastDesc.ScissorEnable = false;
		rastDesc.SlopeScaledDepthBias = 0;

		return rastDesc;
	}

	D3D11_RASTERIZER_DESC RasterizerStates::BackFaceCullDesc()
	{
		D3D11_RASTERIZER_DESC rastDesc;

		rastDesc.AntialiasedLineEnable = FALSE;
		rastDesc.CullMode = D3D11_CULL_BACK;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0f;
		rastDesc.DepthClipEnable = TRUE;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.MultisampleEnable = true;
		rastDesc.ScissorEnable = false;
		rastDesc.SlopeScaledDepthBias = 0;

		return rastDesc;
	}

	D3D11_RASTERIZER_DESC RasterizerStates::NoCullNoMSDesc()
	{
		D3D11_RASTERIZER_DESC rastDesc;

		rastDesc.AntialiasedLineEnable = FALSE;
		rastDesc.CullMode = D3D11_CULL_NONE;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0f;
		rastDesc.DepthClipEnable = TRUE;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.MultisampleEnable = false;
		rastDesc.ScissorEnable = false;
		rastDesc.SlopeScaledDepthBias = 0;

		return rastDesc;
	}

	D3D11_RASTERIZER_DESC RasterizerStates::NoCullScissorDesc()
	{
		D3D11_RASTERIZER_DESC rastDesc;

		rastDesc.AntialiasedLineEnable = FALSE;
		rastDesc.CullMode = D3D11_CULL_NONE;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0f;
		rastDesc.DepthClipEnable = TRUE;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.MultisampleEnable = true;
		rastDesc.ScissorEnable = true;
		rastDesc.SlopeScaledDepthBias = 0;

		return rastDesc;
	}

	void DepthStencilStates::Initialize(ID3D11Device* device)
	{
		device->CreateDepthStencilState(&EqualsDSSDesc(), &m_EqualsDSS);
		device->CreateDepthStencilState(&DepthDisabledDesc(), &m_DepthDisabled);
		device->CreateDepthStencilState(&DepthEnabledDesc(), &m_DepthEnabled);
		device->CreateDepthStencilState(&ReverseDepthEnabledDesc(), &m_RevDepthEnabled);
		device->CreateDepthStencilState(&DepthWriteEnabledDesc(), &m_DepthWriteEnabled);
		device->CreateDepthStencilState(&ReverseDepthWriteEnabledDesc(), &m_RevDepthWriteEnabled);
	}

	D3D11_DEPTH_STENCIL_DESC DepthStencilStates::EqualsDSSDesc()
	{
		D3D11_DEPTH_STENCIL_DESC equalsDesc;
		ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		equalsDesc.DepthEnable = true;
		equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		equalsDesc.DepthFunc = D3D11_COMPARISON_EQUAL;

		return equalsDesc;
	}

	D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthDisabledDesc()
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = false;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.StencilEnable = false;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace = dsDesc.FrontFace;

		return dsDesc;
	}

	D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthEnabledDesc()
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.StencilEnable = false;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace = dsDesc.FrontFace;

		return dsDesc;
	}

	D3D11_DEPTH_STENCIL_DESC DepthStencilStates::ReverseDepthEnabledDesc()
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		dsDesc.StencilEnable = false;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace = dsDesc.FrontFace;

		return dsDesc;
	}

	D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthWriteEnabledDesc()
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.StencilEnable = false;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace = dsDesc.FrontFace;

		return dsDesc;
	}

	D3D11_DEPTH_STENCIL_DESC DepthStencilStates::ReverseDepthWriteEnabledDesc()
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		dsDesc.StencilEnable = false;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace = dsDesc.FrontFace;

		return dsDesc;
	}

	void SamplerStates::Initialize(ID3D11Device* device)
	{
		device->CreateSamplerState(&LinearDesc(), &m_Linear);
		device->CreateSamplerState(&PointDesc(), &m_Point);
		device->CreateSamplerState(&AnisotropicDesc(), &m_Anisotropic);
		device->CreateSamplerState(&ShadowMapDesc(), &m_ShadowMap);
		device->CreateSamplerState(&ShadowMapPCFDesc(), &m_ShadowMapPCF);
	}

	D3D11_SAMPLER_DESC SamplerStates::LinearDesc()
	{
		D3D11_SAMPLER_DESC sampDesc;

		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 1;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return sampDesc;
	}

	D3D11_SAMPLER_DESC SamplerStates::PointDesc()
	{
		D3D11_SAMPLER_DESC sampDesc;

		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 1;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return sampDesc;
	}

	D3D11_SAMPLER_DESC SamplerStates::AnisotropicDesc()
	{
		D3D11_SAMPLER_DESC sampDesc;

		sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 16;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return sampDesc;
	}

	D3D11_SAMPLER_DESC SamplerStates::ShadowMapDesc()
	{
		D3D11_SAMPLER_DESC sampDesc;

		sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 1;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
		sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return sampDesc;
	}

	D3D11_SAMPLER_DESC SamplerStates::ShadowMapPCFDesc()
	{
		D3D11_SAMPLER_DESC sampDesc;

		sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.MipLODBias = 0.0f;
		sampDesc.MaxAnisotropy = 1;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
		sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return sampDesc;
	}
}
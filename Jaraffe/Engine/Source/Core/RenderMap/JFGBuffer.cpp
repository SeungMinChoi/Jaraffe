#include "stdafx.h"
#include "JFGBuffer.h"

JF::RenderMap::JFGBuffer::JFGBuffer()
{

}

JF::RenderMap::JFGBuffer::~JFGBuffer()
{
	Release();
}

void JF::RenderMap::JFGBuffer::Reset(ID3D11Device* _pDevice, int _width, int _height, int _msCount, int _msQuality)
{
	// 1)
	Release();

	// 2)
	CreateTexture(_pDevice, _width, _height, _msCount, _msQuality);
}

void JF::RenderMap::JFGBuffer::Release()
{
	ReleaseCOM_PTR(m_pWorldNormalTexture);
	ReleaseCOM_PTR(m_pWorldNormalRTV);
	ReleaseCOM_PTR(m_pWorldNormalSRV);

	ReleaseCOM_PTR(m_pWorldPositionTexture);
	ReleaseCOM_PTR(m_pWorldPositionRTV);
	ReleaseCOM_PTR(m_pWorldPositionSRV);

	ReleaseCOM_PTR(m_pViewNormalDepthTexture);
	ReleaseCOM_PTR(m_pViewNormalDepthRTV);
	ReleaseCOM_PTR(m_pViewNormalDepthSRV);
}

void JF::RenderMap::JFGBuffer::CreateTexture(ID3D11Device* _pDevice, int _width, int _height, int _msCount, int _msQuality)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width				= _width;
	desc.Height				= _height;
	desc.ArraySize			= 1;
	desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags		= 0;
	desc.Format				= DXGI_FORMAT_R16G16B16A16_FLOAT;
	desc.MipLevels			= 1;
	desc.MiscFlags			= 1;
	desc.SampleDesc.Count	= _msCount;
	desc.SampleDesc.Quality = _msQuality;
	desc.Usage				= D3D11_USAGE_DEFAULT;

	JF::Utile::DXCall(_pDevice->CreateTexture2D(&desc, NULL, &m_pWorldNormalTexture));
	JF::Utile::DXCall(_pDevice->CreateRenderTargetView(m_pWorldNormalTexture, NULL, &m_pWorldNormalRTV));
	JF::Utile::DXCall(_pDevice->CreateShaderResourceView(m_pWorldNormalTexture, NULL, &m_pWorldNormalSRV));

	JF::Utile::DXCall(_pDevice->CreateTexture2D(&desc, NULL, &m_pWorldPositionTexture));
	JF::Utile::DXCall(_pDevice->CreateRenderTargetView(m_pWorldPositionTexture, NULL, &m_pWorldPositionRTV));
	JF::Utile::DXCall(_pDevice->CreateShaderResourceView(m_pWorldPositionTexture, NULL, &m_pWorldPositionSRV));

	JF::Utile::DXCall(_pDevice->CreateTexture2D(&desc, NULL, &m_pViewNormalDepthTexture));
	JF::Utile::DXCall(_pDevice->CreateRenderTargetView(m_pViewNormalDepthTexture, NULL, &m_pViewNormalDepthRTV));
	JF::Utile::DXCall(_pDevice->CreateShaderResourceView(m_pViewNormalDepthTexture, NULL, &m_pViewNormalDepthSRV));
}

#pragma once

#define gRENDERER Jaraffe::CD3DDevice::GetInstance()

namespace Jaraffe
{

class CD3DDevice
{
//=============================================================================
// Singletone)
//=============================================================================
	SINGLETONE(CD3DDevice)

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	HRESULT Init(HWND hWnd);
	HRESULT CleanupDevice();
	void	OnResize();

	void	ClearRenderTargetView(const float* p_pColor);
	void	ClearDepthStencilView();
	void	Present();

	ID3D11Device*			GetDevice()				{ return m_pd3dDevice; }
	ID3D11DeviceContext*	GetDC()					{ return m_pImmediateContext; }
	IDXGISwapChain*			GetSwapChan()			{ return m_pSwapChain; }
	ID3D11RenderTargetView* GetRenderTargetView()	{ return m_pRenderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView()	{ return m_pDepthStencilView; }
	D3D11_VIEWPORT			GetVP()					{ return m_ScreenViewport; }
	HWND					GetTargetHwnd()			{ return m_TargetHwnd; }
	RECT					GetScreenRectSize();

//=============================================================================
// protected Members) 
//=============================================================================
protected:
	ID3D11Device*			m_pd3dDevice			= NULL;
	ID3D11DeviceContext*	m_pImmediateContext		= NULL;
	IDXGISwapChain*			m_pSwapChain			= NULL;
	ID3D11RenderTargetView* m_pRenderTargetView		= NULL;
	ID3D11DepthStencilView* m_pDepthStencilView		= NULL;
	ID3D11Texture2D*		m_pDepthStencilBuffer	= NULL;
	D3D11_VIEWPORT			m_ScreenViewport;

	HWND					m_TargetHwnd;

	bool					m_Enable4xMsaa			= true;
	UINT					m_4xMsaaQuality;

	D3D_DRIVER_TYPE         m_driverType			= D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL       m_featureLevel			= D3D_FEATURE_LEVEL_11_0;
};

}
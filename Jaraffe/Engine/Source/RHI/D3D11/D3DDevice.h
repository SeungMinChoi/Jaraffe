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

	ID3D11Device*			GetDevice()				const { return m_pd3dDevice.GetInterfacePtr(); }
	ID3D11DeviceContext*	GetDC()					const { return m_pImmediateContext.GetInterfacePtr(); }
	IDXGISwapChain*			GetSwapChan()			const { return m_pSwapChain.GetInterfacePtr(); }
	ID3D11RenderTargetView* GetRenderTargetView()	const { return m_pRenderTargetView.GetInterfacePtr(); }
	ID3D11DepthStencilView* GetDepthStencilView()	const { return m_pDepthStencilView.GetInterfacePtr(); }
	D3D11_VIEWPORT			GetVP()					const { return m_ScreenViewport; }
	HWND					GetTargetHwnd()			const { return m_TargetHwnd; }
	RECT					GetScreenRectSize();

//=============================================================================
// protected Members) 
//=============================================================================
protected:
	ID3D11DevicePtr				m_pd3dDevice			= NULL;
	ID3D11DeviceContextPtr		m_pImmediateContext		= NULL;
	IDXGISwapChainPtr			m_pSwapChain			= NULL;
	ID3D11RenderTargetViewPtr	m_pRenderTargetView		= NULL;
	ID3D11DepthStencilViewPtr	m_pDepthStencilView		= NULL;
	ID3D11Texture2DPtr			m_pDepthStencilBuffer	= NULL;
	D3D11_VIEWPORT				m_ScreenViewport;

	HWND						m_TargetHwnd;

	bool						m_Enable4xMsaa			= true;
	UINT						m_4xMsaaQuality;

	D3D_DRIVER_TYPE				m_driverType			= D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL			m_featureLevel			= D3D_FEATURE_LEVEL_11_0;
};

}
#pragma once

// �ӽ�
#define gRENDERER JF::JFCDeviceDirectX11::GetInstance()

namespace JF
{
	class JFCDeviceDirectX11
	{
	//=============================================================================
	// Singletone)
	//=============================================================================
		SINGLETONE(JFCDeviceDirectX11)

	//=============================================================================
	// public Methods)
	//=============================================================================
	public:
		void DeviceInit(HWND _targetWindow);
		void DeviceDestory();

		void Reset();
		void Present();

		// Get)
		ID3D11Device*					Device()					const	{ return m_pDevice.GetInterfacePtr(); };
		ID3D11DeviceContext*			DeviceContext()				const	{ return m_pDeviceContext.GetInterfacePtr(); };
		IDXGISwapChain*					SwapChain()					const	{ return m_pSwapChain.GetInterfacePtr(); };
		ID3D11RenderTargetView*			BackBuffer()				const	{ return m_pBackBufferRTView.GetInterfacePtr(); };
		ID3D11DepthStencilView*			DepthStencilView()			const	{ return m_pAutoDSView; };
		ID3D11ShaderResourceView*		DepthStencilSRView()		const	{ return m_pAutoDSSRView; };

		const bool						FullScreen()				const	{ return m_bFullScreen; };
		const UINT						BackBufferWidth()			const	{ return m_nBackBufferWidth; };
		const UINT						BackBufferHeight()			const	{ return m_nBackBufferHeight; };

		// Set)
		void							SetBackBufferWidth(UINT _width)		{ m_nBackBufferWidth	= _width; };
		void							SetBackBufferHeight(UINT _height)	{ m_nBackBufferHeight	= _height; };

		// Create)
		void							CreateVertexBuffer(void* p_pVertices, UINT p_ByteWidth, ID3D11Buffer** p_pVB);
		void							CreateIndexBuffer(void* p_pIndices, UINT p_ByteWidth, ID3D11Buffer** p_pIB);

	//=============================================================================
	// Protected Methods)
	//=============================================================================
	protected:
		void AfterReset();
		void CheckForSuitableOutput();
		void PrepareFullScreenSettings();

	//=============================================================================
	// Protected Members)
	//=============================================================================
	protected:
		//
		ID3D11DevicePtr					m_pDevice;
		ID3D11DeviceContextPtr			m_pDeviceContext;
		IDXGISwapChainPtr				m_pSwapChain;
		ID3D11Texture2DPtr				m_pBackBufferTexture;
		ID3D11RenderTargetViewPtr		m_pBackBufferRTView;

		// DepthStencil �ؽ���
		bool							m_bEnableAutoDS;
		DXGI_FORMAT						m_AutoDSFormat;
		ID3D11Texture2DPtr				m_pAutoDSTexture;
		ID3D11DepthStencilViewPtr		m_pAutoDSView;

		// Shader ���� ����� DepthStencil �ؽ���
		bool							m_bUseAutoDSAsSR;
		ID3D11ShaderResourceViewPtr		m_pAutoDSSRView;

		// 
		IDXGIFactory1Ptr                m_pFactory;
		IDXGIAdapter1Ptr                m_pAdapter;
		IDXGIOutputPtr                  m_pOutput;

		// ȭ�鰻�� Rate
		DXGI_RATIONAL					m_RefreshRate;

		// MSAA ����.
		UINT							m_nMSCount;
		UINT							m_nMSQuality;

		// Device ���� ����.
		D3D_FEATURE_LEVEL				m_FeatureLevel;
		D3D_FEATURE_LEVEL				m_MinFeatureLevel;

		// BackBuffer ����.
		DXGI_FORMAT						m_BackBufferFormat;
		UINT							m_nBackBufferWidth;
		UINT							m_nBackBufferHeight;

		// �ɼ�.
		bool							m_bSync;
		bool							m_bFullScreen;
	};
}
#pragma once

// 임시
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
		void AfterReset();
		void Present();

		void AutoRander(std::vector<JF::GameObject*>& _objectList, JF::GameObject* _mainLights[MAIN_LIGHT_COUNT], JFCGameTimer* _pTimer);

		// Get)
		ID3D11Device*					Device()					const	{ return m_pDevice.GetInterfacePtr(); };
		ID3D11DeviceContext*			DeviceContext()				const	{ return m_pDeviceContext.GetInterfacePtr(); };
		IDXGISwapChain*					SwapChain()					const	{ return m_pSwapChain.GetInterfacePtr(); };
		ID3D11RenderTargetView*			BackBuffer()				const	{ return m_pBackBufferRTView.GetInterfacePtr(); };
		ID3D11DepthStencilView*			DepthStencilView()			const	{ return m_pAutoDSView.GetInterfacePtr(); };
		ID3D11ShaderResourceView*		DepthStencilSRView()		const	{ return m_pAutoDSSRView.GetInterfacePtr(); };
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
		void CheckForSuitableOutput();
		void PrepareFullScreenSettings();

		// GBuffer Render
		void GBufferRender(std::vector<JF::GameObject*>& _objectList);
		
		// Light Pre Pass Render
		void LightPrePassLightBufferRender(std::vector<JF::GameObject*>& _objectList);

		// Shadow Render
		void ShadowRender(std::vector<JF::GameObject*>& _objectList, JF::GameObject* _mainLights[MAIN_LIGHT_COUNT]);

		// GeometryRender
		void GeometryRender(std::vector<JF::GameObject*>& _objectList, JF::GameObject* _mainLights[MAIN_LIGHT_COUNT], JFCGameTimer* _pTimer);

		// SSAORender
		void SSAORender();
		void SSAOBlurRender(ID3D11ShaderResourceView* _inputSRV, ID3D11RenderTargetView* _outputRTV, bool _horzBlur);

		// Test Render
		void DebugRender(ID3D11ShaderResourceView* _resourceview, XMFLOAT3 _scale, XMFLOAT3 _position, bool _viewOnlyRed);

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
		ID3D11ShaderResourceViewPtr		m_pBackBufferSTView;
		D3D11_VIEWPORT					m_ScreenViewport;

		// DepthStencil 텍스쳐
		bool							m_bEnableAutoDS;
		DXGI_FORMAT						m_AutoDSFormat;
		ID3D11Texture2DPtr				m_pAutoDSTexture;
		ID3D11DepthStencilViewPtr		m_pAutoDSView;

		// Shader 에서 사용할 DepthStencil 텍스쳐
		bool							m_bUseAutoDSAsSR;
		ID3D11ShaderResourceViewPtr		m_pAutoDSSRView;

		// 그림자맵
		ID3D11DepthStencilViewPtr		m_pShadowMapDSView;
		ID3D11ShaderResourceViewPtr		m_pShadowMapSRView;
		D3D11_VIEWPORT					m_ShadowMapViewport;
		XMFLOAT4X4						m_LightView;
		XMFLOAT4X4						m_LightProj;
		XMFLOAT4X4						m_ShadowTransform;

		// 그림자맵 설정값들.
		const UINT						m_nShadowMapSize	= 2048;
		XMFLOAT3						m_SceneBoundsCenter = XMFLOAT3(0.0f, 0.0f, 0.0f);
		float							m_SceneBoundsRadius = sqrtf(20000);

		// G-Buffers
		JF::RenderMap::JFGBuffer*		m_pGBuffer;

		// SSAO
		JF::RenderMap::JFSSAO*			m_pSSAO;

		// Light Buffer
		ID3D11Texture2DPtr				m_pLightBufferTexture;
		ID3D11RenderTargetViewPtr		m_pLightBufferRTView;
		ID3D11ShaderResourceViewPtr		m_pLightBufferSRView;

		// Temp
		
		JF::Component::Mesh*			m_BoxMesh;

		// 
		IDXGIFactory1Ptr                m_pFactory;
		IDXGIAdapter1Ptr                m_pAdapter;
		IDXGIOutputPtr                  m_pOutput;

		// 화면갱신 Rate
		DXGI_RATIONAL					m_RefreshRate;

		// MSAA 정보.
		UINT							m_nMSCount;
		UINT							m_nMSQuality;

		// Device 지원 레벨.
		D3D_FEATURE_LEVEL				m_FeatureLevel;
		D3D_FEATURE_LEVEL				m_MinFeatureLevel;

		// BackBuffer 정보.
		DXGI_FORMAT						m_BackBufferFormat;
		UINT							m_nBackBufferWidth;
		UINT							m_nBackBufferHeight;

		// 옵션.
		bool							m_bSync;
		bool							m_bFullScreen;
	};
}
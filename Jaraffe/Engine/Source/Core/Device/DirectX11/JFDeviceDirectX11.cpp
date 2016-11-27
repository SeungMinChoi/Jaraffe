#include "stdafx.h"
#include "JFDeviceDirectX11.h"


JF::JFCDeviceDirectX11::JFCDeviceDirectX11()
	: m_BackBufferFormat(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
	, m_nBackBufferWidth(START_CLIENT_WIDTH)
	, m_nBackBufferHeight(START_CLIENT_HEIGHT)
	, m_FeatureLevel(D3D_FEATURE_LEVEL_11_0)
	, m_MinFeatureLevel(D3D_FEATURE_LEVEL_11_0)
	, m_nMSCount(1)
	, m_nMSQuality(0)
	, m_bSync(true)
	, m_bFullScreen(false)
	, m_AutoDSFormat(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT)
	, m_bEnableAutoDS(true)
	, m_bUseAutoDSAsSR(false)
{
	m_RefreshRate.Numerator		= 60;
	m_RefreshRate.Denominator	= 1;
}

JF::JFCDeviceDirectX11::~JFCDeviceDirectX11()
{
	DeviceDestory();
}

void JF::JFCDeviceDirectX11::DeviceInit(HWND _targetWindow)
{
	// 1) D3D11 지원여부를 체크하고 어뎁터를 얻는다.
	CheckForSuitableOutput();

	// 2) 전체화면 여부에따른 셋팅을 해준다.
	if (m_bFullScreen)
		PrepareFullScreenSettings();
	else
	{
		m_RefreshRate.Numerator		= 60;
		m_RefreshRate.Denominator	= 1;
	}

	// 3) SwapChain 을 셋팅 한다.
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount					= 2;
	desc.BufferDesc.Format				= m_BackBufferFormat;
	desc.BufferDesc.Width				= m_nBackBufferWidth;
	desc.BufferDesc.Height				= m_nBackBufferHeight;
	desc.BufferDesc.Scaling				= DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering	= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.RefreshRate			= m_RefreshRate;
	desc.SampleDesc.Count				= m_nMSCount;
	desc.SampleDesc.Quality				= m_nMSQuality;
	desc.BufferUsage					= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags							= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.SwapEffect						= DXGI_SWAP_EFFECT_DISCARD;
	desc.OutputWindow					= _targetWindow;
	desc.Windowed						= !m_bFullScreen;

	UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 4) Divice,DeviceContext,SwapChain 을 생성한다
	JF::Utile::DXCall(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags,
		NULL, 0, D3D11_SDK_VERSION, &desc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext));

	m_FeatureLevel = m_pDevice->GetFeatureLevel();

	if (m_FeatureLevel < m_MinFeatureLevel)
	{
		std::wstring majorLevel = JF::Utile::ToString<int>(m_MinFeatureLevel >> 12);
		std::wstring minorLevel = JF::Utile::ToString<int>((m_MinFeatureLevel >> 8) & 0xF);
		throw JFCException(L"The device doesn't support the minimum feature level required to run this sample (DX" + majorLevel + L"." + minorLevel + L")");
	}

	AfterReset();
}

void JF::JFCDeviceDirectX11::DeviceDestory()
{
	if (m_pDeviceContext)
	{
		m_pDeviceContext->ClearState();
		m_pDeviceContext->Flush();
	}
}

void JF::JFCDeviceDirectX11::Reset()
{
	_ASSERT(m_pSwapChain);

	// Release all references
	if (m_pBackBufferTexture)
		m_pBackBufferTexture.Release();

	if (m_pBackBufferRTView)
		m_pBackBufferRTView.Release();

	if (m_pAutoDSTexture)
		m_pAutoDSTexture.Release();

	if (m_pAutoDSSRView)
		m_pAutoDSSRView.Release();

	if (m_pAutoDSSRView)
		m_pAutoDSSRView.Release();

	m_pDeviceContext->ClearState();

	if (m_bFullScreen)
		PrepareFullScreenSettings();
	else
	{
		m_RefreshRate.Numerator		= 60;
		m_RefreshRate.Denominator	= 1;
	}

	JF::Utile::DXCall(m_pSwapChain->SetFullscreenState(m_bFullScreen, NULL));

	JF::Utile::DXCall(m_pSwapChain->ResizeBuffers(2, m_nBackBufferWidth, m_nBackBufferHeight, m_BackBufferFormat, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

	if (m_bFullScreen)
	{
		DXGI_MODE_DESC mode;
		mode.Format						= m_BackBufferFormat;
		mode.Width						= m_nBackBufferWidth;
		mode.Height						= m_nBackBufferHeight;
		mode.RefreshRate.Numerator		= 0;
		mode.RefreshRate.Denominator	= 0;
		mode.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
		mode.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		JF::Utile::DXCall(m_pSwapChain->ResizeTarget(&mode));
	}

	AfterReset();
}

void JF::JFCDeviceDirectX11::Present()
{
	_ASSERT(m_pDevice);

	UINT interval = m_bSync ? 1 : 0;
	JF::Utile::DXCall(m_pSwapChain->Present(interval, 0));
}

void JF::JFCDeviceDirectX11::CreateVertexBuffer(void* p_pVertices, UINT p_ByteWidth, ID3D11Buffer** p_pVB)
{
	// Check
	assert(p_pVertices != nullptr);

	//
	D3D11_BUFFER_DESC vbd;
	vbd.Usage				= D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth			= p_ByteWidth;
	vbd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags		= 0;
	vbd.MiscFlags			= 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = p_pVertices;

	// Create
	HR(m_pDevice->CreateBuffer(&vbd, &vinitData, p_pVB));
}

void JF::JFCDeviceDirectX11::CreateIndexBuffer(void* p_pIndices, UINT p_ByteWidth, ID3D11Buffer** p_pIB)
{
	assert(p_pIndices != nullptr);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage				= D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth			= p_ByteWidth;
	vbd.BindFlags			= D3D11_BIND_INDEX_BUFFER;
	vbd.CPUAccessFlags		= 0;
	vbd.MiscFlags			= 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = p_pIndices;

	HR(m_pDevice->CreateBuffer(&vbd, &vinitData, p_pIB));
}

void JF::JFCDeviceDirectX11::AfterReset()
{
	// 1) 랜더타켓을 생성한다.
	JF::Utile::DXCall(m_pSwapChain->GetBuffer(0, __uuidof(m_pBackBufferTexture), reinterpret_cast<void**>(&m_pBackBufferTexture)));
	JF::Utile::DXCall(m_pDevice->CreateRenderTargetView(m_pBackBufferTexture, NULL, &m_pBackBufferRTView));

	// 2) Create a default DepthStencil buffer
	if (m_bEnableAutoDS)
	{
		UINT bindFlags = D3D11_BIND_DEPTH_STENCIL;
		if (m_bUseAutoDSAsSR)
			bindFlags |= D3D11_BIND_SHADER_RESOURCE;

		DXGI_FORMAT dsTexFormat;
		if (!m_bUseAutoDSAsSR)
			dsTexFormat = m_AutoDSFormat;
		else if (m_AutoDSFormat == DXGI_FORMAT_D16_UNORM)
			dsTexFormat = DXGI_FORMAT_R16_TYPELESS;
		else if (m_AutoDSFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
			dsTexFormat = DXGI_FORMAT_R24G8_TYPELESS;
		else
			dsTexFormat = DXGI_FORMAT_R32_TYPELESS;

		D3D11_TEXTURE2D_DESC dsDesc;
		dsDesc.Width				= m_nBackBufferWidth;
		dsDesc.Height				= m_nBackBufferHeight;
		dsDesc.ArraySize			= 1;
		dsDesc.BindFlags			= bindFlags;
		dsDesc.CPUAccessFlags		= 0;
		dsDesc.Format				= dsTexFormat;
		dsDesc.MipLevels			= 1;
		dsDesc.MiscFlags			= 0;
		dsDesc.SampleDesc.Count		= m_nMSCount;
		dsDesc.SampleDesc.Quality	= m_nMSQuality;
		dsDesc.Usage				= D3D11_USAGE_DEFAULT;
		JF::Utile::DXCall(m_pDevice->CreateTexture2D(&dsDesc, NULL, &m_pAutoDSTexture));

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Format				= m_AutoDSFormat;
		dsvDesc.ViewDimension		= m_nMSCount > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;;
		dsvDesc.Texture2D.MipSlice	= 0;
		dsvDesc.Flags				= 0;
		JF::Utile::DXCall(m_pDevice->CreateDepthStencilView(m_pAutoDSTexture, &dsvDesc, &m_pAutoDSView));

		if (m_bUseAutoDSAsSR)
		{
			DXGI_FORMAT dsSRVFormat;
			if (m_AutoDSFormat == DXGI_FORMAT_D16_UNORM)
				dsSRVFormat = DXGI_FORMAT_R16_UNORM;
			else if (m_AutoDSFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
				dsSRVFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			else
				dsSRVFormat = DXGI_FORMAT_R32_FLOAT;

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format						= dsSRVFormat;
			srvDesc.ViewDimension				= m_nMSCount > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels			= 1;
			srvDesc.Texture2D.MostDetailedMip	= 0;
			JF::Utile::DXCall(m_pDevice->CreateShaderResourceView(m_pAutoDSTexture, &srvDesc, &m_pAutoDSSRView));
		}
		else
		{
			m_pAutoDSSRView = NULL;
		}
	}

	// 3) Set default render targets
	m_pDeviceContext->OMSetRenderTargets(1, &(m_pBackBufferRTView.GetInterfacePtr()), m_pAutoDSView);

	// 4) Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width	= static_cast<float>(m_nBackBufferWidth);
	vp.Height	= static_cast<float>(m_nBackBufferHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);
}

void JF::JFCDeviceDirectX11::CheckForSuitableOutput()
{
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&m_pFactory));
	if (FAILED(hr))
		throw JFCException(L"Unable to create a DXGI 1.1 device.\n Make sure your OS and driver support DirectX 11");

	// D3D11 를 지원하는 adapter 를 찾는다.
	IDXGIAdapter1Ptr curAdapter;
	while (!m_pAdapter && SUCCEEDED(m_pFactory->EnumAdapters1(0, &m_pAdapter)))
		if (SUCCEEDED(m_pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), NULL)))
			m_pAdapter = curAdapter;

	if (!m_pAdapter)
		throw JFCException(L"Unable to locate a DXGI 1.1 adapter that supports a D3D11 device.\n Make sure your OS and driver support DirectX 11");

	// 여러개의 어뎁터가 있더라도 첫번째 출력만 사용합니다.
	JF::Utile::DXCall(m_pAdapter->EnumOutputs(0, &m_pOutput));
}

void JF::JFCDeviceDirectX11::PrepareFullScreenSettings()
{
	_ASSERT(m_pOutput);

	// Have the Output look for the closest matching mode
	DXGI_MODE_DESC desiredMode;
	desiredMode.Format					= m_BackBufferFormat;
	desiredMode.Width					= m_nBackBufferWidth;
	desiredMode.Height					= m_nBackBufferHeight;
	desiredMode.RefreshRate.Numerator	= 0;
	desiredMode.RefreshRate.Denominator = 0;
	desiredMode.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	desiredMode.ScanlineOrdering		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	DXGI_MODE_DESC closestMatch;
	JF::Utile::DXCall(m_pOutput->FindClosestMatchingMode(&desiredMode, &closestMatch, m_pDevice.GetInterfacePtr()));

	m_BackBufferFormat	= closestMatch.Format;
	m_nBackBufferWidth	= closestMatch.Width;
	m_nBackBufferHeight = closestMatch.Height;
	m_RefreshRate		= closestMatch.RefreshRate;
}

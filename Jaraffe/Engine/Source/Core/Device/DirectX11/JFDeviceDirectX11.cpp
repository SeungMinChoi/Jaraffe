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
	, m_bUseAutoDSAsSR(true)
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
	// 1) D3D11 �������θ� üũ�ϰ� ��͸� ��´�.
	CheckForSuitableOutput();

	// 2) ��üȭ�� ���ο����� ������ ���ش�.
	if (m_bFullScreen)
		PrepareFullScreenSettings();
	else
	{
		m_RefreshRate.Numerator		= 60;
		m_RefreshRate.Denominator	= 1;
	}

	// 3) SwapChain �� ���� �Ѵ�.
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

	// 4) Divice,DeviceContext,SwapChain �� �����Ѵ�
	JF::Utile::DXCall(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags,
		NULL, 0, D3D11_SDK_VERSION, &desc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext));

	m_FeatureLevel = m_pDevice->GetFeatureLevel();

	if (m_FeatureLevel < m_MinFeatureLevel)
	{
		std::wstring majorLevel = JF::Utile::ToString<int>(m_MinFeatureLevel >> 12);
		std::wstring minorLevel = JF::Utile::ToString<int>((m_MinFeatureLevel >> 8) & 0xF);
		throw JFCException(L"The device doesn't support the minimum feature level required to run this sample (DX" + majorLevel + L"." + minorLevel + L")");
	}

	// 5) Map ��ü���� ����/���� �Ѵ�.
	m_pSSAO		= new JF::RenderMap::JFSSAO();
	m_pGBuffer	= new JF::RenderMap::JFGBuffer();

	// 6)
	m_pSSAO->Init(m_pDevice);

	// 7) Scene ��ü�� ���� Box�޽��� �����.
	m_BoxMesh = new JF::Component::Mesh();
	JF::GeometryGenerator::CreateFullscreenQuad(m_BoxMesh->GetVertices(), m_BoxMesh->GetIndices());
	m_BoxMesh->Reset();
}

void JF::JFCDeviceDirectX11::DeviceDestory()
{
	// 1) Delete BufferMap
	SafeDelete(m_pSSAO);
	SafeDelete(m_pGBuffer);

	// 2)
	SafeDelete(m_BoxMesh);

	// 3)
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
	ReleaseCOM_PTR(m_pBackBufferTexture);
	ReleaseCOM_PTR(m_pBackBufferRTView);
	ReleaseCOM_PTR(m_pAutoDSTexture);
	ReleaseCOM_PTR(m_pAutoDSView);
	ReleaseCOM_PTR(m_pAutoDSSRView);

	ReleaseCOM_PTR(m_pShadowMapDSView);
	ReleaseCOM_PTR(m_pShadowMapSRView);

	ReleaseCOM_PTR(m_pLightBufferTexture);
	ReleaseCOM_PTR(m_pLightBufferRTView);
	ReleaseCOM_PTR(m_pLightBufferSRView);

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
}

void JF::JFCDeviceDirectX11::Present()
{
	_ASSERT(m_pDevice);

	UINT interval = m_bSync ? 1 : 0;
	JF::Utile::DXCall(m_pSwapChain->Present(interval, 0));
}

void JF::JFCDeviceDirectX11::AutoRander(std::vector<JF::GameObject*>& _objectList, JF::GameObject* _mainLights[MAIN_LIGHT_COUNT], JFCGameTimer* _pTimer)
{
	// 1)
	GBufferRender(_objectList);

	// 2)
	SSAORender();

	// 3)
	m_pDeviceContext->OMSetDepthStencilState(RenderStates::GetDepthStencilStates()->EqualsDSS(), 0);
	for (int i = 0; i < 4; ++i)
	{
		// Ping-pong the two ambient map textures as we apply
		// horizontal and vertical blur passes.
		SSAOBlurRender(m_pSSAO->GetAmbient1SRV(), m_pSSAO->GetAmbient2RTV(), true);
		SSAOBlurRender(m_pSSAO->GetAmbient2SRV(), m_pSSAO->GetAmbient1RTV(), false);
	}
	m_pDeviceContext->OMSetDepthStencilState(0, 0);

	// 4)
	LightPrePassLightBufferRender(_objectList);

	// 5)
	ShadowRender(_objectList, _mainLights);

	// 6)
	GeometryRender(_objectList, _mainLights, _pTimer);

	// 7)
	TestRender();
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
	// 1) ����Ÿ���� �����Ѵ�.
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

	// 4)
	{
		D3D11_TEXTURE2D_DESC desc;
		desc.Width = m_nBackBufferWidth;
		desc.Height = m_nBackBufferHeight;
		desc.ArraySize = 1;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		desc.MipLevels = 1;
		desc.MiscFlags = 1;
		desc.SampleDesc.Count = m_nMSCount;
		desc.SampleDesc.Quality = m_nMSQuality;
		desc.Usage = D3D11_USAGE_DEFAULT;

		JF::Utile::DXCall(m_pDevice->CreateTexture2D(&desc, NULL, &m_pLightBufferTexture));
		JF::Utile::DXCall(m_pDevice->CreateRenderTargetView(m_pLightBufferTexture, NULL, &m_pLightBufferRTView));
		JF::Utile::DXCall(m_pDevice->CreateShaderResourceView(m_pLightBufferTexture, NULL, &m_pLightBufferSRView));
	}
	
	// 3) Create G-Buffer
	m_pGBuffer->Reset(m_pDevice, m_nBackBufferWidth, m_nBackBufferHeight, m_nMSCount, m_nMSQuality);

	// 4) Create SSAO Buffer
	if(Camera::g_pMainCamera != nullptr)
		m_pSSAO->Reset(m_pDevice, m_nBackBufferWidth, m_nBackBufferHeight, Camera::g_pMainCamera->GetFarY(), Camera::g_pMainCamera->GetFarZ());

	// 5) �׸��ڸ� ������ �Ѵ�.
	{
		m_ShadowMapViewport.Width = static_cast<float>(m_nShadowMapSize);
		m_ShadowMapViewport.Height = static_cast<float>(m_nShadowMapSize);
		m_ShadowMapViewport.MinDepth = 0.0f;
		m_ShadowMapViewport.MaxDepth = 1.0f;
		m_ShadowMapViewport.TopLeftX = 0.0f;
		m_ShadowMapViewport.TopLeftY = 0.0f;

		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width = m_nShadowMapSize;
		texDesc.Height = m_nShadowMapSize;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;

		ID3D11Texture2D* pdepthMap = 0;
		HR(m_pDevice->CreateTexture2D(&texDesc, 0, &pdepthMap));

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Flags				= 0;
		dsvDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice	= 0;
		HR(m_pDevice->CreateDepthStencilView(pdepthMap, &dsvDesc, &m_pShadowMapDSView));

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format						= DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		srvDesc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels			= texDesc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip	= 0;
		HR(m_pDevice->CreateShaderResourceView(pdepthMap, &srvDesc, &m_pShadowMapSRView));

		// View saves a reference to the texture so we can release our reference.
		ReleaseCOM(pdepthMap);
	}

	// 6) Setup the viewport
	m_ScreenViewport.Width			= static_cast<float>(m_nBackBufferWidth);
	m_ScreenViewport.Height			= static_cast<float>(m_nBackBufferHeight);
	m_ScreenViewport.MinDepth		= 0.0f;
	m_ScreenViewport.MaxDepth		= 1.0f;
	m_ScreenViewport.TopLeftX		= 0;
	m_ScreenViewport.TopLeftY		= 0;

	m_pDeviceContext->RSSetViewports(1, &m_ScreenViewport);
}

void JF::JFCDeviceDirectX11::CheckForSuitableOutput()
{
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&m_pFactory));
	if (FAILED(hr))
		throw JFCException(L"Unable to create a DXGI 1.1 device.\n Make sure your OS and driver support DirectX 11");

	// D3D11 �� �����ϴ� adapter �� ã�´�.
	IDXGIAdapter1Ptr curAdapter;
	while (!m_pAdapter && SUCCEEDED(m_pFactory->EnumAdapters1(0, &m_pAdapter)))
		if (SUCCEEDED(m_pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), NULL)))
			m_pAdapter = curAdapter;

	if (!m_pAdapter)
		throw JFCException(L"Unable to locate a DXGI 1.1 adapter that supports a D3D11 device.\n Make sure your OS and driver support DirectX 11");

	// �������� ��Ͱ� �ִ��� ù��° ��¸� ����մϴ�.
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

void JF::JFCDeviceDirectX11::GBufferRender(std::vector<JF::GameObject*>& _objectList)
{
	// 1) Set RanderTarget
	ID3D11RenderTargetView* renderTargets[3] = { m_pGBuffer->GetWorldNormalRTV(), m_pGBuffer->GetWorldPositionRTV(), m_pGBuffer->GetViewNormalDepthRTV() };
	m_pDeviceContext->OMSetRenderTargets(3, renderTargets, m_pAutoDSView.GetInterfacePtr());

	// 2) Buffer Clear.
	m_pDeviceContext->ClearRenderTargetView(m_pGBuffer->GetWorldNormalRTV(), reinterpret_cast<const float*>(&JF::Util::Colors::Black));
	m_pDeviceContext->ClearRenderTargetView(m_pGBuffer->GetWorldPositionRTV(), reinterpret_cast<const float*>(&JF::Util::Colors::Black));
	m_pDeviceContext->ClearRenderTargetView(m_pGBuffer->GetViewNormalDepthRTV(), reinterpret_cast<const float*>(&JF::Util::Colors::Black));

	// 3) Depth And Stencil View Clear.
	m_pDeviceContext->ClearDepthStencilView(m_pAutoDSView.GetInterfacePtr(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// 4) Set ViewPort
	m_pDeviceContext->RSSetViewports(1, &m_ScreenViewport);

	// 5) Render All Object Loop 
	for each(auto object in _objectList)
	{
		// Check)
		CONTINUE_IF(object == nullptr);

		// 5-1) Renderer ��ü�� ã�´�.
		auto pRenderer = object->GetComponent<JF::Component::Renderer>();

		// Check)
		CONTINUE_IF(pRenderer == nullptr);

		// 5-2) Rendering �� �ʿ��� ������ ã�´�.
		auto* pMesh			= object->GetComponent<JF::Component::Mesh>();
		auto* pMarerial		= pRenderer->GetMaterial();
		auto* pTransform	= object->GetComponent<JF::Component::Transform>();

		// Check)
		CONTINUE_IF(pMesh == nullptr);
		CONTINUE_IF(pMarerial == nullptr);
		CONTINUE_IF(pTransform == nullptr);

		// 5-3) Set Layout And Topology
		m_pDeviceContext->IASetInputLayout(pMesh->GetInputLayout());
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 5-4) Set VertexBuffer And IndexBuffer
		UINT stride = pMesh->GetStride();
		UINT offset = 0;
		ID3D11Buffer* pVB = pMesh->GetVB();
		ID3D11Buffer* pIB = pMesh->GetIB();
		m_pDeviceContext->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
		m_pDeviceContext->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

		// 5-5) worldViewProj ����� ���Ѵ�.
		XMMATRIX world					= XMLoadFloat4x4(&pTransform->GetTransformMatrix());
		XMMATRIX view					= Camera::g_pMainCamera->GetView();
		XMMATRIX proj					= Camera::g_pMainCamera->GetProj();
		XMMATRIX worldView				= world * view;
		XMMATRIX worldViewProj			= worldView * proj;
		XMMATRIX worldInvTransposeView	= JF::Util::MathHelper::InverseTranspose(world) * view;

		// 5-6) ���̴��� ����� ����.
		Effects::GBufferFX->SetWorld(world);
		Effects::GBufferFX->SetWorldView(worldView);
		Effects::GBufferFX->SetWorldViewProj(worldViewProj);
		Effects::GBufferFX->SetWorldInvTransposeView(worldInvTransposeView);

		// AlphaClip �ɼ� �߰��� ���.
		//if(useAlphaClip && pMarerial->m_MainTexture != nullptr)
		//	Effects::GBufferFX->SetDiffuseMap(pMarerial->m_MainTexture->GetTexture());

		// 
		if (pMarerial->m_BumpTexture != nullptr)
			Effects::GBufferFX->SetNormalMap(pMarerial->m_BumpTexture->GetTexture());

		// 5-7) Render
		ID3DX11EffectTechnique* tech = Effects::GBufferFX->GetTech(pMarerial->m_BumpTexture != nullptr, false);
		D3DX11_TECHNIQUE_DESC techDesc;
		tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			tech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
		}
	}
}

void JF::JFCDeviceDirectX11::LightPrePassLightBufferRender(std::vector<JF::GameObject*>& _objectList)
{
	// 1) Set RanderTarget
	m_pDeviceContext->OMSetRenderTargets(1, &(m_pLightBufferRTView.GetInterfacePtr()), nullptr);

	// 2) Buffer Clear.
	m_pDeviceContext->ClearRenderTargetView(m_pLightBufferRTView.GetInterfacePtr(), reinterpret_cast<const float*>(&JF::Util::Colors::Black));

	// 3) Set ViewPort
	m_pDeviceContext->RSSetViewports(1, &m_ScreenViewport);

	// 4) Set Layout And Topology
	gRENDERER->DeviceContext()->IASetInputLayout(InputLayouts::PosNormalTexTan);
	gRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 5) ����ȥ������ �����Ѵ�.
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	gRENDERER->DeviceContext()->OMSetBlendState(JF::RenderStates::GetBlendStates()->AdditiveBlend(), blendFactors, 0xffffffff);

	// 6) Set VertexBuffer And IndexBuffer
	UINT stride = m_BoxMesh->GetStride();
	UINT offset = 0;
	ID3D11Buffer* pVB = m_BoxMesh->GetVB();
	ID3D11Buffer* pIB = m_BoxMesh->GetIB();
	m_pDeviceContext->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

	// 7) ���̴��� ���� ����� ����.
	Effects::LightPrePassLightBufferFX->SetCameraPos(Camera::g_pMainCamera->GetEyePos());
	Effects::LightPrePassLightBufferFX->SetNormalTexture(m_pGBuffer->GetWorldNormalSRV());
	Effects::LightPrePassLightBufferFX->SetPositionTexture(m_pGBuffer->GetWorldPositionSRV());

	// 8) All Light Render
	for each (auto object in _objectList)
	{
		// Get Light Component)
		auto* transform = object->GetComponent<JF::Component::Transform>();

		// Check)
		CONTINUE_IF(transform == nullptr);

		// Declear)
		ID3DX11EffectTechnique* tech;

		auto* pPointLight	= object->GetComponent<JF::Component::JFPointLight>();
		auto* pSpotLight	= object->GetComponent<JF::Component::JFSpotLight>();
		if (pPointLight != nullptr)
		{
			Effects::LightPrePassLightBufferFX->SetLightPos(transform->GetPosition());
			Effects::LightPrePassLightBufferFX->SetLightColor(XMFLOAT3(pPointLight->GetDiffuse().x, pPointLight->GetDiffuse().y, pPointLight->GetDiffuse().z));
			Effects::LightPrePassLightBufferFX->SetLightRange(pPointLight->GetRange());

			tech = Effects::LightPrePassLightBufferFX->PointLightTech;
		}
		else if (pSpotLight != nullptr)
		{
			Effects::LightPrePassLightBufferFX->SetLightPos(transform->GetPosition());
			Effects::LightPrePassLightBufferFX->SetLightColor(XMFLOAT3(pSpotLight->GetDiffuse().x, pSpotLight->GetDiffuse().y, pSpotLight->GetDiffuse().z));
			Effects::LightPrePassLightBufferFX->SetLightRange(pSpotLight->GetRange());
			Effects::LightPrePassLightBufferFX->SetLightDirection(pSpotLight->GetDirection());
			Effects::LightPrePassLightBufferFX->SetSpotlightAngles(XMFLOAT2(1.0f, 0.9f));

			tech = Effects::LightPrePassLightBufferFX->SpotLightTech;
		}
		else
		{
			continue;
		}

		D3DX11_TECHNIQUE_DESC techDesc;
		tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			tech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(m_BoxMesh->GetIndexCount(), 0, 0);
		}
	}

	gRENDERER->DeviceContext()->OMSetBlendState(0, blendFactors, 0xffffffff);
}

void JF::JFCDeviceDirectX11::ShadowRender(std::vector<JF::GameObject*>& _objectList, JF::GameObject* _mainLights[MAIN_LIGHT_COUNT])
{
	// 1) Set RanderTarget / Depth And Stencil View Clear.
	ID3D11RenderTargetView* renderTargets[1] = { 0 };
	m_pDeviceContext->OMSetRenderTargets(1, renderTargets, m_pShadowMapDSView.GetInterfacePtr());
	m_pDeviceContext->ClearDepthStencilView(m_pShadowMapDSView.GetInterfacePtr(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	// 2) Set ViewPort
	m_pDeviceContext->RSSetViewports(1, &m_ShadowMapViewport);

	// 3) Get Light ( �ϴ� �׸��ڴ� DirectionalLight �� ���� )
	auto pmainLight = _mainLights[0]->GetComponent<JFDirectionalLight>();

	// 4) ����Ʈ �� �������� �׸��ڸ�(����) ����.
	XMVECTOR lightDir = XMLoadFloat3(&pmainLight->GetDirection());
	XMVECTOR lightPos = -2.0f * m_SceneBoundsRadius * lightDir;
	XMVECTOR targetPos = XMLoadFloat3(&m_SceneBoundsCenter);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(lightPos, targetPos, up);

	// 5) ��豸�� ���� �������� ��ȯ�Ѵ�.
	XMFLOAT3 sphereCenterLS;
	XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));

	// 6) ����� ���δ� ���� ���� �������� ����.
	float l = sphereCenterLS.x - m_SceneBoundsRadius;
	float b = sphereCenterLS.y - m_SceneBoundsRadius;
	float n = sphereCenterLS.z - m_SceneBoundsRadius;
	float r = sphereCenterLS.x + m_SceneBoundsRadius;
	float t = sphereCenterLS.y + m_SceneBoundsRadius;
	float f = sphereCenterLS.z + m_SceneBoundsRadius;
	XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	// 7) NDC ���� [-1, +1]^2 �� �ؽ�ó ���� [0, 1]^2 ���� ��ȯ�Ѵ�. 
	XMMATRIX T(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	XMMATRIX S = V * P * T;

	XMStoreFloat4x4(&m_LightView, V);
	XMStoreFloat4x4(&m_LightProj, P);
	XMStoreFloat4x4(&m_ShadowTransform, S);

	// 10) 
	for each (auto object in _objectList)
	{
		// Check)
		CONTINUE_IF(object == nullptr);

		// 10-1) Renderer ��ü�� ã�´�.
		auto pRenderer = object->GetComponent<JF::Component::Renderer>();

		// Check)
		CONTINUE_IF(pRenderer == nullptr);

		// 10-2) Rendering �� �ʿ��� ������ ã�´�.
		auto* pMesh			= object->GetComponent<JF::Component::Mesh>();
		auto* pMarerial		= pRenderer->GetMaterial();
		auto* pTransform	= object->GetComponent<JF::Component::Transform>();

		// Check)
		CONTINUE_IF(pMesh == nullptr);
		CONTINUE_IF(pMarerial == nullptr);
		CONTINUE_IF(pTransform == nullptr);

		// 10-3)
		m_pDeviceContext->IASetInputLayout(pMesh->GetInputLayout());
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Set VertexBuffer And IndexBuffer
		UINT stride = pMesh->GetStride();
		UINT offset = 0;
		ID3D11Buffer* pVB = pMesh->GetVB();
		ID3D11Buffer* pIB = pMesh->GetIB();
		m_pDeviceContext->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
		m_pDeviceContext->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

		//
		XMMATRIX view			= XMLoadFloat4x4(&m_LightView);
		XMMATRIX proj			= XMLoadFloat4x4(&m_LightProj);
		XMMATRIX world			= XMLoadFloat4x4(&pTransform->GetTransformMatrix());
		XMMATRIX worldViewProj	= world * view * proj;

		//
		Effects::ShadowBufferFX->SetWorldViewProj(worldViewProj);

		//
		ID3DX11EffectTechnique* smapTech = Effects::ShadowBufferFX->BuildShadowMapTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		smapTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			smapTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			// ���� 36���� ���ڸ� �׸���.
			m_pDeviceContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
		}
	}
}

void JF::JFCDeviceDirectX11::GeometryRender(std::vector<JF::GameObject*>& _objectList, JF::GameObject* _mainLights[MAIN_LIGHT_COUNT], JFCGameTimer* _pTimer)
{
	// Declear)
	// Transform NDC space [-1,+1]^2 to texture space [0,1]^2
	XMMATRIX toTexSpace(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// 1) Set RanderTarget
	m_pDeviceContext->OMSetRenderTargets(1, &(m_pBackBufferRTView.GetInterfacePtr()), m_pAutoDSView.GetInterfacePtr());

	// 2) Buffer Clear.
	m_pDeviceContext->ClearRenderTargetView(m_pBackBufferRTView.GetInterfacePtr(), reinterpret_cast<const float*>(&JF::Util::Colors::Black));

	// 3) Depth And Stencil View Clear.
	m_pDeviceContext->ClearDepthStencilView(m_pAutoDSView.GetInterfacePtr(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// 4) Set ViewPort
	m_pDeviceContext->RSSetViewports(1, &m_ScreenViewport);

	// 5) Render All Object Loop 
	for each(auto object in _objectList)
	{
		// Check)
		CONTINUE_IF(object == nullptr);

		// 1-1) Renderer ��ü�� ã�´�.
		auto pRenderer = object->GetComponent<JF::Component::Renderer>();

		// Check)
		CONTINUE_IF(pRenderer == nullptr);

		// 1-2) Rendering �� �ʿ��� ������ ã�´�.
		auto* pMesh			= object->GetComponent<JF::Component::Mesh>();
		auto* pMarerial		= pRenderer->GetMaterial();
		auto* pTransform	= object->GetComponent<JF::Component::Transform>();

		// Check)
		CONTINUE_IF(pMesh == nullptr);
		CONTINUE_IF(pMarerial == nullptr);
		CONTINUE_IF(pTransform == nullptr);

		// 1-3) Set Layout And Topology
		m_pDeviceContext->IASetInputLayout(pMesh->GetInputLayout());
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 1-4) �����Ͷ����� ���¸� �����Ѵ�.
		if (pMarerial->m_RSState != nullptr)
			m_pDeviceContext->RSSetState(pMarerial->m_RSState);

		// 1-5) ���� ������Ʈ ���¸� �����Ѵ�.
		if (pMarerial->m_BlendState != nullptr)
			m_pDeviceContext->OMSetBlendState(pMarerial->m_BlendState, blendFactors, 0xffffffff);

		// 1-6) Set VertexBuffer And IndexBuffer
		UINT stride = pMesh->GetStride();
		UINT offset = 0;
		ID3D11Buffer* pVB = pMesh->GetVB();
		ID3D11Buffer* pIB = pMesh->GetIB();
		m_pDeviceContext->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
		m_pDeviceContext->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

		// 1-7) worldViewProj ����� ���Ѵ�.
		XMMATRIX world				= XMLoadFloat4x4(&pTransform->GetTransformMatrix());
		XMMATRIX view				= Camera::g_pMainCamera->GetView();
		XMMATRIX proj				= Camera::g_pMainCamera->GetProj();
		XMMATRIX worldInvTranspose	= JF::Util::MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world * view * proj;

		// Declear) => TODO : ����Ʈ ��� �������� ���̵�� �������� ��ü����.
		BasicEffect* pFX = pMarerial->m_BumpTexture != nullptr ? Effects::NormalMapFX : Effects::BasicFX;

		// 1-8) ���̴��� ����� ����.
		pFX->SetWorld(world);
		pFX->SetEyePosW(Camera::g_pMainCamera->GetEyePos());
		pFX->SetWorldViewProj(worldViewProj);
		pFX->SetWorldViewProjTex(worldViewProj * toTexSpace);
		pFX->SetWorldInvTranspose(worldInvTranspose);
		pFX->SetTexTransform(XMLoadFloat4x4(&pMesh->GetTexTransform()));
		pFX->SetShadowTransform(world * XMLoadFloat4x4(&m_ShadowTransform));

		if(pMarerial->m_MainTexture != nullptr)
			pFX->SetDiffuseMap(pMarerial->m_MainTexture->GetTexture());
		if (pMarerial->m_BumpTexture != nullptr)
			Effects::NormalMapFX->SetNormalMap(pMarerial->m_BumpTexture->GetTexture());
		pFX->SetLightMap(m_pLightBufferSRView);
		pFX->SetShadowMap(m_pShadowMapSRView);
		pFX->SetSSAOMap(m_pSSAO->GetAmbient1SRV());

		int lightIndex = 0;
		JF::Light::DirectionalLight* dirLights[3];
		for each(auto lightObject in _mainLights)
		{
			CONTINUE_IF(lightObject == nullptr);
			auto* dirLight = lightObject->GetComponent<JFDirectionalLight>();
			if(dirLight != nullptr)
				dirLights[lightIndex++] = dirLight->GetDirectionalLight();
		}

		pFX->SetDirLights(dirLights[0]);
		pFX->SetMaterial(pMarerial->m_Material);

		pFX->SetTime(_pTimer->TotalTime());

		// 1-9) SetTech
		ID3DX11EffectTechnique* tech;
		switch (lightIndex)
		{
		case 0:
			if (pMarerial->m_MainTexture != nullptr)
				tech = pFX->Light0TexTech;
			break;
		case 1:
			if (pMarerial->m_MainTexture != nullptr)
				tech = pFX->Light1TexTech;
			else
				tech = pFX->Light1Tech;
			break;
		case 2:
			if (pMarerial->m_MainTexture != nullptr)
				tech = pFX->Light2TexTech;
			else
				tech = pFX->Light2Tech;
			break;
		case 3:
			if (pMarerial->m_MainTexture != nullptr)
				tech = pFX->Light3TexTech;
			else
				tech = pFX->Light3Tech;
			break;
		}

		// 1-10) Render
		D3DX11_TECHNIQUE_DESC techDesc;
		tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			tech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
		}

		// 1-11) �⺻ �������·� �����Ѵ�.
		m_pDeviceContext->RSSetState(0);
		m_pDeviceContext->OMSetBlendState(0, blendFactors, 0xffffffff);
	}
}

void JF::JFCDeviceDirectX11::SSAORender()
{
	// Bind the ambient map as the render target.  Observe that this pass does not bind 
	// a depth/stencil buffer--it does not need it, and without one, no depth test is
	// performed, which is what we want.
	ID3D11RenderTargetView* renderTargets[1] = { m_pSSAO->GetAmbient1RTV() };
	m_pDeviceContext->OMSetRenderTargets(1, renderTargets, 0);
	m_pDeviceContext->ClearRenderTargetView(m_pSSAO->GetAmbient1RTV(), reinterpret_cast<const float*>(&JF::Util::Colors::Black));

	m_pDeviceContext->RSSetViewports(1, &m_pSSAO->GetViewPort());

	// Transform NDC space [-1,+1]^2 to texture space [0,1]^2
	static const XMMATRIX T(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	XMMATRIX P = Camera::g_pMainCamera->GetProj();
	XMMATRIX PT = XMMatrixMultiply(P, T);

	Effects::SSAOBufferFX->SetViewToTexSpace(PT);
	Effects::SSAOBufferFX->SetOffsetVectors(m_pSSAO->GetOffsets());
	Effects::SSAOBufferFX->SetFrustumCorners(m_pSSAO->GetFrustumFarCorner());
	Effects::SSAOBufferFX->SetNormalDepthVMap(m_pGBuffer->GetViewNormalDepthSRV());
	Effects::SSAOBufferFX->SetRandomVecMap(m_pSSAO->GetRandomVectorSRV());

	UINT stride = sizeof(Vertex::PosNormalTex);
	UINT offset = 0;
	ID3D11Buffer* vb = m_pSSAO->GetScreenQuadVB();
	ID3D11Buffer* ib = m_pSSAO->GetScreenQuadIB();

	m_pDeviceContext->IASetInputLayout(InputLayouts::PosNormalTex);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);

	ID3DX11EffectTechnique* tech = Effects::SSAOBufferFX->GetTech();
	D3DX11_TECHNIQUE_DESC techDesc;

	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);
		m_pDeviceContext->DrawIndexed(6, 0, 0);
	}
}

void JF::JFCDeviceDirectX11::SSAOBlurRender(ID3D11ShaderResourceView* _inputSRV, ID3D11RenderTargetView* _outputRTV, bool _horzBlur)
{
	// Declear)
	D3D11_VIEWPORT viewPort = m_pSSAO->GetViewPort();

	m_pDeviceContext->OMSetRenderTargets(1, &_outputRTV, 0);
	m_pDeviceContext->ClearRenderTargetView(_outputRTV, reinterpret_cast<const float*>(&JF::Util::Colors::Black));
	m_pDeviceContext->RSSetViewports(1, &viewPort);

	Effects::SSAOBlurFX->SetTexelWidth(1.0f / viewPort.Width);
	Effects::SSAOBlurFX->SetTexelHeight(1.0f / viewPort.Height);
	Effects::SSAOBlurFX->SetNormalDepthMap(m_pGBuffer->GetViewNormalDepthSRV());
	Effects::SSAOBlurFX->SetInputImage(_inputSRV);

	UINT stride = sizeof(Vertex::PosNormalTex);
	UINT offset = 0;
	ID3D11Buffer* vb = m_pSSAO->GetScreenQuadVB();
	ID3D11Buffer* ib = m_pSSAO->GetScreenQuadIB();

	m_pDeviceContext->IASetInputLayout(InputLayouts::PosNormalTex);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);

	ID3DX11EffectTechnique* tech = Effects::SSAOBlurFX->GetTech(_horzBlur);
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);
		m_pDeviceContext->DrawIndexed(6, 0, 0);

		// Unbind the input SRV as it is going to be an output in the next blur.
		Effects::SSAOBlurFX->SetInputImage(0);
		tech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);
	}
}

void JF::JFCDeviceDirectX11::TestRender()
{
	// 1) Set Layout And Topology
	gRENDERER->DeviceContext()->IASetInputLayout(InputLayouts::PosNormalTexTan);
	gRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 2) Set ViewPort
	m_pDeviceContext->RSSetViewports(1, &m_ScreenViewport);

	// 3) Set VertexBuffer And IndexBuffer
	UINT stride = m_BoxMesh->GetStride();
	UINT offset = 0;
	ID3D11Buffer* pVB = m_BoxMesh->GetVB();
	ID3D11Buffer* pIB = m_BoxMesh->GetIB();
	m_pDeviceContext->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(pIB, DXGI_FORMAT_R32_UINT, 0);

	// 4) Debug View 1
	{
		// Scale and shift quad to lower - right corner.
		XMMATRIX world(
			0.2f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-0.8f, -0.8f, 0.0f, 1.0f);

		// 5)
		Effects::DebugTextureFX->SetWorldViewProj(world);
		Effects::DebugTextureFX->SetTexture(m_pGBuffer->GetWorldNormalSRV());

		// 6)
		ID3DX11EffectTechnique* smapTech = Effects::DebugTextureFX->ViewArgbTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		smapTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			smapTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(m_BoxMesh->GetIndexCount(), 0, 0);
		}
	}

	// 4) Debug View 2
	{
		// Scale and shift quad to lower - right corner.
		XMMATRIX world(
			0.2f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-0.4f, -0.8f, 0.0f, 1.0f);

		// 5)
		Effects::DebugTextureFX->SetWorldViewProj(world);
		Effects::DebugTextureFX->SetTexture(m_pGBuffer->GetWorldPositionSRV());

		// 6)
		ID3DX11EffectTechnique* smapTech = Effects::DebugTextureFX->ViewArgbTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		smapTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			smapTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(m_BoxMesh->GetIndexCount(), 0, 0);
		}
	}

	// 5) Debug View 3
	{
		// Scale and shift quad to lower - right corner.
		XMMATRIX world(
			0.2f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, -0.8f, 0.0f, 1.0f);

		// 5)
		Effects::DebugTextureFX->SetWorldViewProj(world);
		Effects::DebugTextureFX->SetTexture(m_pGBuffer->GetViewNormalDepthSRV());

		// 6)
		ID3DX11EffectTechnique* smapTech = Effects::DebugTextureFX->ViewArgbTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		smapTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			smapTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(m_BoxMesh->GetIndexCount(), 0, 0);
		}
	}

	// 7) Debug View 5
	{
		// Scale and shift quad to lower - right corner.
		XMMATRIX world(
			0.2f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.4f, -0.8f, 0.0f, 1.0f);

		// 5)
		Effects::DebugTextureFX->SetWorldViewProj(world);
		//Effects::DebugTextureFX->SetTexture(m_pLightBufferSRView
		Effects::DebugTextureFX->SetTexture(m_pSSAO->GetAmbient1SRV());

		// 6)
		ID3DX11EffectTechnique* smapTech = Effects::DebugTextureFX->ViewRedTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		smapTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			smapTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(m_BoxMesh->GetIndexCount(), 0, 0);
		}
	}

	// 8) Debug View 6
	{
		// Scale and shift quad to lower - right corner.
		XMMATRIX world(
			0.2f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.8f, -0.8f, 0.0f, 1.0f);

		// 5)
		Effects::DebugTextureFX->SetWorldViewProj(world);
		Effects::DebugTextureFX->SetTexture(m_pShadowMapSRView);

		// 6)
		ID3DX11EffectTechnique* smapTech = Effects::DebugTextureFX->ViewRedTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		smapTech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			smapTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);

			m_pDeviceContext->DrawIndexed(m_BoxMesh->GetIndexCount(), 0, 0);
		}
	}
}
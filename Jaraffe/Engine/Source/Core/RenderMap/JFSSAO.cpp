#include "stdafx.h"
#include "JFSSAO.h"

JF::RenderMap::JFSSAO::JFSSAO()
	: m_pScreenQuadVB(nullptr), m_pScreenQuadIB(nullptr)
{
}

JF::RenderMap::JFSSAO::~JFSSAO()
{
	Release();
}

void JF::RenderMap::JFSSAO::Init(ID3D11Device* _pDevice)
{
	// 1) 
	BuildOffsetVectors();

	// 2)
	BuildFullScreenQuad(_pDevice);

	// 3)
	BuildRandomVectorTexture(_pDevice);
}

void JF::RenderMap::JFSSAO::Reset(ID3D11Device* _pDevice, int _width, int _height, float _fovY, float _farZ)
{
	// 1)
	ReleaseCOM_PTR(m_pAmbientRTV[0]);
	ReleaseCOM_PTR(m_pAmbientSRV[0]);
	ReleaseCOM_PTR(m_pAmbientRTV[1]);
	ReleaseCOM_PTR(m_pAmbientSRV[1]);

	// 2) 
	SettingViewport(_width, _height);

	// 3)
	BuildFrustumFarCorners(_width, _height, _fovY, _farZ);

	// 4)
	BuildTextureViews(_pDevice, _width, _height);
}

void JF::RenderMap::JFSSAO::Release()
{
	ReleaseCOM_PTR(m_pRandomVectorSRV);

	ReleaseCOM_PTR(m_pAmbientRTV[0]);
	ReleaseCOM_PTR(m_pAmbientSRV[0]);
	ReleaseCOM_PTR(m_pAmbientRTV[1]);
	ReleaseCOM_PTR(m_pAmbientSRV[1]);

	ReleaseCOM(m_pScreenQuadVB);
	ReleaseCOM(m_pScreenQuadIB);
}

void JF::RenderMap::JFSSAO::SettingViewport(int _width, int _height)
{
	// SSAO 는 저주파이므로 해상도가 낮아도 큰 차이 나지는 않는다.
	m_ViewPort.TopLeftX = 0.0f;
	m_ViewPort.TopLeftY = 0.0f;
	m_ViewPort.Width	= _width / 2.0f;
	m_ViewPort.Height	= _height / 2.0f;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
}

void JF::RenderMap::JFSSAO::BuildFrustumFarCorners(int _width, int _height, float _fovY, float _farZ)
{
	// 평면 절두체 꼭짓점에 대한 정보를 저장한다.
	float aspect = (float)_width / (float)_height;

	float halfHeight = _farZ * tanf(0.5f*_fovY);
	float halfWidth = aspect * halfHeight;

	m_FrustumFarCorner[0] = XMFLOAT4(-halfWidth, -halfHeight, _farZ, 0.0f);
	m_FrustumFarCorner[1] = XMFLOAT4(-halfWidth, +halfHeight, _farZ, 0.0f);
	m_FrustumFarCorner[2] = XMFLOAT4(+halfWidth, +halfHeight, _farZ, 0.0f);
	m_FrustumFarCorner[3] = XMFLOAT4(+halfWidth, -halfHeight, _farZ, 0.0f);
}

void JF::RenderMap::JFSSAO::BuildOffsetVectors()
{
	// 균일하게 분포 된 14 개의 벡터로 시작합니다. 우리는 큐브의 8 코너를 선택합니다.
	// 와 각 큐브면을 따라 6 개의 중심점을 만듭니다. 우리는 항상 포인트를
	// 큐브의 양쪽을 마주 보게합니다. 이렇게하면 우리는 여전히 벡터가 퍼져 나갑니다.
	// 14 개 미만의 샘플을 사용하도록 선택한 경우.

	// 균일하게 분포된 14개의 백터를 미리 만든다. ( 랜덤을 돌렸을때 균일한 결과를 얻기위해서 )
	// 입방체의 여덟 꼭짓점과 각 면의 중점 여섯 개를 그러한 백터들로 간주한다.
	// 이들을, 이웃한 두 원소가 서로 입방체의 반대쪽에 있도록 하는 순서로
	// 항상 고르게 분포된 백터들을 얻게 된다.

	// 8 cube corners
	m_Offsets[1] = XMFLOAT4(-1.0f, -1.0f, -1.0f, 0.0f);
	m_Offsets[0] = XMFLOAT4(+1.0f, +1.0f, +1.0f, 0.0f);

	m_Offsets[2] = XMFLOAT4(-1.0f, +1.0f, +1.0f, 0.0f);
	m_Offsets[3] = XMFLOAT4(+1.0f, -1.0f, -1.0f, 0.0f);

	m_Offsets[4] = XMFLOAT4(+1.0f, +1.0f, -1.0f, 0.0f);
	m_Offsets[5] = XMFLOAT4(-1.0f, -1.0f, +1.0f, 0.0f);

	m_Offsets[6] = XMFLOAT4(-1.0f, +1.0f, -1.0f, 0.0f);
	m_Offsets[7] = XMFLOAT4(+1.0f, -1.0f, +1.0f, 0.0f);

	// 6 centers of cube faces
	m_Offsets[8] = XMFLOAT4(-1.0f, 0.0f, 0.0f, 0.0f);
	m_Offsets[9] = XMFLOAT4(+1.0f, 0.0f, 0.0f, 0.0f);

	m_Offsets[10] = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	m_Offsets[11] = XMFLOAT4(0.0f, +1.0f, 0.0f, 0.0f);

	m_Offsets[12] = XMFLOAT4(0.0f, 0.0f, -1.0f, 0.0f);
	m_Offsets[13] = XMFLOAT4(0.0f, 0.0f, +1.0f, 0.0f);

	for (int i = 0; i < 14; ++i)
	{
		// Create random lengths in [0.25, 1.0].
		float s = JF::Util::MathHelper::RandF(0.25f, 1.0f);

		XMVECTOR v = s * XMVector4Normalize(XMLoadFloat4(&m_Offsets[i]));

		XMStoreFloat4(&m_Offsets[i], v);
	}
}

void JF::RenderMap::JFSSAO::BuildFullScreenQuad(ID3D11Device* _pDevice)
{
	Vertex::PosNormalTex v[4];

	v[0].Pos = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	v[1].Pos = XMFLOAT3(-1.0f, +1.0f, 0.0f);
	v[2].Pos = XMFLOAT3(+1.0f, +1.0f, 0.0f);
	v[3].Pos = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	// Store far plane frustum corner indices in Normal.x slot.
	v[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	v[1].Normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	v[2].Normal = XMFLOAT3(2.0f, 0.0f, 0.0f);
	v[3].Normal = XMFLOAT3(3.0f, 0.0f, 0.0f);

	v[0].Tex = XMFLOAT2(0.0f, 1.0f);
	v[1].Tex = XMFLOAT2(0.0f, 0.0f);
	v[2].Tex = XMFLOAT2(1.0f, 0.0f);
	v[3].Tex = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage				= D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth			= sizeof(Vertex::PosNormalTex) * 4;
	vbd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags		= 0;
	vbd.MiscFlags			= 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = v;

	HR(_pDevice->CreateBuffer(&vbd, &vinitData, &m_pScreenQuadVB));

	USHORT indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(USHORT) * 6;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.StructureByteStride = 0;
	ibd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;

	HR(_pDevice->CreateBuffer(&ibd, &iinitData, &m_pScreenQuadIB));
}

void JF::RenderMap::JFSSAO::BuildRandomVectorTexture(ID3D11Device* _pDevice)
{
	// 랜덤값이 담긴 텍스쳐를 만든다.
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width				= 256;
	texDesc.Height				= 256;
	texDesc.MipLevels			= 1;
	texDesc.ArraySize			= 1;
	texDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count	= 1;
	texDesc.SampleDesc.Quality	= 0;
	texDesc.Usage				= D3D11_USAGE_IMMUTABLE;
	texDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags		= 0;
	texDesc.MiscFlags			= 0;

	D3D11_SUBRESOURCE_DATA initData = { 0 };
	initData.SysMemPitch = 256 * sizeof(XMCOLOR);

	XMCOLOR color[256 * 256];
	for (int i = 0; i < 256; ++i)
	{
		for (int j = 0; j < 256; ++j)
		{
			XMFLOAT3 v(JF::Util::MathHelper::RandF(), JF::Util::MathHelper::RandF(), JF::Util::MathHelper::RandF());

			color[i * 256 + j] = XMCOLOR(v.x, v.y, v.z, 0.0f);
		}
	}

	initData.pSysMem = color;

	ID3D11Texture2D* tex = 0;
	JF::Utile::DXCall(_pDevice->CreateTexture2D(&texDesc, &initData, &tex));

	JF::Utile::DXCall(_pDevice->CreateShaderResourceView(tex, 0, &m_pRandomVectorSRV));

	// view saves a reference.
	ReleaseCOM(tex);
}

void JF::RenderMap::JFSSAO::BuildTextureViews(ID3D11Device* _pDevice, int _width, int _height)
{
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = _width / 2;
	texDesc.Height = _height / 2;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R16_FLOAT;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	ID3D11Texture2D* ambientTex0 = 0;
	HR(_pDevice->CreateTexture2D(&texDesc, 0, &ambientTex0));
	HR(_pDevice->CreateRenderTargetView(ambientTex0, 0, &m_pAmbientRTV[0]));
	HR(_pDevice->CreateShaderResourceView(ambientTex0, 0, &m_pAmbientSRV[0]));

	ID3D11Texture2D* ambientTex1 = 0;
	HR(_pDevice->CreateTexture2D(&texDesc, 0, &ambientTex1));
	HR(_pDevice->CreateRenderTargetView(ambientTex1, 0, &m_pAmbientRTV[1]));
	HR(_pDevice->CreateShaderResourceView(ambientTex1, 0, &m_pAmbientSRV[1]));

	// view saves a reference.
	ReleaseCOM(ambientTex0);
	ReleaseCOM(ambientTex1);
}
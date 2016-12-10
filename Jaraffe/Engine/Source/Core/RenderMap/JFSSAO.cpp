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
	// SSAO �� �������̹Ƿ� �ػ󵵰� ���Ƶ� ū ���� ������ �ʴ´�.
	m_ViewPort.TopLeftX = 0.0f;
	m_ViewPort.TopLeftY = 0.0f;
	m_ViewPort.Width	= _width / 2.0f;
	m_ViewPort.Height	= _height / 2.0f;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
}

void JF::RenderMap::JFSSAO::BuildFrustumFarCorners(int _width, int _height, float _fovY, float _farZ)
{
	// ��� ����ü �������� ���� ������ �����Ѵ�.
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
	// �����ϰ� ���� �� 14 ���� ���ͷ� �����մϴ�. �츮�� ť���� 8 �ڳʸ� �����մϴ�.
	// �� �� ť����� ���� 6 ���� �߽����� ����ϴ�. �츮�� �׻� ����Ʈ��
	// ť���� ������ ���� �����մϴ�. �̷����ϸ� �츮�� ������ ���Ͱ� ���� �����ϴ�.
	// 14 �� �̸��� ������ ����ϵ��� ������ ���.

	// �����ϰ� ������ 14���� ���͸� �̸� �����. ( ������ �������� ������ ����� ������ؼ� )
	// �Թ�ü�� ���� �������� �� ���� ���� ���� ���� �׷��� ���͵�� �����Ѵ�.
	// �̵���, �̿��� �� ���Ұ� ���� �Թ�ü�� �ݴ��ʿ� �ֵ��� �ϴ� ������
	// �׻� ���� ������ ���͵��� ��� �ȴ�.

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
	// �������� ��� �ؽ��ĸ� �����.
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
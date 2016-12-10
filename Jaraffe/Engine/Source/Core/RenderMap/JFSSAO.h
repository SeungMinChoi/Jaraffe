#pragma once

namespace JF
{
namespace RenderMap
{

class JFSSAO
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	JFSSAO();
	virtual ~JFSSAO();

//=============================================================================
// Basic Classes)
//=============================================================================
public:
	void Init(ID3D11Device* _pDevice);
	void Reset(ID3D11Device* _pDevice, int _width, int _height, float _fovY, float _farZ);
	void Release();

//=============================================================================
// Public Classes)
//=============================================================================
public:
	const D3D11_VIEWPORT&		GetViewPort()			const	{ return m_ViewPort; }

	ID3D11ShaderResourceView*	GetRandomVectorSRV()	const	{ return m_pRandomVectorSRV.GetInterfacePtr(); }

	ID3D11RenderTargetView*		GetAmbient1RTV()		const	{ return m_pAmbientRTV[0].GetInterfacePtr(); }
	ID3D11ShaderResourceView*	GetAmbient1SRV()		const	{ return m_pAmbientSRV[0].GetInterfacePtr(); }
	ID3D11RenderTargetView*		GetAmbient2RTV()		const	{ return m_pAmbientRTV[1].GetInterfacePtr(); }
	ID3D11ShaderResourceView*	GetAmbient2SRV()		const	{ return m_pAmbientSRV[1].GetInterfacePtr(); }

	XMFLOAT4*					GetFrustumFarCorner()			{ return m_FrustumFarCorner;}
	XMFLOAT4*					GetOffsets()					{ return m_Offsets; }

	ID3D11Buffer*				GetScreenQuadVB()		const	{ return m_pScreenQuadVB; }
	ID3D11Buffer*				GetScreenQuadIB()		const	{ return m_pScreenQuadIB; }

//=============================================================================
// Private Classes)
//=============================================================================
private:
	void SettingViewport(int _width, int _height);
	void BuildFrustumFarCorners(int _width, int _height, float _fovY, float _farZ);
	
	void BuildOffsetVectors();
	void BuildFullScreenQuad(ID3D11Device* _pDevice);
	void BuildRandomVectorTexture(ID3D11Device* _pDevice);
	void BuildTextureViews(ID3D11Device* _pDevice, int _width, int _height);

//=============================================================================
// Private Member)
//=============================================================================
private:
	ID3D11ShaderResourceViewPtr m_pRandomVectorSRV;

	ID3D11RenderTargetViewPtr	m_pAmbientRTV[2];
	ID3D11ShaderResourceViewPtr m_pAmbientSRV[2];

	XMFLOAT4 m_FrustumFarCorner[4];

	XMFLOAT4 m_Offsets[14];

	D3D11_VIEWPORT m_ViewPort;

	ID3D11Buffer* m_pScreenQuadVB;
	ID3D11Buffer* m_pScreenQuadIB;
};

}
}
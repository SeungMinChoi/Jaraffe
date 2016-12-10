#pragma once

namespace JF
{
namespace RenderMap
{

class JFGBuffer
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	JFGBuffer();
	virtual ~JFGBuffer();

//=============================================================================
// Basic Classes)
//=============================================================================
public:
	void Reset(ID3D11Device* _pDevice, int _width, int _height, int _msCount, int _msQuality);
	void Release();

//=============================================================================
// Public Classes)
//=============================================================================
public:
	ID3D11RenderTargetView*		GetWorldNormalRTV()			const		{ return m_pWorldNormalRTV.GetInterfacePtr(); }
	ID3D11RenderTargetView*		GetWorldPositionRTV()		const		{ return m_pWorldPositionRTV.GetInterfacePtr(); }
	ID3D11RenderTargetView*		GetViewNormalDepthRTV()		const		{ return m_pViewNormalDepthRTV.GetInterfacePtr(); }

	ID3D11ShaderResourceView*	GetWorldNormalSRV()			const		{ return m_pWorldNormalSRV.GetInterfacePtr(); }
	ID3D11ShaderResourceView*	GetWorldPositionSRV()		const		{ return m_pWorldPositionSRV.GetInterfacePtr(); }
	ID3D11ShaderResourceView*	GetViewNormalDepthSRV()		const		{ return m_pViewNormalDepthSRV.GetInterfacePtr(); }

//=============================================================================
// Private Member)
//=============================================================================
private:
	void CreateTexture(ID3D11Device* _pDevice, int _width, int _height, int _msCount, int _msQuality);

private:
	// 월드공간 Normal(float3, 1.0f)
	ID3D11Texture2DPtr				m_pWorldNormalTexture;
	ID3D11RenderTargetViewPtr		m_pWorldNormalRTV;
	ID3D11ShaderResourceViewPtr		m_pWorldNormalSRV;

	// 월드공간 Position(float3, 1.0f)
	ID3D11Texture2DPtr				m_pWorldPositionTexture;
	ID3D11RenderTargetViewPtr		m_pWorldPositionRTV;
	ID3D11ShaderResourceViewPtr		m_pWorldPositionSRV;

	// 시야공간 Normal + Depth(float3, float1)
	ID3D11Texture2DPtr				m_pViewNormalDepthTexture;
	ID3D11RenderTargetViewPtr		m_pViewNormalDepthRTV;
	ID3D11ShaderResourceViewPtr		m_pViewNormalDepthSRV;
};

}
}
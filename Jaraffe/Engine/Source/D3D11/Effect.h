#pragma once

namespace Jaraffe
{

#pragma region Effect

class Effect
{
public:
	Effect(ID3D11Device* device, const std::wstring& filename);
	virtual ~Effect();

private:
	Effect(const Effect& rhs);
	Effect& operator=(const Effect& rhs);

protected:
	ID3DX11Effect* mFX;
};

#pragma endregion

#pragma region SimpleEffect

class SimpleEffect : public Effect
{
public:
	SimpleEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~SimpleEffect();

	// Get,Set Func
	void SetWorldViewProj(CXMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }

	// Techniques
	ID3DX11EffectTechnique*			ColorTech;

	// Constant Values
	ID3DX11EffectMatrixVariable*	WorldViewProj;
};

#pragma endregion


#pragma region PosNormalEffect

class PosNormalEffect : public Effect
{
public:
	PosNormalEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~PosNormalEffect();

	// Get,Set Func
	void SetWorldViewProj(CXMMATRIX M) { m_fxWorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX m) { m_fxWorld->SetMatrix(reinterpret_cast<const float*>(&m)); }
	void SetWorldInvTranspose(CXMMATRIX m) { m_fxWorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&m)); }
	void SetEyePosW(const XMFLOAT3& v) { m_fxEyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetDirLights(const DirectionalLight* lights) { m_fxDirLight->SetRawValue(lights, 0, 3 * sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat) { m_fxMaterial->SetRawValue(&mat, 0, sizeof(Material)); }

	// Techniques
	ID3DX11EffectTechnique*			LightTech;

	// Constant Values
	ID3DX11EffectMatrixVariable*	m_fxWorldViewProj;
	ID3DX11EffectMatrixVariable*	m_fxWorld;
	ID3DX11EffectMatrixVariable*	m_fxWorldInvTranspose;
	ID3DX11EffectVectorVariable*	m_fxEyePosW;
	ID3DX11EffectVariable*			m_fxDirLight;
	ID3DX11EffectVariable*			m_fxMaterial;
};

#pragma endregion

#pragma region Effects

class Effects
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static SimpleEffect* SimpleFX;
	static PosNormalEffect* PosNormalFX;
};

#pragma endregion

}
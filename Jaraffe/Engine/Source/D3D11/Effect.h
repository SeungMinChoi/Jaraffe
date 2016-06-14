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


#pragma region BasicEffect

class BasicEffect : public Effect
{
public:
	BasicEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~BasicEffect();

	void SetWorldViewProj(CXMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M) { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M) { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M) { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v) { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetDirLights(const Jaraffe::Light::DirectionalLight* lights) { DirLights->SetRawValue(lights, 0, 3 * sizeof(Jaraffe::Light::DirectionalLight)); }
	void SetMaterial(const Jaraffe::Light::Material& mat) { Mat->SetRawValue(&mat, 0, sizeof(Jaraffe::Light::Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex) { DiffuseMap->SetResource(tex); }
	void SetTime(const float& f) { Time->SetFloat(f); }

	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;
	ID3DX11EffectScalarVariable* Time;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
};

#pragma endregion

#pragma region Effects

class Effects
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static SimpleEffect* SimpleFX;
	static BasicEffect* BasicFX;
};

#pragma endregion

}
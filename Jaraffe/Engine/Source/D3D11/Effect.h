#pragma once

namespace JF
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

	void SetWorld				(CXMMATRIX M)						{ World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldViewProj		(CXMMATRIX M)						{ WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose	(CXMMATRIX M)						{ WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }

	void SetTexTransform		(CXMMATRIX M)						{ TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetShadowTransform		(CXMMATRIX M)						{ ShadowTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }

	void SetEyePosW				(const XMFLOAT3& v)					{ EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }

	void SetDirLights			(const void* lights)				{ DirLights->SetRawValue(lights, 0, 1 * sizeof(JF::Light::DirectionalLight)); }
	void SetMaterial			(const JF::Light::Material& mat)	{ Mat->SetRawValue(&mat, 0, sizeof(JF::Light::Material)); }

	void SetTime				(const float& f)					{ Time->SetFloat(f); }

	void SetLightMap			(ID3D11ShaderResourceView* tex)		{ LightMap->SetResource(tex); }
	void SetShadowMap			(ID3D11ShaderResourceView* tex)		{ ShadowMap->SetResource(tex); }
	void SetDiffuseMap			(ID3D11ShaderResourceView* tex)		{ DiffuseMap->SetResource(tex); }

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
	ID3DX11EffectMatrixVariable* ShadowTransform;
	ID3DX11EffectVectorVariable* EyePosW;

	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectScalarVariable* Time;

	ID3DX11EffectShaderResourceVariable* LightMap;
	ID3DX11EffectShaderResourceVariable* ShadowMap;
	ID3DX11EffectShaderResourceVariable* DiffuseMap;
};

#pragma endregion

#pragma region NormalMapEffect

class NormalMapEffect : public BasicEffect
{
public:
	NormalMapEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~NormalMapEffect();

	void SetNormalMap (ID3D11ShaderResourceView* tex) { NormalMap->SetResource(tex); }

	ID3DX11EffectShaderResourceVariable* NormalMap;
};

#pragma endregion

#pragma region ShadowBufferEffect

class ShadowBufferEffect : public Effect
{
public:
	ShadowBufferEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~ShadowBufferEffect();

	void SetWorldViewProj(CXMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }

	void SetDiffuseMap(ID3D11ShaderResourceView* tex) { DiffuseMap->SetResource(tex); }

	ID3DX11EffectTechnique* BuildShadowMapTech;
	ID3DX11EffectTechnique* BuildShadowMapAlphaClipTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;
};

#pragma endregion

#pragma region LightPrePassGeometyBufferEffect

class LightPrePassGeometyBufferEffect : public Effect
{
public:
	LightPrePassGeometyBufferEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~LightPrePassGeometyBufferEffect();

	void SetWorld(CXMMATRIX M)			{ World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldView(CXMMATRIX M)		{ WorldView->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldViewProj(CXMMATRIX M)	{ WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetNormalMap(ID3D11ShaderResourceView* tex) { NormalMap->SetResource(tex); }

	ID3DX11EffectTechnique* BasicTech;
	ID3DX11EffectTechnique* Basic_NoNormal;

	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldView;
	ID3DX11EffectMatrixVariable* WorldViewProj;

	ID3DX11EffectShaderResourceVariable* NormalMap;
};

#pragma endregion

#pragma region LightPrePassLightBufferEffect

class LightPrePassLightBufferEffect : public Effect
{
public:
	LightPrePassLightBufferEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~LightPrePassLightBufferEffect();

	void SetLightPos(const XMFLOAT3& v)			{ LightPos->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetLightColor(const XMFLOAT3& v)		{ LightColor->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetLightDirection(const XMFLOAT3& v)	{ LightDirection->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetSpotlightAngles(const XMFLOAT2& v)	{ SpotlightAngles->SetRawValue(&v, 0, sizeof(XMFLOAT2)); }
	void SetLightRange(const float& f)			{ LightRange->SetFloat(f); }

	void SetCameraPos(const XMFLOAT3& v)		{ CameraPos->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }

	void SetNormalTexture(ID3D11ShaderResourceView* tex) { NormalTexture->SetResource(tex); }
	void SetPositionTexture(ID3D11ShaderResourceView* tex) { PositionTexture->SetResource(tex); }

	ID3DX11EffectTechnique* DirectionalLightTech;
	ID3DX11EffectTechnique* PointLightTech;
	ID3DX11EffectTechnique* SpotLightTech;

	ID3DX11EffectVectorVariable* LightPos;
	ID3DX11EffectVectorVariable* LightColor;
	ID3DX11EffectVectorVariable* LightDirection;
	ID3DX11EffectVectorVariable* SpotlightAngles;
	ID3DX11EffectScalarVariable* LightRange;

	ID3DX11EffectVectorVariable* CameraPos;

	ID3DX11EffectShaderResourceVariable* NormalTexture;
	ID3DX11EffectShaderResourceVariable* PositionTexture;
};

#pragma endregion

#pragma region SkyEffect

class SkyEffect : public Effect
{
public:
	SkyEffect(ID3D11Device* device, const std::wstring& filename);
	~SkyEffect();

	void SetWorldViewProj(CXMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetCubeMap(ID3D11ShaderResourceView* cubemap) { SkyBox->SetResource(cubemap); }

	ID3DX11EffectTechnique* SkyTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;

	ID3DX11EffectShaderResourceVariable* SkyBox;
};

#pragma endregion

#pragma region DebugTexEffect
class DebugTexEffect : public Effect
{
public:
	DebugTexEffect(ID3D11Device* device, const std::wstring& filename);
	~DebugTexEffect();

	void SetWorldViewProj(CXMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexture(ID3D11ShaderResourceView* tex) { Texture->SetResource(tex); }

	ID3DX11EffectTechnique* ViewArgbTech;
	ID3DX11EffectTechnique* ViewRedTech;
	ID3DX11EffectTechnique* ViewGreenTech;
	ID3DX11EffectTechnique* ViewBlueTech;
	ID3DX11EffectTechnique* ViewAlphaTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectShaderResourceVariable* Texture;
};
#pragma endregion

#pragma region Effects

class Effects
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static SimpleEffect*	SimpleFX;

	static BasicEffect*		BasicFX;
	static NormalMapEffect* NormalMapFX;

	static SkyEffect*		CubeMapFX;

	static ShadowBufferEffect* ShadowBufferFX;

	static LightPrePassGeometyBufferEffect* LightPrePassGeometyBufferFX;
	static LightPrePassLightBufferEffect*	LightPrePassLightBufferFX;

	static DebugTexEffect*					DebugTextureFX;
};

#pragma endregion

}
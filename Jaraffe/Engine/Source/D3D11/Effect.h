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
	void SetWorldViewProjTex	(CXMMATRIX M)						{ WorldViewProjTex->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose	(CXMMATRIX M)						{ WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }

	void SetTexTransform		(CXMMATRIX M)						{ TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetShadowTransform		(CXMMATRIX M)						{ ShadowTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }

	void SetEyePosW				(const XMFLOAT3& v)					{ EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }

	void SetFogColor			(const FXMVECTOR v)					{ FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart			(float f)							{ FogStart->SetFloat(f); }
	void SetFogRange			(float f)							{ FogRange->SetFloat(f); }

	void SetDirLights			(const void* lights)				{ DirLights->SetRawValue(lights, 0, 1 * sizeof(JF::Light::DirectionalLight)); }
	void SetMaterial			(const JF::Light::Material& mat)	{ Mat->SetRawValue(&mat, 0, sizeof(JF::Light::Material)); }

	void SetTime				(const float& f)					{ Time->SetFloat(f); }

	void SetSSAOMap				(ID3D11ShaderResourceView* tex)		{ SSAOMap->SetResource(tex); }
	void SetLightMap			(ID3D11ShaderResourceView* tex)		{ LightMap->SetResource(tex); }
	void SetShadowMap			(ID3D11ShaderResourceView* tex)		{ ShadowMap->SetResource(tex); }
	void SetDiffuseMap			(ID3D11ShaderResourceView* tex)		{ DiffuseMap->SetResource(tex); }
	void SetCubeMap				(ID3D11ShaderResourceView* tex)		{ CubeMap->SetResource(tex); }

	ID3DX11EffectTechnique* GetTech(int _nLightIndex, bool _useDiffuse, bool _useAlphaClip, bool _useFog, bool _useReflect)
	{
		int techKey = 0;
		if (_nLightIndex == 0)
			techKey |= Light0;
		else if (_nLightIndex == 1)
			techKey |= Light1;
		else if (_nLightIndex == 2)
			techKey |= Light2;
		else if (_nLightIndex == 3)
			techKey |= Light3;

		if(_useDiffuse == true)
			techKey |= Texture;

		if (_useAlphaClip == true)
			techKey |= AlphaClip;

		if (_useFog == true)
			techKey |= Fog;

		if (_useReflect == true)
			techKey |= Reflect;

		return mapTech[techKey];
	}

private:
	enum TechType
	{
		Light0		= 1,
		Light1		= 1 << 1,
		Light2		= 1 << 2,
		Light3		= 1 << 3,
		Texture		= 1 << 4,
		AlphaClip	= 1 << 5,
		Fog			= 1 << 6,
		Reflect		= 1 << 7,
	};
	typedef typename std::pair<int, ID3DX11EffectTechnique*> MAPTech;

	std::map<int, ID3DX11EffectTechnique*> mapTech;

	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* WorldViewProjTex;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectMatrixVariable* ShadowTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;

	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectScalarVariable* Time;

	ID3DX11EffectShaderResourceVariable* SSAOMap;
	ID3DX11EffectShaderResourceVariable* LightMap;
	ID3DX11EffectShaderResourceVariable* ShadowMap;
	ID3DX11EffectShaderResourceVariable* DiffuseMap;
	ID3DX11EffectShaderResourceVariable* CubeMap;
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

#pragma region GBufferEffect

class GBufferEffect : public Effect
{
public:
	GBufferEffect(ID3D11Device* device, const std::wstring& filename);
	virtual ~GBufferEffect();

	void SetWorld(CXMMATRIX M)							{ World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldView(CXMMATRIX M)						{ WorldView->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldViewProj(CXMMATRIX M)					{ WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTransposeView(CXMMATRIX M)			{ WorldInvTransposeView->SetMatrix(reinterpret_cast<const float*>(&M)); }
	
	void SetNormalMap(ID3D11ShaderResourceView* tex)	{ NormalMap->SetResource(tex); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)	{ DiffuseMap->SetResource(tex); }

	ID3DX11EffectTechnique* GetTech(bool _useNormalMap, bool _useAlphaClip)
	{
		if (_useNormalMap == true && _useAlphaClip == true)
		{
			return GBufferNormalAlphaClipTech;
		}
		else if (_useNormalMap == true)
		{
			return GBufferNormalTech;
		}
		else if (_useAlphaClip == true)
		{
			return GBufferAlphaClipTech;
		}
		else
		{
			return GBufferTech;
		}
	}

private:
	ID3DX11EffectTechnique* GBufferTech;
	ID3DX11EffectTechnique* GBufferNormalTech;
	ID3DX11EffectTechnique* GBufferAlphaClipTech;
	ID3DX11EffectTechnique* GBufferNormalAlphaClipTech;

	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldView;
	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* WorldInvTransposeView;

	ID3DX11EffectShaderResourceVariable* NormalMap;
	ID3DX11EffectShaderResourceVariable* DiffuseMap;
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

#pragma region SSAOBufferEffect
class SSAOBufferEffect : public Effect
{
public:
	SSAOBufferEffect(ID3D11Device* device, const std::wstring& filename);
	~SSAOBufferEffect();

	void SetViewToTexSpace(CXMMATRIX M)						{ ViewToTexSpace->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetOffsetVectors(const XMFLOAT4 v[14])				{ OffsetVectors->SetFloatVectorArray(reinterpret_cast<const float*>(v), 0, 14); }
	void SetFrustumCorners(const XMFLOAT4 v[4])				{ FrustumCorners->SetFloatVectorArray(reinterpret_cast<const float*>(v), 0, 4); }
	void SetOcclusionRadius(float f)						{ OcclusionRadius->SetFloat(f); }
	void SetOcclusionFadeStart(float f)						{ OcclusionFadeStart->SetFloat(f); }
	void SetOcclusionFadeEnd(float f)						{ OcclusionFadeEnd->SetFloat(f); }
	void SetSurfaceEpsilon(float f)							{ SurfaceEpsilon->SetFloat(f); }

	void SetNormalDepthVMap(ID3D11ShaderResourceView* srv)	{ NormalDepthVMap->SetResource(srv); }
	void SetRandomVecMap(ID3D11ShaderResourceView* srv)		{ RandomVecMap->SetResource(srv); }

	ID3DX11EffectTechnique* GetTech()						{ return SsaoTech; }

private:
	ID3DX11EffectTechnique* SsaoTech;

	ID3DX11EffectMatrixVariable* ViewToTexSpace;
	ID3DX11EffectVectorVariable* OffsetVectors;
	ID3DX11EffectVectorVariable* FrustumCorners;
	ID3DX11EffectScalarVariable* OcclusionRadius;
	ID3DX11EffectScalarVariable* OcclusionFadeStart;
	ID3DX11EffectScalarVariable* OcclusionFadeEnd;
	ID3DX11EffectScalarVariable* SurfaceEpsilon;

	ID3DX11EffectShaderResourceVariable* NormalDepthVMap;
	ID3DX11EffectShaderResourceVariable* RandomVecMap;
};
#pragma endregion

#pragma region SSAOBlurEffect
class SSAOBlurEffect : public Effect
{
public:
	SSAOBlurEffect(ID3D11Device* device, const std::wstring& filename);
	~SSAOBlurEffect();

	void SetTexelWidth(float f) { TexelWidth->SetFloat(f); }
	void SetTexelHeight(float f) { TexelHeight->SetFloat(f); }

	void SetInputImage(ID3D11ShaderResourceView* srv) { InputImage->SetResource(srv); }
	void SetNormalDepthMap(ID3D11ShaderResourceView* srv) { NormalDepthMap->SetResource(srv); }

	ID3DX11EffectTechnique* GetTech(bool _horzBlur)
	{
		if (_horzBlur == true)
			return HorzBlurTech;
		else
			return VertBlurTech;
	}

private:
	ID3DX11EffectTechnique* HorzBlurTech;
	ID3DX11EffectTechnique* VertBlurTech;

	ID3DX11EffectScalarVariable* TexelWidth;
	ID3DX11EffectScalarVariable* TexelHeight;

	ID3DX11EffectShaderResourceVariable* InputImage;
	ID3DX11EffectShaderResourceVariable* NormalDepthMap;
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

	static GBufferEffect*					GBufferFX;

	static SSAOBufferEffect*				SSAOBufferFX;
	static SSAOBlurEffect*					SSAOBlurFX;

	static ShadowBufferEffect*				ShadowBufferFX;
	static LightPrePassLightBufferEffect*	LightPrePassLightBufferFX;

	static DebugTexEffect*					DebugTextureFX;
};

#pragma endregion

}
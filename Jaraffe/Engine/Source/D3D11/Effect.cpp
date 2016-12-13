#include "stdafx.h"
#include "Effect.h"

#pragma region Effect

JF::Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: mFX(0)
{
	auto fin = JFAPI::FILE::Open(filename.c_str(), eFILE_OPERATION::READ);
	size_t size = JFAPI::FILE::GetLength(fin);

	std::vector<char> compiledShader(size);

	JFAPI::FILE::Read(fin, size, &compiledShader[0]);
	JFAPI::FILE::Close(fin);

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, device, &mFX));
}

JF::Effect::~Effect()
{
	ReleaseCOM(mFX);
}

#pragma endregion

#pragma region SimpleEffect

JF::SimpleEffect::SimpleEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	// Techniques
	ColorTech = mFX->GetTechniqueByName("ColorTech");

	// Constant Values
	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

JF::SimpleEffect::~SimpleEffect()
{
}

#pragma endregion

#pragma region BasicEffect

JF::BasicEffect::BasicEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	//TechType;
	mapTech.insert(MAPTech(Light1, mFX->GetTechniqueByName("Light1")));
	mapTech.insert(MAPTech(Light2, mFX->GetTechniqueByName("Light2")));
	mapTech.insert(MAPTech(Light3, mFX->GetTechniqueByName("Light3")));

	mapTech.insert(MAPTech(Light0 | Texture, mFX->GetTechniqueByName("Light0Tex")));
	mapTech.insert(MAPTech(Light1 | Texture, mFX->GetTechniqueByName("Light1Tex")));
	mapTech.insert(MAPTech(Light2 | Texture, mFX->GetTechniqueByName("Light2Tex")));
	mapTech.insert(MAPTech(Light3 | Texture, mFX->GetTechniqueByName("Light3Tex")));

	mapTech.insert(MAPTech(Light0 | Texture | AlphaClip, mFX->GetTechniqueByName("Light0TexAlphaClip")));
	mapTech.insert(MAPTech(Light1 | Texture | AlphaClip, mFX->GetTechniqueByName("Light1TexAlphaClip")));
	mapTech.insert(MAPTech(Light2 | Texture | AlphaClip, mFX->GetTechniqueByName("Light2TexAlphaClip")));
	mapTech.insert(MAPTech(Light3 | Texture | AlphaClip, mFX->GetTechniqueByName("Light3TexAlphaClip")));

	mapTech.insert(MAPTech(Light1 | Texture | Fog, mFX->GetTechniqueByName("Light1Fog")));
	mapTech.insert(MAPTech(Light2 | Texture | Fog, mFX->GetTechniqueByName("Light2Fog")));
	mapTech.insert(MAPTech(Light3 | Texture | Fog, mFX->GetTechniqueByName("Light3Fog")));

	mapTech.insert(MAPTech(Light0 | Texture | Fog, mFX->GetTechniqueByName("Light0TexFog")));
	mapTech.insert(MAPTech(Light1 | Texture | Fog, mFX->GetTechniqueByName("Light1TexFog")));
	mapTech.insert(MAPTech(Light2 | Texture | Fog, mFX->GetTechniqueByName("Light2TexFog")));
	mapTech.insert(MAPTech(Light3 | Texture | Fog, mFX->GetTechniqueByName("Light3TexFog")));

	mapTech.insert(MAPTech(Light0 | Texture | AlphaClip | Fog, mFX->GetTechniqueByName("Light0TexAlphaClipFog")));
	mapTech.insert(MAPTech(Light1 | Texture | AlphaClip | Fog, mFX->GetTechniqueByName("Light1TexAlphaClipFog")));
	mapTech.insert(MAPTech(Light2 | Texture | AlphaClip | Fog, mFX->GetTechniqueByName("Light2TexAlphaClipFog")));
	mapTech.insert(MAPTech(Light3 | Texture | AlphaClip | Fog, mFX->GetTechniqueByName("Light3TexAlphaClipFog")));

	mapTech.insert(MAPTech(Light1 | Reflect, mFX->GetTechniqueByName("Light1Reflect")));
	mapTech.insert(MAPTech(Light2 | Reflect, mFX->GetTechniqueByName("Light2Reflect")));
	mapTech.insert(MAPTech(Light3 | Reflect, mFX->GetTechniqueByName("Light3Reflect")));

	mapTech.insert(MAPTech(Light0 | Texture | Reflect, mFX->GetTechniqueByName("Light0TexReflect")));
	mapTech.insert(MAPTech(Light1 | Texture | Reflect, mFX->GetTechniqueByName("Light1TexReflect")));
	mapTech.insert(MAPTech(Light2 | Texture | Reflect, mFX->GetTechniqueByName("Light2TexReflect")));
	mapTech.insert(MAPTech(Light3 | Texture | Reflect, mFX->GetTechniqueByName("Light3TexReflect")));

	mapTech.insert(MAPTech(Light0 | Texture | AlphaClip | Reflect, mFX->GetTechniqueByName("Light0TexAlphaClipReflect")));
	mapTech.insert(MAPTech(Light1 | Texture | AlphaClip | Reflect, mFX->GetTechniqueByName("Light1TexAlphaClipReflect")));
	mapTech.insert(MAPTech(Light2 | Texture | AlphaClip | Reflect, mFX->GetTechniqueByName("Light2TexAlphaClipReflect")));
	mapTech.insert(MAPTech(Light3 | Texture | AlphaClip | Reflect, mFX->GetTechniqueByName("Light3TexAlphaClipReflect")));

	mapTech.insert(MAPTech(Light1 | Fog | Reflect, mFX->GetTechniqueByName("Light1FogReflect")));
	mapTech.insert(MAPTech(Light2 | Fog | Reflect, mFX->GetTechniqueByName("Light2FogReflect")));
	mapTech.insert(MAPTech(Light3 | Fog | Reflect, mFX->GetTechniqueByName("Light3FogReflect")));

	mapTech.insert(MAPTech(Light0 | Texture | Fog | Reflect, mFX->GetTechniqueByName("Light0TexFogReflect")));
	mapTech.insert(MAPTech(Light1 | Texture | Fog | Reflect, mFX->GetTechniqueByName("Light1TexFogReflect")));
	mapTech.insert(MAPTech(Light2 | Texture | Fog | Reflect, mFX->GetTechniqueByName("Light2TexFogReflect")));
	mapTech.insert(MAPTech(Light3 | Texture | Fog | Reflect, mFX->GetTechniqueByName("Light3TexFogReflect")));

	mapTech.insert(MAPTech(Light0 | Texture | AlphaClip | Fog | Reflect, mFX->GetTechniqueByName("Light0TexAlphaClipFogReflect")));
	mapTech.insert(MAPTech(Light1 | Texture | AlphaClip | Fog | Reflect, mFX->GetTechniqueByName("Light1TexAlphaClipFogReflect")));
	mapTech.insert(MAPTech(Light2 | Texture | AlphaClip | Fog | Reflect, mFX->GetTechniqueByName("Light2TexAlphaClipFogReflect")));
	mapTech.insert(MAPTech(Light3 | Texture | AlphaClip | Fog | Reflect, mFX->GetTechniqueByName("Light3TexAlphaClipFogReflect")));

	World				= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldViewProj		= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	WorldViewProjTex	= mFX->GetVariableByName("gWorldViewProjTex")->AsMatrix();
	WorldInvTranspose	= mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform		= mFX->GetVariableByName("gTexTransform")->AsMatrix();
	ShadowTransform		= mFX->GetVariableByName("gShadowTransform")->AsMatrix();
	EyePosW				= mFX->GetVariableByName("gEyePosW")->AsVector();

	FogColor			= mFX->GetVariableByName("gFogColor")->AsVector();
	FogStart			= mFX->GetVariableByName("gFogStart")->AsScalar();
	FogRange			= mFX->GetVariableByName("gFogRange")->AsScalar();

	DirLights			= mFX->GetVariableByName("gDirLights");
	Mat					= mFX->GetVariableByName("gMaterial");

	SSAOMap				= mFX->GetVariableByName("gSSAOMap")->AsShaderResource();
	LightMap			= mFX->GetVariableByName("gLightMap")->AsShaderResource();
	ShadowMap			= mFX->GetVariableByName("gShadowMap")->AsShaderResource();
	DiffuseMap			= mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	CubeMap				= mFX->GetVariableByName("gCubeMap")->AsShaderResource();

	Time				= mFX->GetVariableByName("gTime")->AsScalar();
}

JF::BasicEffect::~BasicEffect()
{
}

#pragma endregion 

#pragma region NormalMapEffect

JF::NormalMapEffect::NormalMapEffect(ID3D11Device * device, const std::wstring & filename)
	: BasicEffect(device, filename)
{
	NormalMap = mFX->GetVariableByName("gNormalMap")->AsShaderResource();
}

JF::NormalMapEffect::~NormalMapEffect()
{
}

#pragma endregion 

#pragma region ShadowBufferEffect

JF::ShadowBufferEffect::ShadowBufferEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	BuildShadowMapTech			= mFX->GetTechniqueByName("BuildShadowMapTech");
	BuildShadowMapAlphaClipTech = mFX->GetTechniqueByName("BuildShadowMapAlphaClipTech");

	WorldViewProj	= mFX->GetVariableByName("gLightMVP")->AsMatrix();
	DiffuseMap		= mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

JF::ShadowBufferEffect::~ShadowBufferEffect()
{
}

#pragma endregion 

#pragma region GBufferEffect

JF::GBufferEffect::GBufferEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	GBufferTech					= mFX->GetTechniqueByName("GBuffer");
	GBufferNormalTech			= mFX->GetTechniqueByName("GBufferNormal");
	GBufferAlphaClipTech		= mFX->GetTechniqueByName("GBufferAlphaClip");
	GBufferNormalAlphaClipTech	= mFX->GetTechniqueByName("GBufferNormalAlphaClip");
	
	World						= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldView					= mFX->GetVariableByName("gWorldView")->AsMatrix();
	WorldViewProj				= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	WorldInvTransposeView		= mFX->GetVariableByName("gWorldInvTransposeView")->AsMatrix();

	NormalMap					= mFX->GetVariableByName("gNormalMap")->AsShaderResource();
	DiffuseMap					= mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

JF::GBufferEffect::~GBufferEffect()
{
}

#pragma endregion 

#pragma region LightPrePassLightBufferEffect

JF::LightPrePassLightBufferEffect::LightPrePassLightBufferEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	DirectionalLightTech	= mFX->GetTechniqueByName("DirectionalLight");
	PointLightTech			= mFX->GetTechniqueByName("PointLight");
	SpotLightTech			= mFX->GetTechniqueByName("Spotlight");

	LightPos				= mFX->GetVariableByName("LightPos")->AsVector();
	LightColor				= mFX->GetVariableByName("LightColor")->AsVector();
	LightDirection			= mFX->GetVariableByName("LightDirection")->AsVector();
	SpotlightAngles			= mFX->GetVariableByName("SpotLightAngles")->AsVector();
	LightRange				= mFX->GetVariableByName("LightRange")->AsScalar();

	CameraPos				= mFX->GetVariableByName("CameraPos")->AsVector();

	NormalTexture			= mFX->GetVariableByName("gNormalTexture")->AsShaderResource();
	PositionTexture			= mFX->GetVariableByName("gPositionTexture")->AsShaderResource();
}

JF::LightPrePassLightBufferEffect::~LightPrePassLightBufferEffect()
{
}

#pragma endregion 

#pragma region SSAOBufferEffect
JF::SSAOBufferEffect::SSAOBufferEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	SsaoTech			= mFX->GetTechniqueByName("Ssao");

	ViewToTexSpace		= mFX->GetVariableByName("gViewToTexSpace")->AsMatrix();
	OffsetVectors		= mFX->GetVariableByName("gOffsetVectors")->AsVector();
	FrustumCorners		= mFX->GetVariableByName("gFrustumCorners")->AsVector();
	OcclusionRadius		= mFX->GetVariableByName("gOcclusionRadius")->AsScalar();
	OcclusionFadeStart	= mFX->GetVariableByName("gOcclusionFadeStart")->AsScalar();
	OcclusionFadeEnd	= mFX->GetVariableByName("gOcclusionFadeEnd")->AsScalar();
	SurfaceEpsilon		= mFX->GetVariableByName("gSurfaceEpsilon")->AsScalar();

	NormalDepthVMap		= mFX->GetVariableByName("gNormalDepthVMap")->AsShaderResource();
	RandomVecMap		= mFX->GetVariableByName("gRandomVecMap")->AsShaderResource();
}

JF::SSAOBufferEffect::~SSAOBufferEffect()
{
}
#pragma endregion

#pragma region SSAOBlurEffect
JF::SSAOBlurEffect::SSAOBlurEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	HorzBlurTech = mFX->GetTechniqueByName("HorzBlur");
	VertBlurTech = mFX->GetTechniqueByName("VertBlur");

	TexelWidth = mFX->GetVariableByName("gTexelWidth")->AsScalar();
	TexelHeight = mFX->GetVariableByName("gTexelHeight")->AsScalar();

	InputImage = mFX->GetVariableByName("gInputImage")->AsShaderResource();
	NormalDepthMap = mFX->GetVariableByName("gNormalDepthMap")->AsShaderResource();
}

JF::SSAOBlurEffect::~SSAOBlurEffect()
{
}
#pragma endregion

#pragma region SkyEffect

JF::SkyEffect::SkyEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	SkyTech			= mFX->GetTechniqueByName("SkyTech");
	WorldViewProj	= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	SkyBox			= mFX->GetVariableByName("gCubeMap")->AsShaderResource();
}

JF::SkyEffect::~SkyEffect()
{
}

#pragma endregion

#pragma region DebugTexEffect

JF::DebugTexEffect::DebugTexEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	ViewArgbTech = mFX->GetTechniqueByName("ViewArgbTech");
	ViewRedTech = mFX->GetTechniqueByName("ViewRedTech");
	ViewGreenTech = mFX->GetTechniqueByName("ViewGreenTech");
	ViewBlueTech = mFX->GetTechniqueByName("ViewBlueTech");
	ViewAlphaTech = mFX->GetTechniqueByName("ViewAlphaTech");

	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	Texture = mFX->GetVariableByName("gTexture")->AsShaderResource();
}

JF::DebugTexEffect::~DebugTexEffect()
{

}

#pragma endregion


#pragma region Effects

// Static Values
JF::SimpleEffect*						JF::Effects::SimpleFX = 0;

JF::BasicEffect*						JF::Effects::BasicFX = 0;
JF::NormalMapEffect*					JF::Effects::NormalMapFX = 0;

JF::SkyEffect*							JF::Effects::CubeMapFX = 0;

JF::GBufferEffect*						JF::Effects::GBufferFX = 0;
JF::ShadowBufferEffect*					JF::Effects::ShadowBufferFX = 0;
JF::LightPrePassLightBufferEffect*		JF::Effects::LightPrePassLightBufferFX = 0;

JF::SSAOBufferEffect*					JF::Effects::SSAOBufferFX = 0;
JF::SSAOBlurEffect*						JF::Effects::SSAOBlurFX = 0;

JF::DebugTexEffect*						JF::Effects::DebugTextureFX = 0;

void JF::Effects::InitAll(ID3D11Device * device)
{
	SimpleFX					= new SimpleEffect(device, L"Source/Shader/ForwardRender/Color.fxo");

	BasicFX						= new BasicEffect(device, L"Source/Shader/ForwardRender/Basic.fxo");
	NormalMapFX					= new NormalMapEffect(device, L"Source/Shader/ForwardRender/NormalMap.fxo");

	CubeMapFX					= new SkyEffect(device, L"Source/Shader/ForwardRender/CubeMap.fxo");

	GBufferFX					= new GBufferEffect(device, L"Source/Shader/GBuffer/GBuffer.fxo");
	ShadowBufferFX				= new ShadowBufferEffect(device, L"Source/Shader/Shadow/ShadowBuffer.fxo");
	LightPrePassLightBufferFX	= new LightPrePassLightBufferEffect(device, L"Source/Shader/LightPrePass/LightPrePassLightBuffer.fxo");
	
	SSAOBufferFX				= new SSAOBufferEffect(device, L"Source/Shader/SSAO/SSAOBuffer.fxo");
	SSAOBlurFX					= new SSAOBlurEffect(device, L"Source/Shader/SSAO/SSAOBlur.fxo");

	DebugTextureFX				= new DebugTexEffect(device, L"Source/Shader/DebugRender/DebugTexture.fxo");
}

void JF::Effects::DestroyAll()
{
	SafeDelete(SimpleFX);

	SafeDelete(BasicFX);
	SafeDelete(NormalMapFX);

	SafeDelete(CubeMapFX);

	SafeDelete(GBufferFX);
	SafeDelete(ShadowBufferFX);
	SafeDelete(LightPrePassLightBufferFX);

	SafeDelete(SSAOBufferFX);
	SafeDelete(SSAOBlurFX);

	SafeDelete(DebugTextureFX);
}

#pragma endregion
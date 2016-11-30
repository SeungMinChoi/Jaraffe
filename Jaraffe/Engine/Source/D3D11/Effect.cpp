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
	Light1Tech = mFX->GetTechniqueByName("Light1");
	Light2Tech = mFX->GetTechniqueByName("Light2");
	Light3Tech = mFX->GetTechniqueByName("Light3");

	Light0TexTech = mFX->GetTechniqueByName("Light0Tex");
	Light1TexTech = mFX->GetTechniqueByName("Light1Tex");
	Light2TexTech = mFX->GetTechniqueByName("Light2Tex");
	Light3TexTech = mFX->GetTechniqueByName("Light3Tex");

	Light0TexNorma = mFX->GetTechniqueByName("Light0TexNormal");
	Light1TexNorma = mFX->GetTechniqueByName("Light1TexNormal");
	Light2TexNorma = mFX->GetTechniqueByName("Light2TexNormal");
	Light3TexNorma = mFX->GetTechniqueByName("Light3TexNormal");

	WorldViewProj		= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World				= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose	= mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform		= mFX->GetVariableByName("gTexTransform")->AsMatrix();
	EyePosW				= mFX->GetVariableByName("gEyePosW")->AsVector();
	DirLights			= mFX->GetVariableByName("gDirLights");
	Mat					= mFX->GetVariableByName("gMaterial");
	DiffuseMap			= mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	NormalMap			= mFX->GetVariableByName("gNormalMap")->AsShaderResource();

	Time				= mFX->GetVariableByName("gTime")->AsScalar();
}

JF::BasicEffect::~BasicEffect()
{
}

#pragma endregion 

#pragma region LightPrePassGeometyBufferEffect

JF::LightPrePassGeometyBufferEffect::LightPrePassGeometyBufferEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	BasicTech		= mFX->GetTechniqueByName("Basic");
	Basic_NoNormal	= mFX->GetTechniqueByName("Basic_NoNormal");
	
	World			= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldView		= mFX->GetVariableByName("gWorldView")->AsMatrix();
	WorldViewProj	= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	NormalMap		= mFX->GetVariableByName("gNormalMap")->AsShaderResource();
}

JF::LightPrePassGeometyBufferEffect::~LightPrePassGeometyBufferEffect()
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
	LightRange				= mFX->GetVariableByName("LightRange")->AsVector();

	CameraPos				= mFX->GetVariableByName("CameraPos")->AsVector();

	NormalTexture			= mFX->GetVariableByName("gNormalTexture")->AsShaderResource();
	PositionTexture			= mFX->GetVariableByName("gPositionTexture")->AsShaderResource();
}

JF::LightPrePassLightBufferEffect::~LightPrePassLightBufferEffect()
{
}

#pragma endregion 

#pragma region LightPrePassGeometry

JF::LightPrePassGeometry::LightPrePassGeometry(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	BasicTech		= mFX->GetTechniqueByName("Basic");

	World			= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldView		= mFX->GetVariableByName("gWorldView")->AsMatrix();
	WorldViewProj	= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();

	SpecularAlbedo	= mFX->GetVariableByName("SpecularAlbedo")->AsVector();

	DiffuseMap		= mFX->GetVariableByName("DiffuseMap")->AsShaderResource();
	LightTexture	= mFX->GetVariableByName("LightTexture")->AsShaderResource();
}

JF::LightPrePassGeometry::~LightPrePassGeometry()
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

#pragma region Effects

// Static Values
JF::SimpleEffect*						JF::Effects::SimpleFX = 0;
JF::BasicEffect*						JF::Effects::BasicFX = 0;
JF::SkyEffect*							JF::Effects::CubeMapFX = 0;
JF::LightPrePassGeometyBufferEffect*	JF::Effects::LightPrePassGeometyBufferFX = 0;
JF::LightPrePassLightBufferEffect*		JF::Effects::LightPrePassLightBufferFX = 0;
JF::LightPrePassGeometry*				JF::Effects::LightPrePassGeometryFX = 0;


void JF::Effects::InitAll(ID3D11Device * device)
{
	SimpleFX					= new SimpleEffect(device, L"Source/Shader/Color.fxo");
	BasicFX						= new BasicEffect(device, L"Source/Shader/Basic.fxo");
	CubeMapFX					= new SkyEffect(device, L"Source/Shader/CubeMap.fxo");
	LightPrePassGeometyBufferFX = new LightPrePassGeometyBufferEffect(device, L"Source/Shader/LightPrePass/LightPrePassGeometryBuffer.fxo");
	LightPrePassLightBufferFX	= new LightPrePassLightBufferEffect(device, L"Source/Shader/LightPrePass/LightPrePassLightBuffer.fxo");
	LightPrePassGeometryFX		= new LightPrePassGeometry(device, L"Source/Shader/LightPrePass/LightPrePassGeometry.fxo");
}

void JF::Effects::DestroyAll()
{
	SafeDelete(SimpleFX);
	SafeDelete(BasicFX);
	SafeDelete(CubeMapFX);
	SafeDelete(LightPrePassGeometyBufferFX);
	SafeDelete(LightPrePassLightBufferFX);
	SafeDelete(LightPrePassGeometryFX);
}

#pragma endregion
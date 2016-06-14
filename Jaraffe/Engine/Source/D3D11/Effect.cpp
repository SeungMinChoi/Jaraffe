#include "stdafx.h"
#include "Effect.h"

#pragma region Effect

Jaraffe::Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: mFX(0)
{
	std::ifstream fin(filename.c_str(), std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, device, &mFX));
}

Jaraffe::Effect::~Effect()
{
	ReleaseCOM(mFX);
}

#pragma endregion

#pragma region SimpleEffect

Jaraffe::SimpleEffect::SimpleEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	// Techniques
	ColorTech = mFX->GetTechniqueByName("ColorTech");

	// Constant Values
	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

Jaraffe::SimpleEffect::~SimpleEffect()
{
}

#pragma endregion

#pragma region BasicEffect

Jaraffe::BasicEffect::BasicEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	Light1Tech = mFX->GetTechniqueByName("Light1");
	Light2Tech = mFX->GetTechniqueByName("Light2");
	Light3Tech = mFX->GetTechniqueByName("Light3");

	Light0TexTech = mFX->GetTechniqueByName("Light0Tex");
	Light1TexTech = mFX->GetTechniqueByName("Light1Tex");
	Light2TexTech = mFX->GetTechniqueByName("Light2Tex");
	Light3TexTech = mFX->GetTechniqueByName("Light3Tex");

	WorldViewProj		= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World				= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose	= mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform		= mFX->GetVariableByName("gTexTransform")->AsMatrix();
	EyePosW				= mFX->GetVariableByName("gEyePosW")->AsVector();
	DirLights			= mFX->GetVariableByName("gDirLights");
	Mat					= mFX->GetVariableByName("gMaterial");
	DiffuseMap			= mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();

	Time				= mFX->GetVariableByName("gTime")->AsScalar();
}

Jaraffe::BasicEffect::~BasicEffect()
{
}

#pragma endregion 

#pragma region Effects

// Static Values
Jaraffe::SimpleEffect* Jaraffe::Effects::SimpleFX = 0;
Jaraffe::BasicEffect* Jaraffe::Effects::BasicFX = 0;

void Jaraffe::Effects::InitAll(ID3D11Device * device)
{
	SimpleFX	= new SimpleEffect(device, L"Source/Shader/Color.fxo");
	BasicFX		= new BasicEffect(device, L"Source/Shader/Basic.fxo");
}

void Jaraffe::Effects::DestroyAll()
{
	SafeDelete(SimpleFX);
	SafeDelete(BasicFX);
}

#pragma endregion
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

#pragma region PosNormalEffect

Jaraffe::PosNormalEffect::PosNormalEffect(ID3D11Device * device, const std::wstring & filename)
	: Effect(device, filename)
{
	// Techniques
	LightTech = mFX->GetTechniqueByName("LightTech");

	// Constant Values
	m_fxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	m_fxWorld = mFX->GetVariableByName("gWorld")->AsMatrix();
	m_fxWorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_fxEyePosW = mFX->GetVariableByName("gEyePosW")->AsVector();
	m_fxDirLight = mFX->GetVariableByName("gDirLight");
	m_fxMaterial = mFX->GetVariableByName("gMaterial");
}

Jaraffe::PosNormalEffect::~PosNormalEffect()
{
}

#pragma endregion 

#pragma region Effects

// Static Values
Jaraffe::SimpleEffect* Jaraffe::Effects::SimpleFX = 0;
Jaraffe::PosNormalEffect* Jaraffe::Effects::PosNormalFX = 0;

void Jaraffe::Effects::InitAll(ID3D11Device * device)
{
	SimpleFX	= new SimpleEffect(device, L"Source/Shader/Color.fxo");
	PosNormalFX = new PosNormalEffect(device, L"Source/Shader/Basic.fxo");
}

void Jaraffe::Effects::DestroyAll()
{
	SafeDelete(SimpleFX);
	SafeDelete(PosNormalFX);
}

#pragma endregion
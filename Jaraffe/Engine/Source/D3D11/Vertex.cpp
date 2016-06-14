#include "stdafx.h"
#include "Vertex.h"

#pragma region InputLayoutDesc

const D3D11_INPUT_ELEMENT_DESC Jaraffe::InputLayoutDesc::PosColor[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC Jaraffe::InputLayoutDesc::PosNormalTex[3] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

#pragma endregion

#pragma region cInputLayouts

// Static Values
ID3D11InputLayout* Jaraffe::InputLayouts::PosColor = 0;
ID3D11InputLayout* Jaraffe::InputLayouts::PosNormalTex = 0;

void Jaraffe::InputLayouts::InitAll(ID3D11Device * device)
{
	D3DX11_PASS_DESC passDesc;

	Effects::SimpleFX->ColorTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosColor, 2,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &PosColor));

	Effects::BasicFX->Light1TexTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosNormalTex, 3,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &PosNormalTex));
}

void Jaraffe::InputLayouts::DestroyAll()
{
	ReleaseCOM(PosColor);
	ReleaseCOM(PosNormalTex);
}

#pragma endregion
#include "stdafx.h"
#include "Vertex.h"

#pragma region InputLayoutDesc

const D3D11_INPUT_ELEMENT_DESC Jaraffe::InputLayoutDesc::Simple[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC Jaraffe::InputLayoutDesc::PosNormal[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

#pragma endregion

#pragma region cInputLayouts

// Static Values
ID3D11InputLayout* Jaraffe::InputLayouts::Simple = 0;
ID3D11InputLayout* Jaraffe::InputLayouts::PosNormal = 0;

void Jaraffe::InputLayouts::InitAll(ID3D11Device * device)
{
	D3DX11_PASS_DESC passDesc;

	Effects::SimpleFX->ColorTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::Simple, 2,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &Simple));

	Effects::PosNormalFX->LightTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosNormal, 2,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &PosNormal));
}

void Jaraffe::InputLayouts::DestroyAll()
{
	ReleaseCOM(Simple);
	ReleaseCOM(PosNormal);
}

#pragma endregion
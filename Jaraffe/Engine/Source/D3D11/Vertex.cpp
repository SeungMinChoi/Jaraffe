#include "stdafx.h"
#include "Vertex.h"

#pragma region InputLayoutDesc

const D3D11_INPUT_ELEMENT_DESC JF::InputLayoutDesc::Position[1] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC JF::InputLayoutDesc::PosColor[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC JF::InputLayoutDesc::PosNormalTex[3] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC JF::InputLayoutDesc::PosNormalTexTan[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

#pragma endregion

#pragma region cInputLayouts

// Static Values
ID3D11InputLayout* JF::InputLayouts::Position = 0;
ID3D11InputLayout* JF::InputLayouts::PosColor = 0;
ID3D11InputLayout* JF::InputLayouts::PosNormalTex = 0;
ID3D11InputLayout* JF::InputLayouts::PosNormalTexTan = 0;

void JF::InputLayouts::InitAll(ID3D11Device * device)
{
	D3DX11_PASS_DESC passDesc;
	
	Effects::LightPrePassLightBufferFX->DirectionalLightTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::Position, 1,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &Position));

	Effects::SimpleFX->ColorTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosColor, 2,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &PosColor));

	Effects::SSAOBufferFX->GetTech()->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosNormalTex, 3,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &PosNormalTex));

	Effects::NormalMapFX->GetTech(1, false, false, false, false)->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosNormalTexTan, 4,
		passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &PosNormalTexTan));
}

void JF::InputLayouts::DestroyAll()
{
	ReleaseCOM(Position);
	ReleaseCOM(PosColor);
	ReleaseCOM(PosNormalTex);
	ReleaseCOM(PosNormalTexTan);
}

#pragma endregion
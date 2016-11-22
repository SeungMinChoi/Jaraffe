#include "stdafx.h"
#include "TextureMgr.h"

Jaraffe::TextureMgr::TextureMgr()
{
}

Jaraffe::TextureMgr::~TextureMgr()
{
	Release();
}

void Jaraffe::TextureMgr::Init()
{
	// TODO : TEST Textures
	CreateTexture(L"Resources/Textures/WoodCrate01.dds");
	CreateTexture(L"Resources/Textures/flare.dds");
	CreateTexture(L"Resources/Textures/flarealpha.dds");
}

void Jaraffe::TextureMgr::Release()
{
	mTextureSRV.clear();
}

ID3D11ShaderResourceView* Jaraffe::TextureMgr::CreateTexture(std::wstring filename)
{
	ID3D11ShaderResourceViewPtr srv = nullptr;

	// Does it already exist?
	if( mTextureSRV.find(filename) != mTextureSRV.end() )
	{
		srv = mTextureSRV[filename];
	}
	else
	{
		HR(D3DX11CreateShaderResourceViewFromFile(gRENDERER->GetDevice(), filename.c_str(), 0, 0, &srv, 0 ));

		mTextureSRV[filename] = srv;
	}

	return srv.GetInterfacePtr();
}
 

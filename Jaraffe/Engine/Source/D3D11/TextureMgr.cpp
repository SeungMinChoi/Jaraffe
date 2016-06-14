#include "stdafx.h"
#include "TextureMgr.h"

Jaraffe::TextureMgr::TextureMgr()
{
}

Jaraffe::TextureMgr::~TextureMgr()
{
	for(auto it = mTextureSRV.begin(); it != mTextureSRV.end(); ++it)
    {
		ReleaseCOM(it->second);
    }

	mTextureSRV.clear();
}

void Jaraffe::TextureMgr::Init()
{
	// TODO : TEST Textures
	CreateTexture(L"Resources/Textures/WoodCrate01.dds");
	CreateTexture(L"Resources/Textures/flare.dds");
	CreateTexture(L"Resources/Textures/flarealpha.dds");
}

ID3D11ShaderResourceView* Jaraffe::TextureMgr::CreateTexture(std::wstring filename)
{
	ID3D11ShaderResourceView* srv = 0;

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

	return srv;
}
 

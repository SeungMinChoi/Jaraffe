#include "stdafx.h"
#include "TextureMgr.h"

JF::TextureMgr::TextureMgr()
{
}

JF::TextureMgr::~TextureMgr()
{
	Release();
}

void JF::TextureMgr::Reset()
{

}

void JF::TextureMgr::Release()
{
	mTextureSRV.clear();
}

ID3D11ShaderResourceView* JF::TextureMgr::CreateTexture(std::wstring filename)
{
	ID3D11ShaderResourceViewPtr srv = nullptr;

	// Does it already exist?
	if( mTextureSRV.find(filename) != mTextureSRV.end() )
	{
		srv = mTextureSRV[filename];
	}
	else
	{
		HR(D3DX11CreateShaderResourceViewFromFile(gRENDERER->Device(), filename.c_str(), 0, 0, &srv, 0 ));

		mTextureSRV[filename] = srv;
	}

	return srv.GetInterfacePtr();
}
 

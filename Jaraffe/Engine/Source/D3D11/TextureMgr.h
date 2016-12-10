#pragma once

#define gTEXTUREMGR JF::TextureMgr::GetInstance()

namespace JF
{

class TextureMgr
{
//=============================================================================
// Singletone)
//=============================================================================
	SINGLETONE(TextureMgr)

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	void Reset();
	void Release();

	ID3D11ShaderResourceView* CreateTexture(std::wstring filename);

//=============================================================================
// private Members) 
//=============================================================================
private:
	std::map<std::wstring, ID3D11ShaderResourceViewPtr> mTextureSRV;
};

}
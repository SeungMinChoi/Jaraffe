#pragma once

#define gTEXTUREMGR Jaraffe::TextureMgr::GetInstance()

namespace Jaraffe
{

class TextureMgr
{
//=============================================================================
// Singletone)
//=============================================================================
	SINGLETONE(TextureMgr)

//=============================================================================
// Not Use Operators)
//=============================================================================
private:
	TextureMgr(const TextureMgr& rhs);
	TextureMgr& operator=(const TextureMgr& rhs);

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	void Init();

	ID3D11ShaderResourceView* CreateTexture(std::wstring filename);

//=============================================================================
// private Members) 
//=============================================================================
private:
	std::map<std::wstring, ID3D11ShaderResourceViewPtr> mTextureSRV;
};

}
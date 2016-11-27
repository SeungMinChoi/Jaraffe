#pragma once

namespace JF
{

class Texture
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Texture();
	virtual ~Texture();

//=============================================================================
// public Functions)
//=============================================================================
public:
	ID3D11ShaderResourceView* GetTexture();
	void SetTexture(ID3D11ShaderResourceView* p_pTexture);

//=============================================================================
// private Members)
//=============================================================================
private:
	ID3D11ShaderResourceView* m_pTexture;
};

}
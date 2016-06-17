#include "stdafx.h"
#include "Texture.h"

Jaraffe::Texture::Texture()
{
}

Jaraffe::Texture::~Texture()
{
}

void Jaraffe::Texture::SetTexture(ID3D11ShaderResourceView* p_pTexture)
{
	m_pTexture = p_pTexture;
}
#include "stdafx.h"
#include "Texture.h"

Jaraffe::Texture::Texture()
{
}

Jaraffe::Texture::~Texture()
{
}

ID3D11ShaderResourceView* Jaraffe::Texture::GetTexture()
{
	if (m_pTexture == nullptr)
	{
		
	}

	return m_pTexture;
}

void Jaraffe::Texture::SetTexture(ID3D11ShaderResourceView* p_pTexture)
{
	m_pTexture = p_pTexture;
}
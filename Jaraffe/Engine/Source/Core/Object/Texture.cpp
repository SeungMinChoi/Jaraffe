#include "stdafx.h"
#include "Texture.h"

JF::Texture::Texture()
{
}

JF::Texture::~Texture()
{
}

ID3D11ShaderResourceView* JF::Texture::GetTexture()
{
	if (m_pTexture == nullptr)
	{
		
	}

	return m_pTexture;
}

void JF::Texture::SetTexture(ID3D11ShaderResourceView* p_pTexture)
{
	m_pTexture = p_pTexture;
}
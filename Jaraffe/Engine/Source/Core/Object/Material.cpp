#include "stdafx.h"
#include "Material.h"

Jaraffe::Material::Material()
{
	m_Material.Ambient	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Diffuse	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Reflect	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
}

Jaraffe::Material::~Material()
{

}
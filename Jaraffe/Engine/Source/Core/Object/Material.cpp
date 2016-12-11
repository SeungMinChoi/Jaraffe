#include "stdafx.h"
#include "Material.h"

JF::Material::Material()
{
	m_Material.Ambient	= XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_Material.Diffuse	= XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_Material.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.5f);
	m_Material.Reflect	= XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
}

JF::Material::~Material()
{

}
#include "stdafx.h"
#include "Material.h"

Jaraffe::Material Jaraffe::Material::m_pDefalutMaterial;

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

Jaraffe::Material* Jaraffe::Material::GetDefalutMaterial()
{
	static bool isOnce = false;

	if (isOnce == false)
	{
		m_pDefalutMaterial.m_Material.Ambient	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pDefalutMaterial.m_Material.Diffuse	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pDefalutMaterial.m_Material.Specular	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pDefalutMaterial.m_Material.Reflect	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		m_pDefalutMaterial.m_MainTexture = new Jaraffe::Texture();
		m_pDefalutMaterial.m_MainTexture->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WireFence.dds"));

		isOnce = true;
	}

	return &m_pDefalutMaterial;
}
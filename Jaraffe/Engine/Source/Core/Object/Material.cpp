#include "stdafx.h"
#include "Material.h"

JF::Material JF::Material::m_pDefalutMaterial;

JF::Material::Material()
{
	m_Material.Ambient	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Diffuse	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Material.Reflect	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
}

JF::Material::~Material()
{

}

JF::Material* JF::Material::GetDefalutMaterial()
{
	static bool isOnce = false;

	if (isOnce == false)
	{
		m_pDefalutMaterial.m_Material.Ambient	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pDefalutMaterial.m_Material.Diffuse	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pDefalutMaterial.m_Material.Specular	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pDefalutMaterial.m_Material.Reflect	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		m_pDefalutMaterial.m_MainTexture = new JF::Texture();
		m_pDefalutMaterial.m_MainTexture->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WireFence.dds"));

		isOnce = true;
	}

	return &m_pDefalutMaterial;
}
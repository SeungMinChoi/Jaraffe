#include "stdafx.h"
#include "Renderer.h"

DECLARE_IDENTIFIER(JF::Component::Renderer);

JF::Component::Renderer::Renderer()
{

}

JF::Component::Renderer::~Renderer()
{

}

JF::Material* JF::Component::Renderer::GetMaterial()
{
	if (m_Material == nullptr)
	{
		return JF::Material::GetDefalutMaterial();
	}

	return m_Material;
}

void JF::Component::Renderer::SetMaterial(JF::Material* p_pMaterial)
{
	m_Material = p_pMaterial;
}
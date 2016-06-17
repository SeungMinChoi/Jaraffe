#include "stdafx.h"
#include "Renderer.h"

DECLARE_IDENTIFIER(Jaraffe::Component::Renderer);

Jaraffe::Component::Renderer::Renderer()
{

}

Jaraffe::Component::Renderer::~Renderer()
{

}

void Jaraffe::Component::Renderer::SetMaterial(Jaraffe::Material* p_pMaterial)
{
	m_Material = p_pMaterial;
}
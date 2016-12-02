#include "stdafx.h"
#include "Light.h"

// Static Member DECLARE
DECLARE_IDENTIFIER(JF::Component::Light);

JF::Component::Light::Light()
{
}

JF::Component::Light::~Light()
{
}

void JF::Component::Light::Init()
{

}

void JF::Component::Light::Release()
{
	SafeDelete(m_pLight);
}

JF::Light::BasicLight* JF::Component::Light::SetLightType(JF::Light::LightType p_LightType)
{
	//
	m_LightType = p_LightType;

	//
	SafeDelete(m_pLight);

	// 
	switch (m_LightType)
	{
	case JF::Light::LightType::Directional:
		m_pLight = new JF::Light::DirectionalLight;
		break;

	case JF::Light::LightType::Point:
		m_pLight = new JF::Light::PointLight;
		break;

	case JF::Light::LightType::Spot:
		m_pLight = new JF::Light::SpotLight;
		break;
	}

	return m_pLight;
}
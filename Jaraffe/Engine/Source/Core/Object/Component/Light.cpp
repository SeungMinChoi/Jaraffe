#include "stdafx.h"
#include "Light.h"

// Static Member DECLARE
DECLARE_IDENTIFIER(JF::Component::Light);
std::vector<Light*> JF::Component::Light::m_vLights;

JF::Component::Light::Light()
{
	m_vLights.push_back(this);
}

JF::Component::Light::~Light()
{
	Light* pthisLight = this;
	auto iterFind = std::find_if(m_vLights.begin(), m_vLights.end(), [pthisLight](const Light* rhs)
	{
		if (pthisLight == nullptr)
			return false;

		return rhs == pthisLight;
	});

	if (iterFind == m_vLights.end())
		return;

	m_vLights.erase(iterFind);
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

JF::Light::BasicLight* JF::Component::Light::GetLight()
{
	return m_pLight;
}

JF::Light::DirectionalLight* JF::Component::Light::GetDirectionalLight()
{
	return (JF::Light::DirectionalLight*)m_pLight;
}

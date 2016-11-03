#include "stdafx.h"
#include "Light.h"

// Static Member DECLARE
DECLARE_IDENTIFIER(Jaraffe::Component::Light);
std::vector<Light*> Jaraffe::Component::Light::m_vLights;

Jaraffe::Component::Light::Light()
{
	m_vLights.push_back(this);
}

Jaraffe::Component::Light::~Light()
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

void Jaraffe::Component::Light::Init()
{

}

void Jaraffe::Component::Light::Release()
{
	SafeDelete(m_pLight);
}

Jaraffe::Light::BasicLight* Jaraffe::Component::Light::SetLightType(Jaraffe::Light::LightType p_LightType)
{
	//
	m_LightType = p_LightType;

	//
	SafeDelete(m_pLight);

	// 
	switch (m_LightType)
	{
	case Jaraffe::Light::LightType::Directional:
		m_pLight = new Jaraffe::Light::DirectionalLight;
		break;

	case Jaraffe::Light::LightType::Point:
		m_pLight = new Jaraffe::Light::PointLight;
		break;

	case Jaraffe::Light::LightType::Spot:
		m_pLight = new Jaraffe::Light::SpotLight;
		break;
	}

	return m_pLight;
}

Jaraffe::Light::BasicLight* Jaraffe::Component::Light::GetLight()
{
	return m_pLight;
}

Jaraffe::Light::DirectionalLight* Jaraffe::Component::Light::GetDirectionalLight()
{
	return (Jaraffe::Light::DirectionalLight*)m_pLight;
}

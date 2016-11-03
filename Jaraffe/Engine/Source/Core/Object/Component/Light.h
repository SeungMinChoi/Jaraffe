#pragma once

namespace Jaraffe
{
namespace Component
{

class Light : public BaseComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	Light();
	virtual ~Light();

// ****************************************************************************
// Component IDENTIFIER)
// ----------------------------------------------------------------------------
public:
	COMPONENT_IDENTIFIER(Light, BaseComponent, true);

// ****************************************************************************
// override) 
// ----------------------------------------------------------------------------
public:
	virtual void Init();
	virtual void Release();

// ****************************************************************************
// public Funtions) 
// ----------------------------------------------------------------------------
public:
	Jaraffe::Light::BasicLight*			SetLightType(Jaraffe::Light::LightType p_LightType);
	
	Jaraffe::Light::BasicLight*			GetLight();
	Jaraffe::Light::DirectionalLight*	GetDirectionalLight();

// ****************************************************************************
// Private Members) 
// ----------------------------------------------------------------------------
private:
	// ������ Ÿ��.
	Jaraffe::Light::LightType m_LightType = Jaraffe::Light::LightType::Directional;

	// 
	Jaraffe::Light::BasicLight* m_pLight = nullptr;

// ****************************************************************************
// public static Members) 
// ----------------------------------------------------------------------------
public:
	static std::vector<Light*> m_vLights;
};

}
}
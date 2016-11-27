#pragma once

namespace JF
{
namespace Component
{

class Light : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	Light();
	virtual ~Light();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(Light, BaseComponent, true);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void Init();
	virtual void Release();

//=============================================================================
// public Funtions) 
//=============================================================================
public:
	JF::Light::BasicLight*			SetLightType(JF::Light::LightType p_LightType);
	
	JF::Light::BasicLight*			GetLight();
	JF::Light::DirectionalLight*	GetDirectionalLight();

//=============================================================================
// Private Members) 
//=============================================================================
private:
	// 라이팅 타입.
	JF::Light::LightType m_LightType = JF::Light::LightType::Directional;

	// 
	JF::Light::BasicLight* m_pLight = nullptr;

//=============================================================================
// public static Members) 
//=============================================================================
public:
	static std::vector<Light*> m_vLights;
};

}
}
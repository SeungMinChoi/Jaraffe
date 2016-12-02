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
	
	const JF::Light::LightType&				GetLightType()				const	{ return m_LightType; }
	const JF::Light::DirectionalLight*		GetDirectionalLight()				{ return static_cast<JF::Light::DirectionalLight*>(m_pLight); }
	const JF::Light::PointLight*			GetPointLight()						{ return static_cast<JF::Light::PointLight*>(m_pLight); }
	const JF::Light::SpotLight*				GetSpotLight()						{ return static_cast<JF::Light::SpotLight*>(m_pLight); }

//=============================================================================
// Private Members) 
//=============================================================================
private:
	// 라이팅 타입.
	JF::Light::LightType m_LightType = JF::Light::LightType::Directional;

	// 
	JF::Light::BasicLight* m_pLight = nullptr;
};

}
}
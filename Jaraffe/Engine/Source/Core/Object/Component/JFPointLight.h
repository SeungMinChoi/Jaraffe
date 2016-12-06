#pragma once

namespace JF
{
namespace Component
{

class JFPointLight : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	JFPointLight()			{ m_pLight = new JF::Light::PointLight(); }
	virtual ~JFPointLight() { SafeDelete(m_pLight); }

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(JFPointLight, BaseComponent, true);

//=============================================================================
// public Funtions) 
//=============================================================================
public:
	void SetAmbient		(const XMFLOAT4& _ambient)					{ m_pLight->Ambient		= _ambient; }
	void SetDiffuse		(const XMFLOAT4& _diffuse)					{ m_pLight->Diffuse		= _diffuse; }
	void SetSpecular	(const XMFLOAT4& _specular)					{ m_pLight->Specular	= _specular; }
																			  
	void SetAmbient		(float x, float y, float z, float w)		{ m_pLight->Ambient		= XMFLOAT4(x, y, z, w); }
	void SetDiffuse		(float x, float y, float z, float w)		{ m_pLight->Diffuse		= XMFLOAT4(x, y, z, w); }
	void SetSpecular	(float x, float y, float z, float w)		{ m_pLight->Specular	= XMFLOAT4(x, y, z, w);	}
																			  
	void SetRange		(float _range)								{ m_pLight->Range = _range; }

	const XMFLOAT4&							GetAmbient()			const	{ return m_pLight->Ambient; }
	const XMFLOAT4&							GetDiffuse()			const	{ return m_pLight->Diffuse; }
	const XMFLOAT4&							GetSpecular()			const	{ return m_pLight->Specular; }

	const float								GetRange()				const	{ return m_pLight->Range; }

	const JF::Light::PointLight*			GetPointLight()			const	{ return m_pLight; }

//=============================================================================
// Private Members) 
//=============================================================================
private:
	JF::Light::PointLight* m_pLight;
};

}
}
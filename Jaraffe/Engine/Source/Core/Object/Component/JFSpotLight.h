#pragma once

namespace JF
{
namespace Component
{

class JFSpotLight : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	JFSpotLight()			{ m_pLight = new JF::Light::SpotLight(); }
	virtual ~JFSpotLight()	{ SafeDelete(m_pLight); }

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(JFSpotLight, BaseComponent, true);

//=============================================================================
// public Funtions) 
//=============================================================================
public:
	void SetAmbient		(const XMFLOAT4& _ambient)					{ m_pLight->Ambient		= _ambient; }
	void SetDiffuse		(const XMFLOAT4& _diffuse)					{ m_pLight->Diffuse		= _diffuse; }
	void SetSpecular	(const XMFLOAT4& _specular)					{ m_pLight->Specular	= _specular; }
	void SetDirection	(const XMFLOAT3& _direction)				{ m_pLight->Direction	= _direction; }
	void SetAtt			(const XMFLOAT3& _att)						{ m_pLight->Att			= _att; }

	void SetAmbient		(float x, float y, float z, float w)		{ m_pLight->Ambient		= XMFLOAT4(x, y, z, w); }
	void SetDiffuse		(float x, float y, float z, float w)		{ m_pLight->Diffuse		= XMFLOAT4(x, y, z, w); }
	void SetSpecular	(float x, float y, float z, float w)		{ m_pLight->Specular	= XMFLOAT4(x, y, z, w);	}
	void SetDirection	(float x, float y, float z)					{ m_pLight->Direction	= XMFLOAT3(x, y, z); }
	void SetAtt			(float x, float y, float z)					{ m_pLight->Att			= XMFLOAT3(x, y, z); }

	void SetRange		(float _range)								{ m_pLight->Range = _range; }

	const XMFLOAT4&							GetAmbient()			const	{ return m_pLight->Ambient; }
	const XMFLOAT4&							GetDiffuse()			const	{ return m_pLight->Diffuse; }
	const XMFLOAT4&							GetSpecular()			const	{ return m_pLight->Specular; }
	const XMFLOAT3&							GetDirection()			const	{ return m_pLight->Direction; }
	const XMFLOAT3&							GetAtt()				const	{ return m_pLight->Att; }

	const float								GetRange()				const	{ return m_pLight->Range; }

	const JF::Light::SpotLight*				GetSpotLight()			const	{ return m_pLight; }

//=============================================================================
// Private Members) 
//=============================================================================
private:
	JF::Light::SpotLight* m_pLight;
};

}
}
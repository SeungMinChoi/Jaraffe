#pragma once

namespace JF
{
namespace Component 
{

class JFDirectionalLight : public BaseComponent
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	JFDirectionalLight()			{ m_pLight = new JF::Light::DirectionalLight();}
	virtual ~JFDirectionalLight()	{ SafeDelete(m_pLight); }

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(JFDirectionalLight, BaseComponent, true);

//=============================================================================
// public Funtions) 
//=============================================================================
public:
	void SetAmbient		(const XMFLOAT4& _ambient)					{ m_pLight->Ambient		= _ambient; }
	void SetDiffuse		(const XMFLOAT4& _diffuse)					{ m_pLight->Diffuse		= _diffuse; }
	void SetSpecular	(const XMFLOAT4& _specular)					{ m_pLight->Specular	= _specular; }
	void SetDirection	(const XMFLOAT3& _direction)				{ m_pLight->Direction	= _direction; }
																			  
	void SetAmbient		(float x, float y, float z, float w)		{ m_pLight->Ambient		= XMFLOAT4(x, y, z, w); }
	void SetDiffuse		(float x, float y, float z, float w)		{ m_pLight->Diffuse		= XMFLOAT4(x, y, z, w); }
	void SetSpecular	(float x, float y, float z, float w)		{ m_pLight->Specular	= XMFLOAT4(x, y, z, w);	}
	void SetDirection	(float x, float y, float z)					{ m_pLight->Direction	= XMFLOAT3(x, y, z);	}

	const	XMFLOAT4&						GetAmbient()			const	{ return m_pLight->Ambient; }
	const	XMFLOAT4&						GetDiffuse()			const	{ return m_pLight->Diffuse; }
	const	XMFLOAT4&						GetSpecular()			const	{ return m_pLight->Specular; }
	const	XMFLOAT3&						GetDirection()			const	{ return m_pLight->Direction; }
			JF::Light::DirectionalLight*	GetDirectionalLight()	const	{ return m_pLight; }

//=============================================================================
// Private Members) 
//=============================================================================
private:
	JF::Light::DirectionalLight* m_pLight;
};

}
}
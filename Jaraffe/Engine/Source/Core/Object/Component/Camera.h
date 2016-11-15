#pragma once

namespace Jaraffe
{
namespace Component
{

class Camera : public BaseComponent
{
public:
//=============================================================================
// Constructor/Destructor)
//=============================================================================
	Camera();
	virtual ~Camera();

//=============================================================================
// Component IDENTIFIER)
//=============================================================================
public:
	COMPONENT_IDENTIFIER(Camera, BaseComponent, true);

//=============================================================================
// override) 
//=============================================================================
public:
	virtual void	Init();
	virtual void	Update(float t);
	virtual void	Render();
	virtual void	Release();

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	void			CalculationProj();

	XMMATRIX		GetView() const;
	XMMATRIX		GetProj() const;
	XMMATRIX		GetViewProj() const;

	XMFLOAT3		GetEyePos() const;

//=============================================================================
// Public static Functions) 
//=============================================================================
public:
	static void		SetMainCamera(Camera* p_pCamera);

//=============================================================================
// static Members) 
//=============================================================================
public:
	static Camera* g_pMainCamera;

//=============================================================================
// private Members) 
//=============================================================================
private:
	//
	XMFLOAT3		m_vEye;
	XMFLOAT3		m_vUp;
	XMFLOAT3		m_vLookAt;

	// Frustum Property
	float			m_Aspect;
	float			m_NearZ;
	float			m_FarZ;
	float			m_FovY;

	// Mouse
	XMFLOAT2		m_LastMousePos;

	// 구면좌표를 데카르트좌표로 변환하기 위한 변수들.
	float			m_Theta;
	float			m_Phi;
	float			m_Radius;

	// View Matrix, Projection Matrix
	XMFLOAT4X4		m_View;
	XMFLOAT4X4		m_Proj;
};

}
}
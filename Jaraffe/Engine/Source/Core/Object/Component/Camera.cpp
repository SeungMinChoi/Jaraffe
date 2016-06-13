#include "stdafx.h"
#include "Camera.h"

DECLARE_IDENTIFIER(Jaraffe::Component::Camera);

Jaraffe::Component::Camera* Jaraffe::Component::Camera::g_pMainCamera;

Jaraffe::Component::Camera::Camera()
: m_Theta(1.5f * XM_PI)
, m_Phi(0.25f * XM_PI)
, m_Radius(5.0f)
, m_vEye(0.0f, 0.0f, -20.0f)
, m_vUp(0.0f, 1.0f, 0.0f)
, m_vLookAt(0.0f, 0.0f, 0.0f)
, m_Aspect(1.0f)
, m_NearZ(1.0f)
, m_FarZ(3000.0f)
, m_FovY(0.25f * XM_PI)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&m_View, I);
	XMStoreFloat4x4(&m_Proj, I);
}

Jaraffe::Component::Camera::~Camera()
{
}

void Jaraffe::Component::Camera::Init()
{
	// 뷰 행렬과 투영행렬을 계산한다.
	CalculationView();
	CalculationProj();
}

void Jaraffe::Component::Camera::Update()
{
}

void Jaraffe::Component::Camera::Render()
{
}

void Jaraffe::Component::Camera::Release()
{
}

void Jaraffe::Component::Camera::Receve()
{

}

void Jaraffe::Component::Camera::UpdateViewMatrix()
{
	// 뷰 행렬을 갱신한다.
	CalculationView();
}

void Jaraffe::Component::Camera::CalculationView()
{
	//float x = m_Radius * sinf(m_Phi) * cosf(m_Theta);
	//float z = m_Radius * sinf(m_Phi) * sinf(m_Theta);
	//float y = m_Radius * cosf(m_Phi);

	// Initialize the view matrix
	XMVECTOR Eye	= XMLoadFloat3(&m_vEye);
	XMVECTOR At		= XMLoadFloat3(&m_vLookAt);
	XMVECTOR Up		= XMLoadFloat3(&m_vUp);
	XMStoreFloat4x4(&m_View, XMMatrixLookAtLH(Eye, At, Up));
}

void Jaraffe::Component::Camera::CalculationProj()
{
	// 현재 화면의 크기를 구한뒤 투영행렬을 계산한다.
	RECT rc		= gRENDERER->GetScreenRectSize();
	UINT width	= rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	m_Aspect	= width / (FLOAT)height;

	// Initialize the projection matrix
	XMStoreFloat4x4(&m_Proj, XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ));
}

XMMATRIX Jaraffe::Component::Camera::GetView() const
{
	return XMLoadFloat4x4(&m_View);
}

XMMATRIX Jaraffe::Component::Camera::GetProj() const
{
	return XMLoadFloat4x4(&m_Proj);
}

XMMATRIX Jaraffe::Component::Camera::GetViewProj() const
{
	return XMMatrixMultiply(GetView(), GetProj());
}

XMFLOAT3 Jaraffe::Component::Camera::GetEyePos() const
{
	return m_vEye;
}

void Jaraffe::Component::Camera::SetMainCamera(Camera* p_pCamera)
{
	Jaraffe::Component::Camera::g_pMainCamera = p_pCamera;
}

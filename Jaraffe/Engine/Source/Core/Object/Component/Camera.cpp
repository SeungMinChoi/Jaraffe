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
	CalculationProj();
}

void Jaraffe::Component::Camera::Update(float t)
{
	// Transform 이 없다면 무의미하므로 리턴.
	auto* pTransform = GetOwner()->GetComponent<Jaraffe::Component::Transform>();
	if (pTransform == nullptr)
		return;

	// 1) 메인 카메라 라면 움직임을 제어할수 있다.
	if (g_pMainCamera == this)
	{
		XMFLOAT3 pos = gINPUT->GetMousePosition();

		if (gINPUT->GetKeyDown('W')) {
			pTransform->Walk(25.0f * t);
		}
		if (gINPUT->GetKeyDown('S')) {
			pTransform->Walk(-25.0f * t);
		}

		if (gINPUT->GetKeyDown('A')) {
			pTransform->Strafe(-25.0f * t);
		}
		if (gINPUT->GetKeyDown('D')) {
			pTransform->Strafe(25.0f * t);
		}

		if (gINPUT->GetKeyDown('Q'))
		{
			pTransform->Upper(-25.0f * t);
		}
		if (gINPUT->GetKeyDown('E'))
		{
			pTransform->Upper(25.0f * t);
		}

		if (gINPUT->GetMouseButtonDown(VK_RBUTTON))
		{
			float dx = XMConvertToRadians(0.25f*static_cast<float>(pos.x - m_LastMousePos.x));
			float dy = XMConvertToRadians(0.25f*static_cast<float>(pos.y - m_LastMousePos.y));

			pTransform->Roll(dx , false);
			pTransform->Pitch(dy);
		}

		m_LastMousePos.x = pos.x;
		m_LastMousePos.y = pos.y;
	}

	// 2) View Materix 를 갱신한다.
	XMFLOAT3 vRight = pTransform->Right();
	XMFLOAT3 vUp	= pTransform->Up();
	XMFLOAT3 vLook	= pTransform->Forward();

	XMVECTOR R = XMLoadFloat3(&vRight);
	XMVECTOR U = XMLoadFloat3(&vUp);
	XMVECTOR L = XMLoadFloat3(&vLook);
	XMVECTOR P = XMLoadFloat3(&pTransform->GetPosition());

	// Fill in the view matrix entries.
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	m_View(0, 0) = vRight.x;
	m_View(1, 0) = vRight.y;
	m_View(2, 0) = vRight.z;
	m_View(3, 0) = x;

	m_View(0, 1) = vUp.x;
	m_View(1, 1) = vUp.y;
	m_View(2, 1) = vUp.z;
	m_View(3, 1) = y;

	m_View(0, 2) = vLook.x;
	m_View(1, 2) = vLook.y;
	m_View(2, 2) = vLook.z;
	m_View(3, 2) = z;

	m_View(0, 3) = 0.0f;
	m_View(1, 3) = 0.0f;
	m_View(2, 3) = 0.0f;
	m_View(3, 3) = 1.0f;
}

void Jaraffe::Component::Camera::Render()
{
}

void Jaraffe::Component::Camera::Release()
{
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

#include "stdafx.h"
#include "Scene.h"

using namespace Jaraffe::Component;

Jaraffe::CScene::CScene()
{
}

Jaraffe::CScene::~CScene()
{
}

HRESULT Jaraffe::CScene::Init()
{
	// 1) Create MainCamera
	Camera* newCamera = new Camera();
	Camera::SetMainCamera(newCamera);

	GameObject* m_pMainCamera = GameObject::Create();
	m_pMainCamera->InsertComponent(new Transform);
	m_pMainCamera->InsertComponent(newCamera);

	m_pMainCamera->Init();

	// 2) Create Directional Light
	Jaraffe::Component::Light* pMainLight = new Jaraffe::Component::Light();
	auto plight = pMainLight->SetLightType(Jaraffe::Light::LightType::Directional);
	if (plight != nullptr)
	{
		auto cast = (Jaraffe::Light::DirectionalLight*)plight;
		cast->Ambient	= XMFLOAT4(0.2f, 0.5f, 0.7f, 1.0f);
		cast->Diffuse	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		cast->Specular	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		cast->Direction = XMFLOAT3(6.57735f, -0.57735f, 0.57735f);
	}

	GameObject* m_DirectionalLight = GameObject::Create();
	m_DirectionalLight->InsertComponent(new Transform);
	m_DirectionalLight->InsertComponent(pMainLight);

	//---- T E S T ----

	GameObject* m_pTestModel = GameObject::Create();
	m_pTestModel->InsertComponent(new Transform);
	m_pTestModel->InsertComponent(new MeshRenderer);
	m_pTestModel->InsertComponent(new Mesh);
	m_pTestModel->InsertComponent(new Jaraffe::Component::Material);

	m_ObjectList.push_back(m_pTestModel);

	//---- E N D   ----

	// All GameObject Init
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Init();
	}

	return S_OK;
}

void Jaraffe::CScene::Update(float t)
{
	// 1) Camera Update.
	Camera::g_pMainCamera->Update();

	// 2) All GameObject Update
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Update();
	}
}

void Jaraffe::CScene::Render()
{
	// 1) Back Buffer BackGround Clear.
	gRENDERER->ClearRenderTargetView( reinterpret_cast<const float*>(&Jaraffe::Util::Colors::Blue) );

	// 2) Depth And Stencil View Clear.
	gRENDERER->ClearDepthStencilView();

	// 3) View Matrix Calculation.
	Camera::g_pMainCamera->UpdateViewMatrix();

	// 4) All Renderer Render
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Render();
	}

	// Final) Back Buffer Screen Present.
	gRENDERER->Present();
}

void Jaraffe::CScene::Release()
{
	// 1) All GameObject Release
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Release();
	}
	m_ObjectList.clear();
}
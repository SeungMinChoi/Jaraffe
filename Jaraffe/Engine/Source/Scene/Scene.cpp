#include "stdafx.h"
#include "Scene.h"

using namespace Jaraffe;
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

	//---- T E S T ----

	GameObject* m_pTestModel = GameObject::Create();
	m_pTestModel->InsertComponent(new Transform);
	m_pTestModel->InsertComponent(new Mesh);

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

	// 4) All Renderer Render TODO : 구조잡기전 임시. 
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		auto model = m_ObjectList[i]->GetComponent<Jaraffe::Component::Mesh>();
		if(model == nullptr)
			continue;

		model->Render();
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
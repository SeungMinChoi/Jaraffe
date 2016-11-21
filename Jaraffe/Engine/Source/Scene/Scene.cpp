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
	{
		Camera* newCamera = new Camera();
		Camera::SetMainCamera(newCamera);

		Transform* transform = new Transform();
		transform->SetPosition(0.0f, 0.0f, -10.0f);

		GameObject* m_pMainCamera = GameObject::Create();
		m_pMainCamera->InsertComponent(transform);
		m_pMainCamera->InsertComponent(newCamera);

		m_pMainCamera->Init();

		m_ObjectList.push_back(m_pMainCamera);
	}

	// 2) Create Directional Light 1
	{
		Jaraffe::Component::Light* pMainLight = new Jaraffe::Component::Light();
		auto plight = pMainLight->SetLightType(Jaraffe::Light::LightType::Directional);
		if (plight != nullptr)
		{
			auto cast = (Jaraffe::Light::DirectionalLight*)plight;
			cast->Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			cast->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			cast->Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			cast->Direction = XMFLOAT3(-0.707f, 0.0f, 0.707f);
		}

		GameObject* m_DirectionalLight = GameObject::Create();
		m_DirectionalLight->InsertComponent(new Transform);
		m_DirectionalLight->InsertComponent(pMainLight);

		m_ObjectList.push_back(m_DirectionalLight);
	}

	// ---- CubeMap -- //
	{
		Jaraffe::Texture* pTex = new Jaraffe::Texture();
		//pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/grasscube1024.dds"));
		pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/HomeCubeMap.dds"));

		GameObject* m_pCubeMap = GameObject::Create();
		m_pCubeMap->InsertComponent(new CubeMap(5000.0f, pTex));

		m_ObjectList.push_back(m_pCubeMap);
	}

	// ---- T E S T _ B O X 1 ---- //
	{
		Jaraffe::Material* pMat = new Jaraffe::Material();
		Jaraffe::Texture* pTex = new Jaraffe::Texture();
		pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WireFence.dds"));
		pMat->m_RSState = Jaraffe::RenderStates::GetRasterizerStates()->BackFaceCull();
		pMat->m_MainTexture = pTex;

		MeshRenderer* pBoxMeshRenderer = new MeshRenderer();
		pBoxMeshRenderer->SetMaterial(pMat);

		Mesh* pBoxMesh = new Mesh();
		float w2 = 1.0f;
		float h2 = 1.0f;
		float d2 = 1.0f;
		Jaraffe::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(new Transform);
		m_pTestBox->InsertComponent(pBoxMeshRenderer);
		m_pTestBox->InsertComponent(pBoxMesh);

		ColisionBox* pColisionBox = new ColisionBox();
		pColisionBox->SethalfExtents(XMFLOAT3(0.5f, 0.5f, 0.5f));
		m_pTestBox->InsertComponent(pColisionBox);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 2 ---- //
	{
		Jaraffe::Material* pMat = new Jaraffe::Material();
		Jaraffe::Texture* pTex = new Jaraffe::Texture();
		pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/darkbrickdxt1.dds"));
		pMat->m_RSState = Jaraffe::RenderStates::GetRasterizerStates()->BackFaceCull();
		pMat->m_MainTexture = pTex;

		MeshRenderer* pBoxMeshRenderer = new MeshRenderer();
		pBoxMeshRenderer->SetMaterial(pMat);

		Mesh* pBoxMesh = new Mesh();
		float w2 = 1.0f;
		float h2 = 1.0f;
		float d2 = 1.0f;
		Jaraffe::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

		Transform* transform = new Transform();
		transform->SetPosition(3.0f, 0.0f, 0.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(pBoxMeshRenderer);
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ G R O U N D ---- //
	{
		Jaraffe::Material* pMat = new Jaraffe::Material();
		Transform* groundtransform = new Transform;
		groundtransform->SetScale(50.0f, 1.0f, 50.0f);
		groundtransform->SetPosition(0.0f, -3.0f, 0.0f);

		Mesh* pGroundMesh = new Mesh();
		Jaraffe::MeshLoader::OBJLoad(L"Resources/Models/ground.obj", pGroundMesh->GetVertices(), pGroundMesh->GetIndices(), *pMat);

		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);

		MeshRenderer* pMeshRenderer = new MeshRenderer();
		pMeshRenderer->SetMaterial(pMat);
		m_pTestGround->InsertComponent(pMeshRenderer);
		m_pTestGround->InsertComponent(pGroundMesh);

		// 임시 고정 플렌 콜리전
		PxRigidStatic* groundPlane = PxCreatePlane(*PhysXDevice::GetInstance()->GetPhysics(), PxPlane(0, 1, 0, 3), *PhysXDevice::GetInstance()->GetMaterial());
		PhysXDevice::GetInstance()->GetScene()->addActor(*groundPlane);

		m_ObjectList.push_back(m_pTestGround);
	}

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
	// 1) physics Update
	PX_UNUSED(true);
	PhysXDevice::GetInstance()->GetScene()->simulate(t);
	PhysXDevice::GetInstance()->GetScene()->fetchResults(true);

	// test
	{
		m_ObjectList[4]->GetComponent<Transform>()->Roll(t);
		m_ObjectList[4]->GetComponent<Transform>()->Pitch(t);
		m_ObjectList[4]->GetComponent<Transform>()->Yaw(t);
	}

	// 2) All GameObject Update
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Update(t);
	}
}

void Jaraffe::CScene::Render()
{
	// 1) Back Buffer BackGround Clear.
	gRENDERER->ClearRenderTargetView( reinterpret_cast<const float*>(&Jaraffe::Util::Colors::Blue) );

	// 2) Depth And Stencil View Clear.
	gRENDERER->ClearDepthStencilView();

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
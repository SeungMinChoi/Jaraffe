#include "stdafx.h"
#include "Scene.h"

using namespace JF::Component;

JF::JFCScene::JFCScene(JFCApp* _appInfo) : m_pApp(_appInfo)
{
}

JF::JFCScene::~JFCScene()
{
}

HRESULT JF::JFCScene::Init()
{
	// Declear)
	int nClientWidth;
	int nClientHeight;

	// 1) Setting
	m_pApp->GetWindow()->GetClientArea(nClientWidth, nClientHeight);
	m_pApp->GetPXDevice()->SceneSetting(PxVec3(0.0f, -9.81f, 0.0f), 0.5f, 0.5f, 0.6f);

	// 1) Create MainCamera ( SkyBox 도 붙인다. )
	{
		JF::Texture* pTex = new JF::Texture();
		//pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/grasscube1024.dds"));
		pTex->SetTexture(gTEXTUREMGR->CreateTexture( L"Resources/Textures/HomeCubeMap.dds"));

		Camera* newCamera = new Camera(nClientWidth, nClientHeight);
		Camera::SetMainCamera(newCamera);

		Transform* transform = new Transform();
		transform->SetPosition(-10.0f, 5.0f, -50.0f);

		GameObject* m_pMainCamera = GameObject::Create();
		m_pMainCamera->InsertComponent(transform);
		m_pMainCamera->InsertComponent(newCamera);
		m_pMainCamera->InsertComponent(new SkyBox(5000.0f, pTex));

		m_pMainCamera->Init();

		m_ObjectList.push_back(m_pMainCamera);
	}

	// 2) Directional Light 1
	{
		JF::Component::Light* directionalLight = new JF::Component::Light();
		auto* plight = directionalLight->SetLightType(JF::Light::LightType::Directional);
		if (plight != nullptr)
		{
			auto cast = (JF::Light::DirectionalLight*)plight;
			cast->Ambient	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			cast->Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			cast->Specular	= XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			cast->Direction = XMFLOAT3(-0.707f, -0.30f, 0.707f);
		}

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(new Transform);
		m_pTestBox->InsertComponent(directionalLight);

		m_ObjectList.push_back(m_pTestBox);
	}

	// 2) Spot Light 1
	{
		JF::Component::Light* directionalLight = new JF::Component::Light();
		auto* plight = directionalLight->SetLightType(JF::Light::LightType::Spot);
		if (plight != nullptr)
		{
			auto cast = (JF::Light::SpotLight*)plight;
			cast->Diffuse	= XMFLOAT4(1.0f, 0.7f, 0.1f, 1.0f);
			cast->Direction = XMFLOAT3(0.0f, 0.0f, 1.1f);
			cast->Range = 50.0f;
		}

		auto* plightPos = new Transform();
		plightPos->SetPosition(-10.0f, 10.0f, -10.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(plightPos);
		m_pTestBox->InsertComponent(directionalLight);

		m_ObjectList.push_back(m_pTestBox);
	}

	// 2) Point Light 1
	{
		int offsetX = 0;
		int offsetZ = 0;
		for (int i = 0; i < 50; ++i)
		{
			offsetX = i % 5;
			offsetZ = i / 10;

			auto* pLight = new JF::Component::Light();
			auto* pPointLight = pLight->SetLightType(JF::Light::LightType::Point);
			if (pPointLight != nullptr)
			{
				auto cast = (JF::Light::PointLight*)pPointLight;
				cast->Diffuse	= XMFLOAT4(JF::Util::MathHelper::RandF() * 2, JF::Util::MathHelper::RandF() * 2, JF::Util::MathHelper::RandF() * 2, 1.0f);
				cast->Range		= 10.0f;
			}

			auto* plightPos = new Transform();
			plightPos->SetPosition(offsetX * 20.0f - 40.0f, 0.0f, offsetZ * 20.0f - 40.0f);

			GameObject* pNewGameObject = GameObject::Create();
			pNewGameObject->InsertComponent(plightPos);
			pNewGameObject->InsertComponent(pLight);

			m_ObjectList.push_back(pNewGameObject);
		}
	}

	// ---- T E S T _ B O X 1 ---- //
	{
		JF::Material* pMat = new JF::Material();
		{
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture( L"Resources/Textures/WoodCrate01.dds"));

			pMat->m_RSState = JF::RenderStates::GetRasterizerStates()->BackFaceCull();
			pMat->m_MainTexture = pTex;
		}

		MeshRenderer* pBoxMeshRenderer = new MeshRenderer();
		pBoxMeshRenderer->SetMaterial(pMat);

		Mesh* pBoxMesh = new Mesh();
		float w2 = 1.0f;
		float h2 = 1.0f;
		float d2 = 1.0f;
		JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

		Transform* transform = new Transform();
		transform->SetPosition(3.0f, 0.0f, 0.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(pBoxMeshRenderer);
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 2---- //
	{
		JF::Material* pMat = new JF::Material();
		JF::Texture* pTex = new JF::Texture();
		pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WireFence.dds"));

		pMat->m_RSState = JF::RenderStates::GetRasterizerStates()->BackFaceCull();
		pMat->m_MainTexture = pTex;

		MeshRenderer* pBoxMeshRenderer = new MeshRenderer();
		pBoxMeshRenderer->SetMaterial(pMat);

		Mesh* pBoxMesh = new Mesh();
		float w2 = 1.0f;
		float h2 = 1.0f;
		float d2 = 1.0f;
		JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(new Transform);
		m_pTestBox->InsertComponent(pBoxMeshRenderer);
		m_pTestBox->InsertComponent(pBoxMesh);

		ColisionBox* pColisionBox = new ColisionBox(m_pApp->GetPXDevice());
		pColisionBox->SethalfExtents(XMFLOAT3(0.5f, 0.5f, 0.5f));
		m_pTestBox->InsertComponent(pColisionBox);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 3 ---- //
	{
		JF::Material* pMat = new JF::Material();
		{
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture( L"Resources/Textures/gravel_a.dds"));

			JF::Texture* pTexNormal = new JF::Texture();
			pTexNormal->SetTexture(gTEXTUREMGR->CreateTexture( L"Resources/Textures/TestBumpMap.png"));
			//pTexNormal->SetTexture(gTEXTUREMGR->CreateTexture( L"Resources/Textures/TestBumpMap2.dds"));

			pMat->m_RSState = JF::RenderStates::GetRasterizerStates()->BackFaceCull();
			pMat->m_MainTexture = pTex;
			pMat->m_BumpTexture = pTexNormal;
		}

		MeshRenderer* pBoxMeshRenderer = new MeshRenderer();
		pBoxMeshRenderer->SetMaterial(pMat);

		Mesh* pBoxMesh = new Mesh();
		float w2 = 1.0f;
		float h2 = 1.0f;
		float d2 = 1.0f;
		JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

		Transform* transform = new Transform();
		transform->SetPosition(0.0f, 0.0f, 0.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(pBoxMeshRenderer);
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 4---- //
	{
		JF::Material* pMat = new JF::Material();
		{
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/gravel_a.dds"));

			pMat->m_MainTexture = pTex;
		}

		MeshRenderer* pBoxMeshRenderer = new MeshRenderer();
		pBoxMeshRenderer->SetMaterial(pMat);

		Mesh* pBoxMesh = new Mesh();
		float w2 = 1.0f;
		float h2 = 1.0f;
		float d2 = 1.0f;
		JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

		Transform* transform = new Transform();
		transform->SetPosition(-10.0f, 10.0f, 10.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);
		transform->SetScale(30.0f, 30.0f, 1.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(pBoxMeshRenderer);
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ M O D E L 1 ---- //
	{
		JF::Material* pMat = new JF::Material();
		Transform* groundtransform = new Transform;
		groundtransform->SetScale(0.5f, 0.5f, 0.5f);
		groundtransform->SetPosition(20.0f, -3.0f, 0.0f);

		Mesh* pGroundMesh = new Mesh();
		JF::MeshLoader::OBJLoad(L"Resources/Models/Rock02.obj", pGroundMesh->GetVertices(), pGroundMesh->GetIndices(), *pMat);

		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);

		MeshRenderer* pMeshRenderer = new MeshRenderer();
		pMeshRenderer->SetMaterial(pMat);
		m_pTestGround->InsertComponent(pMeshRenderer);
		m_pTestGround->InsertComponent(pGroundMesh);

		m_ObjectList.push_back(m_pTestGround);
	}

	// ---- T E S T _ G R O U N D ---- //
	{
		JF::Material* pMat = new JF::Material();
		Transform* groundtransform = new Transform;
		groundtransform->SetScale(50.0f, 1.0f, 50.0f);
		groundtransform->SetPosition(0.0f, -3.0f, 0.0f);

		Mesh* pGroundMesh = new Mesh();
		JF::MeshLoader::OBJLoad(L"Resources/Models/ground.obj", pGroundMesh->GetVertices(), pGroundMesh->GetIndices(), *pMat);

		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);

		MeshRenderer* pMeshRenderer = new MeshRenderer();
		pMeshRenderer->SetMaterial(pMat);
		m_pTestGround->InsertComponent(pMeshRenderer);
		m_pTestGround->InsertComponent(pGroundMesh);

		// 임시 고정 플렌 콜리전
		PxRigidStatic* groundPlane = PxCreatePlane(*m_pApp->GetPXDevice()->GetPhysics(), PxPlane(0, 1, 0, 3), *m_pApp->GetPXDevice()->GetMaterial());
		m_pApp->GetPXDevice()->GetScene()->addActor(*groundPlane);

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

void JF::JFCScene::Update()
{
	// Declear)
	float deltaTime = m_pApp->GetTimer()->DeltaTime();

	// 1) physics Update
	PX_UNUSED(true);
	m_pApp->GetPXDevice()->GetScene()->simulate(deltaTime);
	m_pApp->GetPXDevice()->GetScene()->fetchResults(true);

	// test
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		auto* boxRenderer = m_ObjectList[i]->GetComponent<MeshRenderer>();
		if(boxRenderer == nullptr)
			continue;

		m_ObjectList[i]->GetComponent<Transform>()->Roll(deltaTime);
		m_ObjectList[i]->GetComponent<Transform>()->Pitch(deltaTime);
		m_ObjectList[i]->GetComponent<Transform>()->Yaw(deltaTime);

		break;
	}

	// 2) All GameObject Update
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Update(deltaTime);
	}
}

void JF::JFCScene::Render()
{
	// 1)
	gRENDERER->AutoRander(m_ObjectList);
}

void JF::JFCScene::Release()
{
	// 1) All GameObject Release
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Release();
		SafeDelete(m_ObjectList[i]);
	}
	m_ObjectList.clear();

	// 2)
	m_pApp = nullptr;
}

void JF::JFCScene::Resize(int _width, int _height)
{
	if (Camera::g_pMainCamera != nullptr)
		Camera::g_pMainCamera->CalculationProj(_width, _height);
}
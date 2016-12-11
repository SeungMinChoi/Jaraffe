#include "stdafx.h"
#include "Scene.h"

using namespace JF::Component;

JF::JFCScene::JFCScene(JFCApp* _appInfo) : m_pApp(_appInfo)
{
}

JF::JFCScene::~JFCScene()
{
}

HRESULT JF::JFCScene::Reset()
{
	// Declear)
	int nClientWidth;
	int nClientHeight;

	// 1) Setting
	m_pApp->GetWindow()->GetClientArea(nClientWidth, nClientHeight);
	m_pApp->GetPXDevice()->SceneSetting(PxVec3(0.0f, -9.81f, 0.0f), 0.5f, 0.5f, 0.6f);

	// 2) Setting Main Light
	{
		m_MainLight[0] = GameObject::Create();
		m_MainLight[1] = GameObject::Create();
		m_MainLight[2] = GameObject::Create();

		auto* pdirectionalLightMain = new JFDirectionalLight();
		pdirectionalLightMain->SetAmbient(0.5f, 0.5f, 0.5f, 1.0f);
		pdirectionalLightMain->SetDiffuse(1.0f, 0.9f, 0.9f, 1.0f);
		pdirectionalLightMain->SetSpecular(0.5f, 0.5f, 0.5f, 1.0f);
		pdirectionalLightMain->SetDirection(-0.57735f, -0.57735f, 0.57735f);
		m_MainLight[0]->InsertComponent(pdirectionalLightMain);

		auto* pdirectionalLightSub1 = new JFDirectionalLight();
		pdirectionalLightSub1->SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
		pdirectionalLightSub1->SetDiffuse(0.40f, 0.40f, 0.40f, 1.0f);
		pdirectionalLightSub1->SetSpecular(0.2f, 0.2f, 0.2f, 1.0f);
		pdirectionalLightSub1->SetDirection(0.707f, -0.707f, 0.0f);
		m_MainLight[1]->InsertComponent(pdirectionalLightSub1);

		auto* pdirectionalLightSub2 = new JFDirectionalLight();
		pdirectionalLightSub2->SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
		pdirectionalLightSub2->SetDiffuse(0.4f, 0.4f, 0.4f, 1.0f);
		pdirectionalLightSub2->SetSpecular(0.2f, 0.2f, 0.2f, 1.0f);
		pdirectionalLightSub2->SetDirection(0.0f, 0.0, -1.0f);
		m_MainLight[2]->InsertComponent(pdirectionalLightSub2);
	}

	// 3) Create MainCamera ( SkyBox 도 붙인다. )
	{
		JF::Texture* pTex = new JF::Texture();
		pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/grasscube1024.dds"));
		//pTex->SetTexture(gTEXTUREMGR->CreateTexture( L"Resources/Textures/HomeCubeMap.dds"));

		Camera* newCamera = new Camera(nClientWidth, nClientHeight);
		Camera::SetMainCamera(newCamera);

		Transform* transform = new Transform();
		transform->SetPosition(0.0f, 3.0f, -70.0f);

		GameObject* m_pMainCamera = GameObject::Create();
		m_pMainCamera->InsertComponent(transform);
		m_pMainCamera->InsertComponent(newCamera);
		m_pMainCamera->InsertComponent(new SkyBox(1.0f, pTex));

		m_pMainCamera->Reset();

		m_ObjectList.push_back(m_pMainCamera);
	}

	// 4) Spot Light
	{
		JF::Component::JFSpotLight* pSpotLight = new JF::Component::JFSpotLight();
		pSpotLight->SetDiffuse(1.0f, 0.7f, 0.3f, 1.0f);
		pSpotLight->SetDirection(0.0f, 0.0f, 1.1f);
		pSpotLight->SetRange(50.0f);
		pSpotLight->SetAtt(XMFLOAT3(1.0f, 0.9f, 1.0f));

		auto* plightPos = new Transform();
		plightPos->SetPosition(-10.0f, 10.0f, -10.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(plightPos);
		m_pTestBox->InsertComponent(pSpotLight);

		m_ObjectList.push_back(m_pTestBox);
	}

	// 5) Point Lights ( 100th )
	{
		int offsetX = 0;
		int offsetZ = 0;
		for (int i = 0; i < 100; ++i)
		{
			offsetX = i % 10;
			offsetZ = i / 10;

			auto* plightPos = new Transform();
			plightPos->SetPosition(offsetX * 20.0f - 90.0f, 0.0f, offsetZ * 20.0f - 90.0f);

			auto* pPointLight = new JF::Component::JFPointLight();
			pPointLight->SetDiffuse(JF::Util::MathHelper::RandF() * 2, JF::Util::MathHelper::RandF() * 2, JF::Util::MathHelper::RandF() * 2, 1.0f);
			pPointLight->SetAmbient(plightPos->GetPosition().x, plightPos->GetPosition().y, plightPos->GetPosition().z, 0.0f);
			pPointLight->SetRange(10.0f);

			GameObject* pNewGameObject = GameObject::Create();
			pNewGameObject->InsertComponent(plightPos);
			pNewGameObject->InsertComponent(pPointLight);

			m_ObjectList.push_back(pNewGameObject);
		}
	}

	// ---- T E S T _ S P H E R E 1 ---- //
	{
		Mesh* pSphereMesh = new Mesh();
		{
			JF::GeometryGenerator::CreateSphere(1.0f, 20, 20, pSphereMesh->GetVertices(), pSphereMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/bricks.dds"));

			//
			Mesh::Subset subset;
			subset.VertexCount						= pSphereMesh->GetVertices().size();
			subset.FaceCount						= pSphereMesh->GetIndices().size();
			subset.m_Material.m_MainTexture			= pTex;

			pSphereMesh->GetSubset().push_back(subset);
		}

		Transform* transform = new Transform();
		transform->SetPosition(17.0f, 0.0f, -5.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);
		transform->SetScale(2.0f, 2.0f, 2.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pSphereMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ S P H E R E 2 ---- //
	{
		Mesh* pSphereMesh = new Mesh();
		{
			JF::GeometryGenerator::CreateSphere(1.0f, 20, 20, pSphereMesh->GetVertices(), pSphereMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/water1.dds"));

			//
			Mesh::Subset subset;
			subset.VertexCount	= pSphereMesh->GetVertices().size();
			subset.FaceCount	= pSphereMesh->GetIndices().size();
			subset.m_Material.m_MainTexture = pTex;
			subset.m_Material.m_Material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.1f);
			subset.m_Material.m_BlendState = RenderStates::GetBlendStates()->AlphaBlend();

			pSphereMesh->GetSubset().push_back(subset);
		}

		Transform* transform = new Transform();
		transform->SetPosition(23.0f, 0.0f, -5.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);
		transform->SetScale(2.0f, 2.0f, 2.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pSphereMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 1 ---- //
	{
		Mesh* pBoxMesh = new Mesh();
		{
			//
			float w2 = 1.0f;
			float h2 = 1.0f;
			float d2 = 1.0f;
			JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WoodCrate01.dds"));

			//
			Mesh::Subset subset;
			subset.VertexCount				= pBoxMesh->GetVertices().size();
			subset.FaceCount				= pBoxMesh->GetIndices().size();
			subset.m_Material.m_MainTexture	= pTex;

			pBoxMesh->GetSubset().push_back(subset);
		}

		Transform* transform = new Transform();
		transform->SetPosition(7.0f, 0.0f, 0.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 2---- //
	{
		Mesh* pBoxMesh = new Mesh();
		{
			//
			float w2 = 1.0f;
			float h2 = 1.0f;
			float d2 = 1.0f;
			JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WoodCrate02.dds"));

			//
			Mesh::Subset subset;
			subset.VertexCount				= pBoxMesh->GetVertices().size();
			subset.FaceCount				= pBoxMesh->GetIndices().size();
			subset.m_Material.m_MainTexture	= pTex;

			pBoxMesh->GetSubset().push_back(subset);
		}

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(new Transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pBoxMesh);

		ColisionBox* pColisionBox = new ColisionBox(m_pApp->GetPXDevice());
		pColisionBox->SethalfExtents(XMFLOAT3(0.5f, 0.5f, 0.5f));
		m_pTestBox->InsertComponent(pColisionBox);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 3 ---- //
	{
		Mesh* pBoxMesh = new Mesh();
		{
			//
			float w2 = 1.0f;
			float h2 = 1.0f;
			float d2 = 1.0f;
			JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/gravel_a.dds"));

			JF::Texture* pTexNormal = new JF::Texture();
			pTexNormal->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/TestBumpMap.png"));

			//
			Mesh::Subset subset;
			subset.VertexCount				= pBoxMesh->GetVertices().size();
			subset.FaceCount				= pBoxMesh->GetIndices().size();
			subset.m_Material.m_MainTexture	= pTex;
			subset.m_Material.m_BumpTexture	= pTexNormal;

			pBoxMesh->GetSubset().push_back(subset);
		}

		Transform* transform = new Transform();
		transform->SetPosition(3.0f, 0.0f, 0.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 4---- //
	{
		Mesh* pBoxMesh = new Mesh();
		{
			//
			float w2 = 1.0f;
			float h2 = 1.0f;
			float d2 = 1.0f;
			JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/gravel_a.dds"));

			//
			Mesh::Subset subset;
			subset.VertexCount				= pBoxMesh->GetVertices().size();
			subset.FaceCount				= pBoxMesh->GetIndices().size();
			subset.m_Material.m_MainTexture	= pTex;

			pBoxMesh->GetSubset().push_back(subset);
		}

		Transform* transform = new Transform();
		transform->SetPosition(-8.0f, 10.0f, 10.0f);
		transform->SetRotation(0.0f, 0.0f, 0.0f);
		transform->SetScale(30.0f, 30.0f, 1.0f);

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ B O X 5 ---- //
	{
		Mesh* pBoxMesh = new Mesh();
		{
			//
			float w2 = 1.0f;
			float h2 = 1.0f;
			float d2 = 1.0f;
			JF::GeometryGenerator::CreateBox(w2, h2, d2, pBoxMesh->GetVertices(), pBoxMesh->GetIndices());

			//
			JF::Texture* pTex = new JF::Texture();
			pTex->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/WireFence.dds"));

			//
			Mesh::Subset subset;
			subset.VertexCount	= pBoxMesh->GetVertices().size();
			subset.FaceCount	= pBoxMesh->GetIndices().size();
			subset.m_Material.m_RSState = JF::RenderStates::GetRasterizerStates()->BackFaceCull();
			subset.m_Material.m_MainTexture = pTex;
			subset.m_Material.m_bAlphaClip = true;

			pBoxMesh->GetSubset().push_back(subset);
		}

		GameObject* m_pTestBox = GameObject::Create();
		m_pTestBox->InsertComponent(new Transform);
		m_pTestBox->InsertComponent(new MeshRenderer());
		m_pTestBox->InsertComponent(pBoxMesh);

		m_ObjectList.push_back(m_pTestBox);
	}

	// ---- T E S T _ M O D E L 1 ---- //
	{
		Mesh* pMesh = new Mesh();
		{
			JF::JFMeshLoader loader;
			loader.OBJLoad("Resources/Models/VH-BumbleBee.obj", pMesh->GetVertices(), pMesh->GetIndices(), pMesh->GetSubset());

			auto& subset1 = pMesh->GetSubset()[0];
			{
				subset1.m_Material.m_Material.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
				subset1.m_Material.m_Material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				subset1.m_Material.m_Material.Reflect = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.5f);
				subset1.m_Material.m_Material.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.3f);
			}

			auto& subset2 = pMesh->GetSubset()[1];
			{
				subset2.m_Material.m_Material.Ambient	= XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
				subset2.m_Material.m_Material.Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				subset2.m_Material.m_Material.Reflect	= XMFLOAT4(0.3f, 0.3f, 0.3f, 0.2f);
				subset2.m_Material.m_Material.Specular	= XMFLOAT4(0.2f, 0.2f, 0.2f, 0.3f);
			}
		}

		Transform* groundtransform = new Transform;
		groundtransform->SetScale(0.2f, 0.2f, 0.2f);
		groundtransform->SetPosition(-8.0f, -3.0f, 0.0f);
		groundtransform->SetRotation(0.0f, 8.5f, 0.0f);
		
		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);
		m_pTestGround->InsertComponent(new MeshRenderer());
		m_pTestGround->InsertComponent(pMesh);

		m_ObjectList.push_back(m_pTestGround);
	}

	// ---- T E S T _ M O D E L 2 ---- //
	{
		Mesh* prockMesh = new Mesh();
		{
			JF::JFMeshLoader loader;
			loader.OBJLoad("Resources/Models/RB-BumbleBee.obj", prockMesh->GetVertices(), prockMesh->GetIndices(), prockMesh->GetSubset());

			for (auto& subset : prockMesh->GetSubset())
			{
				subset.m_Material.m_Material.Reflect = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.2f);
			}
		}

		Transform* groundtransform = new Transform;
		groundtransform->SetScale(0.2f, 0.2f, 0.2f);
		groundtransform->SetPosition(-23.0f, -3.0f, 0.0f);
		groundtransform->SetRotation(0.0f, 0.7f, 0.0f);

		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);
		m_pTestGround->InsertComponent(new MeshRenderer());
		m_pTestGround->InsertComponent(prockMesh);

		m_ObjectList.push_back(m_pTestGround);
	}

	// ---- T E S T _ M O D E L 3 ---- //
	{
		Mesh* prockMesh = new Mesh();
		{
			JF::JFMeshLoader loader;
			loader.OBJLoad("Resources/Models/ElementalistModel.obj", prockMesh->GetVertices(), prockMesh->GetIndices(), prockMesh->GetSubset());
		}

		Transform* groundtransform = new Transform;
		groundtransform->SetScale(0.2f, 0.2f, 0.2f);
		groundtransform->SetPosition(-17.0f, -3.0f, -10.0f);
		groundtransform->SetRotation(0.0f, 0.0f, 0.0f);

		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);
		m_pTestGround->InsertComponent(new MeshRenderer());
		m_pTestGround->InsertComponent(prockMesh);

		m_ObjectList.push_back(m_pTestGround);
	}

	// ---- T E S T _ G R O U N D ---- //
	{
		Mesh* pGroundMesh = new Mesh();
		{
			Mesh::Subset subset;
		
			JF::MeshLoader::OBJLoad(L"Resources/Models/ground.obj", pGroundMesh->GetVertices(), pGroundMesh->GetIndices(), subset.m_Material);
		
			subset.FaceCount = pGroundMesh->GetIndices().size();
			subset.VertexCount = pGroundMesh->GetVertices().size();
			pGroundMesh->GetSubset().push_back(subset);
		}
		
		Transform* groundtransform = new Transform;
		groundtransform->SetScale(100.0f, 1.0f, 100.0f);
		groundtransform->SetPosition(0.0f, -3.0f, 0.0f);
		
		GameObject* m_pTestGround = GameObject::Create();
		m_pTestGround->InsertComponent(groundtransform);
		m_pTestGround->InsertComponent(new MeshRenderer());
		m_pTestGround->InsertComponent(pGroundMesh);
		
		// 임시 고정 플렌 콜리전
		PxRigidStatic* groundPlane = PxCreatePlane(*m_pApp->GetPXDevice()->GetPhysics(), PxPlane(0, 1, 0, 3), *m_pApp->GetPXDevice()->GetMaterial());
		m_pApp->GetPXDevice()->GetScene()->addActor(*groundPlane);
		
		m_ObjectList.push_back(m_pTestGround);
	}

	//---- E N D   ----

	// All GameObject Reset
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Reset();
	}

	// Main Lights
	for (size_t i = 0; i < MAIN_LIGHT_COUNT; i++)
	{
		m_MainLight[i]->Reset();
	}

	return S_OK;
}

void JF::JFCScene::Update()
{
	// Declear)
	float deltaTime = m_pApp->GetTimer()->DeltaTime();

	static bool revers = false;
	static float t = 0.0f;
	{
		if (t >= 5.0f)
			revers = true;
		if (t <= 0.0f)
			revers = false;

		if (revers == false)
			t += deltaTime;
		else
			t -= deltaTime;
	}

	// 1) physics Update
	PX_UNUSED(true);
	m_pApp->GetPXDevice()->GetScene()->simulate(deltaTime);
	m_pApp->GetPXDevice()->GetScene()->fetchResults(true);

	// test
	int modelCnt = 0;
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		if (modelCnt == 0 || modelCnt == 1)
		{
			auto* pmesh = m_ObjectList[i]->GetComponent<Mesh>();
			if (pmesh != nullptr)
			{
				if (modelCnt == 1)
				{
					XMStoreFloat4x4(&pmesh->GetTexTransform(), XMMatrixTranslation(t / 3.0f, t / 3.0f, 1.0f) * XMMatrixScaling(0.2f, 0.2f, 0.2f));
				}

				++modelCnt;
			}
		}
		else if (modelCnt == 2)
		{
			auto* boxRenderer = m_ObjectList[i]->GetComponent<MeshRenderer>();
			if (boxRenderer != nullptr)
			{
				m_ObjectList[i]->GetComponent<Transform>()->Roll(deltaTime);
				m_ObjectList[i]->GetComponent<Transform>()->Pitch(deltaTime);
				m_ObjectList[i]->GetComponent<Transform>()->Yaw(deltaTime);

				++modelCnt;
			}
		}

		auto* spotLight = m_ObjectList[i]->GetComponent<JF::Component::JFSpotLight>();
		if (spotLight != nullptr)
		{
			spotLight->SetDirection(XMFLOAT3(cos(t), sin(t), 1.0f));			
		}

		if (t >= 3.5f)
		{
			auto* colisionBox = m_ObjectList[i]->GetComponent<JF::Component::ColisionBox>();
			if (colisionBox != nullptr)
			{
				m_ObjectList[i]->GetComponent<Transform>()->SetPosition(0.0f, 5.0f, 0.0f);
			}
		}
	}

	// 2) All GameObject Update
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Update(deltaTime);
	}

	// 3) Main Lights
	for (int i = 0; i < MAIN_LIGHT_COUNT; ++i)
	{
		m_MainLight[i]->Update(deltaTime);
	}
}

void JF::JFCScene::Render()
{
	// 1)
	gRENDERER->AutoRander(m_ObjectList, m_MainLight, m_pApp->GetTimer());

	// 2) Debug Render
	for (size_t i = 0; i < m_ObjectList.size(); i++)
	{
		m_ObjectList[i]->Render();
	}
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

	// 2) Main Lights
	for (int i = 0; i < MAIN_LIGHT_COUNT; ++i)
	{
		m_MainLight[i]->Release();
		SafeDelete(m_MainLight[i]);
	}

	// 3)
	m_pApp = nullptr;
}

void JF::JFCScene::Resize(int _width, int _height)
{
	if (Camera::g_pMainCamera != nullptr)
		Camera::g_pMainCamera->CalculationProj(_width, _height);
}
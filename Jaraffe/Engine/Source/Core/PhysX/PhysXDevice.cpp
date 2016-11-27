#include "stdafx.h"
#include "PhysXDevice.h"


JF::JFCPhysXDevice::JFCPhysXDevice()
{
}

JF::JFCPhysXDevice::~JFCPhysXDevice()
{
}

void JF::JFCPhysXDevice::DeviceInit()
{
	// 1) 
	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);

	// 2) 프로파일러 생성
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(m_Foundation);
	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true, profileZoneManager);

	// 3) 그래픽 디버거 연결.
	if (m_Physics->getPvdConnectionManager())
	{
		m_Physics->getVisualDebugger()->setVisualizeConstraints(true);
		m_Physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		m_Physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);
		m_Connection = PxVisualDebuggerExt::createConnection(m_Physics->getPvdConnectionManager(), "127.0.0.1", 5425, 10);
	}

	// 4)
	m_Dispatcher = PxDefaultCpuDispatcherCreate(2);
}

void JF::JFCPhysXDevice::DeviceDestory()
{
	//
	PX_UNUSED(false);

	//
	ReleasePX(m_pScene);
	ReleasePX(m_Dispatcher);

	//
	ReleasePX(m_Connection);
	ReleasePX(m_Physics);
	ReleasePX(m_Foundation);
}

void JF::JFCPhysXDevice::SceneSetting(PxVec3 _gravity, PxReal _staticFriction, PxReal _dynamicFriction, PxReal _restitution)
{
	// 1) Scene 생성
	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity		= _gravity;
	sceneDesc.cpuDispatcher = m_Dispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
	
	m_pScene = m_Physics->createScene(sceneDesc);

	// 2) 마찰력 정보 생성
	m_Material = m_Physics->createMaterial(_staticFriction, _dynamicFriction, _restitution);
}
#include "stdafx.h"
#include "PhysXDevice.h"


PhysXDevice::PhysXDevice()
{
}


PhysXDevice::~PhysXDevice()
{
}

void PhysXDevice::DeviceInit()
{
	// 1) 
	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);

	// 2) �������Ϸ� ����
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(m_Foundation);
	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true, profileZoneManager);

	// 3) �׷��� ����� ����.
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

void PhysXDevice::CleanupDevice()
{
	PX_UNUSED(false);
	m_Scene->release();
	m_Dispatcher->release();
	PxProfileZoneManager* profileZoneManager = m_Physics->getProfileZoneManager();
	if (m_Connection != NULL)
		m_Connection->release();
	m_Physics->release();
	profileZoneManager->release();
	m_Foundation->release();
}

void PhysXDevice::SceneSetting(PxVec3 _gravity, PxReal _staticFriction, PxReal _dynamicFriction, PxReal _restitution)
{
	// 1) Scene ����
	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity		= _gravity;
	sceneDesc.cpuDispatcher = m_Dispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
	m_Scene = m_Physics->createScene(sceneDesc);

	// 2) ������ ���� ����
	m_Material = m_Physics->createMaterial(_staticFriction, _dynamicFriction, _restitution);
}
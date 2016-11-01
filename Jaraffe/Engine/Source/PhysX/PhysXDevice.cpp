#include "stdafx.h"
#include "PhysXDevice.h"


PhysXDevice::PhysXDevice()
{
}


PhysXDevice::~PhysXDevice()
{
}

void PhysXDevice::Init()
{
	// 1)
	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);

	// 2)
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(m_Foundation);
	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true, profileZoneManager);

	// 3)
	if (m_Physics->getPvdConnectionManager())
	{
		m_Physics->getVisualDebugger()->setVisualizeConstraints(true);
		m_Physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		m_Physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);
		m_Connection = PxVisualDebuggerExt::createConnection(m_Physics->getPvdConnectionManager(), "127.0.0.1", 5425, 10);
	}

	// 4)
	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	m_Dispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_Dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	m_Scene =m_Physics->createScene(sceneDesc);

	// 5)
	m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.6f);

	// 6) 
	PxRigidStatic* groundPlane = PxCreatePlane(*m_Physics, PxPlane(0, 1, 0, 0), *m_Material);
	m_Scene->addActor(*groundPlane);

}
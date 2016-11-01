#pragma once

using namespace physx;

class PhysXDevice
{
public:
	PhysXDevice();
	virtual ~PhysXDevice();

public:
	void Init();

private:
	PxDefaultAllocator			m_Allocator;
	PxDefaultErrorCallback		m_ErrorCallback;

	PxFoundation*				m_Foundation	= NULL;
	PxPhysics*					m_Physics		= NULL;
								
	PxDefaultCpuDispatcher*		m_Dispatcher	= NULL;
	PxScene*					m_Scene			= NULL;
								
	PxMaterial*					m_Material		= NULL;
								
	PxVisualDebuggerConnection* m_Connection	= NULL;

};
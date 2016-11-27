#pragma once

using namespace physx;

namespace JF
{
	class JFCPhysXDevice
	{
	public:
		JFCPhysXDevice();
		virtual ~JFCPhysXDevice();

	public:
		void DeviceInit();
		void DeviceDestory();

		void SceneSetting(PxVec3 _gravity, PxReal _staticFriction, PxReal _dynamicFriction, PxReal _restitution);

		PxPhysics*	GetPhysics() { return m_Physics; }
		PxScene*	GetScene() { return m_pScene; }
		PxMaterial* GetMaterial() { return m_Material; }

	private:
		PxDefaultAllocator			m_Allocator;
		PxDefaultErrorCallback		m_ErrorCallback;

		PxFoundation*				m_Foundation	= NULL;
		PxPhysics*					m_Physics		= NULL;

		PxDefaultCpuDispatcher*		m_Dispatcher	= NULL;
		PxScene*					m_pScene		= NULL;

		PxMaterial*					m_Material		= NULL;

		PxVisualDebuggerConnection* m_Connection	= NULL;
	};
}
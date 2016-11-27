#pragma once

namespace JF
{
	class JFCApp
	{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
	public:
		JFCApp()			{}
		virtual ~JFCApp()	{}

	//=============================================================================
	// Virtual Methods)
	//=============================================================================
	public:
		virtual void Initialize()	= 0;
		virtual void Update()		= 0;
		virtual void Render()		= 0;
		virtual void BeforeReset()	= 0;
		virtual void AfterReset()	= 0;

	//=============================================================================
	// public Methods)
	//=============================================================================
	public:
		JFCPlatformWindow*	GetWindow()		const { return m_pWindow; }
		//JFCDeviceDirectX11*	GetDevice()		const { return m_pDevice; }
		JFCPhysXDevice*		GetPXDevice()	const { return m_pPXDevice; }
		JFCGameTimer*		GetTimer()		const { return m_pTimer; }

	//=============================================================================
	// protected Members)
	//=============================================================================
	protected:
		JFCPlatformWindow*	m_pWindow;		// 멀티플렛폼 들어갈때 인터페이스 만들어야함.
		//JFCDeviceDirectX11*	m_pDevice;		// 멀티플렛폼 들어갈때 인터페이스 만들어야함. ( 임시로 없앰. )
		JFCPhysXDevice*		m_pPXDevice;

		JFCScene*			m_pScene;
		JFCGameTimer*		m_pTimer;
	};
}
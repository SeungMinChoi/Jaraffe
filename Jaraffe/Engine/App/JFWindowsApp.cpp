#include "stdafx.h"
#include "JFWindowsApp.h"

using std::tr1::bind;
using std::tr1::mem_fn;
using namespace std::tr1::placeholders;

JF::JFCWindowsApp::JFCWindowsApp()
{
	m_pWindow	= new JFCPlatformWindow();
	//m_pDevice	= new JFCDeviceDirectX11();
	m_pPXDevice	= new JFCPhysXDevice();

	m_pScene	= new JFCScene(this);
	m_pTimer	= new JFCGameTimer();
}

JF::JFCWindowsApp::~JFCWindowsApp()
{
	Exit();
}

void JF::JFCWindowsApp::Run()
{
	try
	{
		// 1)
		Initialize();

		// 2)
		m_pWindow->ShowWindow();

		// 3)
		gRENDERER->DeviceInit(m_pWindow->GetHwnd());

		// 4)
		m_pPXDevice->DeviceInit();

		// 5)
		gTEXTUREMGR->Reset();

		// 6)
		JF::Effects::InitAll(gRENDERER->Device());
		JF::RenderStates::InitAll(gRENDERER->Device());
		JF::InputLayouts::InitAll(gRENDERER->Device());

		// 7) Scene Setting)
		m_pScene->Reset();

		// 8)
		gRENDERER->AfterReset();

		// 9) Window 메세지를 등록한다.
		m_pWindow->SetUserMessageFunction(WM_SIZE,			bind(mem_fn(&JFCWindowsApp::WindowResized), this, _1, _2, _3, _4));

		m_pWindow->SetUserMessageFunction(WM_MOUSEMOVE,		bind(mem_fn(&JFCWindowsApp::MouseMove), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_LBUTTONDOWN,	bind(mem_fn(&JFCWindowsApp::MouseDown), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_MBUTTONDOWN,	bind(mem_fn(&JFCWindowsApp::MouseDown), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_RBUTTONDOWN,	bind(mem_fn(&JFCWindowsApp::MouseDown), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_KEYDOWN,		bind(mem_fn(&JFCWindowsApp::KeyDown), this, _1, _2, _3, _4));

		m_pWindow->SetUserMessageFunction(WM_LBUTTONUP,		bind(mem_fn(&JFCWindowsApp::MouseUp), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_MBUTTONUP,		bind(mem_fn(&JFCWindowsApp::MouseUp), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_RBUTTONUP,		bind(mem_fn(&JFCWindowsApp::MouseUp), this, _1, _2, _3, _4));
		m_pWindow->SetUserMessageFunction(WM_KEYUP,			bind(mem_fn(&JFCWindowsApp::KeyUp), this, _1, _2, _3, _4));

		// 9) Loop
		m_pTimer->Reset();
		while (m_pWindow->IsAlive())
		{
			if (!m_pWindow->IsMinimized())
			{
				m_pTimer->Tick();

				CalculateFrameStats();

				Update();

				Render();
				gRENDERER->Present();
			}

			m_pWindow->MessageLoop();
		}
	}
	catch (JF::JFCException ex)
	{
		ex.ShowErrorMessage();
	}
}

void JF::JFCWindowsApp::Exit()
{
	// 1)
	m_pScene->Release();

	// 2)
	JF::Effects::DestroyAll();
	JF::RenderStates::DestroyAll();
	JF::InputLayouts::DestroyAll();
	
	// 3)
	gTEXTUREMGR->Release();

	// 4)
	m_pPXDevice->DeviceDestory();

	// 5)
	gRENDERER->DeviceDestory();

	// 6)
	m_pWindow->DestroyWindows();

	// Pointer Destory
	SafeDelete(m_pWindow);
	//SafeDelete(m_pDevice);
	SafeDelete(m_pPXDevice);
	SafeDelete(m_pScene);
	SafeDelete(m_pTimer);
}

void JF::JFCWindowsApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((m_pTimer->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << ENGINE_NAME << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(m_pWindow->GetHwnd(), outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void JF::JFCWindowsApp::Update()
{
	m_pScene->Update();
}

void JF::JFCWindowsApp::Render()
{
	m_pScene->Render();
}

LRESULT JF::JFCWindowsApp::WindowResized(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	if (!gRENDERER->FullScreen() && _wParam != SIZE_MINIMIZED)
	{
		int width, height;
		m_pWindow->GetClientArea(width, height);

		if (width != gRENDERER->BackBufferWidth() || height != gRENDERER->BackBufferHeight())
		{
			BeforeReset();

			m_pScene->Resize(width, height);

			gRENDERER->SetBackBufferWidth(width);
			gRENDERER->SetBackBufferHeight(height);
			gRENDERER->Reset();
			gRENDERER->AfterReset();

			AfterReset();
		}
	}

	return 0;
}

LRESULT JF::JFCWindowsApp::MouseMove(HWND /*_hWnd*/, UINT /*_msg*/, WPARAM /*_wParam*/, LPARAM _lParam)
{
	gINPUT->OnMouseMove(_lParam);

	return 0;
}

LRESULT JF::JFCWindowsApp::MouseDown(HWND /*_hWnd*/, UINT /*_msg*/, WPARAM /*_wParam*/, LPARAM /*_lParam*/)
{
	gINPUT->OnKeyDown(VK_LBUTTON);
	gINPUT->OnKeyDown(VK_MBUTTON);
	gINPUT->OnKeyDown(VK_RBUTTON);

	return 0;
}

LRESULT JF::JFCWindowsApp::MouseUp(HWND /*_hWnd*/, UINT /*_msg*/, WPARAM /*_wParam*/, LPARAM /*_lParam*/)
{
	gINPUT->OnKeyUp(VK_LBUTTON);
	gINPUT->OnKeyUp(VK_MBUTTON);
	gINPUT->OnKeyUp(VK_RBUTTON);

	return 0;
}

LRESULT JF::JFCWindowsApp::KeyDown(HWND /*_hWnd*/, UINT /*_msg*/, WPARAM _wParam, LPARAM /*_lParam*/)
{
	gINPUT->OnKeyDown(_wParam);

	return 0;
}

LRESULT JF::JFCWindowsApp::KeyUp(HWND /*_hWnd*/, UINT /*_msg*/, WPARAM _wParam, LPARAM /*_lParam*/)
{
	gINPUT->OnKeyUp(_wParam);

	return 0;
}
#include "stdafx.h"
#include "..\Source\Scene\Scene.h"

// Forward declaration
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// Application Class
class App
{
public:
	App()
	: m_MainWndCaption(L"Jaraffe")
	, m_ClientWidth(800)
	, m_ClientHeight(600)
	, m_hwnd(0)
	, m_finished(false)
	, m_AppPaused(false)
	, m_pTestScene(nullptr)
	{
	};

	virtual ~App() 
	{
	};

// Basic 
public:
	HRESULT Init()
	{
		// 1) Alloca TODO : 메모리풀 만들면 new 쓰는거 다 바꺼야함.. ( 그냥 인터페이스 만들어놀껄.. )
		m_pTestScene = new Jaraffe::CScene();

		// 2) Create Window
		createWindow();

		// 3) Renderer Init
		gRENDERER->Init(m_hwnd);

		// 4) TextureMGR Init
		gTEXTUREMGR->Init();

		// 4)
		Jaraffe::Effects::InitAll(gRENDERER->GetDevice());
		Jaraffe::RenderStates::InitAll(gRENDERER->GetDevice());
		Jaraffe::InputLayouts::InitAll(gRENDERER->GetDevice());

		// 5) Test Scene Init
		m_pTestScene->Init();

		return S_OK;
	}

	int Run()
	{
		m_finished = false;
		while (m_finished == false)
		{
			MSG msg = { 0 };

			m_Timer.Reset();

			while (msg.message != WM_QUIT)
			{
				// If there are Window messages then process them.
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				// Otherwise, do animation/game stuff.
				else
				{
					m_Timer.Tick();

					if (!m_AppPaused)
					{
						CalculateFrameStats();
						m_pTestScene->Update(m_Timer.DeltaTime());
						m_pTestScene->Render();
					}
					else
					{
						Sleep(100);
					}
				}
			}

			return (int)msg.wParam;
		}

		return 0;
	}

	void Shutdown()
	{
		//
		m_pTestScene->Release();
		SafeDelete(m_pTestScene);

		//
		Jaraffe::Effects::DestroyAll();
		Jaraffe::RenderStates::DestroyAll();
		Jaraffe::InputLayouts::DestroyAll();

		//
		gRENDERER->CleanupDevice();
	}

// Call Back
public:
	LRESULT OnMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_CLOSE:			PostQuitMessage(0);		break;
		case WM_MOVE:
		case WM_SIZE:			OnResize();				break;
		case WM_QUIT:			m_finished = true;		break;
		case WM_INPUT:			handleRawInput(lparam); break;
		case WM_EXITSIZEMOVE:	m_Timer.Start();		break;
		case WM_ENTERSIZEMOVE:	m_Timer.Stop();			break;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	void OnResize()
	{
		RECT rect;
		RECT screen_rect;
		GetClientRect(m_hwnd, &rect);
		GetWindowRect(m_hwnd, &screen_rect);
		int w = rect.right - rect.left;
		int h = rect.bottom - rect.top;
		if (w > 0)
		{
			ClipCursor(&screen_rect);

			gRENDERER->OnResize();
		}
	}

	void handleRawInput(LPARAM lParam)
	{
	}

// 
private:
	void createWindow()
	{
		WNDCLASS wc;
		wc.style			= CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc		= MainWndProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= GetModuleHandle(NULL);
		wc.hIcon			= LoadIcon(0, IDI_APPLICATION);
		wc.hCursor			= LoadCursor(0, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= L"Jaraffe";

		if (!RegisterClass(&wc))
		{
			MessageBox(0, L"RegisterClass Failed.", 0, 0);
			return;
		}
		
		m_hwnd = CreateWindow(L"Jaraffe", L"Jaraffe", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 600, NULL, NULL, wc.hInstance, 0);

		RAWINPUTDEVICE Rid;
		Rid.usUsagePage = 0x01;
		Rid.usUsage		= 0x02;
		Rid.dwFlags		= 0;
		Rid.hwndTarget	= 0;
		RegisterRawInputDevices(&Rid, 1, sizeof(Rid));

		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);

		SetForegroundWindow(m_hwnd);
	}

	void CalculateFrameStats()
	{
		// Code computes the average frames per second, and also the 
		// average time it takes to render one frame.  These stats 
		// are appended to the window caption bar.

		static int frameCnt = 0;
		static float timeElapsed = 0.0f;

		frameCnt++;

		// Compute averages over one second period.
		if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = (float)frameCnt; // fps = frameCnt / 1
			float mspf = 1000.0f / fps;

			std::wostringstream outs;
			outs.precision(6);
			outs << m_MainWndCaption << L"    "
				<< L"FPS: " << fps << L"    "
				<< L"Frame Time: " << mspf << L" (ms)";
			SetWindowText(m_hwnd, outs.str().c_str());

			// Reset for next average.
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}


private:
	Jaraffe::CScene*			m_pTestScene = nullptr;

private:
	Jaraffe::Util::CGameTimer	m_Timer;

private:
	HWND m_hwnd;

	bool m_finished;
	bool m_AppPaused;

private:
	std::wstring	m_MainWndCaption;
	int				m_ClientWidth;
	int				m_ClientHeight;
};

static App* g_App = nullptr;

// Msg 
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (g_App != nullptr)
	{
		return g_App->OnMessage(hwnd, msg, wparam, lparam);
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

// Main
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
// Debug Mode Memory Leak Check
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// 
	g_App = new App();
	g_App->Init();
	g_App->Run();
	g_App->Shutdown();

	// Delete
	delete g_App;
	g_App = nullptr;

	// 
	return 0;
}
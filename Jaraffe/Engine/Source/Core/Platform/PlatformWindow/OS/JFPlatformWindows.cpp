#include "stdafx.h"
#include "JFPlatformWindows.h"


JF::JFCPlatformWindow::JFCPlatformWindow() 
{
	// 1) Value Setting)
	m_Style		= WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
	m_ExStyle	= WS_EX_APPWINDOW;

	// 2) Windows Handle 을 얻어온다.
	if (m_Hinstance == NULL)
		m_Hinstance = GetModuleHandle(NULL);

	// 3)
	CreateWindows();
	
	// 4) 윈도우 크기를 셋팅한다.
	SetClientArea(START_CLIENT_WIDTH, START_CLIENT_HEIGHT);
}

JF::JFCPlatformWindow::~JFCPlatformWindow()
{
	DestroyWindows();
}

void JF::JFCPlatformWindow::DestroyWindows()
{
	//
	m_mapUserMessages.clear();

	//
	::DestroyWindow(m_Hwnd);
	::UnregisterClass(ENGINE_NAME, m_Hinstance);
}

HWND JF::JFCPlatformWindow::GetHwnd() const
{
	return m_Hwnd;
}

HINSTANCE JF::JFCPlatformWindow::GetHinstance() const
{
	return m_Hinstance;
}

void JF::JFCPlatformWindow::MessageLoop()
{
	// Main message loop:
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

BOOL JF::JFCPlatformWindow::IsAlive() const
{
	return ::IsWindow(m_Hwnd);
}

BOOL JF::JFCPlatformWindow::IsMinimized() const
{
	return ::IsIconic(m_Hwnd);
}

LONG_PTR JF::JFCPlatformWindow::WindowStyle() const
{
	return GetWindowLongPtr(m_Hwnd, GWL_STYLE);
}

LONG_PTR JF::JFCPlatformWindow::ExtendedStyle() const
{
	return GetWindowLongPtr(m_Hwnd, GWL_EXSTYLE);
}

void JF::JFCPlatformWindow::SetWindowStyle(DWORD _newStyle)
{
	if (!::SetWindowLongPtr(m_Hwnd, GWL_STYLE, _newStyle))
		throw JFCWindowsException(::GetLastError());

	m_Style = _newStyle;
}

void JF::JFCPlatformWindow::SetExtendedStyle(DWORD _newExStyle)
{
	if (!::SetWindowLongPtr(m_Hwnd, GWL_EXSTYLE, _newExStyle))
		throw JFCWindowsException(::GetLastError());

	m_Style = _newExStyle;
}

void JF::JFCPlatformWindow::Maximize()
{
	::ShowWindow(m_Hwnd, SW_MAXIMIZE);
}

void JF::JFCPlatformWindow::SetWindowTitle(LPCWSTR _title)
{
	if (!::SetWindowText(m_Hwnd, _title))
		throw JFCWindowsException(::GetLastError());
}

void JF::JFCPlatformWindow::ShowWindow(bool _show /*= true*/)
{
	INT cmdShow = _show ? SW_SHOW : SW_HIDE;

	::ShowWindow(m_Hwnd, cmdShow);
}

void JF::JFCPlatformWindow::SetWindowPos(INT _posX, INT _posY)
{
	if (!::SetWindowPos(m_Hwnd, HWND_NOTOPMOST, _posX, _posY, 0, 0, SWP_NOSIZE))
		throw JFCWindowsException(::GetLastError());
}

void JF::JFCPlatformWindow::GetWindowPos(INT& _posX, INT& _posY) const
{
	RECT windowRect;
	if (!::GetWindowRect(m_Hwnd, &windowRect))
		throw JFCWindowsException(::GetLastError());

	_posX = windowRect.left;
	_posY = windowRect.top;
}

void JF::JFCPlatformWindow::SetClientArea(INT _clientX, INT _clientY)
{
	RECT windowRect;
	::SetRect(&windowRect, 0, 0, _clientX, _clientY);

	BOOL bIsMenu = (::GetMenu(m_Hwnd) != NULL);
	if (!::AdjustWindowRectEx(&windowRect, m_Style, bIsMenu, m_ExStyle))
		throw JFCWindowsException(::GetLastError());

	if (!::SetWindowPos(m_Hwnd, HWND_NOTOPMOST, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOMOVE))
		throw JFCWindowsException(::GetLastError());
}

void JF::JFCPlatformWindow::GetClientArea(INT& _clientX, INT& _clientY) const
{
	RECT clientRect;
	if (!::GetClientRect(m_Hwnd, &clientRect))
		throw JFCWindowsException(::GetLastError());

	_clientX = clientRect.right;
	_clientY = clientRect.bottom;
}

void JF::JFCPlatformWindow::SetUserMessageFunction(UINT _message, MsgFunction _msgFunction)
{
	m_mapUserMessages[_message] = _msgFunction;
}

void JF::JFCPlatformWindow::CreateWindows()
{
	HICON hIcon		= ::LoadIcon(NULL, IDI_APPLICATION);
	HCURSOR hCursor = ::LoadCursorW(NULL, IDC_ARROW);

	// Register the window class
	WNDCLASSEX wc = 
	{
		sizeof(WNDCLASSEX),
		CS_DBLCLKS,
		WndProc,
		0,
		0,
		m_Hinstance,
		hIcon,
		hCursor,
		nullptr,
		nullptr,
		ENGINE_NAME,
		nullptr
	};

	if (!::RegisterClassEx(&wc))
		throw JFCWindowsException(::GetLastError());

	// Create the application's window
	m_Hwnd = ::CreateWindowEx
	(
		m_ExStyle,
		ENGINE_NAME,
		ENGINE_NAME,
		m_Style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		m_Hinstance,
		(void*)this
	);

	if (!m_Hwnd)
		throw JFCWindowsException(::GetLastError());
}

LRESULT JF::JFCPlatformWindow::MessageHandler(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	if (m_mapUserMessages.find(_uMsg) != m_mapUserMessages.end())
	{
		MsgFunction msgFunction = m_mapUserMessages[_uMsg];
		return msgFunction(_hWnd, _uMsg, _wParam, _lParam);
	}
	else
	{
		switch (_uMsg)
		{
			// Window is being destroyed
			case WM_DESTROY:
				::PostQuitMessage(0);
				return 0;

			// Window is being closed
			case WM_CLOSE:
				DestroyWindow(_hWnd);
				return 0;
		}
	}

	return ::DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}

LRESULT WINAPI JF::JFCPlatformWindow::WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
		case WM_NCCREATE:
		{
			LPCREATESTRUCT pCreateStruct	= reinterpret_cast<LPCREATESTRUCT>(_lParam);
			JFCPlatformWindow* pObj			= reinterpret_cast<JFCPlatformWindow*>(pCreateStruct->lpCreateParams);

			::SetWindowLongPtr(_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
			return ::DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
		}
	}

	JFCPlatformWindow* pObj = reinterpret_cast<JFCPlatformWindow*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	if (pObj)
		return pObj->MessageHandler(_hWnd, _uMsg, _wParam, _lParam);
		
	return ::DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}
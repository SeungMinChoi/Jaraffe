#pragma once

namespace JF
{
	class JFCPlatformWindow
	{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
	public:
		JFCPlatformWindow();
		virtual ~JFCPlatformWindow();

	//=============================================================================
	// Public Types)
	//=============================================================================
	public:
		typedef std::tr1::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> MsgFunction;
		typedef std::tr1::function<INT_PTR(HWND, UINT, WPARAM, LPARAM)> DlgFunction;

	//=============================================================================
	// Public Methods)
	//=============================================================================
	public:
		void		CreateWindows();
		void		DestroyWindows();

		HWND		GetHwnd() const;
		HINSTANCE	GetHinstance() const;

		void		MessageLoop();

		BOOL		IsAlive() const;
		BOOL		IsMinimized() const;
		LONG_PTR	WindowStyle() const;
		LONG_PTR	ExtendedStyle() const;
		void		SetWindowStyle(DWORD _newStyle);
		void		SetExtendedStyle(DWORD _newExStyle);
		void		Maximize();
		void		SetWindowTitle(LPCWSTR _title);
		void		ShowWindow(bool _show = true);
		void		SetWindowPos(INT _posX, INT _posY);
		void		GetWindowPos(INT& _posX, INT& _posY) const;
		void		SetClientArea(INT _clientX, INT _clientY);
		void		GetClientArea(INT& _clientX, INT& _clientY) const;

		void		SetUserMessageFunction(UINT _message, MsgFunction _msgFunction);

	//=============================================================================
	// Private Methods)
	//=============================================================================
	private:
		LRESULT					MessageHandler(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
		static LRESULT WINAPI	WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

	//=============================================================================
	// Private Members)
	//=============================================================================
	private: 
		// Windosw properties
		HWND			m_Hwnd		= nullptr;			// The window handle
		HINSTANCE		m_Hinstance	= nullptr;			// The HINSTANCE of the application
		std::wstring	m_AppName;						// The name of the application
		DWORD			m_Style;						// The current window style
		DWORD			m_ExStyle;						// The extended window style

		//
		std::map<UINT, MsgFunction>	m_mapUserMessages;	// User message map
	};
}
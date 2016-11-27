#pragma once

namespace JF
{
	class JFCWindowsApp : JFCApp
	{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
	public:
		JFCWindowsApp();
		virtual ~JFCWindowsApp();

	//=============================================================================
	// Public Methods)
	//=============================================================================
	public:
		void Run();

	//=============================================================================
	// Override Methods)
	//=============================================================================
	protected:
		virtual void Initialize()								override {}
		virtual void Update()									override;
		virtual void Render()									override;
		virtual void BeforeReset()								override {}
		virtual void AfterReset()								override {}

	//=============================================================================
	// protected Methods)
	//=============================================================================
	protected:
		LRESULT WindowResized(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

		LRESULT MouseMove(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
		LRESULT MouseDown(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
		LRESULT MouseUp(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

		LRESULT KeyDown(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
		LRESULT KeyUp(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	//=============================================================================
	// private Methods)
	//=============================================================================
	private:
		void Exit();
		void CalculateFrameStats();
	};
}
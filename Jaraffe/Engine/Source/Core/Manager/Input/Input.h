#pragma once

#define gINPUT JF::JFCInput::GetInstance()

namespace JF
{

class JFCInput
{
	SINGLETONE(JFCInput)

protected:
	bool m_bKeyCodeArray[256];
	bool m_bKeyCodeArrayUp[256];

	XMFLOAT3 m_vMousePos;
	XMFLOAT3 m_vClickPos;

public:
	void OnKeyDown(WPARAM wParam);
	void OnKeyUp(WPARAM wParam);
	void OnMouseMove(LPARAM lParam);
	void OnMouseClick(LPARAM lParam);

	bool GetKey(WPARAM wParam);
	bool GetKeyDown(WPARAM wParam);
	bool GetKeyUP(WPARAM wParam);
	bool GetMouseButton(WPARAM wParam);
	bool GetMouseButtonDown(WPARAM wParam);
	bool GetMouseButtonUp(WPARAM wParam);

	XMFLOAT3 GetMousePosition() const;
};

}
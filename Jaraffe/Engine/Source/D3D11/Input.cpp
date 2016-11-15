#include "stdafx.h"
#include "Input.h"

Jaraffe::Input::Input()
{
	memset(m_bKeyCodeArray, 0, sizeof(m_bKeyCodeArray));
	memset(m_bKeyCodeArrayUp, 0, sizeof(m_bKeyCodeArrayUp));
	m_vMousePos = { 0, 0, 0 };
	m_vClickPos = { 0, 0, 0 };
}

Jaraffe::Input::~Input()
{
}

void Jaraffe::Input::OnKeyDown(WPARAM wParam)
{
	m_bKeyCodeArray[wParam] = true;
	m_bKeyCodeArrayUp[wParam] = false;
}

void Jaraffe::Input::OnKeyUp(WPARAM wParam)
{
	m_bKeyCodeArray[wParam] = false;
	m_bKeyCodeArrayUp[wParam] = true;
}

void Jaraffe::Input::OnMouseMove(LPARAM lParam)
{
	m_vMousePos.x = LOWORD(lParam);
	m_vMousePos.y = HIWORD(lParam);
}

void Jaraffe::Input::OnMouseClick(LPARAM lParam)
{
	m_vClickPos.x = LOWORD(lParam);
	m_vClickPos.y = HIWORD(lParam);
}

bool Jaraffe::Input::GetKey(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool Jaraffe::Input::GetKeyDown(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool Jaraffe::Input::GetKeyUP(WPARAM wParam)
{
	bool ret = m_bKeyCodeArrayUp[wParam];
	m_bKeyCodeArrayUp[wParam] = false;
	return ret;
}

bool Jaraffe::Input::GetMouseButton(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool Jaraffe::Input::GetMouseButtonDown(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool Jaraffe::Input::GetMouseButtonUp(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

XMFLOAT3 Jaraffe::Input::GetMousePosition()
{
	return m_vMousePos;
}

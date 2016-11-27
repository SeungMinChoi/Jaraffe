#include "stdafx.h"
#include "Input.h"

JF::JFCInput::JFCInput()
{
	memset(m_bKeyCodeArray, 0, sizeof(m_bKeyCodeArray));
	memset(m_bKeyCodeArrayUp, 0, sizeof(m_bKeyCodeArrayUp));
	m_vMousePos = { 0, 0, 0 };
	m_vClickPos = { 0, 0, 0 };
}

JF::JFCInput::~JFCInput()
{
}

void JF::JFCInput::OnKeyDown(WPARAM wParam)
{
	m_bKeyCodeArray[wParam] = true;
	m_bKeyCodeArrayUp[wParam] = false;
}

void JF::JFCInput::OnKeyUp(WPARAM wParam)
{
	m_bKeyCodeArray[wParam] = false;
	m_bKeyCodeArrayUp[wParam] = true;
}

void JF::JFCInput::OnMouseMove(LPARAM lParam)
{
	m_vMousePos.x = LOWORD(lParam);
	m_vMousePos.y = HIWORD(lParam);
}

void JF::JFCInput::OnMouseClick(LPARAM lParam)
{
	m_vClickPos.x = LOWORD(lParam);
	m_vClickPos.y = HIWORD(lParam);
}

bool JF::JFCInput::GetKey(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool JF::JFCInput::GetKeyDown(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool JF::JFCInput::GetKeyUP(WPARAM wParam)
{
	bool ret = m_bKeyCodeArrayUp[wParam];
	m_bKeyCodeArrayUp[wParam] = false;
	return ret;
}

bool JF::JFCInput::GetMouseButton(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool JF::JFCInput::GetMouseButtonDown(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

bool JF::JFCInput::GetMouseButtonUp(WPARAM wParam)
{
	return m_bKeyCodeArray[wParam];
}

XMFLOAT3 JF::JFCInput::GetMousePosition() const
{
	return m_vMousePos;
}
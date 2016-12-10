#pragma once

namespace JF
{

class JFCScene
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
public:
	JFCScene(JFCApp* _appInfo);
	virtual ~JFCScene();

//=============================================================================
// public Method)
//=============================================================================
public:
	virtual HRESULT Reset();
	virtual void	Update();
	virtual void	Render();
	virtual void	Release();

	virtual void	Resize(int _width, int _height);

//=============================================================================
// protected Member)
//=============================================================================
protected:
	JFCApp*							m_pApp;
	std::vector<JF::GameObject*>	m_ObjectList;

	JF::GameObject*					m_MainLight[MAIN_LIGHT_COUNT];	// 주 라이트 ( 첫번째 라이트만 그림자 표시. )
};

}
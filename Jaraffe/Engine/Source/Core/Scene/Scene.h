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
	virtual HRESULT Init();
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
};

}
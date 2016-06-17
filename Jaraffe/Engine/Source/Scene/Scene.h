#pragma once

namespace Jaraffe
{

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Init();
	virtual void	Update(float t);
	virtual void	Render();
	virtual void	Release();

	std::vector<Jaraffe::GameObject*>	m_ObjectList;
};

}
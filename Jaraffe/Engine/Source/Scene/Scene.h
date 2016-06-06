#pragma once

namespace Jaraffe
{

class CScene : public IObject
{
public:
	CScene();
	virtual ~CScene();

public:
	// Inherited via IObject
	virtual HRESULT Init()				override;
	virtual void	Update(float t)		override;
	virtual void	Render()			override;
	virtual void	Release()			override;

	std::vector<Jaraffe::GameObject*>	m_ObjectList;
};

}
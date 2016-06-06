#pragma once

namespace Jaraffe
{

class IObject
{
public:
	IObject() {};
	virtual ~IObject() {};

public:
	virtual HRESULT Init()			= 0;
	virtual void	Update(float t) = 0;
	virtual void	Render()		= 0;
	virtual void	Release()		= 0;
};

}
#include "stdafx.h"
#include "GameObject.h"

JF::GameObject::GameObject()
{
}

JF::GameObject::~GameObject()
{
}

JF::GameObject* JF::GameObject::Create()
{
	return new JF::GameObject();
}

void JF::GameObject::Reset()
{
	for each (auto component in m_mapComponents)
	{
		component.second->Reset();
	}
}

void JF::GameObject::Update(float t)
{
	for each (auto component in m_mapComponents)
	{
		component.second->Update(t);
	}
}

void JF::GameObject::Render()
{
	auto pCubeMap = GetComponent<JF::Component::SkyBox>();
	if (pCubeMap != nullptr)
	{
		pCubeMap->Render();
	}

	auto pColision = GetComponent<JF::Component::Colision>();
	if (pColision != nullptr)
	{
		pColision->Render();
	}
}

void JF::GameObject::Release()
{
	for each (auto component in m_mapComponents)
	{
		component.second->Release();
		SafeDelete(component.second);
	}
}
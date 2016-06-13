#include "stdafx.h"
#include "GameObject.h"

Jaraffe::GameObject::GameObject()
{
}

Jaraffe::GameObject::~GameObject()
{
}

Jaraffe::GameObject* Jaraffe::GameObject::Create()
{
	return new Jaraffe::GameObject();
}

void Jaraffe::GameObject::Init()
{
	for each (auto component in m_mapComponents)
	{
		component.second->Init();
	}
}

void Jaraffe::GameObject::Update()
{
	for each (auto component in m_mapComponents)
	{
		component.second->Update();
	}
}

void Jaraffe::GameObject::Render()
{
	auto pRenderer = GetComponent<Jaraffe::Component::Renderer>();
	if (pRenderer != nullptr)
	{
		pRenderer->Render();
	}
}

void Jaraffe::GameObject::Release()
{
	for each (auto component in m_mapComponents)
	{
		component.second->Release();
	}
}
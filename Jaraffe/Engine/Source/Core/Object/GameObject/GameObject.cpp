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

void Jaraffe::GameObject::Update(float t)
{
	for each (auto component in m_mapComponents)
	{
		component.second->Update(t);
	}
}

void Jaraffe::GameObject::Render()
{
	auto pRenderer = GetComponent<Jaraffe::Component::Renderer>();
	if (pRenderer != nullptr)
	{
		pRenderer->Render();
	}

	auto pCubeMap = GetComponent<Jaraffe::Component::CubeMap>();
	if (pCubeMap != nullptr)
	{
		pCubeMap->Render();
	}

	auto pColision = GetComponent<Jaraffe::Component::Colision>();
	if (pColision != nullptr)
	{
		pColision->Render();
	}
}

void Jaraffe::GameObject::Release()
{
	for each (auto component in m_mapComponents)
	{
		component.second->Release();
	}
}
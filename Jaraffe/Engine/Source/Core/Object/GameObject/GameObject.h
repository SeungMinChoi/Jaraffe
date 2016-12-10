#pragma once

using namespace JF::Component;

namespace JF
{

class GameObject
{
//=============================================================================
// Constructor/Destructor)
//=============================================================================
private:
	GameObject();

public:
	virtual ~GameObject();

public:
	static GameObject* Create();

//=============================================================================
// Template Functions) 
//=============================================================================
public:
	// Component Insert
	template<class _component_t>
	void InsertComponent(_component_t* p_newComponent);

	// Component Remove ( Map Remove And Return Remove Value )
	template<class _component_t>
	void RemoveComponent();

	// Get Component
	template<class _component_t>
	_component_t* GetComponent(void);

//=============================================================================
// Public Functions) 
//=============================================================================
public:
	void Reset();
	void Update(float t);
	void Render();
	void Release();

//=============================================================================
// Private Members) 
//=============================================================================
private:
	std::unordered_map<size_t, BaseComponent*> m_mapComponents;
};

#pragma region Template Functions

template<class _component_t>
void JF::GameObject::InsertComponent(_component_t* p_newComponent)
{
	size_t componentId = get_component<_component_t>::type::GetComponentID();
	if (m_mapComponents.find(componentId) != m_mapComponents.end())
		m_mapComponents[componentId]->Release();

	p_newComponent->SetOwner(this);
	m_mapComponents[componentId] = p_newComponent;
}

template<class _component_t>
void JF::GameObject::RemoveComponent()
{
	size_t componentId = get_component<_component_t>::type::GetComponentID();
	auto iterFind = m_mapComponents.find(componentId);
	if (iterFind == m_mapComponents.end())
		return;

	*iterFind->Release();
	m_mapComponents.erase(iterFind);
}

template<class _component_t>
_component_t* JF::GameObject::GetComponent(void)
{
	size_t componentId = get_component<_component_t>::type::GetComponentID();
	if (m_mapComponents.find(componentId) == m_mapComponents.end())
		return nullptr;

	return reinterpret_cast<_component_t*>(m_mapComponents[componentId]);
}

#pragma endregion


}
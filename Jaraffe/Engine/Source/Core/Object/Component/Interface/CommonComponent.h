#pragma once

//=============================================================================
// MetaTemplate)
//=============================================================================
namespace JF
{
namespace Component
{

// ---------------------------------------
// component null
// ---------------------------------------
struct null_t {};

// ---------------------------------------
// Component Identifier
// ---------------------------------------
template<class _component_t, class _Parent_component_t, bool _is_unique>
struct Identifier
{
	typedef _component_t			current_component;
	typedef _Parent_component_t		Parent_component;

	enum { isUnique = _is_unique };
};

// ---------------------------------------
// Component Is Unique Check
// ---------------------------------------
template<class _component_t>
struct is_unique_component
{
	typedef typename _component_t::Identifier_t			Identifier_t;
	typedef typename Identifier_t::Parent_component		Parent_t;

	enum
	{
		value = std::_If<Identifier_t::isUnique, std::true_type, is_unique_component<Parent_t>>::type::value
	};
};

template<>
struct is_unique_component<null_t>
{
	enum { value = false };
};

// ---------------------------------------
// Get Unique Component
// ---------------------------------------
template<class _component_t>
struct get_unique_component
{
	typedef typename _component_t::Identifier_t			Identifier_t;
	typedef typename Identifier_t::Parent_component		Parent_t;

	typedef typename std::_If<Identifier_t::isUnique, _component_t, typename get_unique_component<Parent_t>::type>::type type;
};

template<>
struct get_unique_component<null_t>
{
	typedef null_t type;
};

// ---------------------------------------
// Get Component
// ---------------------------------------
template<class _component_t>
struct get_component
{
	typedef typename std::_If<is_unique_component<_component_t>::value, typename get_unique_component<_component_t>::type, _component_t>::type type;
};

// ---------------------------------------
// Identifier
// ---------------------------------------
#define COMPONENT_IDENTIFIER(component_name, parent_component_name, bUnique)				\
	public:																					\
		typedef Identifier<component_name, parent_component_name, bUnique> Identifier_t;	\
		static size_t GetComponentID(void) { return reinterpret_cast<size_t>(&UID); }		\
	private:																				\
		static Identifier_t UID;															\

#define DECLARE_IDENTIFIER(component_name)													\
component_name::Identifier_t component_name::UID;											\

}
}
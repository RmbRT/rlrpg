#include "Character.hpp"

namespace rlrpg
{
	Character::Character(
		unsigned level,
		attrs_t const& base_attributes,
		Inventory const& inventory):
		m_level(level),
		m_base_attributes(base_attributes),
		m_inventory(inventory),
		m_health(base_attributes[size_t(Attr::Health)]) { }

	unsigned Character::health() const { return m_health; }
	unsigned Character::level() const { return m_level; }

	attrs_t & Character::base_attributes() { return m_base_attributes; }
	attrs_t const& Character::base_attributes() const { return m_base_attributes; }

	Inventory & Character::inventory() { return m_inventory; }
	Inventory const& Character::inventory() const { return m_inventory; }
}
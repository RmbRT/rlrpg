#include "Enchantment.hpp"

namespace rlrpg
{
	EnchantmentDesc::EnchantmentDesc(
		std::string name,
		Rarity rarity,
		unsigned allowed_flags,
		attrs_t const& add_min,
		attrs_t const& add_range,
		factors_t const& mul_min,
		factors_t const& mul_range) :
		m_name(std::move(name)),
		m_rarity(rarity),
		m_allowed_flags(m_allowed_flags),
		m_add_min(add_min),
		m_add_range(add_range),
		m_mul_min(mul_min),
		m_mul_range(mul_range) { }

	bool EnchantmentDesc::allowed_for(EquipmentType type) const { return m_allowed_flags & (1<<int(type)); }
	
	Rarity EnchantmentDesc::rarity() const { return m_rarity; }
	
	attrs_t const& EnchantmentDesc::add_min() const { return m_add_min; }
	attrs_t const& EnchantmentDesc::add_range() const { return m_add_range; }

	
	factors_t const& EnchantmentDesc::mul_min() const { return m_mul_min; }
	factors_t const& EnchantmentDesc::mul_range() const { return m_mul_range; }

	std::string const& EnchantmentDesc::name() const { return m_name; }


}
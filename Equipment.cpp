#include "Equipment.hpp"
#include <cassert>

namespace rlrpg
{
	EquipmentDesc::EquipmentDesc(
		std::string name,
		EquipmentType type,
		attrs_t const& add_min,
		attrs_t const& add_range,
		factors_t const& mul_min,
		factors_t const& mul_range):
		m_name(std::move(name)),
		m_type(type),
		m_add_min(add_min),
		m_add_range(add_range),
		m_mul_min(mul_min),
		m_mul_range(mul_range) { }

	EquipmentType EquipmentDesc::type() const { return m_type; }

	attrs_t const& EquipmentDesc::add_min() const { return m_add_min; }
	attrs_t const& EquipmentDesc::add_range() const { return m_add_range; }

	factors_t const& EquipmentDesc::mul_min() const { return m_mul_min; }
	factors_t const& EquipmentDesc::mul_range() const { return m_mul_range; }

	std::string const& EquipmentDesc::name() const { return m_name; }

	Equipment::Equipment(
		unsigned desc,
		EquipmentType type,
		Rarity rarity,
		attrs_t const& base_attributes,
		unsigned quality,
		unsigned durability,
		std::vector<Enchantment> enchantments):
		m_desc(desc),
		m_type(type),
		m_rarity(rarity),
		m_base_attributes(base_attributes),
		m_quality(quality),
		m_durability(durability),
		m_enchantments(std::move(enchantments)) { }

	EquipmentType Equipment::type() const { return m_type; }
	Rarity Equipment::rarity() const { return m_rarity; }
	
	attrs_t const& Equipment::base_attributes() const { return m_base_attributes; }
	unsigned Equipment::quality() const { return m_quality; }
	unsigned Equipment::durability() const { return m_durability; }

	attrs_t Equipment::calculated_attributes() const
	{
		return (attrs_t(m_base_attributes) *= (m_quality+10)) /= 10;
	}

	void Equipment::dec_durability(unsigned amount)
	{
		if(m_durability > amount)
			m_durability -= amount;
		else
			m_durability = 0;
	}

	void Equipment::inc_durability(unsigned amount)
	{
		m_durability += amount;
	}

	void Equipment::inc_quality(unsigned amount)
	{
		m_quality += amount;
	}

	std::vector<Enchantment> const& Equipment::enchantments() const { return m_enchantments; }

	void Equipment::enchant(Enchantment const& enchantment)
	{
		m_enchantments.push_back(enchantment);
	}
}
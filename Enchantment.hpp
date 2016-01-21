#ifndef __rlrpg_enchantment_hpp_defined
#define __rlrpg_enchantment_hpp_defined

#include "EquipmentType.hpp"
#include "Attribute.hpp"
#include "Rarity.hpp"
#include "Generated.hpp"
#include "QualityDurability.hpp"

#include <string>

namespace rlrpg
{
	class EnchantmentDesc;
	class Enchantment;

	class EnchantmentDesc
	{
		unsigned m_id;
		Rarity m_rarity;
		unsigned m_allowed_flags;
		
		attrs_t m_add_min, m_add_range;
		factors_t m_mul_min, m_mul_range;

		std::string m_name;
	public:
		EnchantmentDesc(
			unsigned id,
			std::string name,
			Rarity rarity,
			unsigned allowed_flags,
			attrs_t const& add_min,
			attrs_t const& add_range,
			factors_t const& mul_min,
			factors_t const& mul_range);

		bool allowed_for(EquipmentType type) const;

		Rarity rarity() const;

		attrs_t const& add_min() const;
		attrs_t const& add_range() const;

		factors_t const& mul_min() const;
		factors_t const& mul_range() const;

		std::string const& name() const;

		Enchantment generate(id_t equipment_id, Generated const& gen) const;
	};

	class Enchantment : public Generated, public QualityDurability
	{
		unsigned m_type;
		id_t m_equipment;
		
		attrs_t m_base_add;
		factors_t m_base_mul;
	public:
		Enchantment(
			Generated const& gen_params,
			QualityDurability const& quality_durability,
			id_t equipment,
			unsigned type,
			attrs_t const& base_add,
			factors_t const& base_mul);
		
		unsigned type() const;
		id_t equipment() const;

		attrs_t const& base_add() const;
		factors_t const& base_mul() const;
	};

}

#endif
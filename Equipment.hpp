#ifndef __rlrpg_equipment_hpp_defined
#define __rlrpg_equipment_hpp_defined

#include "Attribute.hpp"
#include "Rarity.hpp"
#include "Enchantment.hpp"
#include "EquipmentType.hpp"
#include "Generated.hpp"
#include "RNG.hpp"
#include "QualityDurability.hpp"
#include <vector>

namespace rlrpg
{
	class EquipmentDesc;
	class Equipment;

	class LogicAssets;

	/*Describes a class of Equipment.*/
	class EquipmentDesc
	{
		unsigned m_id;
		EquipmentType m_type;

		attrs_t m_add_min;
		attrs_t m_add_range;

		factors_t m_mul_min;
		factors_t m_mul_range;

		std::string m_name;
	public:
		EquipmentDesc(
			unsigned id,
			std::string name,
			EquipmentType type,
			attrs_t const& add_min,
			attrs_t const& add_range,
			factors_t const& mul_min,
			factors_t const& mul_range);

		unsigned id() const;

		EquipmentType type() const;

		attrs_t const& add_min() const;
		attrs_t const& add_range() const;
		
		factors_t const& mul_min() const;
		factors_t const& mul_range() const;

		std::string const& name() const;

		Equipment generate(Generated const& gen, LogicAssets const& db) const;
	};

	/*Describes a piece of Equipment.*/
	class Equipment : public Generated, public QualityDurability
	{
		unsigned m_desc;
		EquipmentType m_type;
		id_t m_enchantment_counter; // used for generating new unique enchantments.

		Rarity m_rarity;
		
		attrs_t m_base_add;
		factors_t m_base_mul;

		std::vector<Enchantment> m_enchantments;
	public:
		Equipment() = default;
		Equipment(
			Generated const& gen_params,
			QualityDurability const& quality_durability,
			unsigned desc,
			EquipmentType type,
			id_t enchantment_counter,
			Rarity rarity,
			attrs_t const& base_add,
			factors_t const& base_mul,
			std::vector<Enchantment> enchantments);
		Equipment(Equipment&&);
		Equipment & operator=(Equipment&&);
		
		unsigned desc() const;

		EquipmentType type() const;
		Rarity rarity() const;

		attrs_t const& base_add() const;
		factors_t const& base_mul() const;

		attrs_t enchantments_add() const;
		factors_t enchantments_mul() const;

		std::vector<Enchantment> const& enchantments() const;

		void enchant(EnchantmentDesc const& enchantment, attr_t luck);
		void disenchant(size_t index);
	};
}


#endif
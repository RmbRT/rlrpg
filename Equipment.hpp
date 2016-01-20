#ifndef __rlrpg_equipment_hpp_defined
#define __rlrpg_equipment_hpp_defined

#include "Attribute.hpp"
#include "Rarity.hpp"
#include "Enchantment.hpp"
#include "EquipmentType.hpp"
#include "Registered.hpp"
#include "RNG.hpp"
#include <vector>

namespace rlrpg
{
	/*Describes a class of Equipment.*/
	class EquipmentDesc
	{
		EquipmentType m_type;

		attrs_t m_add_min;
		attrs_t m_add_range;

		factors_t m_mul_min;
		factors_t m_mul_range;

		std::string m_name;
	public:
		EquipmentDesc(
			std::string name,
			EquipmentType type,
			attrs_t const& add_min,
			attrs_t const& add_range,
			factors_t const& mul_min,
			factors_t const& mul_range);

		EquipmentType type() const;

		attrs_t const& add_min() const;
		attrs_t const& add_range() const;
		
		factors_t const& mul_min() const;
		factors_t const& mul_range() const;

		std::string const& name() const;

		Enchantment generate(RNG rng, attr_t luck) const;
	};

	/*Describes a piece of Equipment.*/
	class Equipment : public Registered
	{
		unsigned m_desc;
		EquipmentType m_type;
		Rarity m_rarity;
		
		attrs_t m_base_attributes;
		unsigned m_quality;
		unsigned m_durability;

		std::vector<Enchantment> m_enchantments;
	public:
		Equipment() = default;
		Equipment(
			unsigned desc,
			EquipmentType type,
			Rarity rarity,
			attrs_t const& base_attributes,
			unsigned quality,
			unsigned durability,
			std::vector<Enchantment> enchantments);
		
		unsigned desc() const;

		EquipmentType type() const;
		Rarity rarity() const;

		attrs_t const& base_attributes() const;
		unsigned quality() const;
		unsigned durability() const;

		/*Attributes with quality and durability applied. enchantments are not counted in.*/
		attrs_t calculated_attributes() const;

		void dec_durability(unsigned amount);
		void inc_durability(unsigned amount);
		void inc_quality(unsigned amount);


		std::vector<Enchantment> const& enchantments() const;

		void enchant(Enchantment const& enchantment);
	};
}


#endif
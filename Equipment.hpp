#ifndef __rlrpg_equipment_hpp_defined
#define __rlrpg_equipment_hpp_defined

#include "Attribute.hpp"
#include "Enchantment.hpp"
#include "EquipmentType.hpp"
#include "Generated.hpp"
#include "RNG.hpp"
#include "QDValue.hpp"
#include <vector>

namespace rlrpg
{
	/* Types. */
	class EquipmentDesc;
	class Equipment;

	/* Forward declarations. */
	class LogicAssets;

	/* Describes a class of Equipment. */
	class EquipmentDesc
	{
		/* The id of this equipment descriptor.
		Must be identical to the index in the LogicAssets list. */
		id_t m_id;
		/* The general equipment classification of
		equipments described by this descriptor. */
		EquipmentType m_type;
		/* The minimal character level required to wield / generate this equipment. */
		level_t m_level;

		/* The range of attributes equipments of this type can grant. */
		AttributesRange m_attributes;

		/* The name of this type of equipment. */
		std::string m_name;
	public:
		EquipmentDesc(
			id_t id,
			std::string name,
			EquipmentType type,
			level_t level,
			AttributesRange const& attributes);

		/* Returns the id of this equipment descriptor. */
		id_t id() const;
		/* Returns the general equipment classification of the described equipment type. */
		EquipmentType type() const;
		/* Returns the minimal level required to wield / generate this type of equipment. */
		level_t level() const;

		/* Returns the range of attributes equipments of this type can grant. */
		AttributesRange const& attributes() const;

		/* Returns the name of this type of equipment. */
		std::string const& name() const;

		/* Generates an instance of equipment of this type.
		@param[in] gen: The generation parameters for (re-) generating this equipment.
		@param[in] db: The LogicAssets */
		Equipment generate(Generated const& gen, LogicAssets const& db, level_t level) const;
	};

	/*Describes a piece of Equipment.*/
	class Equipment : public Generated, public QDValue
	{
		/* The id of the equipment descriptor that describes this equipment instance. */
		id_t m_descriptor;
		/* Counts how many enchantments have ever been applied to this object.
		Used for generating new enchantment ids. */
		id_t m_enchantment_counter;
		/* The basic attributes of this equipment.
		The attributes added by enchantments or the quality level are not contained. */
		Attributes m_attributes;
		/* The enchantments of this equipment. */
		std::vector<Enchantment> m_enchantments;
		/* The level of the item. Is guaranteed to be greater than or equal to the descriptor level. */
		level_t m_level;
	public:
		Equipment() = default;
		Equipment(
			Generated const& gen_params,
			QDValue const& qdval,
			id_t desc,
			id_t enchantment_counter,
			Attributes const& attributes,
			std::vector<Enchantment> enchantments,
			level_t level);

		Equipment(Equipment&&);
		Equipment & operator=(Equipment&&);
		
		/* Returns the id of this equipment's type. */
		id_t descriptor() const;

		/* Returns the base attributes of the equipment, excluding attributes added by
		enchantments and the quality level. */
		Attributes const& base_attributes() const;
		/* Returns the sum of the attributes added by the enchantments of the equipment. */
		Attributes enchantment_attributes() const;

		/* Returns this equipment's enchantments. */
		std::vector<Enchantment> const& enchantments() const;

		/* Returns this equipment's level. */
		level_t level() const;

		/* Enchants this equipment.
		@side-effect: Adds a new enchantment to this items enchantment list.
		@param[in] enchantment: the enchantment descriptor of which to generate a new instance. */
		void enchant(EnchantmentDesc const& enchantment);
		/* Removes an enchantment from the equipment.
		@param[in] index: the index in the enchantment list of the enchantment to remove.
		@side-effect: Removes the enchantment with the index <index> from the enchantment list. */
		void disenchant(size_t index);
	};
}


#endif
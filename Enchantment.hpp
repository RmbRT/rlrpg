#ifndef __rlrpg_enchantment_hpp_defined
#define __rlrpg_enchantment_hpp_defined

#include "EquipmentType.hpp"
#include "Attribute.hpp"
#include "Generated.hpp"
#include "QDValue.hpp"

#include <string>

namespace rlrpg
{
	/* Types. */
	class EnchantmentDesc;
	class Enchantment;

	/* A descriptor for an enchantment.
	Stores the enchantment name,
	possisble equipment types that are compatible with this enchantment,
	the minimal required character level and
	the range of bonuses an enchantment of this type can give. */
	class EnchantmentDesc
	{
		/* The id of the enchantment descriptor.
		Must be identical to the index in the LogicAssets list. */
		id_t m_id;
		/* The compatibility flags, regarding EquipmentType.
		Each EquipmentType has their integer value as bit index. */
		unsigned m_allowed_flags;
		/* The minimal character level needed to wield / generate this enchantment. */
		level_t m_level;
		/* The range of attribute bonuses this enchantment can give. */
		AttributesRange m_attributes;
		/* The name of this enchantment. */
		std::string m_name;
	public:
		EnchantmentDesc(
			id_t id,
			std::string name,
			unsigned allowed_flags,
			level_t level,
			AttributesRange const& attributes);

		/* Returns whether this enchantment type is allowed for the given equipment type.
		@param[in] type: The equipment type to test for.
		@return: Whether an equipment of the given type can have an enchantment of this type. */
		bool allowed_for(EquipmentType type) const;

		/* Returns the minimal character level required
		to wield / generate this type of enchantment. */
		level_t level() const;
		/* Returns the attribute bonus range an enchantment of this type can give. */
		AttributesRange const& attributes() const;
		/* Returns the name of this enchantment type. */
		std::string const& name() const;
		/* Generates an enchantment instance of this enchantment type.
		@param[in] equipment_id: The id of the equipment that is to be enchanted.
		@param[in] gen: The generation parameters needed for (re-) generating an enchantment.
		@return: the generated enchantment. */
		Enchantment generate(id_t equipment_id, Generated const& gen) const;
	};

	/* Describes an enchantment instance.
	The values of an enchantment are influenced by its quality and durability. */
	class Enchantment : public Generated, public QDValue
	{
		/* The id of the enchantment descriptor used to generate this enchantment. */
		id_t m_type;
		/* The id of the equipment instance that has this enchantment. */
		id_t m_equipment;
		/* The attributes this enchantment grants. */
		Attributes m_attributes;
	public:
		Enchantment(
			Generated const& gen_params,
			QDValue const& quality_durability,
			id_t equipment,
			unsigned type,
			Attributes const& attributes);
		
		/* Returns the id of the enchantment descriptor used to generate this enchantment. */
		id_t type() const;
		/* Returns the id of the equipment that has this enchantment. */
		id_t equipment() const;
		/* Returns the attributes this enchantment grants. */
		Attributes const& attributes() const;
	};

}

#endif
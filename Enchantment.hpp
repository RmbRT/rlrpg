#ifndef __rlrpg_enchantment_hpp_defined
#define __rlrpg_enchantment_hpp_defined

#include "EquipmentType.hpp"
#include "Attribute.hpp"
#include "Rarity.hpp"
#include "Registered.hpp"

#include <string>

namespace rlrpg
{

	class EnchantmentDesc
	{
		Rarity m_rarity;
		unsigned m_allowed_flags;
		
		attrs_t m_add_min, m_add_range;
		factors_t m_mul_min, m_mul_range;

		std::string m_name;
	public:
		EnchantmentDesc(
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
	};

	struct Enchantment : public Registered
	{
		unsigned type;
		
		attrs_t base_add;
		factors_t base_mul;
	};

}

#endif
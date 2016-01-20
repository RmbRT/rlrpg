#ifndef __rlrpg_character_hpp_defined
#define __rlrpg_character_hpp_defined

#include "Attribute.hpp"
#include "Registered.hpp"
#include "Inventory.hpp"

namespace rlrpg
{
	class Character : public Registered
	{
		unsigned m_health;

		unsigned m_level;
		attrs_t m_base_attributes;

		Inventory m_inventory;
	public:
		Character(
			unsigned level,
			attrs_t const& base_attributes,
			Inventory const& inventory = Inventory());

		unsigned health() const;
		unsigned level() const;

		attrs_t & base_attributes();
		attrs_t const& base_attributes() const;

		Inventory & inventory();
		Inventory const& inventory() const;
	};
}


#endif
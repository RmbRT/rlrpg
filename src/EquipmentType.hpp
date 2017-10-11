#ifndef __rlrpg_itemtype_hpp_defined
#define __rlrpg_itemtype_hpp_defined

#include "defines.hpp"

namespace rlrpg
{
	enum class EquipmentType
	{
		Helm,
		Gauntlets,
		Arms,
		Torso,
		Legs,
		Feet,

		Ring,
		Necklace,

		Sword,
		Dagger,
		Club,
		Axe,
		Wand,
		Bow,
		Staff,

		rlrpg_last(Shield)
	};
}

#endif
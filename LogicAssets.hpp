#ifndef __rlrpg_logicassets_hpp_defined
#define __rlrpg_logicassets_hpp_defined

#include "Equipment.hpp"
#include "Enchantment.hpp"

#include <vector>

namespace rlrpg
{
	/* Stores all the logic assets the game needs (such as Equipment prototypes).
	Assets such as textures are not contained, as the do not influence the game logic. */
	class LogicAssets
	{
		std::vector<EquipmentDesc> m_equipment_descs;
		std::vector<EnchantmentDesc> m_enchantment_descs;
	public:
		LogicAssets(
			std::vector<EquipmentDesc> equipment_descs,
			std::vector<EnchantmentDesc> enchantment_descs);

		std::vector<EquipmentDesc> const& equipment_descs() const;
		std::vector<EnchantmentDesc> const& enchantment_descs() const;
	};
}

#endif
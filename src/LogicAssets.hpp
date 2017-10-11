#ifndef __rlrpg_logicassets_hpp_defined
#define __rlrpg_logicassets_hpp_defined

#include "Equipment.hpp"
#include "Enchantment.hpp"
#include "Character.hpp"

#include <vector>

namespace rlrpg
{
	/* Stores all the logic assets the game needs (such as Equipment prototypes).
	Assets such as textures are not contained, as they do not influence the game logic. */
	class LogicAssets
	{
		noise_coord_t m_noise_coord;
		id_t m_item_counter;
		std::vector<EquipmentDesc> m_equipment_descs;
		std::vector<EnchantmentDesc> m_enchantment_descs;
	public:
		LogicAssets(
			std::vector<EquipmentDesc> equipment_descs,
			std::vector<EnchantmentDesc> enchantment_descs,
			id_t item_counter);

		std::vector<EquipmentDesc> const& equipment_descs() const;
		std::vector<EnchantmentDesc> const& enchantment_descs() const;

		Equipment generateEquipment(EquipmentType type, level_t level);
		Equipment generateEquipment(EquipSlot slot, level_t level);

		Enchantment generateEnchantment(id_t equipment_descriptor, level_t level);

	};
}

#endif
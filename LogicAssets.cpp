#include "LogicAssets.hpp"

namespace rlrpg
{
	LogicAssets::LogicAssets(
		std::vector<EquipmentDesc> equipment_descs,
		std::vector<EnchantmentDesc> enchantment_descs):
		m_equipment_descs(std::move(equipment_descs)),
		m_enchantment_descs(std::move(enchantment_descs)) { }

	std::vector<EquipmentDesc> const& LogicAssets::equipment_descs() const
	{
		return m_equipment_descs;
	}

	std::vector<EnchantmentDesc> const& LogicAssets::enchantment_descs() const
	{
		return m_enchantment_descs;
	}


}
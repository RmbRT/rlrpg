#include "LogicAssets.hpp"

namespace rlrpg
{
	LogicAssets::LogicAssets(
		std::vector<EquipmentDesc> equipment_descs,
		std::vector<EnchantmentDesc> enchantment_descs,
		id_t item_counter):
		m_noise_coord(0),
		m_item_counter(item_counter),
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

	Equipment LogicAssets::generateEquipment(EquipmentType type, level_t level)
	{
		RNG rng(noise_coord(math::vec<2,noise_coord_t>({m_noise_coord++, m_item_counter})));
		
		size_t suitable_count = 0;
		for(EquipmentDesc const& ed : m_equipment_descs)
			if(ed.type() == type && ed.level() <= level)
				suitable_count++;

		assert(suitable_count != 0 && "there does not exist any equipment description of the requested type.");

		id_t chosen = rng.roll_dice(suitable_count);
		for(EquipmentDesc const& ed : m_equipment_descs)
			if(ed.type() == type && ed.level() <= level && !chosen--)
				return ed.generate(Generated(m_item_counter++), *this, level);

		assert(!"this should never happen!");
	}

	Equipment LogicAssets::generateEquipment(EquipSlot slot, level_t level)
	{
		RNG rng(noise_coord(math::vec<2,noise_coord_t>({m_noise_coord++, m_item_counter})));
		
		EquipmentType type;

		switch(slot)
		{
		case EquipSlot::Ring1:
		case EquipSlot::Ring2:
			{
				type = EquipmentType::Ring;
			} break;
		case EquipSlot::Arms:
			{
				type = EquipmentType::Arms;
			} break;
		case EquipSlot::Feet:
			{
				type = EquipmentType::Feet;
			} break;
		case EquipSlot::Hands:
			{
				type = EquipmentType::Gauntlets;
			} break;
		case EquipSlot::Head:
			{
				type = EquipmentType::Helm;
			} break;
		case EquipSlot::Legs:
			{
				type = EquipmentType::Legs;
			} break;
		case EquipSlot::Mainhand:
			{
				static EquipmentType const choices[] = {
					EquipmentType::Axe,
					EquipmentType::Bow,
					EquipmentType::Club,
					EquipmentType::Dagger,
					EquipmentType::Staff,
					EquipmentType::Sword,
					EquipmentType::Wand
				};

				type = choices[rng.roll_dice(_countof(choices))];
			} break;
		case EquipSlot::Necklace:
			{
				type = EquipmentType::Necklace;
			} break;
		case EquipSlot::Offhand:
			{
				type = EquipmentType::Shield;
			} break;
		case EquipSlot::Torso:
			{
				type = EquipmentType::Torso;
			} break;
		default:
			{
				assert(!"incomplete switch (EquipSlot).");
			} break;
		}

		return generateEquipment(type, level);
	}


	EnchantmentDesc const* LogicAssets::chooseEnchantment(id_t equipment_descriptor, level_t level)
	{
		RNG rng(m_noise_coord++);

		EquipmentDesc & eq = m_equipment_descs[equipment_descriptor];
		
		size_t suitable = 0;
		for(EnchantmentDesc const& ed: m_enchantment_descs)
			if(ed.allowed_for(eq.type()) && ed.level() <= level)
				suitable++;
		
		if(!suitable)
			return nullptr;

		suitable = rng.roll_dice(suitable+1);

		for(EnchantmentDesc const& ed: m_enchantment_descs)
			if(ed.allowed_for(eq.type()) && ed.level() <= level && !suitable--)
				return &ed;
	}

}
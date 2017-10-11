#include "Inventory.hpp"

#include <cassert>

namespace rlrpg
{
	EquipmentSlot::EquipmentSlot():
		m_equipment(kEmpty) { }
	EquipmentSlot::EquipmentSlot(Equipment && equipment):
		m_equipment(std::move(equipment)) { }

	Equipment * EquipmentSlot::equipment()
	{
		return m_equipment ? &m_equipment() : nullptr;
	}

	Equipment const * EquipmentSlot::equipment() const
	{
		return m_equipment ? &m_equipment() : nullptr;
	}

	void EquipmentSlot::set(Equipment && equipment)
	{
		assert(!m_equipment && "Attempted to put an equipment into a slot that already had an item equipped.");

		m_equipment = std::move(equipment);
	}

	void EquipmentSlot::clear()
	{
		m_equipment = kEmpty;
	}


	std::vector<Equipment> & Inventory::stored_equipment()
	{
		return m_stored_equipment;
	}

	std::vector<Equipment> const& Inventory::stored_equipment() const
	{
		return m_stored_equipment;
	}

	void Inventory::store(Equipment && equipment)
	{
		m_stored_equipment.push_back(std::move(equipment));
	}

	void Inventory::unstore(size_t index)
	{
		m_stored_equipment.erase(m_stored_equipment.begin() + index);
	}

	void Inventory::wear(EquipSlot slot, size_t index)
	{
		assert(index < m_stored_equipment.size());
		assert(!m_worn[size_t(slot)].equipment());

		m_worn[size_t(slot)].set(std::move(m_stored_equipment[index]));
		unstore(index);
	}

	void Inventory::unwear(EquipSlot slot)
	{
		assert(m_worn[size_t(slot)].equipment());

		store(std::move(*m_worn[size_t(slot)].equipment()));
		m_worn[size_t(slot)].clear();
	}

	Equipment * Inventory::worn(EquipSlot slot)
	{
		return m_worn[size_t(slot)].equipment();
	}

	Equipment const * Inventory::worn(EquipSlot slot) const
	{
		return m_worn[size_t(slot)].equipment();
	}

	Attributes Inventory::worn_attributes() const
	{
		attrs_t flat, relative;
		for(EquipmentSlot const& es : m_worn)
			if(Equipment const * eq = es.equipment())
			{
				Attributes eq_attrs = eq->attributes();
				flat += eq_attrs.flat;
				relative += eq_attrs.relative;
			}

		return { flat, relative };
	}
}
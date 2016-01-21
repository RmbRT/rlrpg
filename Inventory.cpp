#include "Inventory.hpp"

#include <cassert>

namespace rlrpg
{
	EquipmentSlot::EquipmentSlot():
		m_used(false) { }
	EquipmentSlot::EquipmentSlot(Equipment const& equipment):
		m_used(true),
		m_equipment(equipment) { }

	Equipment * EquipmentSlot::equipment()
	{
		return m_used ? &m_equipment : nullptr;
	}

	Equipment const * EquipmentSlot::equipment() const
	{
		return m_used ? &m_equipment : nullptr;
	}

	void EquipmentSlot::set(Equipment const& equipment)
	{
		assert(!m_used && "Attempted to put an equipment into a slot that already had an item equipped.");

		m_used = true;

		m_equipment = equipment;
	}

	void EquipmentSlot::clear()
	{
		m_used = false;
	}
		

	std::vector<Equipment> & Inventory::stored_equipment()
	{
		return m_stored_equipment;
	}

	std::vector<Equipment> const& Inventory::stored_equipment() const
	{
		return m_stored_equipment;
	}

	void Inventory::store(Equipment const& equipment)
	{
		m_stored_equipment.push_back(equipment);
	}

	void Inventory::unstore(size_t index)
	{
		m_stored_equipment.erase(m_stored_equipment.begin() + index);
	}

	void Inventory::wear(EquipSlot slot, size_t index)
	{
		assert(index < m_stored_equipment.size());
		assert(!m_worn[size_t(slot)].equipment());

		m_worn[size_t(slot)].set(m_stored_equipment[index]);
		unstore(index);
	}

	void Inventory::unwear(EquipSlot slot)
	{
		assert(m_worn[size_t(slot)].equipment());

		store(*m_worn[size_t(slot)].equipment());
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
}
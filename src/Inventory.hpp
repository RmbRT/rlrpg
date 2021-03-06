#ifndef __rlrpg_inventory_hpp_defined
#define __rlrpg_inventory_hpp_defined

#include "Equipment.hpp"
#include "util/Optional.hpp"
#include <vector>

namespace rlrpg
{
	class EquipmentSlot
	{
		Optional<Equipment> m_equipment;
	public:
		EquipmentSlot();
		EquipmentSlot(Equipment && equipment);

		Equipment * equipment();
		Equipment const * equipment() const;

		void set(Equipment && equipment);
		void clear();
	};

	enum class EquipSlot
	{
		Head,
		Ring1,
		Ring2,
		Necklace,
		Hands,
		Arms,
		Torso,
		Legs,
		Feet,
		Mainhand,
		rlrpg_last(Offhand)
	};


	/*The inventory of a character. Contains equip slots for worn equipment, and space for stored equipment.*/
	class Inventory
	{
		EquipmentSlot m_worn[rlrpgenumcount(EquipSlot)];
		std::vector<Equipment> m_stored_equipment;
	public:
		std::vector<Equipment> & stored_equipment();
		std::vector<Equipment> const& stored_equipment() const;

		void store(Equipment && equipment);
		void unstore(size_t index);

		void wear(EquipSlot slot, size_t index);
		void unwear(EquipSlot slot);

		Equipment * worn(EquipSlot slot);
		Equipment const * worn(EquipSlot slot) const;

		Attributes worn_attributes() const;
	};
}


#endif
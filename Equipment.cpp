#include "Equipment.hpp"
#include "LogicAssets.hpp"
#include <cassert>

namespace rlrpg
{
	EquipmentDesc::EquipmentDesc(
		unsigned id,
		std::string name,
		EquipmentType type,
		attrs_t const& add_min,
		attrs_t const& add_range,
		factors_t const& mul_min,
		factors_t const& mul_range):
		m_id(id),
		m_name(std::move(name)),
		m_type(type),
		m_add_min(add_min),
		m_add_range(add_range),
		m_mul_min(mul_min),
		m_mul_range(mul_range) { }

	unsigned EquipmentDesc::id() const { return m_id; }
	EquipmentType EquipmentDesc::type() const { return m_type; }

	attrs_t const& EquipmentDesc::add_min() const { return m_add_min; }
	attrs_t const& EquipmentDesc::add_range() const { return m_add_range; }

	factors_t const& EquipmentDesc::mul_min() const { return m_mul_min; }
	factors_t const& EquipmentDesc::mul_range() const { return m_mul_range; }

	std::string const& EquipmentDesc::name() const { return m_name; }

	Equipment EquipmentDesc::generate(Generated const& gen, LogicAssets const& db) const
	{
		static noisef_t const probabilities[] = { 0.9000, 0.9900, 0.9990, 0.9999 };
		/* The luck factor for roll values (Attr::Luck). */
		noisef_t const luck_factor = rlrpg::luck_factor(gen.gen_luck());

		RNG rng = noise_coord_t(gen.gen_id());
		
		Rarity rarity = Rarity::__last;

		
		{	/* Roll for the rarity of the item from a list of probabilities. */
			noisef_t roll = rng.roll_dicef(1) * luck_factor;

			for(int i = _countof(probabilities); i--;)
				if(roll < probabilities[i])
				{
					rarity = (Rarity)i;
					break;
				}
		}	/* /rarity roll. */

		QualityDurability qd(rng.roll_dice(1 + (size_t(rarity)<<2)), 0);
		qd.inc_durability(1+rng.roll_dice(qd.max_durability()));


		attrs_t base_add = m_add_min;
		factors_t base_mul = m_add_min;

		/* Roll the flat stats of the equipment. */
		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base_add[i] += rng.roll_dicef(1) * luck_factor * m_add_range[i];
		/* Roll the relative stats of the equipment. */
		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base_mul[i] += rng.roll_dicef(1) * luck_factor * m_mul_range[i];

		std::vector<Enchantment> enchantments;
		{	/* Roll the enchantments of the equipment. */

			size_t const ench_count = rng.roll_dice(size_t(rarity)+1);

			enchantments.reserve(ench_count);

			size_t suitable_enchantments = 0;
			for(EnchantmentDesc const& ench : db.enchantment_descs())
				if(ench.allowed_for(m_type) && size_t(ench.rarity()) <= size_t(rarity))
					suitable_enchantments++;

			for(size_t ench = 0; ench < ench_count; ench++)
			{
				size_t index = rng.roll_dice(suitable_enchantments);

				for(EnchantmentDesc const& ench: db.enchantment_descs())
					if(ench.allowed_for(m_type) && size_t(ench.rarity()) <= size_t(rarity) && !index--)
					{
						enchantments.push_back(
							ench.generate(
								gen.gen_id(),
								Generated(enchantments.size(), gen.gen_luck())));
						break;
					}
			}
		}

		/* Create  the instance. */
		return Equipment(
			gen,
			qd,
			m_id,
			m_type,
			(id_t)enchantments.size(),
			rarity,
			base_add,
			base_mul,
			std::move(enchantments));
	}

	Equipment::Equipment(
		Generated const& gen_params,
		QualityDurability const& quality_durability,
		unsigned desc,
		EquipmentType type,
		id_t enchantment_counter,
		Rarity rarity,
		attrs_t const& base_add,
		factors_t const& base_mul,
		std::vector<Enchantment> enchantments):
		Generated(
			gen_params.gen_id(),
			gen_params.gen_luck()),
		QualityDurability(quality_durability),
		m_desc(desc),
		m_type(type),
		m_enchantment_counter(enchantment_counter),
		m_rarity(rarity),
		m_base_add(base_add),
		m_base_mul(base_mul),
		m_enchantments(std::move(enchantments)) { }

	Equipment::Equipment(Equipment&& move):
		Generated(move),
		QualityDurability(move),
		m_desc(move.m_desc),
		m_type(move.m_type),
		m_enchantment_counter(move.m_enchantment_counter),
		m_rarity(move.m_rarity),
		m_base_add(move.m_base_add),
		m_base_mul(move.m_base_mul),
		m_enchantments(std::move(move.m_enchantments)) { }

	Equipment & Equipment::operator=(Equipment &&move)
	{
		if(this == &move)
			return *this;

		static_cast<Generated&>(*this)= move;
		static_cast<QualityDurability&>(*this) = move;
		m_desc = move.m_desc;
		m_type = move.m_type;
		m_enchantment_counter = move.m_enchantment_counter;
		m_rarity = move.m_rarity;
		m_base_add = move.m_base_add;
		m_base_mul = move.m_base_mul;
		m_enchantments = std::move(move.m_enchantments);

		return *this;
	}


	unsigned Equipment::desc() const { return m_desc; }

	EquipmentType Equipment::type() const { return m_type; }
	Rarity Equipment::rarity() const { return m_rarity; }
	
	attrs_t const& Equipment::base_add() const { return m_base_add; }
	factors_t const& Equipment::base_mul() const { return m_base_mul; }

	std::vector<Enchantment> const& Equipment::enchantments() const { return m_enchantments; }

	void Equipment::enchant(EnchantmentDesc const& enchantment, attr_t luck)
	{
		enchantment.generate(gen_id(), Generated(m_enchantment_counter++, luck));
	}
}
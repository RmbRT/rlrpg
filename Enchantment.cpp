#include "Enchantment.hpp"
#include "RNG.hpp"

namespace rlrpg
{
	EnchantmentDesc::EnchantmentDesc(
		unsigned id,
		std::string name,
		Rarity rarity,
		unsigned allowed_flags,
		attrs_t const& add_min,
		attrs_t const& add_range,
		factors_t const& mul_min,
		factors_t const& mul_range) :
		m_id(id),
		m_name(std::move(name)),
		m_rarity(rarity),
		m_allowed_flags(m_allowed_flags),
		m_add_min(add_min),
		m_add_range(add_range),
		m_mul_min(mul_min),
		m_mul_range(mul_range) { }

	bool EnchantmentDesc::allowed_for(EquipmentType type) const { return m_allowed_flags & (1<<int(type)); }
	
	Rarity EnchantmentDesc::rarity() const { return m_rarity; }
	
	attrs_t const& EnchantmentDesc::add_min() const { return m_add_min; }
	attrs_t const& EnchantmentDesc::add_range() const { return m_add_range; }

	
	factors_t const& EnchantmentDesc::mul_min() const { return m_mul_min; }
	factors_t const& EnchantmentDesc::mul_range() const { return m_mul_range; }

	std::string const& EnchantmentDesc::name() const { return m_name; }

	Enchantment EnchantmentDesc::generate(id_t equipment_id, Generated const& gen) const
	{
		factor_t const luck_factor = rlrpg::luck_factor(gen.gen_luck());
		RNG rng = noise_coord(math::vec<2,noise_coord_t>({equipment_id,gen.gen_id()}));

		QualityDurability qd(rng.roll_dice(1 + (size_t(m_rarity)<<2)), 0);
		qd.inc_durability(1+rng.roll_dice(qd.max_durability()));

		attrs_t base_add = m_add_min;
		factors_t base_mul = m_mul_min;

		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base_add[i] += rng.roll_dicef(1) * luck_factor * m_add_range[i];

		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base_mul[i] += rng.roll_dicef(1) * luck_factor * m_mul_range[i];
		
		return Enchantment(
			gen,
			qd,
			equipment_id,
			m_id,
			base_add,
			base_mul);
	}

	Enchantment::Enchantment(
		Generated const& gen_params,
		QualityDurability const& quality_durability,
		id_t equipment,
		unsigned type,
		attrs_t const& base_add,
		factors_t const& base_mul):
		Generated(
			gen_params.gen_id(),
			gen_params.gen_luck()),
		QualityDurability(quality_durability),
		m_equipment(equipment),
		m_type(type),
		m_base_add(base_add),
		m_base_mul(base_mul) { }

	unsigned Enchantment::type() const
	{
		return m_type;
	}

	id_t Enchantment::equipment() const
	{
		return m_equipment;
	}


	attrs_t const& Enchantment::base_add() const
	{
		return m_base_add;
	}

	factors_t const& Enchantment::base_mul() const
	{
		return m_base_mul;
	}

}
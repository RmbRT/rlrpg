#include "Enchantment.hpp"
#include "RNG.hpp"

namespace rlrpg
{
	EnchantmentDesc::EnchantmentDesc(
		id_t id,
		std::string name,
		unsigned allowed_flags,
		level_t level,
		AttributesRange const& attributes) :
		m_id(id),
		m_name(std::move(name)),
		m_allowed_flags(allowed_flags),
		m_level(level),
		m_attributes(attributes) { }

	bool EnchantmentDesc::allowed_for(EquipmentType type) const { return m_allowed_flags & (1<<int(type)); }

	AttributesRange const& EnchantmentDesc::attributes() const { return m_attributes; }

	std::string const& EnchantmentDesc::name() const { return m_name; }

	Enchantment EnchantmentDesc::generate(id_t equipment_id, Generated const& gen) const
	{
		RNG rng = noise_coord(math::vec<noise_coord_t>(equipment_id, gen.gen_id()));

		QDValue qd;

		Attributes base(m_attributes.base);

		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base.flat[i] += rng.roll_dice(m_attributes.range.flat[i] +1);

		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base.relative[i] += rng.roll_dice(m_attributes.range.relative[i] +1);

		return Enchantment(
			gen,
			qd,
			equipment_id,
			m_id,
			base);
	}

	Enchantment::Enchantment(
		Generated const& gen_params,
		QDValue const& quality_durability,
		id_t equipment,
		unsigned type,
		Attributes const& attributes):
		Generated(gen_params),
		QDValue(quality_durability),
		m_equipment(equipment),
		m_type(type),
		m_attributes(attributes) { }

	unsigned Enchantment::type() const
	{
		return m_type;
	}

	id_t Enchantment::equipment() const
	{
		return m_equipment;
	}

	Attributes const& Enchantment::attributes() const
	{
		return m_attributes;
	}

}
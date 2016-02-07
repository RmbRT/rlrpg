#include "Equipment.hpp"
#include "LogicAssets.hpp"
#include <cassert>

namespace rlrpg
{
	EquipmentDesc::EquipmentDesc(
		id_t id,
		std::string name,
		EquipmentType type,
		level_t level,
		AttributesRange const& attributes):
		m_id(id),
		m_name(std::move(name)),
		m_type(type),
		m_level(level),
		m_attributes(attributes) { }

	id_t EquipmentDesc::id() const { return m_id; }
	EquipmentType EquipmentDesc::type() const { return m_type; }
	level_t EquipmentDesc::level() const { return m_level; }

	AttributesRange const& EquipmentDesc::attributes() const { return m_attributes; }

	std::string const& EquipmentDesc::name() const { return m_name; }

	Equipment EquipmentDesc::generate(Generated const& gen, LogicAssets const& db, level_t level) const
	{
		assert(level >= m_level && "tried to create an equipment with a level lower than its descriptor's requirement.");

		static noise_t const enchantment_probs[] = { 5000, 900, 95, 5 };

		RNG rng = noise_coord_t(gen.gen_id());

		QDValue qd(0, 0, 0);
		qd.full_repair();

		Attributes base(m_attributes.base);

		/* Roll the flat stats of the equipment. */
		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base.flat[i] += rng.roll_dice(m_attributes.range.flat[i]+1);
		/* Roll the relative stats of the equipment. */
		for(unsigned i = rlrpgenumcount(Attr); i--;)
			base.relative[i] += rng.roll_dice(m_attributes.range.relative[i]+1);

		size_t ench_count = 0;
		{
			noise_t const roll = rng.roll_dice(100000);
			for(int i = _countof(enchantment_probs); i--;)
				if(roll <= enchantment_probs[i])
					ench_count = i+1;
		}

		std::vector<Enchantment> enchs;
		enchs.reserve(ench_count);

		while(ench_count--)
		{
			
			size_t suitable = 0;
			for(EnchantmentDesc const& ed: db.enchantment_descs())
				if(ed.allowed_for(m_type) && ed.level() <= )
					suitable++;
		
			if(!suitable)
			{
				enchs.clear();
				ench_count = 0;
				break;
			}

			suitable = rng.roll_dice(suitable+1);

			for(EnchantmentDesc const& ed: db.enchantment_descs())
				if(ed.allowed_for(m_type) && ed.level() <= level && !suitable--)
				{
					enchs.push_back(ed.generate(gen.gen_id(), Generated(enchs.size())));
				}
		}

		/* Create  the instance. */
		return Equipment(
			gen,
			qd,
			m_id,
			enchs.size(),
			base,
			std::move(enchs),
			level);
	}

	Equipment::Equipment(
		Generated const& gen_params,
		QDValue const& quality_durability,
		id_t descriptor,
		id_t enchantment_counter,
		Attributes const& attributes,
		std::vector<Enchantment> enchantments,
		level_t level):
		Generated(gen_params),
		QDValue(quality_durability),
		m_descriptor(descriptor),
		m_enchantment_counter(enchantment_counter),
		m_attributes(attributes),
		m_enchantments(std::move(enchantments)),
		m_level(level) { }

	Equipment::Equipment(Equipment&& move):
		Generated(move),
		QDValue(move),
		m_descriptor(move.m_descriptor),
		m_enchantment_counter(move.m_enchantment_counter),
		m_attributes(move.m_attributes),
		m_enchantments(std::move(move.m_enchantments)),
		m_level(move.m_level) { }

	Equipment & Equipment::operator=(Equipment &&move)
	{
		if(this == &move)
			return *this;

		static_cast<Generated&>(*this) = move;
		static_cast<QDValue&>(*this) = move;
		m_descriptor = move.m_descriptor;
		m_enchantment_counter = move.m_enchantment_counter;
		m_attributes = move.m_attributes;
		m_enchantments = std::move(move.m_enchantments);
		m_level = move.m_level;

		return *this;
	}


	unsigned Equipment::descriptor() const { return m_descriptor; }
	
	Attributes const& Equipment::base_attributes() const { return m_attributes; }

	Attributes Equipment::enchantment_attributes() const
	{
		Attributes attrs(attrs_t(0), attrs_t(0));

		for(Enchantment const& ec : m_enchantments)
			if(!ec.broken())
			{
				attrs.flat += ec.attributes().flat * ec.quality_factor();
				attrs.relative += ec.attributes().relative * ec.quality_factor();
			}
		return attrs;
	}

	attrs_t Equipment::enchantments_relative() const
	{
		attrs_t relative(0);
		for(Enchantment const& ec : m_enchantments)
			if(!ec.broken())
				relative += ec.base_relative() * ec.quality_factor();
		return relative;
	}

	std::vector<Enchantment> const& Equipment::enchantments() const { return m_enchantments; }

	void Equipment::enchant(EnchantmentDesc const& enchantment, attr_t luck)
	{
		assert(enchantment.rarity() <= gen_rarity() && "Tried to enchant a lower rarity equipment with a higher rarity enchantment.");
		enchantment.generate(gen_id(), Generated(m_enchantment_counter++, luck, enchantment.rarity()));
	}
}
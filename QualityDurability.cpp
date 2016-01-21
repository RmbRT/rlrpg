#include "QualityDurability.hpp"

namespace rlrpg
{
	QualityDurability::QualityDurability():
		m_quality(0),
		m_durability(base_durability_capacity) { }

	QualityDurability::QualityDurability(
		quality_t quality,
		durability_t durability):
		m_quality(quality),
		m_durability(durability) { }

	void QualityDurability::enhance_quality()
	{
		size_t const damage = max_durability() - m_durability;
		++m_quality;

		m_durability = max_durability() - damage * (m_quality-1) / m_quality;
	}

	void QualityDurability::inc_durability(durability_t increase)
	{
		assert(m_durability <= m_durability + increase);
		m_durability += increase;
	}

	void QualityDurability::dec_durability(durability_t decrease)
	{
		assert(m_durability >= m_durability - decrease);
		m_durability -= decrease;
	}

	void QualityDurability::full_repair()
	{
		m_durability = max_durability();
	}

	quality_t QualityDurability::quality() const
	{
		return m_quality;
	}

	durability_t QualityDurability::durability() const
	{
		return m_durability;
	}

	bool QualityDurability::broken() const
	{
		return !m_durability;
	}

	factor_t QualityDurability::quality_factor() const
	{
		return factor_t(m_quality+10) * (factor_t(1)/10);
	}

	durability_t QualityDurability::max_durability() const
	{
		return 10000 + 10000 * m_quality;
	}
}
#include "QDValue.hpp"

#include <cassert>

namespace rlrpg
{
	QDValue::QDValue():
		m_quality(0),
		m_durability(0),
		m_durability_base(0) { }

	QDValue::QDValue(
		quality_t quality,
		durability_t durability_max,
		durability_t durability_current):
		m_quality(quality),
		m_durability(0),
		m_durability_base(durability_max)
	{
		// Validate the durability value.
		repair(durability_current);
	}

	void QDValue::repair(durability_t increase)
	{
		assert(m_durability <= m_durability + increase && "Tried to do negative repair or overflow durability.");
		m_durability += increase;

		durability_t const limit = max_durability();
		if(m_durability > limit)
			m_durability = limit;
	}

	void QDValue::damage(durability_t decrease)
	{
		assert(m_durability >= m_durability - decrease);
		if(decrease >= m_durability)
			m_durability = 0;
		else
			m_durability -= decrease;
	}

	void QDValue::full_repair()
	{
		m_durability = max_durability();
	}

	quality_t QDValue::quality() const
	{
		return m_quality;
	}

	durability_t QDValue::durability() const
	{
		return m_durability;
	}

	bool QDValue::broken() const
	{
		return !m_durability;
	}

	factor_t QDValue::quality_factor() const
	{
		return factor_t(m_quality+10) * (factor_t(1)/10);
	}

	durability_t QDValue::max_durability() const
	{
		return m_quality;
	}
}
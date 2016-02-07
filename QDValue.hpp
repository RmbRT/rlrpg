#ifndef __rlrpg_qualitydurability_hpp_defined
#define __rlrpg_qualitydurability_hpp_defined

#include "Attribute.hpp"

namespace rlrpg
{
	typedef unsigned int quality_t;
	typedef unsigned int durability_t;

	/* Describes an object that can be enhanced and damaged/repaired. */
	class QDValue
	{
		/* The quality level. Improves the
		durability limit and other values. */
		quality_t m_quality;
		/* The current durability value. */
		durability_t m_durability;
		/* The base durability limit. The actual limit
		is calculated using the quality level. */
		durability_t m_durability_base;
	public:
		QDValue();
		/* Validates the durability value after setting quality and limit. */
		QDValue(
			quality_t quality,
			durability_t durability_base,
			durability_t durability_current);
		
		/* When repairing an object. Increases
		the durability by the given amount. */
		void repair(durability_t increase);
		/* When damaging an object. Decreases
		the durability by the given amount. */
		void damage(durability_t decrease);
		/* Sets the durability to the maximum. */
		void full_repair();
		/* The quality level of the object. */
		quality_t quality() const;
		/* The durability of the object. */
		durability_t durability() const;
		/* The quality factor. */
		factor_t quality_factor() const;

		/* Whether the durability is 0. */
		bool broken() const;

		/* The maximum durability. 
		@return: The quality factor applied to the base durability limit. */
		durability_t max_durability() const;
	};
}

#endif
#ifndef __rlrpg_qualitydurability_hpp_defined
#define __rlrpg_qualitydurability_hpp_defined

#include "Attribute.hpp"

namespace rlrpg
{
	typedef unsigned quality_t;
	typedef unsigned durability_t;

	static const durability_t base_durability_capacity = 10000;

	/* Describes an object that can be enhanced and damaged/repaired. */
	class QualityDurability
	{
		quality_t m_quality;
		durability_t m_durability;
	public:
		QualityDurability();
		QualityDurability(
			quality_t quality,
			durability_t durability);
		
		/* Increases the quality by one level. */
		void enhance_quality();
		/* When repairing an object. Only positive values or 0 are allowed. */
		void inc_durability(durability_t increase);
		/* When damaging an object. Only positive values or 0 are allowed. */
		void dec_durability(durability_t decrease);
		/* Sets the durability to the maximum. */
		void full_repair();

		/* The quality level of the object. */
		quality_t quality() const;
		/* The durability level of the object. */
		durability_t durability() const;

		/* Broken objects stop functioning until they are repaired. */
		bool broken() const;

		/* The factor for the quality bonus (where quality 0 has a factor 1). */
		factor_t quality_factor() const;

		durability_t max_durability() const;
	};
}

#endif
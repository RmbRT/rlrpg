#ifndef __rlrpg_attribute_hpp_defined
#define __rlrpg_attribute_hpp_defined

#include "defines.hpp"
#include "math/vector.hpp"

namespace rlrpg
{
	enum class Attr : unsigned
	{
		Health,
		HealthRegen,

		Damage,
		DamageRange,

		Armor,

		Evasion,
		Accuracy,

		rlrpg_last(Luck)
	};

	typedef int attr_t;
	typedef float factor_t;

	typedef math::vec<rlrpgenumcount(Attr), attr_t> attrs_t;
	typedef math::vec<rlrpgenumcount(Attr), factor_t> factors_t;

	attrs_t apply_attribs(attrs_t const& base, attrs_t const& add, factors_t const& mul);

	factor_t luck_factor(attr_t luck);
}

#endif
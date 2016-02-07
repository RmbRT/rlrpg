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
		rlrpg_last(Accuracy)
	};

	typedef int attr_t;
	typedef float factor_t;

	typedef unsigned level_t;

	typedef math::vec<rlrpgenumcount(Attr), attr_t> attrs_t;

	struct Attributes
	{
		attrs_t
			flat,
			relative;

		Attributes(attrs_t const& flat, attrs_t const& relative);

		attrs_t combine() const;
		attr_t combine(Attr which) const;
		Attributes multiply(factor_t factor) const;
	};

	struct AttributesRange
	{
		Attributes base, range;

		AttributesRange(Attributes const& base, Attributes const& range);
	};

	attr_t apply_relative(attr_t base, attr_t relative);
}

#endif
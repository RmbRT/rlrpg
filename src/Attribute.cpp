#include "Attribute.hpp"

namespace rlrpg
{
	Attributes::Attributes(attrs_t const& flat, attrs_t const& relative):flat(flat), relative(relative) { }

	attrs_t Attributes::combine() const
	{
		attrs_t result;
		for(unsigned i = attrs_t::Dimension; i--;)
			result[i] = apply_relative(flat[i], relative[i]);
		return result;
	}

	attr_t Attributes::combine(Attr which) const
	{
		return apply_relative(flat[size_t(which)], relative[size_t(which)]);
	}

	Attributes Attributes::multiply(factor_t factor) const
	{
		return Attributes(flat * factor, relative * factor);
	}

	attr_t apply_relative(attr_t base, attr_t relative)
	{
		return base + (base * relative) / 100;
	}
}
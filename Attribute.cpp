#include "Attribute.hpp"
#include <cmath>

namespace rlrpg
{
	attrs_t apply_attribs(attrs_t const& base, attrs_t const& add, factors_t const& mul)
	{
		attrs_t added = base+add;
		return added += math::scale(added, mul);
	}
}
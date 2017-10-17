#ifndef __rlrpg_noise_hpp_defined
#define __rlrpg_noise_hpp_defined


#include "math/Vector.hpp"

namespace rlrpg
{
	typedef unsigned long noise_t;
	typedef unsigned long noise_coord_t;
	typedef double noisef_t;

	/* noise in the range (0, noise_t_max), the bounds are probably never reached. */
	noise_t noise(noise_coord_t);
	/* noise in the range (0, 1). 0 and 1 are probably never reached. */
	noisef_t noisef(noise_coord_t);

	static auto const noise_factors = math::vec<noise_coord_t>(
		1u, 59u, 20353u, 1249033u, 213973541u
	);

	template<std::size_t kDim>
	static noise_coord_t noise_coord(math::Vector<kDim, noise_coord_t> const& val)
	{
		return math::dot(val, noise_factors.subvec<kDim>());
	}
}

#endif
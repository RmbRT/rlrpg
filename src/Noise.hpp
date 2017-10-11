#ifndef __rlrpg_noise_hpp_defined
#define __rlrpg_noise_hpp_defined


#include "math/vector.hpp"

namespace rlrpg
{
	typedef unsigned long noise_t;
	typedef unsigned long noise_coord_t;
	typedef double noisef_t;

	/* noise in the range (0, noise_t_max), the bounds are probably never reached. */
	noise_t noise(noise_coord_t);
	/* noise in the range (0, 1). 0 and 1 are probably never reached. */
	noisef_t noisef(noise_coord_t);

	static noise_coord_t const noise_factors[] = { 1, 59, 20353, 1249033, 213973541 };

	template<unsigned DIM>
	static noise_coord_t noise_coord(math::vec<DIM, noise_coord_t> const& val)
	{
		return math::dot(val,
			reinterpret_cast<
				math::vec<_countof(noise_factors), noise_coord_t> const&>
				(noise_factors[0])
			.subvec<DIM>());
	}
}

#endif
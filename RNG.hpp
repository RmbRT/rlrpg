#ifndef __rlrpg_rng_hpp_defined
#define __rlrpg_rng_hpp_defined

#include "Noise.hpp"

namespace rlrpg
{
	class RNG
	{
		noise_coord_t m_coord;
	public:
		RNG(noise_coord_t);

		noise_coord_t nextCoord();
		
		size_t roll_dice(size_t sides);
		size_t roll_dices(size_t sides, size_t count);

		noisef_t roll_dicef(noisef_t sides);
		noisef_t roll_dicesf(noisef_t sides, size_t count);

		noise_t nextN();
		noisef_t nextF();
		
	};
}

#endif
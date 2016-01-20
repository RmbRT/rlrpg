#include "Dice.hpp"

namespace rlrpg
{
	size_t roll_dice(size_t sides, noise_coord_t coord)
	{
		return noise_t(noise(coord) % (sides<<3)) >> 3;
	}

	noisef_t roll_dicef(noisef_t sides, noise_coord_t coord)
	{
		return noisef_t(noisef(coord) * sides);
	}
}
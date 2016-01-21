#include "RNG.hpp"

#include "Dice.hpp"

namespace rlrpg
{
	RNG::RNG(noise_coord_t coord) : m_coord(coord) { }
	noise_coord_t RNG::nextCoord() { return ++ m_coord; }

	size_t RNG::roll_dice(size_t sides)
	{
		return rlrpg::roll_dice(sides, nextCoord());
	}

	size_t RNG::roll_dices(size_t count, size_t sides)
	{
		size_t sum = 0;
		while(count--)
			sum += roll_dice(sides);
		return sum;
	}

	noisef_t RNG::roll_dicef(noisef_t sides)
	{
		return rlrpg::roll_dicef(sides, nextCoord());
	}
	noisef_t RNG::roll_dicesf(size_t count, noisef_t sides)
	{
		noisef_t sum = 0;
		while(count--)
			sum += roll_dicef(sides);
		return sum;
	}

	noise_t RNG::nextN()
	{
		return noise(nextCoord());
	}

	noisef_t RNG::nextF()
	{
		return noisef(nextCoord());
	}
}
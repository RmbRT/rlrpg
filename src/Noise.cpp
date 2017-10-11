#include "Noise.hpp"

namespace rlrpg
{

	noise_t noise(noise_coord_t n)
	{
		n = n ^ (n << 13);
		return n * (n * n * 15731 + 789221) + 1376312589;
	}

	noisef_t noisef(noise_coord_t n)
	{
		return noise(n) / (noisef_t) ~(noise_t)0;
	}

}
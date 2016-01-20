#ifndef __rlrpg_dice_hpp_defined
#define __rlrpg_dice_hpp_defined

#include "Noise.hpp"

namespace rlrpg
{
	size_t roll_dice(size_t sides, noise_coord_t coord);
	noisef_t roll_dicef(noisef_t sides, noise_coord_t coord);
}

#endif
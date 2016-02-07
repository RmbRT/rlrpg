#ifndef __rlrpg_rng_hpp_defined
#define __rlrpg_rng_hpp_defined

#include "Noise.hpp"
#include "Attribute.hpp"

namespace rlrpg
{
	/* Seeded pseudo random number generator class.
	Has functions for dice rolling and noise values.
	Each function goes to the next noise coordinate in noise space. */
	class RNG
	{
		/* The coordinate in noise space used for the next calculation. */
		noise_coord_t m_coord;
	public:
		/* Creates a RNG with the given seed. */
		RNG(noise_coord_t seed);
		/* Goes to the next noise coordinate and returns the current coordinate.
		To be used with custom noise functions.
		@side-effect: goes to the next noise coordinate.
		@return: the current noise coordinate. */
		noise_coord_t nextCoord();
		
		/* Rolls a dice with <sides> sides, with values from 0 to <sides>-1.
		@side-effect: goes to the next noise coordinate.
		@param[in] sides: the sides of the dice to be rolled. 
		@return: a value from 0 to <sides>-1.*/
		size_t roll_dice(size_t sides);
		/* Rolls <count> dices with <sides> sides, with values from 0 to <sides>-1.
		@side-effect: goes to the <count>-th next noise coordinate.
		@param[in] count: the amount of dices to roll.
		@param[in] sides: the amount of sides each dice has.
		@return: the sum of all rolls, where each roll ranges from 0 to <sides>-1. */
		size_t roll_dices(size_t count, size_t sides);

		/* Rolls a floating point dice with values between 0 and <sides>.
		@side-effect: goes to the next noise coordinate.
		@param[in] sides: the range of the returned value.
		@return: a value ranging from 0 to <sides>. */
		noisef_t roll_dicef(noisef_t sides);
		/* Rolls <count> dices with <sides> sides, with values from 0 to <sides>.
		@side-effect: goes to the <count>-th next noise coordinate.
		@param[in] count: the amount of dices to roll.
		@param[in] sides: the value range of each dice.
		@return: the sum off all rolls, where each roll ranges from 0 to <sides>. */
		noisef_t roll_dicesf(size_t count, noisef_t sides);

		/* Returns the next integer noise value.
		@side-effect: goes to the next noise coordinate.
		@return: the noise value of the current noise coordinate. */
		noise_t nextN();
		/* Returns the next real noise value.
		@side-effect: goes to the next noise coordinate.
		@return: the noise value of the current noise coordinate, ranging from 0 to 1. */
		noisef_t nextF();
	};
}

#endif
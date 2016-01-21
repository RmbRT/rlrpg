#ifndef __rlrpg_generated_hpp_defined
#define __rlrpg_generated_hpp_defined

#include "Attribute.hpp"

namespace rlrpg
{
	typedef unsigned id_t;

	class Generated
	{
		id_t m_gen_id;
		attr_t m_gen_luck;
	public:
		/* Initializes the object so that it has no id. */
		Generated();
		Generated(id_t gen_id, attr_t gen_luck);

		/* Only works if the instance did not have an id before. */
		void set_gen_params(id_t gen_id, attr_t gen_luck);
		/* Fails if the instance did not have an id before. */
		id_t gen_id() const;
		/* Fails if the instance did not have an id before. */
		attr_t gen_luck() const;

		/* Whether this instance has an id or not. */
		bool is_generated() const;
	};

}

#endif
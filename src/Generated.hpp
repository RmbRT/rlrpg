#ifndef __rlrpg_generated_hpp_defined
#define __rlrpg_generated_hpp_defined

#include <cinttypes>

namespace rlrpg
{
	typedef std::uint32_t id_t;

	class Generated
	{
		/* The id of the generated object. */
		id_t m_gen_id;
	public:
		/* Initializes the object so that it has no id. */
		Generated();
		explicit Generated(id_t gen_id);

		/* Only works if the instance did not have an id before. */
		void set_gen_id(id_t gen_id);
		/* Fails if the instance did not have an id before. */
		id_t gen_id() const;

		/* Whether this instance has an id or not. */
		bool is_generated() const;
	};

}

#endif
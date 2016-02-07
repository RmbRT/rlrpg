#include "Generated.hpp"
#include <cassert>


namespace rlrpg
{
	Generated::Generated() : m_gen_id(~id_t(0)) { }
	Generated::Generated(id_t gen_id):
		m_gen_id(gen_id) { assert(is_generated() && "initialized instance with invalid id."); }

	void Generated::set_gen_id(id_t gen_id)
	{
		assert(~gen_id && "trying to register an invalid id.");
		assert(!is_generated() && "trying to override a valid id.");
		m_gen_id = gen_id;
	}

	id_t Generated::gen_id() const
	{
		assert(is_generated() && "trying to read invalid id.");
		return m_gen_id;
	}

	bool Generated::is_generated() const
	{
		return ~m_gen_id;
	}
}
#include "Generated.hpp"
#include <cassert>


namespace rlrpg
{
	Generated::Generated() : m_gen_id(~id_t(0)) { }
	Generated::Generated(id_t gen_id, attr_t gen_luck):
		m_gen_id(gen_id),
		m_gen_luck(gen_luck) { assert(is_generated() && "initialized instance with invalid id."); }

	void Generated::set_gen_params(id_t gen_id, attr_t gen_luck)
	{
		assert(~gen_id && "trying to register an invalid id.");
		assert(!is_generated() && "trying to override a valid id.");
		m_gen_id = gen_id;
		m_gen_luck = gen_luck;
	}

	id_t Generated::gen_id() const
	{
		assert(is_generated() && "trying to read invalid id.");
		return m_gen_id;
	}

	attr_t Generated::gen_luck() const
	{
		assert(is_generated() && "trying to read luck of uninitialized instance.");
		return m_gen_luck;
	}

	bool Generated::is_generated() const
	{
		return ~m_gen_id;
	}
}
#include "Registered.hpp"


namespace rlrpg
{
	id_t Registered::s_id_counter = 0;

	Registered::Registered() : m_id(0) { }
	id_t Registered::id() const
	{
		return m_id ? m_id : (m_id = ++s_id_counter);
	}

	bool Registered::has_id() const { return m_id; }

	id_t Registered::id_counter() { return s_id_counter; }
}
#ifndef __rlrpg_registered_hpp_defined
#define __rlrpg_registered_hpp_defined


namespace rlrpg
{
	typedef unsigned id_t;

	class Registered
	{
		mutable id_t m_id; // lazy generation.
		static id_t s_id_counter; // used to create new ids.
	public:
		Registered();

		id_t id() const;

		bool has_id() const;

		static id_t id_counter();
	};

}

#endif
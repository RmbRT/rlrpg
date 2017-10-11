#include <cassert>
namespace rlrpg
{
	template<class T>
	Optional<T>::Optional():
		m_exists(false)
	{
	}

	template<class T>
	Optional<T>::Optional(empty_t):
		m_exists(false)
	{
	}

	template<class T>
	Optional<T>::Optional(default_t):
		m_exists(false)
	{
		in_place();
	}

	template<class T>
	template<class ...Args>
	Optional<T>::Optional(Args &&... args):
		m_exists(true)
	{
		new (m_instance) T(std::forward<Args>(args)...);
	}

	template<class T>
	Optional<T>::operator bool() const
	{
		return m_exists;
	}

	template<class T>
	template<class ...Args>
	void Optional<T>::in_place(Args && ... args)
	{
		if(m_exists)
		{
			reinterpret_cast<T&>(m_instance[0]) = T(std::forward<Args>(args)...);
		} else
		{
			new (m_instance) T(std::forward<Args>(args)...);
			m_exists = true;
		}
	}

	template<class T>
	T const& Optional<T>::operator()() const
	{
		assert(m_exists && "Tried to access empty object.");
		return reinterpret_cast<T const&>(m_instance[0]);
	}

	template<class T>
	T & Optional<T>::operator()()
	{
		assert(m_exists && "Tried to access empty object.");
		return reinterpret_cast<T &>(m_instance[0]);
	}

	template<class T>
	Optional<T>::~Optional()
	{
		if(m_exists)
			reinterpret_cast<T*>(m_instance)->~T();
	}

	template<class T>
	Optional<T> &Optional<T>::operator=(empty_t)
	{
		if(m_exists)
		{
			reinterpret_cast<T*>(m_instance)->~T();
			m_exists = false;
		}
	}
}
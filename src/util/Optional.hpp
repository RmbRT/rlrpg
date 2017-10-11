#ifndef __rlrpg_util_optional_hpp_defined
#define __rlrpg_util_optional_hpp_defined

#include <cinttypes>

namespace rlrpg
{
	struct empty_t {} const kEmpty;
	struct default_t {} const kDefault;

	template<class T>
	class Optional
	{
		std::uint8_t m_instance[sizeof(T)];
		bool m_exists;
	public:
		Optional();
		Optional(empty_t);
		Optional(default_t);
		Optional(Optional const&) = default;
		Optional(Optional &&) = default;

		template<class ...Args>
		Optional(Args &&... args);

		operator bool() const;

		template<class ...Args>
		void in_place(Args &&... args);

		T const& operator()() const;
		T &operator()();

		~Optional();

		Optional<T> &operator=(Optional<T> const&) = default;
		Optional<T> &operator=(Optional<T> &&) = default;

		Optional<T> &operator=(empty_t);
	};
}

#include "Optional.inl"

#endif
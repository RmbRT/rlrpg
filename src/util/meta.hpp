#ifndef __rlrpg_util_meta_hpp_defined
#define __rlrpg_util_meta_hpp_defined

namespace rlrpg
{
	namespace util
	{
		template<bool e, bool ...rest>
		struct Each
		{
			enum { value = e && Each<rest...>::value };
		};

		template<bool e>
		struct Each<e>
		{
			enum { value = e };
		};

		template<bool e, bool ...rest>
		struct Any
		{
			enum { value = e || Any<rest...>::value };
		};

		template<bool e>
		struct Any<e>
		{
			enum { value = e };
		};
	}
}

#endif
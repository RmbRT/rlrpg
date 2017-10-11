#ifndef __rlrpg_math_vector_hpp_defined
#define __rlrpg_math_vector_hpp_defined

#include "../defines.hpp"

#include <cstddef>
#include <cmath>

#if __cplusplus > 201103l
/*c++14 is needed for the conversion to a native c++ array (instead of operator[]).*/
#define RLRPG_NATIVE_ARRAY_CONVERSION
#endif

#ifndef RLRPG_NATIVE_ARRAY_CONVERSION
#include <cassert>
#endif

namespace rlrpg
{
	namespace math
	{
		template<std::size_t DIM, typename T>
		struct vec
		{
			enum { Dimension = DIM };
			typedef T array[DIM];

			vec() = default;
			explicit vec(T const& v) { for(T & val : m_v) val = v; }

			vec(array const& v) : vec(reinterpret_cast<vec<DIM,T>const&>(v[0])) { }

			template<class O>
			vec(vec<DIM,O> const& v) { for(T & val : m_v) val = (T const&) v; }

			template<std::size_t LOWERDIM>
			vec(vec<LOWERDIM,T> const& lower, vec<DIM-LOWERDIM, T> const& upper)
			{
				subvec<LOWERDIM,0>() = lower;
				subvec<DIM-LOWERDIM, LOWERDIM>() = upper;
			}

#ifdef RLRPG_NATIVE_ARRAY_CONVERSION
			// native array subscript operation.
			forceinline operator array&() { return m_v; }
			forceinline operator array const&() const { return m_v; }
#else // non-native array subscript.
			forceinline T& operator[](size_t i) { assert(i<DIM); return m_v[i]; }
			forceinline T const& operator[](size_t i) const { assert(i<DIM); return m_v[i]; }
#endif
			template<std::size_t LOWERDIM>
			forceinline operator vec<LOWERDIM, T> &() { return subvec<LOWERDIM>(); }

			template<std::size_t LOWERDIM>
			forceinline operator vec<LOWERDIM, T> const&() const { return subvec<LOWERDIM>(); }

			template<std::size_t LOWERDIM, std::size_t OFFSET = 0>
			forceinline vec<LOWERDIM,T> & subvec() { static_assert(OFFSET + LOWERDIM <= DIM && LOWERDIM > 0, "invalid template parameter.");
				return reinterpret_cast<vec<LOWERDIM,T> &>((*this)[OFFSET]);
			}

			template<std::size_t LOWERDIM, std::size_t OFFSET = 0>
			forceinline vec<LOWERDIM,T> const& subvec() const { static_assert(OFFSET + LOWERDIM <= DIM && LOWERDIM > 0, "invalid template parameter.");
				return reinterpret_cast<vec<LOWERDIM,T> const&>((*this)[OFFSET]);
			}

			forceinline vec<DIM,T> &operator<<=(signed shift)
			{
				for(T& v: m_v)
					v = v<<shift;
				return *this;
			}
			forceinline vec<DIM,T> &operator>>=(signed shift)
			{
				for(T& v: m_v)
					v = v>>shift;
				return *this;
			}
			forceinline vec<DIM,T> operator<<(signed shift) const
			{
				return vec<DIM,T>(*this) <<= shift;
			}

			forceinline vec<DIM,T> operator>>(signed shift) const
			{
				return vec<DIM,T>(*this) >>= shift;
			}

		private:
			array m_v;
		};


		/* Manhattan distance of a vector. Equals to the sum of the absolute value of all components. */
		template<std::size_t DIM, typename T>
		forceinline T man(vec<DIM,T> const& v)
		{
			T dist = 0;
			for(T const& t : v)
				dist += std::abs(t);
			return dist;
		}

		template<std::size_t DIM, typename T>
		forceinline vec<DIM, T> operator+(vec<DIM,T> const& a, vec<DIM,T> const& b)
		{
			vec<DIM, T> temp;
			for(std::size_t i = DIM; i--;)
				temp[i] = a[i] + b[i];

			return temp;
		}

		template<std::size_t DIM, typename T>
		forceinline vec<DIM, T> &operator+=(vec<DIM,T> &self, vec<DIM,T> const& rhs)
		{
			for(std::size_t i = DIM; i--;)
				self[i] += rhs[i];

			return self;
		}

		template<std::size_t DIM, typename T>
		forceinline vec<DIM, T> operator-(vec<DIM,T> const& a, vec<DIM,T> const& b)
		{
			vec<DIM,T> temp;
			for(std::size_t i = DIM; i--;)
				temp[i] = a[i] - b[i];

			return temp;
		}

		template<std::size_t DIM, typename T>
		forceinline T dot(vec<DIM,T> const& a, vec<DIM,T> const& b)
		{
			T temp = 0;
			for(std::size_t i = DIM; i--;)
				temp += a[i] * b[i];

			return temp;
		}

		template<std::size_t DIM, typename T>
		forceinline bool operator==(vec<DIM,T> const& a, vec<DIM,T> const& b)
		{
			for(std::size_t i = DIM; i--;)
				if(a[i] != b[i])
					return false;
			return true;
		}
		template<std::size_t DIM, typename T>
		forceinline bool operator!=(vec<DIM,T> const& a, vec<DIM,T> const& b)
		{
			for(std::size_t i = DIM; i--;)
				if(a[i] != b[i])
					return true;
			return false;
		}
		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> scale(vec<DIM,T> const& a, vec<DIM,U> const& b)
		{
			vec<DIM,T> temp;
			for(std::size_t i = DIM; i--;)
				temp[i] = a[i] * b[i];
			return temp;
		}

		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> &operator*=(vec<DIM,T> &self, U const& factor)
		{
			for(std::size_t i = DIM; i--;)
				self[i] *= factor;
			return self;
		}

		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> operator*(vec<DIM,T> const& self, U const& factor)
		{
			vec<DIM,T> temp(self);
			temp *= factor;
			return temp;
		}

		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> operator*(U const& factor, vec<DIM,T> const& self)
		{
			return vec<DIM,T>(self) *= factor;
		}

		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> &operator/=(vec<DIM,T> &self, U const& factor)
		{
			for(T& v: self.m_v)
				v /= factor;
			return self;
		}

		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> operator/(vec<DIM,T> const& self, U const& factor)
		{
			return vec<DIM,T>(self) /= factor;
		}

		template<std::size_t DIM, typename T, typename U>
		forceinline vec<DIM,T> operator/(U const& factor, vec<DIM,T> const& self)
		{
			return vec<DIM,T>(self) /= factor;
		}
	}
}

#endif
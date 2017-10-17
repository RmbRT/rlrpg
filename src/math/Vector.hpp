#ifndef __rlrpg_math_vector_hpp_defined
#define __rlrpg_math_vector_hpp_defined

#include "../defines.hpp"
#include "../util/meta.hpp"

#include <type_traits>
#include <cstddef>
#include <cmath>

namespace rlrpg
{
	namespace math
	{
		template<std::size_t kDim, class T>
		/** Vector class. */
		class Vector
		{
			/** The vector's elements. */
			T m_elements[kDim];
		public:
			/** The vector's dimension. */
			enum { kDimension = kDim };
			/** The vector's element type. */
			typedef T elem_t;

			/** Creates a zero vector. */
			Vector() = default;
			/** Creates a vector with all elements set to `value`.
			@param[in] value:
				The value of each of the vector's elements. */
			Vector(
				T const& value);
			/** Creates a vector with the given components.
			@tparam Args:
				The argument types. Must be the same number as `kDimension` and convertible to `T`.
			@param values:
				The arguments to initialise the elements with. */
			template<class ...Args, class = typename std::enable_if<
				sizeof...(Args) == kDim
				&& util::Each<std::is_convertible<Args, T>::value...>::value, void>::type>
			Vector(
				Args && ...values);

			/** Returns the `i`-th element.
			@param[in] i:
				The index.
			@retunr
				The `i`-th element. */
			inline T & operator[](
				std::size_t i);

			/** Returns the `i`-th element.
			@param[in] i:
				The index.
			@retunr
				The `i`-th element. */
			inline T const& operator[](
				std::size_t i) const;

			/** Adds two vectors.
			@param[in] rhs:
				The vector to add.
			@return
				The sum vector. */
			Vector<kDim, T> operator+(
				Vector<kDim, T> const& rhs) const;
			/** Adds a vector to `this`.
			@param[in] rhs:
				The vector to add to `this`.
			@return
				`this`, after `rhs` was added to it. */
			Vector<kDim, T> &operator+=(
				Vector<kDim, T> const& rhs);

			/** Subtracts a vector from `this`.
			@param[in] rhs:
				The vector to subtract from `this`.
			@return
				The difference between `this` and `rhs`. */
			Vector<kDim, T> operator-(
				Vector<kDim, T> const& rhs) const;
			/** Subtracts a vector from `this`.
			@param[in] rhs:
				The vector to subtract from `this`.
			@return
				`this`, after `rhs` was subtracted from it. */
			Vector<kDim, T> &operator-=(
				Vector<kDim, T> const& rhs);

			template<std::size_t size, std::size_t start = 0, class = typename std::enable_if<size + start < kDim, void>::type>
			/** Retrieves a subvector.
			@tparam size:
				The dimension of the subvector.
			@tparam start:
				Optional, the beginning index of the subvector.
			@return
				A subvector ranging over indices `[start, start+size]`. */
			inline Vector<size, T> & subvec();

			template<std::size_t size, std::size_t start = 0, class = typename std::enable_if<size + start < kDim, void>::type>
			/** Retrieves a subvector.
			@tparam size:
				The dimension of the subvector.
			@tparam start:
				Optional, the beginning index of the subvector.
			@return
				A subvector ranging over indices `[start, start+size]`. */
			inline Vector<size, T> const& subvec() const;
		};

		template<std::size_t kDim, class T, class S, class = typename std::enable_if<std::is_arithmetic<S>::value, void>::type>
		/** Multiplies a vector's elements by a given scale factor.
		@param[in] scale:
			The factor to scale the vector by.
		@param[in] v:
			The vector to scale.
		@return
			The scaled vector. */
		Vector<kDim, T> operator*(
			S const& scale,
			Vector<kDim, T> const& v);


		template<std::size_t kDim, class T>
		/** Calculates the dot product.
		@param[in] a:
			The first vector.
		@param[in] b:
			The second vector.
		@return
			The dot product. */
		T dot(
			Vector<kDim, T> const& a,
			Vector<kDim, T> const& b);

		template<class T, class ...Args>
		/** Short-hand constructor for vectors.
		@tparam T:
			The type of the vector.
		@param[in] args:
			The arguments to construct a vector.
		@return
			A vector of type `T` and the given values. */
		inline Vector<sizeof...(Args), T> vec(
			Args && ... args);
	}
}

#include "Vector.inl"

#endif
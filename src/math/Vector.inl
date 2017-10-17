namespace rlrpg
{
	namespace math
	{
		template<std::size_t kDim, class T>
		Vector<kDim, T>::Vector(
			T const& value)
		{
			for(T & elem : m_elements)
				elem = value;
		}

		template<std::size_t kDim, class T>
		template<class ...Args, typename>
		Vector<kDim, T>::Vector(
			Args && ...values) : m_elements { std::forward<Args>(values)... }
		{
		}

		template<std::size_t kDim, class T>
		T & Vector<kDim, T>::operator[](
			std::size_t i)
		{
			return m_elements[i];
		}

		template<std::size_t kDim, class T>
		T const& Vector<kDim, T>::operator[](
			std::size_t i) const
		{
			return m_elements[i];
		}

		template<std::size_t kDim, class T>
		Vector<kDim, T> Vector<kDim, T>::operator+(
			Vector<kDim, T> const& rhs) const
		{
			return Vector<kDim, T>(*this) += rhs;
		}

		template<std::size_t kDim, class T>
		Vector<kDim, T> &Vector<kDim, T>::operator+=(
			Vector<kDim, T> const& rhs)
		{
			for(std::size_t i = 0; i < kDim; i++)
				m_elements[i] += rhs.m_elements[i];
			return *this;
		}

		template<std::size_t kDim, class T>
		Vector<kDim, T> Vector<kDim, T>::operator-(
			Vector<kDim, T> const& rhs) const
		{
			return Vector<kDim, T>(*this) -= rhs;
		}

		template<std::size_t kDim, class T>
		Vector<kDim, T> &Vector<kDim, T>::operator-=(
			Vector<kDim, T> const& rhs)
		{
			for(std::size_t i = 0; i < kDim; i++)
				m_elements[i] -= rhs.m_elements[i];
			return *this;
		}

		template<std::size_t kDim, class T>
		template<std::size_t size, std::size_t start, class>
		Vector<size, T> &Vector<kDim, T>::subvec()
		{
			return reinterpret_cast<Vector<size, T> &>(
				m_elements[start]);
		}

		template<std::size_t kDim, class T>
		template<std::size_t size, std::size_t start, class>
		Vector<size, T> const& Vector<kDim, T>::subvec() const
		{
			return reinterpret_cast<Vector<size, T> const&>(
				m_elements[start]);
		}

		template<std::size_t kDim, class T, class S, class>
		Vector<kDim, T> operator*(
			S const& scale,
			Vector<kDim, T> const& v)
		{
			Vector<kDim, T> result;
			for(std::size_t i = 0; i < kDim; i++)
				result[i] = scale * v[i];

			return result;
		}

		template<std::size_t kDim, class T>
		T dot(
			Vector<kDim, T> const& a,
			Vector<kDim, T> const& b)
		{
			T result = 0;
			for(std::size_t i = 0; i < kDim; i++)
				result += a[i] * b[i];

			return result;
		}

		template<class T, class ...Args>
		Vector<sizeof...(Args), T> vec(
			Args && ... args)
		{
			return Vector<sizeof...(Args), T>(
				std::forward<Args>(args)...);
		}
	}
}
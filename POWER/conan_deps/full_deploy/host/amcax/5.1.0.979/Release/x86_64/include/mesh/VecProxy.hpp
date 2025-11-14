
#pragma once
#include <common/CoordT.hpp>

namespace AMCAX
{
	template<size_t DIM, typename T>
	class VecProxy : public CoordT<T, DIM>
	{
	public:
		using Base = CoordT<T, DIM>;
		using NT = T;
		using VT = VecProxy<DIM, T>;
		static constexpr size_t size_ = DIM;
		using value_type = T;
		using vector_type = VT;

	public:
		constexpr VecProxy() = default;

		constexpr VecProxy(const Base& c)
			: Base(c)
		{
		}

		constexpr VecProxy(Base&& c)
			: Base(c)
		{
		}

		constexpr explicit VecProxy(const T* v) noexcept
		{
			const T* first = v;
			for (auto it = Base::begin(); it != Base::end(); it++, first++)
			{
				*it = *first;
			}
		}

		constexpr explicit VecProxy(const T& v0) noexcept
		{
			vectorize(v0);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ == 2>>
		constexpr explicit VecProxy(NT v0, NT v1) noexcept
			: Base(v0, v1)
		{
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ == 3>>
		constexpr explicit VecProxy(NT v0, NT v1, NT v2) noexcept
			: Base(v0, v1, v2)
		{
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ == 4>>
		constexpr explicit VecProxy(NT v0, NT v1, NT v2, NT v3) noexcept
			: Base(v0, v1, v2, v3)
		{
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 1>>
		constexpr T& x()
		{
			return operator[](0);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 2>>
		constexpr T& y()
		{
			return operator[](1);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 3>>
		constexpr T& z()
		{
			return operator[](2);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 4>>
		constexpr T& w()
		{
			return operator[](3);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 1>>
		constexpr const T& x() const
		{
			return operator[](0);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 2>>
		constexpr const T& y() const
		{
			return operator[](1);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 3>>
		constexpr const T& z() const
		{
			return operator[](2);
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ >= 4>>
		constexpr const T& w() const
		{
			return operator[](3);
		}

		constexpr size_t size() const
		{
			return size_;
		}

		constexpr T* data()
		{
			return Base::Data();
		}
		constexpr const T* data() const
		{
			return Base::Data();
		}

		constexpr T& operator[](size_t dim)
		{
			return Base::operator[](static_cast<int>(dim));
		}

		constexpr const T& operator[](size_t dim) const
		{
			return Base::operator[](static_cast<int>(dim));
		}

		VT& operator+=(const VT& rhs)
		{
			return static_cast<VT&>(Base::operator+=(rhs));
		}

		VT& operator-=(const VT& rhs)
		{
			return static_cast<VT&>(Base::operator-=(rhs));
		}

		VT& operator*=(const VT& rhs)
		{
			return static_cast<VT&>(Base::operator*=(rhs));
		}

		VT& operator*=(const T& rhs)
		{
			return static_cast<VT&>(Base::operator*=(rhs));
		}

		VT& operator/=(const VT& rhs)
		{
			return static_cast<VT&>(Base::operator/=(rhs));
		}

		VT& operator/=(const T& rhs)
		{
			return static_cast<VT&>(Base::operator/=(rhs));
		}

		VT operator+(const VT& rhs) const
		{
			return static_cast<VT&&>(Base::operator+(rhs));
		}

		VT operator-(const VT& rhs) const
		{
			return static_cast<VT&&>(Base::operator-(rhs));
		}

		VT operator*(const VT& rhs) const
		{
			return static_cast<VT&&>(Base::operator*(rhs));
		}

		VT operator*(const T& rhs) const
		{
			return static_cast<VT&&>(Base::operator*(rhs));
		}

		VT operator/(const VT& rhs) const
		{
			return static_cast<VT&&>(Base::operator/(rhs));
		}

		VT operator/(const T& rhs) const
		{
			return static_cast<VT&&>(Base::operator/(rhs));
		}

		VT operator-() const
		{
			return static_cast<VT&&>(Base::operator-());
		}

		friend VT operator*(const T& d, const VT& rhs)
		{
			return static_cast<VT&&>(rhs * d);
		}

		constexpr bool less_on(size_t dim, const VT& rhs) const
		{
			return (this->operator[](dim) < rhs[dim]);
		}
		constexpr bool less_on(size_t dim, const T& rhs) const
		{
			return (this->operator[](dim) < rhs);
		}

		void minimize(const VT& rhs)
		{
			Minimize(rhs);
		}

		void maximize(const VT& rhs)
		{
			Maximize(rhs);
		}

		constexpr VT& vectorize(const T& s)
		{
			return static_cast<VT&>(fill(s));
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ == 3>>
		auto cross(const VT& rhs) const
		{
			return static_cast<VT&&>(Base::Cross(rhs));
		}

		template<size_t X_ = DIM, typename = std::enable_if_t<X_ == 3>>
		auto operator%(const VT& rhs) const
		{
			return static_cast<VT&&>(Base::operator%(rhs));
		}

		T dot(const VT& rhs) const
		{
			return this->Dot(rhs);
		}
		T operator|(const VT& rhs) const
		{
			return dot(rhs);
		}
		T sqrnorm() const
		{
			return Base::SquaredNorm();
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		inline VT& normalize()
		{
			return static_cast<VT&>(Base::Normalize());
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		inline VT normalized() const
		{
			return static_cast<VT&&>(Base::Normalized());
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		T norm() const
		{
			return Base::Norm();
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		T length() const
		{
			return norm();
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		VT pow(const T& exp) const
		{
			VT result;
			for (size_t i = 0; i < DIM; i++)
			{
				result[i] = std::pow(operator[](i), exp);
			}
			return result;
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		T pnorm(const T& exp) const
		{
			T result(0);
			for (auto& left : *this)
			{
				result += std::pow(std::abs(left), exp);
			}
			return std::pow(result, 1. / exp);
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		bool isfinite() const
		{
			for (auto& elem : *this)
			{
				if (!std::isfinite(elem))
				{
					return false;
				}
			}
			return true;
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		VT floor() const
		{
			VT result;
			for (size_t i = 0; i < DIM; i++)
			{
				result[i] = std::floor(operator[](i));
			}
			return result;
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		VT ceil() const
		{
			VT result;
			for (size_t i = 0; i < DIM; i++)
			{
				result[i] = std::ceil(operator[](i));
			}
			return result;
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		VT round() const
		{
			VT result;
			for (size_t i = 0; i < DIM; i++)
			{
				result[i] = std::round(operator[](i));
			}
			return result;
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		VT abs() const
		{
			VT result;
			for (size_t i = 0; i < DIM; i++)
			{
				result[i] = std::abs(operator[](i));
			}
			return result;
		}

		template<typename U = T, typename = std::enable_if_t<std::is_floating_point_v<U>>>
		VT& negate()
		{
			for (auto& res : *this)
			{
				res = -res;
			}
			return *this;
		}
	};
} // namespace AMCAX

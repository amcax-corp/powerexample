/// @file      Precision.hpp
/// @brief     Class of precision
/// @details   Functions of precision criteria for comparing two numbers
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <cmath>
#include <limits>

namespace AMCAX
{
/// @brief Functions of precision criteria for comparing two numbers
class Precision
{
public:
	/// @brief Get the angular tolerance
	/// @return The angular tolerance
	static constexpr double Angular() noexcept;

	/// @brief Get the confusion tolerance
	/// @return The confusion tolerance
	static constexpr double Confusion() noexcept;

	/// @brief Get the confusion tolerance in the 2D parametric space
	/// @param t The precision ratio
	/// @return The confusion tolerance in the 2D parametric space
	static constexpr double PConfusion(double t) noexcept;

	/// @brief Get the confusion tolerance in the 2D parametric space
	/// @return The confusion tolerance in the 2D parametric space
	static constexpr double PConfusion() noexcept;

	/// @brief Get the squared confusion tolerance
	/// @return The squared confusion tolerance
	static constexpr double SquaredConfusion() noexcept;

	/// @brief Get the squared confusion tolerance in the 2D parametric space
	/// @return The squared confusion tolerance in the 2D parametric space
	static constexpr double SquaredPConfusion() noexcept;

	/// @brief Get the intersection tolerance
	/// @return The intersection tolerance
	static constexpr double Intersection() noexcept;

	/// @brief Get the intersection tolerance in the 2D parametric space
	/// @param t The precision ratio
	/// @return The intersection tolerance in the 2D parametric space
	static constexpr double PIntersection(double t) noexcept;

	/// @brief Get the intersection tolerance in the 2D parametric space
	/// @return The intersection tolerance in the 2D parametric space
	static constexpr double PIntersection() noexcept;

	/// @brief Get the approximation tolerance
	/// @return The approximation tolerance
	static constexpr double Approximation() noexcept;

	/// @brief Get the approximation tolerance in the 2D parametric space
	/// @param t The precision ratio
	/// @return The approximation tolerance in the 2D parametric space
	static constexpr double PApproximation(double t) noexcept;

	/// @brief Get the approximation tolerance in the 2D parametric space
	/// @return The approximation tolerance in the 2D parametric space
	static constexpr double PApproximation() noexcept;

	/// @brief Compute the precision in the parametric space
	/// @param p The precision in the 3D space
	/// @param t The precision ratio
	/// @return The precision in the 2D parametric space
	static constexpr double Parametric(double p, double t) noexcept;

	/// @brief Compute the precision in the parametric space
	/// @param p The precision in the 3D space
	/// @return The precision in the 2D parametric space
	static constexpr double Parametric(double p) noexcept;

	/// @brief Get the positive infinity
	/// @return The positive infinity
	static constexpr double PositiveInfinity() noexcept;

	/// @brief Get the negative infinity
	/// @return The negative infinity
	static constexpr double NegativeInfinity() noexcept;

	/// @brief Determine whether a value is infinity
	/// @param r The test value
	/// @return True if the value is infinity
	static constexpr bool IsInfinity(double r) noexcept;

	/// @brief Determine whether a value is positive infinity
	/// @param r The test value
	/// @return True if the value is positive infinity
	static constexpr bool IsPositiveInfinity(double r) noexcept;

	/// @brief Determine whether a value is negative infinity
	/// @param r The test value
	/// @return True if the value is negative infinity
	static constexpr bool IsNegativeInfinity(double r) noexcept;

	/// @brief Compute the epsilon of a real number in double precision
	/// @param v The real number
	/// @return The epsilon of the real number
	static double Epsilon(double v) noexcept;

private:
	/// @brief The range of infinity
	static constexpr double infinity = 2e100;

	/// @brief The angle tolerance
	static constexpr double angleTol = 1e-12;

	/// @brief The confusion tolerance
	static constexpr double confusion = 1e-7;
};

constexpr double Precision::Angular() noexcept
{
	return angleTol;
}

constexpr double Precision::Confusion() noexcept
{
	return confusion;
}

constexpr double Precision::PConfusion(double t) noexcept
{
	return Parametric(Confusion(), t);
}

constexpr double Precision::PConfusion() noexcept
{
	return Parametric(Confusion());
}

constexpr double Precision::SquaredConfusion() noexcept
{
	return Confusion() * Confusion();
}

constexpr double Precision::SquaredPConfusion() noexcept
{
	return PConfusion() * PConfusion();
}

constexpr double Precision::Intersection() noexcept
{
	return Confusion() * 0.01;
}

constexpr double Precision::PIntersection(double t) noexcept
{
	return Parametric(Intersection(), t);
}

constexpr double Precision::PIntersection() noexcept
{
	return Parametric(Intersection());
}

constexpr double Precision::Approximation() noexcept
{
	return Confusion() * 10.0;
}

constexpr double Precision::PApproximation(double t) noexcept
{
	return Parametric(Approximation(), t);
}

constexpr double Precision::PApproximation() noexcept
{
	return Parametric(Approximation());
}

constexpr double Precision::Parametric(double p, double t) noexcept
{
	return p / t;
}

constexpr double Precision::Parametric(double p) noexcept
{
	return Parametric(p, 100.0);
}

constexpr double Precision::PositiveInfinity() noexcept
{
	return 0.5 * infinity;
}

constexpr double Precision::NegativeInfinity() noexcept
{
	return -PositiveInfinity();
}

constexpr bool Precision::IsInfinity(double r) noexcept
{
	return (r <= 0 ? -r : r) >= PositiveInfinity();
}

constexpr bool Precision::IsPositiveInfinity(double r) noexcept
{
	return r >= PositiveInfinity();
}

constexpr bool Precision::IsNegativeInfinity(double r) noexcept
{
	return r <= NegativeInfinity();
}

inline double Precision::Epsilon(double v) noexcept
{
	double y{v};
	char* t = reinterpret_cast<char*>(&y);
	++(*reinterpret_cast<long long*>(t));
	return std::fabs(y - v);
}
} // namespace AMCAX

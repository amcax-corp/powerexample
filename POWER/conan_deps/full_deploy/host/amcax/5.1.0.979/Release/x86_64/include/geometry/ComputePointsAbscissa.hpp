/// @file      ComputePointsAbscissa.hpp
/// @brief     Class of compute the parameter of a point on a curve of given arc length
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Adaptor2Curve;
class Adaptor3Curve;
#ifndef DOXYGEN_SKIP
class ComputePointsAbscissaImpl;
#endif

/// @brief Class of compute the parameter of a point on a curve of given arc length
class ComputePointsAbscissa
{
public:
	/// @brief Compute the parameter of a point on a 3D curve with given arc length and a tolerance
	/// @param tol The tolerance
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	AMCAX_API ComputePointsAbscissa(double tol, const Adaptor3Curve& c, double abscissa, double u0);

	/// @brief Compute the parameter of a point on a 2D curve with given arc length and a tolerance
	/// @param tol The tolerance
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	AMCAX_API ComputePointsAbscissa(double tol, const Adaptor2Curve& c, double abscissa, double u0);

	/// @brief Compute the parameter of a point on a 3D curve with given arc length
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	AMCAX_API ComputePointsAbscissa(const Adaptor3Curve& c, double abscissa, double u0);

	/// @brief Compute the parameter of a point on a 2D curve with given arc length
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	AMCAX_API ComputePointsAbscissa(const Adaptor2Curve& c, double abscissa, double u0);

	/// @brief Compute the parameter of a point on a 3D curve with given arc length and an initial guess
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	/// @param ui The initial guess of the parameter
	AMCAX_API ComputePointsAbscissa(const Adaptor3Curve& c, double abscissa, double u0, double ui);

	/// @brief Compute the parameter of a point on a 2D curve with given arc length and an initial guess
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	/// @param ui The initial guess of the parameter
	AMCAX_API ComputePointsAbscissa(const Adaptor2Curve& c, double abscissa, double u0, double ui);

	/// @brief Compute the parameter of a point on a 3D curve with given arc length, an initial guess, and a tolerance
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	/// @param ui The initial guess of the parameter
	/// @param tol The tolerance
	AMCAX_API ComputePointsAbscissa(const Adaptor3Curve& c, double abscissa, double u0, double ui, double tol);

	/// @brief Compute the parameter of a point on a 2D curve with given arc length, an initial guess, and a tolerance
	/// @param c The curve
	/// @param abscissa The arc length
	/// @param u0 The starting parameter
	/// @param ui The initial guess of the parameter
	/// @param tol The tolerance
	AMCAX_API ComputePointsAbscissa(const Adaptor2Curve& c, double abscissa, double u0, double ui, double tol);

	/// @brief Is the computation done
	/// @return True if the computation done
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Get the parameter of the point
	/// @return The parameter of the point
	[[nodiscard]] AMCAX_API double Parameter() const;

	/// @brief Compute the length of a 3D curve
	/// @param c The curve
	/// @return The length of a curve
	[[nodiscard]] AMCAX_API static double Length(const Adaptor3Curve& c);

	/// @brief Compute the length of a 2D curve
	/// @param c The curve
	/// @return The length of a curve
	[[nodiscard]] AMCAX_API static double Length(const Adaptor2Curve& c);

	/// @brief Compute the length of a 3D curve with a tolerance
	/// @param c The curve
	/// @param tol The tolerance
	/// @return The length of a curve
	[[nodiscard]] AMCAX_API static double Length(const Adaptor3Curve& c, double tol);

	/// @brief Compute the length of a 2D curve with a tolerance
	/// @param c The curve
	/// @param tol The tolerance
	/// @return The length of a curve
	[[nodiscard]] AMCAX_API static double Length(const Adaptor2Curve& c, double tol);

	/// @brief Compute the length of a 3D curve in a given interval
	/// @param c The curve
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	/// @return The length of a curve in a given interval
	[[nodiscard]] AMCAX_API static double Length(const Adaptor3Curve& c, double u1, double u2);

	/// @brief Compute the length of a 2D curve in a given interval
	/// @param c The curve
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	/// @return The length of a curve in a given interval
	[[nodiscard]] AMCAX_API static double Length(const Adaptor2Curve& c, double u1, double u2);

	/// @brief Compute the length of a 3D curve in a given interval with a tolerance
	/// @param c The curve
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	/// @param tol The tolerance
	/// @return The length of a curve in a given interval
	[[nodiscard]] AMCAX_API static double Length(const Adaptor3Curve& c, double u1, double u2, double tol);

	/// @brief Compute the length of a 2D curve in a given interval with a tolerance
	/// @param c The curve
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	/// @param tol The tolerance
	/// @return The length of a curve in a given interval
	[[nodiscard]] AMCAX_API static double Length(const Adaptor2Curve& c, double u1, double u2, double tol);

private:
	template<class AdaptorType>
	static double Length(const AdaptorType& c, double u1, double u2, const double* tol);
	template<class AdaptorType>
	void Compute(const AdaptorType& c, double abscissa, double u0);
	template<class AdaptorType>
	void Compute(double tol, const AdaptorType& c, double abscissa, double u0);
	std::shared_ptr<ComputePointsAbscissaImpl> computer;
};
} // namespace AMCAX

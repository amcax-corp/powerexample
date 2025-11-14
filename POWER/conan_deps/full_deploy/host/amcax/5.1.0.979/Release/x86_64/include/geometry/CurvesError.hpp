/// @file      CurvesError.hpp
/// @brief     The class of curves error calculation
/// @details   This class computes the error of the two curves
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
class Adaptor3Curve;

/// @brief Calculate the error of approximation
class CurvesError
{
public:
	/// @brief Constructor
	/// @param curve1 The first curve
	/// @param curve2 The second curve
	/// @param nsample The number of sample points
	AMCAX_API CurvesError(const Adaptor3Curve& curve1, const Adaptor3Curve& curve2, int nsample = 1000);

	/// @brief Get the maximum error of the two curves
	/// @return The maximum error
	[[nodiscard]] AMCAX_API double MaxError() const noexcept;

	/// @brief Get the parameters whose error is the maximum
	/// @return The first curve parameter and the second curve parameter
	[[nodiscard]] AMCAX_API std::pair<double, double> MaxErrorParameters() const noexcept;

	/// @brief Get the sample point ID whose error is the maximum
	/// @return The curve sample point ID whose error is the maximum
	[[nodiscard]] AMCAX_API int MaxErrorSamplePointIDs() const noexcept;

	/// @brief Get the sample points whose error is the maximum
	/// @return The first curve point and the second curve point whose error is the maximum
	[[nodiscard]] AMCAX_API std::pair<Point3, Point3> MaxErrorSamplePoints() const noexcept;

	/// @brief Get the number of the sample points
	/// @return The number of the sample points
	[[nodiscard]] AMCAX_API int NSample() const noexcept;

	/// @brief Get the sample parameters of curve 1
	/// @return The sample parameters of curve 1
	[[nodiscard]] AMCAX_API const std::vector<double>& Curve1SampleParameters() const noexcept;

	/// @brief Get the sample parameters of curve 2
	/// @return The sample parameters of curve 2
	[[nodiscard]] AMCAX_API const std::vector<double>& Curve2SampleParameters() const noexcept;

	/// @brief Get the sample points of curve 1
	/// @return The sample points of curve 1
	[[nodiscard]] AMCAX_API const std::vector<Point3>& Curve1SamplePoints() const noexcept;

	/// @brief Get the sample points of curve 2
	/// @return The sample points of curve 2
	[[nodiscard]] AMCAX_API const std::vector<Point3>& Curve2SamplePoints() const noexcept;

	/// @brief Get the errors at the parameters
	/// @return The errors at the sample parameters
	[[nodiscard]] AMCAX_API const std::vector<double>& Errors() const noexcept;

private:
	int nsample;
	double maxError;
	double maxErrorParameter1 = 0.0;
	double maxErrorParameter2 = 0.0;
	int maxErrorSampleID = -1;
	Point3 maxErrorPoint1;
	Point3 maxErrorPoint2;
	std::vector<double> sampleParams1;
	std::vector<double> sampleParams2;
	std::vector<Point3> samplePoints1;
	std::vector<Point3> samplePoints2;
	std::vector<double> errors;
};
} // namespace AMCAX

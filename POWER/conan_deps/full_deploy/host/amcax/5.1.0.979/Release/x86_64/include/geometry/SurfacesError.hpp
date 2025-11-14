/// @file      SurfacesError.hpp
/// @brief     The class of surfaces error calculation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Array2.hpp>
#include <common/PointT.hpp>

namespace AMCAX
{
class Adaptor3Surface;

/// @brief The class of surfaces error calculation
/// @details This class computes the error of the two surfaces
class SurfacesError
{
public:
	/// @brief Constructor
	/// @param surface1 The first surface
	/// @param surface2 The second surface
	/// @param nusample The number of sample points on u direction
	/// @param nvsample The number of sample points on b direction
	AMCAX_API SurfacesError(const Adaptor3Surface& surface1, const Adaptor3Surface& surface2, int nusample = 100, int nvsample = 100);

	/// @brief Get the max error
	/// @return The max error
	[[nodiscard]] AMCAX_API double MaxError() const noexcept;

	/// @brief Get the max error sample ID
	/// @return The max error sample ID
	[[nodiscard]] AMCAX_API std::pair<int, int> MaxErrorSampleID() const noexcept;

	/// @brief Get the max error sample parameters
	/// @return The max error sample parameters
	[[nodiscard]] AMCAX_API std::pair<Point2, Point2> MaxErrorSampleParams() const noexcept;

	/// @brief Get the max error sample points
	/// @return The max error sample points
	[[nodiscard]] AMCAX_API std::pair<Point3, Point3> MaxErrorSamplePoints() const noexcept;

	/// @brief Get the sample uv of the first surface
	/// @return The sample uv of the first surface
	[[nodiscard]] AMCAX_API const Array2<Point2>& Surface1SampleParams() const noexcept;

	/// @brief Get the sample points of the first surface
	/// @return The sample points of the first surface
	[[nodiscard]] AMCAX_API const Array2<Point3>& Surface1SamplePoints() const noexcept;

	/// @brief Get the sample uv of the second surface
	/// @return The sample uv of the second surface
	[[nodiscard]] AMCAX_API const Array2<Point2>& Surface2SampleParams() const noexcept;

	/// @brief Get the sample points of the second surface
	/// @return The sample points of the second surface
	[[nodiscard]] AMCAX_API const Array2<Point3>& Surface2SamplePoints() const noexcept;

	/// @brief Get the sample errors
	/// @return The sample errors
	[[nodiscard]] AMCAX_API const Array2<double>& Errors() const noexcept;

private:
	double maxError;
	int maxErrorUSampleID = -1;
	int maxErrorVSampleID = -1;
	Point2 maxErrorSampleParam1;
	Point2 maxErrorSampleParam2;
	Point3 maxErrorSamplePoint1;
	Point3 maxErrorSamplePoint2;
	std::vector<double> usample1;
	std::vector<double> vsample1;
	std::vector<double> usample2;
	std::vector<double> vsample2;
	Array2<Point2> sampleParams1;
	Array2<Point2> sampleParams2;
	Array2<Point3> samplePoints1;
	Array2<Point3> samplePoints2;
	Array2<double> errors;
};
} // namespace AMCAX

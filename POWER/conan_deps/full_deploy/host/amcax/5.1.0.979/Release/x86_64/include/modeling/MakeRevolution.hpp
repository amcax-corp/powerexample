/// @file      MakeRevolution.hpp
/// @brief     Class of making a revolved shape from a curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeOneAxis.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom2Curve;
class Geom3Curve;
class MakeRevolutionImpl;
#endif

/// @brief Class of making a revolved shape from a curve
/// @details The input curve will be located in the XOZ plane of the local frame, and the revolved shape is the curve rotated around z-axis of the local frame.
/// This class has the following requirements:
/// 1. The end points of curve should be located on the X >= 0 halfplane of the XOZ plane.
/// 2. The start point of curve should have a z-coordinate not greater than the end point of curve.
/// 3. The rotation angle should be in (0, 2pi], vMin should be less than vMax.
/// 4. The input curve should not be nullptr.
/// If the input parameters do not meet the requirements, a construction error will be thrown.
/// Note: if the input curve has self-intersection or is intersected with the rotation axis except for the two end points, the output shape may be physically invalid.
class AMCAX_CLASS_API MakeRevolution : public MakeOneAxis
{
public:
	/// @brief Construct from a curve
	/// @param meridian The curve
	AMCAX_API explicit MakeRevolution(const std::shared_ptr<Geom3Curve>& meridian);

	/// @brief Construct from a curve and a rotation angle
	/// @param meridian The curve
	/// @param angle The rotation angle
	AMCAX_API MakeRevolution(const std::shared_ptr<Geom3Curve>& meridian, double angle);

	/// @brief Construct from a curve with parameter bounds
	/// @param meridian The curve
	/// @param vMin The first parameter on the curve
	/// @param vMax The last parameter on the curve
	AMCAX_API MakeRevolution(const std::shared_ptr<Geom3Curve>& meridian, double vMin, double vMax);

	/// @brief Construct from a curve with parameter bounds and a rotation angle
	/// @param meridian The curve
	/// @param vMin The first parameter on the curve
	/// @param vMax The last parameter on the curve
	/// @param angle The rotation angle
	AMCAX_API MakeRevolution(const std::shared_ptr<Geom3Curve>& meridian, double vMin, double vMax, double angle);

	/// @brief Construct from a local coordinate system and a curve
	/// @param frame The local coordinate system
	/// @param meridian The curve
	AMCAX_API MakeRevolution(const Frame3& frame, const std::shared_ptr<Geom3Curve>& meridian);

	/// @brief Construct from a local coordinate system, a curve and a rotation angle
	/// @param frame The local coordinate system
	/// @param meridian The curve
	/// @param angle The rotation angle
	AMCAX_API MakeRevolution(const Frame3& frame, const std::shared_ptr<Geom3Curve>& meridian, double angle);

	/// @brief Construct from a local coordinate system and a curve with parameter bounds
	/// @param frame The local coordinate system
	/// @param meridian The curve
	/// @param vMin The first parameter on the curve
	/// @param vMax The last parameter on the curve
	AMCAX_API MakeRevolution(const Frame3& frame, const std::shared_ptr<Geom3Curve>& meridian, double vMin, double vMax);

	/// @brief Construct from a local coordinate system and a curve with parameter bounds and a rotation angle
	/// @param frame The local coordinate system
	/// @param meridian The curve
	/// @param vMin The first parameter on the curve
	/// @param vMax The last parameter on the curve
	/// @param angle The rotation angle
	AMCAX_API MakeRevolution(const Frame3& frame, const std::shared_ptr<Geom3Curve>& meridian, double vMin, double vMax, double angle);

	/// @brief Destructor
	AMCAX_API ~MakeRevolution();

#ifndef DOXYGEN_SKIP

	void Init(const Frame3& frame, const std::shared_ptr<Geom3Curve>& meridian, double vMin, double vMax);

	/// @internal
	[[nodiscard]] MakeOneAxisImpl& OneAxis() noexcept override;

	/// @internal
	[[nodiscard]] MakeRevolutionImpl& Revolution() noexcept;

#endif

private:
	static std::shared_ptr<Geom2Curve> Project(const std::shared_ptr<Geom3Curve>& meridian);
	static std::shared_ptr<Geom2Curve> Project(const std::shared_ptr<Geom3Curve>& meridian, const Frame3& frame);
	std::shared_ptr<MakeRevolutionImpl> revolution;
};
} // namespace AMCAX

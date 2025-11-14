/// @file      NURBSCurveSection.hpp
/// @brief     The class of NURBS section
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3Curve;

/// @brief Class of curve section
/// @details A curve section with informations including the begin parameter, orientation, etc.
class NURBSCurveSection
{
public:
	/// @brief Constructor of an empty section
	NURBSCurveSection() noexcept = default;

	/// @brief Constructor of a section with a curve
	/// @param curve The curve
	AMCAX_API explicit NURBSCurveSection(const std::shared_ptr<Geom3Curve>& curve);

	/// @brief Constructor of a section with the source curve, the begin parameter (the closed point) and the curve orientation
	/// @param curve The source curve
	/// @param beginParameter The begin parameter of the curve
	/// @param isReverse The orientation of the curve
	AMCAX_API NURBSCurveSection(const std::shared_ptr<Geom3Curve>& curve, double beginParameter, bool isReverse);

	/// @brief Set the curve of the section
	/// @param c The curve
	AMCAX_API void SetCurve(const std::shared_ptr<Geom3Curve>& c);

	/// @brief Get the curve of the section
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Curve> Curve() const;

	/// @brief Get if the curve is periodic
	[[nodiscard]] AMCAX_API bool IsPeriodic() const;

	/// @brief Set the curve begin parameter
	/// @param t The begin parameter
	AMCAX_API void SetBeginParameter(double t);

	/// @brief Get the curve begin parameter
	[[nodiscard]] AMCAX_API double GetBeginParameter() const;

	/// @brief Get the curve additional orientation
	[[nodiscard]] AMCAX_API bool IsReverse() const;

private:
	std::shared_ptr<Geom3Curve> curve;
	double beginParameter = 0.0;
	bool isPeriodic = false;
	bool isReverse = false;
};
} // namespace AMCAX

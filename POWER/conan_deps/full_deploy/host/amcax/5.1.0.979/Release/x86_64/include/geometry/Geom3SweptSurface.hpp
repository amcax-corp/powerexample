/// @file      Geom3SweptSurface.hpp
/// @brief     Base class of 3D swept surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Surface.hpp>

namespace AMCAX
{
class Geom3Curve;

/// @brief Base class of 3D swept surface
class AMCAX_CLASS_API Geom3SweptSurface : public Geom3Surface
{
public:
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Get the reference direction of the swept surface
	/// @return The reference direction
	[[nodiscard]] AMCAX_API const Direction3& Direction() const noexcept;

	/// @brief Get the basis curve of the swept surface
	/// @return The basis curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Curve>& BasisCurve() const noexcept;

protected:
	/// @brief Basis curve of the swept surface
	std::shared_ptr<Geom3Curve> basisCurve;

	/// @brief Reference direction of the swept surface
	Direction3 direction;

	/// @brief The continuity of the swept surface
	ContinuityType continuity = ContinuityType::CN;
};
} // namespace AMCAX

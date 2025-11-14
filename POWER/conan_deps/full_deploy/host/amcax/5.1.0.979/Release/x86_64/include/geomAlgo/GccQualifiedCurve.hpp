/// @file      GccQualifiedCurve.hpp
/// @brief     Class of a curve with a qualifier used in gcc
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geomAlgo/GccMacros.hpp>
#include <geometry/AdaptorGeom2Curve.hpp>

namespace AMCAX
{
/// @brief Class of a curve with a qualifier used in gcc
class GccQualifiedCurve
{
public:
	/// @brief Construct from a curve adaptor and a position type
	/// @param curve The curve adaptor
	/// @param qualifier The position type
	AMCAX_API GccQualifiedCurve(const AdaptorGeom2Curve& curve, GccPosition qualifier) noexcept;

	/// @brief Get the curve
	/// @return The curve
	[[nodiscard]] AMCAX_API const AdaptorGeom2Curve& Qualified() const noexcept;

	/// @brief Get the qualifier
	/// @return The qualifier
	[[nodiscard]] AMCAX_API GccPosition Qualifier() const noexcept;

	/// @brief Is the curve unqualified
	/// @return True if the solution is unqualified
	[[nodiscard]] AMCAX_API bool IsUnqualified() const noexcept;

	/// @brief Is the curve enclosing
	/// @return True if the solution is enclosing the curve
	[[nodiscard]] AMCAX_API bool IsEnclosing() const noexcept;

	/// @brief Is the curve enclosed
	/// @return True if the solution is enclosed by the curve
	[[nodiscard]] AMCAX_API bool IsEnclosed() const noexcept;

	/// @brief Is the curve outside
	/// @return True if the solution is outside the curve
	[[nodiscard]] AMCAX_API bool IsOutside() const noexcept;

private:
	AdaptorGeom2Curve qualified;
	GccPosition qualifier;
};
} // namespace AMCAX

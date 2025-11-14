/// @file      GccEntity.hpp
/// @brief     Class of useful tools of constructing qualified curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geomAlgo/GccMacros.hpp>
#include <math/CircleT.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class AdaptorGeom2Curve;
class GccQualifiedCircle;
class GccQualifiedCurve;
class GccQualifiedLine;
#endif

/// @brief Class of useful tools of constructing qualified curves
class GccEntity
{
public:
	/// @brief Convert the position type to a string
	/// @param position The position
	/// @return The string of the position
	[[nodiscard]] AMCAX_API static std::string PositionToString(GccPosition position);

	/// @brief Get the position type from a string
	/// @param positionString The string of a position
	/// @return The resulting position type
	[[nodiscard]] AMCAX_API static GccPosition PositionFromString(const std::string& positionString) noexcept;

	/// @brief Get the position type from a string
	/// @param positionString The string of a position
	/// @param position The resulting position type
	/// @return True if the position type is known
	AMCAX_API static bool PositionFromString(const std::string& positionString, GccPosition& position) noexcept;

#ifndef DOXYGEN_SKIP
	/// @brief Construct an unqualified line, i.e. applying all solutions
	/// @param l The line
	/// @return The unqualified line
	[[nodiscard]] static GccQualifiedLine Unqualified(const Line2& l) noexcept;

	/// @brief Construct an unqualified circle, i.e. applying all solutions
	/// @param c The circle
	/// @return The unqualified circle
	[[nodiscard]] static GccQualifiedCircle Unqualified(const Circle2& c) noexcept;
#endif

	/// @brief Construct an unqualified curve, i.e. applying all solutions
	/// @param c The curve
	/// @return The unqualified curve
	[[nodiscard]] AMCAX_API static GccQualifiedCurve Unqualified(const AdaptorGeom2Curve& c) noexcept;

#ifndef DOXYGEN_SKIP
	/// @brief Construct an enclosing circle
	/// @param c The circle
	/// @return The enclosing circle
	[[nodiscard]] static GccQualifiedCircle Enclosing(const Circle2& c) noexcept;
#endif

	/// @brief Construct an enclosing curve
	/// @param c The curve
	/// @return The enclosing curve
	[[nodiscard]] AMCAX_API static GccQualifiedCurve Enclosing(const AdaptorGeom2Curve& c) noexcept;

#ifndef DOXYGEN_SKIP
	/// @brief Construct an enclosed line
	/// @param l The line
	/// @return The enclosed line
	[[nodiscard]] static GccQualifiedLine Enclosed(const Line2& l) noexcept;

	/// @brief Construct an enclosed circle
	/// @param c The circle
	/// @return The enclosed circle
	[[nodiscard]] static GccQualifiedCircle Enclosed(const Circle2& c) noexcept;
#endif

	/// @brief Construct an enclosed curve
	/// @param c The curve
	/// @return The enclosed curve
	[[nodiscard]] AMCAX_API static GccQualifiedCurve Enclosed(const AdaptorGeom2Curve& c) noexcept;

#ifndef DOXYGEN_SKIP
	/// @brief Construct an outside line
	/// @param l The line
	/// @return The outside line
	[[nodiscard]] static GccQualifiedLine Outside(const Line2& l) noexcept;

	/// @brief Construct an outside circle
	/// @param c The circle
	/// @return The outside circle
	[[nodiscard]] static GccQualifiedCircle Outside(const Circle2& c) noexcept;
#endif

	/// @brief Construct an outside curve
	/// @param c The curve
	/// @return The outside curve
	[[nodiscard]] AMCAX_API static GccQualifiedCurve Outside(const AdaptorGeom2Curve& c) noexcept;
};
} // namespace AMCAX

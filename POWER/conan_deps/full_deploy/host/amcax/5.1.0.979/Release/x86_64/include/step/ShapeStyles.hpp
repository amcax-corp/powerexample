/// @file       ShapeStyles.hpp
/// @brief      Classes for style representation.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <map>
#include <optional>

#include <common/Macros.hpp>

#include <step/ShapeRGBA.hpp>
#include <step/ShapeStyleLevel.hpp>

namespace AMCAX::STEP
{
/// @brief Line width value for curves (in document units).
using CurveWidth = double;

/// @brief Indicates which side of a surface the style applies to.
enum class SurfaceSide
{
	POSITIVE, ///< Positive side of the surface.
	NEGATIVE, ///< Negative side of the surface.
	BOTH	  ///< Both sides of the surface.
};

/// @brief Pattern (line style) for curves.
enum class CurveFont
{
	CONTINUOUS,
	CHAIN,
	CHAIN_DOUBLE_DASH,
	DASHED,
	DOTTED
};

/// @brief Style information for surfaces.
class SurfaceStyle
{
public:
	/// @brief Default constructor, leaves all fields uninitialized.
	AMCAX_API SurfaceStyle();

	/// @brief Copy constructor.
	/// @param style The SurfaceStyle to copy.
	AMCAX_API SurfaceStyle(const SurfaceStyle& style);

	/// @brief Construct from side and color.
	/// @param side The surface side to which this style applies.
	/// @param color The color for this surface.
	AMCAX_API SurfaceStyle(const SurfaceSide& side, const ShapeRGBA& color);

	/// @brief Equality operator.
	/// @param style The SurfaceStyle to compare with.
	/// @retval true If both styles are equal.
	/// @retval false Otherwise.
	AMCAX_API bool operator==(const SurfaceStyle& style) const;

	/// @brief Inequality operator.
	/// @param style The SurfaceStyle to compare with.
	/// @retval true If the styles differ.
	/// @retval false Otherwise.
	AMCAX_API bool operator!=(const SurfaceStyle& style) const;

	/// @brief Assignment operator.
	/// @param style The SurfaceStyle to assign from.
	/// @return Reference to this object.
	AMCAX_API SurfaceStyle& operator=(const SurfaceStyle& style);

	/// @brief Set the surface side.
	/// @param side The side to set.
	AMCAX_API void SetSide(const SurfaceSide& side);

	/// @brief Set the surface color.
	/// @param color The color to set.
	AMCAX_API void SetColor(const ShapeRGBA& color);

	/// @brief Get the surface side.
	/// @return The surface side value.
	AMCAX_API SurfaceSide GetSide() const;

	/// @brief Get the surface color.
	/// @return The color value. If no color is set, the object is invalid.
	AMCAX_API ShapeRGBA GetColor() const;

	/// @brief Check if a color value is set.
	/// @retval true If a color value is present.
	/// @retval false Otherwise.
	AMCAX_API bool ColorHasValue() const;

private:
	SurfaceSide _side;
	std::optional<ShapeRGBA> _color;
};

/// @brief Style information for curves.
class CurveStyle
{
public:
	/// @brief Default constructor, leaves all fields uninitialized.
	AMCAX_API CurveStyle();

	/// @brief Copy constructor.
	/// @param style The CurveStyle to copy.
	AMCAX_API CurveStyle(const CurveStyle& style);

	/// @brief Construct from font, width, and color.
	/// @param font The curve line font (pattern).
	/// @param width The line width.
	/// @param color The line color.
	AMCAX_API CurveStyle(const CurveFont& font, const CurveWidth& width, const ShapeRGBA& color);

	/// @brief Assignment operator.
	/// @param style The CurveStyle to assign from.
	/// @return Reference to this object.
	AMCAX_API CurveStyle& operator=(const CurveStyle& style);

	/// @brief Equality operator.
	/// @param style The CurveStyle to compare with.
	/// @retval true If both styles are equal.
	/// @retval false Otherwise.
	AMCAX_API bool operator==(const CurveStyle& style) const;

	/// @brief Inequality operator.
	/// @param style The CurveStyle to compare with.
	/// @retval true If the styles differ.
	/// @retval false Otherwise.
	AMCAX_API bool operator!=(const CurveStyle& style) const;

	/// @brief Set the curve font (pattern).
	/// @param font The font to set.
	AMCAX_API void SetFont(const CurveFont& font);

	/// @brief Set the line width.
	/// @param width The width to set.
	AMCAX_API void SetWidth(const CurveWidth& width);

	/// @brief Set the line color.
	/// @param color The color to set.
	AMCAX_API void SetColor(const ShapeRGBA& color);

	/// @brief Get the curve font (pattern).
	/// @return The font value.
	AMCAX_API CurveFont GetFont() const;

	/// @brief Get the line width.
	/// @return The width value.
	AMCAX_API CurveWidth GetWidth() const;

	/// @brief Get the line color.
	/// @return The color value.
	AMCAX_API ShapeRGBA GetColor() const;

	/// @brief Check if a font value is set.
	/// @retval true If a font is present.
	/// @retval false Otherwise.
	AMCAX_API bool FontHasValue() const;

	/// @brief Check if a width value is set.
	/// @retval true If a width is present.
	/// @retval false Otherwise.
	AMCAX_API bool WidthHasValue() const;

	/// @brief Check if a color value is set.
	/// @retval true If a color is present.
	/// @retval false Otherwise.
	AMCAX_API bool ColorHasValue() const;

private:
	std::optional<CurveFont> _font;
	std::optional<CurveWidth> _width;
	std::optional<ShapeRGBA> _color;
};

/// @brief Combined curve/surface style representation.
class ShapeStyle
{
public:
	/// @brief Default constructor.
	AMCAX_API ShapeStyle() = default;

	/// @brief Construct with a surface style.
	/// @param surfacestyle The SurfaceStyle to set.
	AMCAX_API ShapeStyle(const SurfaceStyle& surfacestyle);

	/// @brief Construct with a curve style.
	/// @param curvestyle The CurveStyle to set.
	AMCAX_API ShapeStyle(const CurveStyle& curvestyle);

	/// @brief Equality operator.
	/// @param style The ShapeStyle to compare with.
	/// @retval true If both styles are equal.
	/// @retval false Otherwise.
	AMCAX_API bool operator==(const ShapeStyle& style) const;

	/// @brief Inequality operator.
	/// @param style The ShapeStyle to compare with.
	/// @retval true If the styles differ.
	/// @retval false Otherwise.
	AMCAX_API bool operator!=(const ShapeStyle& style) const;

	/// @brief Destructor.
	AMCAX_API ~ShapeStyle() = default;

	/// @brief Get the effective color of this style.
	/// @return The color value if available; otherwise an invalid ShapeRGBA (flags set to false).
	AMCAX_API ShapeRGBA GetColor() const;

	/// @brief Set the curve style.
	/// @param curvestyle The curve style to set.
	AMCAX_API void SetCurveStyle(const CurveStyle& curvestyle);

	/// @brief Get the current curve style.
	/// @return The curve style value.
	AMCAX_API CurveStyle GetCurveStyle() const;

	/// @brief Set the surface style.
	/// @param surfacestyle The surface style to set.
	AMCAX_API void SetSurfaceStyle(const SurfaceStyle& surfacestyle);

	/// @brief Get the current surface style.
	/// @return The surface style value.
	AMCAX_API SurfaceStyle GetSurfaceStyle() const;

	/// @brief Check if a curve style is set.
	/// @retval true If a curve style is present.
	/// @retval false Otherwise.
	AMCAX_API bool CurveStyleHasValue() const;

	/// @brief Check if a surface style is set.
	/// @retval true If a surface style is present.
	/// @retval false Otherwise.
	AMCAX_API bool SurfaceStyleHasValue() const;

	/// @brief Check if either a curve style or surface style is set.
	/// @retval true If at least one style is present.
	/// @retval false If none are present.
	AMCAX_API bool StyleHasValue() const;

	/// @brief Clear the curve style.
	AMCAX_API void NullifyCurveStyle();

	/// @brief Clear the surface style.
	AMCAX_API void NullifySurfaceStyle();

private:
	std::optional<CurveStyle> _curvestyle;
	std::optional<SurfaceStyle> _surfacestyle;
};

} // namespace AMCAX::STEP

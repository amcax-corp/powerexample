/// @file       ShapeRGBA.hpp
/// @brief		Represents a color in RGBA format, with validity flags for channels.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#include <common/Macros.hpp>

namespace AMCAX::STEP
{
/// @brief Represents a color in RGBA format, with validity flags for channels.
class ShapeRGBA
{
private:
	double _R{0.75};  ///< Red channel value.
	double _G{0.75};  ///< Green channel value.
	double _B{0.75};  ///< Blue channel value.
	double _A{1.00};  ///< Alpha channel value.
	uint8_t valid{0}; ///< Bitfield indicating which channels are valid.

	/// @brief Flags representing valid channels.
	enum ValidFlags : uint8_t
	{
		RGBValid = 1 << 0,	 ///< RGB channels are valid.
		AlphaValid = 1 << 1, ///< Alpha channel is valid.
	};

public:
	/// @brief Default constructor. Initializes channels to defaults and marks all invalid.
	ShapeRGBA() = default;

	/// @brief Copy constructor.
	/// @param other The ShapeRGBA to copy.
	ShapeRGBA(const ShapeRGBA& other) = default;

	/// @brief Move constructor.
	/// @param other The ShapeRGBA to move.
	ShapeRGBA(ShapeRGBA&& other) noexcept = default;

	/// @brief Construct with valid RGB; alpha defaults to 1.0 (opaque).
	/// @param R Red channel value.
	/// @param G Green channel value.
	/// @param B Blue channel value.
	ShapeRGBA(const double& R, const double& G, const double& B)
		: ShapeRGBA(R, G, B, 1.0)
	{
		valid |= RGBValid;
		valid &= ~AlphaValid;
	}

	/// @brief Construct with only alpha set; RGB defaults to 0.75 gray.
	/// @param A Alpha channel value.
	ShapeRGBA(const double& A)
		: ShapeRGBA(.75, .75, .75, A)
	{
		valid &= ~RGBValid;
		valid |= AlphaValid;
	}

	/// @brief Construct with all RGBA channels set and valid.
	/// @param R Red channel value.
	/// @param G Green channel value.
	/// @param B Blue channel value.
	/// @param A Alpha channel value.
	ShapeRGBA(const double& R, const double& G, const double& B, const double& A)
		: _R(R),
		  _G(G),
		  _B(B),
		  _A(A),
		  valid(RGBValid | AlphaValid)
	{
	}

	/// @brief Destructor.
	~ShapeRGBA() = default;

	/// @brief Copy assignment operator.
	/// @param other The ShapeRGBA to assign from.
	/// @return Reference to this object.
	ShapeRGBA& operator=(const ShapeRGBA& other) = default;

	/// @brief Move assignment operator.
	/// @param other The ShapeRGBA to move from.
	/// @return Reference to this object.
	ShapeRGBA& operator=(ShapeRGBA&& other) noexcept = default;

	/// @brief Equality operator.
	/// @param other The ShapeRGBA to compare with.
	/// @retval true If all channels and valid flags are equal.
	/// @retval false Otherwise.
	constexpr bool operator==(const ShapeRGBA& other) const
	{
		return this->_R == other._R &&
			this->_G == other._G &&
			this->_B == other._B &&
			this->_A == other._A &&
			this->valid == other.valid;
	}

	/// @brief Inequality operator.
	/// @param other The ShapeRGBA to compare with.
	/// @retval true If any channel or valid flag differs.
	/// @retval false Otherwise.
	constexpr bool operator!=(const ShapeRGBA& other) const
	{
		return this->_R != other._R ||
			this->_G != other._G ||
			this->_B != other._B ||
			this->_A != other._A ||
			this->valid != other.valid;
	}

	/// @brief Boolean conversion operator.
	/// @retval true If either RGB or Alpha channel is marked valid.
	/// @retval false If no channels are valid.
	constexpr operator bool() const
	{
		return valid;
	}

	/// @brief Get the red channel value.
	/// @return Const reference to red component.
	constexpr const double& R() const
	{
		return _R;
	}

	/// @brief Set the red channel value (marks RGB as valid).
	/// @param R New value.
	/// @return Const reference to the updated value.
	constexpr const double& SetR(const double& R)
	{
		valid |= RGBValid;
		return _R = R;
	}

	/// @brief Get the green channel value.
	/// @return Const reference to green component.
	constexpr const double& G() const
	{
		return _G;
	}

	/// @brief Set the green channel value (marks RGB as valid).
	/// @param G New value.
	/// @return Const reference to the updated value.
	constexpr const double& SetG(const double& G)
	{
		valid |= RGBValid;
		return _G = G;
	}

	/// @brief Get the blue channel value.
	/// @return Const reference to blue component.
	constexpr const double& B() const
	{
		return _B;
	}

	/// @brief Set the blue channel value (marks RGB as valid).
	/// @param B New value.
	/// @return Const reference to the updated value.
	constexpr const double& SetB(const double& B)
	{
		valid |= RGBValid;
		return _B = B;
	}

	/// @brief Get the alpha channel value.
	/// @return Const reference to alpha component.
	constexpr const double& A() const
	{
		return _A;
	}

	/// @brief Set the alpha channel value (marks Alpha as valid).
	/// @param A New value.
	/// @return Const reference to the updated value.
	constexpr const double& SetA(const double& A)
	{
		valid |= AlphaValid;
		return _A = A;
	}

	/// @brief Check if RGB channels are valid.
	/// @retval true If RGB channels are marked valid.
	/// @retval false Otherwise.
	constexpr bool IsValidRGB() const
	{
		return valid & RGBValid;
	}

	/// @brief Check if alpha channel is valid.
	/// @retval true If alpha is marked valid.
	/// @retval false Otherwise.
	constexpr bool IsValidA() const
	{
		return valid & AlphaValid;
	}

	/// @brief Convert this color to a hexadecimal string (e.g. "#RRGGBB" or "#RRGGBBAA").
	/// @return Hexadecimal color code string.
	std::string to_string() const
	{
		std::ostringstream oss;
		oss << '#' << std::hex << std::uppercase << std::setfill('0')
			<< std::setw(2) << unsigned(std::clamp(_R, 0.0, 1.0) * 255.0)
			<< std::setw(2) << unsigned(std::clamp(_G, 0.0, 1.0) * 255.0)
			<< std::setw(2) << unsigned(std::clamp(_B, 0.0, 1.0) * 255.0);
		if (valid & AlphaValid)
		{
			oss << std::setw(2) << unsigned(std::clamp(_A, 0.0, 1.0) * 255.0);
		}
		return oss.str();
	}

	/// @brief Create a ShapeRGBA from a color string.
	/// @details Supports HTML-like hex codes (e.g. "#DEADBEEF", "09e6bd", "777") and some color names ("red", "green", etc.).
	/// @param hex Color string (hex code or name).
	/// @return Corresponding color object.
	AMCAX_API static ShapeRGBA MakeColor(std::string hex);

	/// @brief Convert transparency to alpha.
	/// @details Supports input in ranges [0,1], [0,255], and [0,65535].
	/// @param transparency Transparency value.
	/// @return Alpha value, normalized to [0.0, 1.0].
	AMCAX_API static double TransparencyToAlpha(const double transparency);

	/// @brief Convert alpha to transparency.
	/// @details Supports output in ranges [0,1], [0,255], and [0,65535].
	/// @param alpha Input alpha value between 0.0 and 1.0.
	/// @return Transparency value in the chosen range.
	AMCAX_API static double AlphaToTransparency(const double alpha);
};
} // namespace AMCAX::STEP

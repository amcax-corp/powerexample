/// @file      MakeCone.hpp
/// @brief     Class of making a cone
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeOneAxis.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeConeImpl;
#endif

/// @brief Class of making a cone
/// @details The top and bottom radii should be non-negative and inequal, height should be positive, angle should be in (0, 2pi]
class AMCAX_CLASS_API MakeCone : public MakeOneAxis
{
public:
	/// @brief Construct from a bottom radius, a top radius and a height
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	AMCAX_API MakeCone(double r1, double r2, double h);

	/// @brief Construct from a bottom radius, a top radius, a height and a rotation angle
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	/// @param angle The rotation angle to construct a part cone
	AMCAX_API MakeCone(double r1, double r2, double h, double angle);

	/// @brief Construct from a local coordinate system, a bottom radius, a top radius and a height
	/// @param frame The local coordinate system
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	AMCAX_API MakeCone(const Frame3& frame, double r1, double r2, double h);

	/// @brief Construct from a local coordinate system, a bottom radius, a top radius, a height and a rotation angle
	/// @param frame The local coordinate system
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	/// @param angle The rotation angle to construct a part cone
	AMCAX_API MakeCone(const Frame3& frame, double r1, double r2, double h, double angle);

	/// @brief Destructor
	AMCAX_API ~MakeCone();

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] MakeOneAxisImpl& OneAxis() noexcept override;

	/// @internal
	[[nodiscard]] MakeConeImpl& Cone() noexcept;

#endif

private:
	std::shared_ptr<MakeConeImpl> cone;
};
} // namespace AMCAX

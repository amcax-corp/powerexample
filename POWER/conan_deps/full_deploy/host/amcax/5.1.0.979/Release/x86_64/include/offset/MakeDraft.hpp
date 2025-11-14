/// @file      MakeDraft.hpp
/// @brief     Class of making a draft surface along a wire
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <modeling/MakeShape.hpp>
#include <offset/TransitionMode.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepFillDraft;
class Geom3Surface;
class TopoShell;
#endif

/// @brief Class of making a draft surface along a wire
class AMCAX_CLASS_API MakeDraft : public MakeShape
{
public:
	/// @brief Construct from a shape with a draft direction
	/// @param s The shape to be processed
	/// @param dir The draft direction
	/// @param angle The draft angle
	AMCAX_API MakeDraft(const TopoShape& s, const Direction3& dir, double angle);

	/// @brief Set the draft options
	/// @param style The type of transition
	/// @param angleMin The maximal angle for performing transition
	/// @param angleMax The maximal angle for performing transition
	AMCAX_API void SetOptions(TransitionMode style = TransitionMode::RightCorner, double angleMin = 0.01, double angleMax = 3.0);

	/// @brief Set the draft direction
	/// @param isInternal Whether the draft is internal
	AMCAX_API void SetDraft(bool isInternal = false);

	/// @brief Perform the draft with the maximal length of draft edge
	/// @param lengthMax The maximal length
	AMCAX_API void Perform(double lengthMax);

	/// @brief Perform the draft up to the surface
	/// @param surface The surface
	/// @param keepInsideSurface Whether to keep the surface inside the draft
	AMCAX_API void Perform(const std::shared_ptr<Geom3Surface>& surface, bool keepInsideSurface = true);

	/// @brief Perform the draft up to the stop shape
	/// @param stopShape The stop shape
	/// @param keepOutSide Whether to keep the shape outside the draft
	AMCAX_API void Perform(const TopoShape& stopShape, bool keepOutSide = true);

	/// @brief Get the constructed shell
	/// @return The constructed shell
	[[nodiscard]] AMCAX_API TopoShell Shell() const;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& S) override;

private:
	std::shared_ptr<BRepFillDraft> draftTool;
};
} // namespace AMCAX

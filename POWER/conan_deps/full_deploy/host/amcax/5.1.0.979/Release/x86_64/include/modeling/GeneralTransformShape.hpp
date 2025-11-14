/// @file      GeneralTransformShape.hpp
/// @brief     Class of transforming a shape by a general transformation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/GeneralTransformationT.hpp>
#include <modeling/ModifyShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Collect;
#endif

/// @brief Class of transforming a shape by a general transformation
class AMCAX_CLASS_API GeneralTransformShape : public ModifyShape
{
public:
	/// @brief Construct from a general transformation
	/// @param t The general transformation
	AMCAX_API explicit GeneralTransformShape(const GeneralTransformation3& t);

	/// @brief Transform a shape by a general transformation
	/// @param s The shape
	/// @param t The general transformation
	/// @param copy Whether the geometry of the shape is copied
	AMCAX_API GeneralTransformShape(const TopoShape& s, const GeneralTransformation3& t, bool copy = false);

	/// @brief Perform the transformation to a shape
	/// @param s The shape
	/// @param copy Whether the geometry of the shape is copied
	AMCAX_API void Perform(const TopoShape& s, bool copy = false);

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;
	[[nodiscard]] AMCAX_API TopoShape ModifiedShape(const TopoShape& s) const override;

private:
	GeneralTransformation3 gt;
	std::shared_ptr<Collect> collect;
};
} // namespace AMCAX

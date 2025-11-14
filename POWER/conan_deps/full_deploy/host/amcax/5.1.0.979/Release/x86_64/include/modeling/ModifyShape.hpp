/// @file      ModifyShape.hpp
/// @brief     Base class of modifying a shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ShapeModifier;
class ShapeModification;
#endif

/// @brief Base class of modifying a shape
class AMCAX_CLASS_API ModifyShape : public MakeShape
{
public:
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;

	/// @brief Get the modified shape corresponding to a shape
	/// @details The argument shape should be the initial shape or its sub-shape
	/// @param s The shape
	/// @return The modifed shape
	[[nodiscard]] AMCAX_API virtual TopoShape ModifiedShape(const TopoShape& s) const;

protected:
	/// @brief Default constructor
	ModifyShape();

	/// @brief Construct from a shape to be modified
	/// @param s The shape to be modified
	explicit ModifyShape(const TopoShape& s);

	/// @brief Construct from an internal modification algorithm
	/// @param m The modification algorithm
	explicit ModifyShape(const std::shared_ptr<ShapeModification>& m);

	/// @brief Construct from a shape to be modified and an internal modification algorithm
	/// @param s The shape to be modified
	/// @param m The modification algorithm
	ModifyShape(const TopoShape& s, const std::shared_ptr<ShapeModification>& m);

	/// @brief Perform the modification on a shape
	/// @param s The shape
	void DoModif(const TopoShape& s);

	/// @brief Perform the modification using a modification algorithm
	/// @param m The modification algorithm
	void DoModif(const std::shared_ptr<ShapeModification>& m);

	/// @brief Perform the modification on a shape using a modification algorithm
	/// @param s The shape
	/// @param m The modification algorithm
	void DoModif(const TopoShape& s, const std::shared_ptr<ShapeModification>& m);

	/// @brief The initial shape
	TopoShape initialShape;

	/// @brief The modifier
	std::shared_ptr<ShapeModifier> modifier;

	/// @brief The modification algorithm
	std::shared_ptr<ShapeModification> modification;

private:
	void DoModif();
};
} // namespace AMCAX

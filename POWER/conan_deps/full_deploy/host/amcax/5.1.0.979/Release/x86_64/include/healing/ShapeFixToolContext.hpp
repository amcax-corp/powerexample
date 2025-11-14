/// @file      ShapeFixToolContext.hpp
/// @brief     An useful tool for fixing shapes
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <memory>

#include <topology/TopoShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class ShapeFixToolContextHistory;
#endif

/// @brief An useful tool for fixing shapes
class ShapeFixToolContext
{
public:
	/// @brief Construct an empty ShapeFixToolContext object
	AMCAX_API ShapeFixToolContext();

	/// @brief Construct an empty ShapeFixToolContext object and initialize it
	/// @param shape A TopoShape object to be fixed.
	/// @param prec Precision
	/// @param maxTol Max tolerance
	AMCAX_API explicit ShapeFixToolContext(const TopoShape& shape, double prec, double maxTol);

	/// @brief Destructor
	AMCAX_API ~ShapeFixToolContext();

	/// @brief Initialize fix parameters.
	/// @param shape A TopoShape object to be fixed.
	/// @param prec Precision
	/// @param maxTol Max tolerance
	AMCAX_API void Init(const TopoShape& shape, double prec, double maxTol);

	/// @brief Perform ShapeFix on the TopoShape object.
	/// @return True if ShapeFix is performed successfully.
	AMCAX_API bool Perform();

	/// @brief Get the resulting shape
	/// @return The resulting shape
	[[nodiscard]] AMCAX_API TopoShape Shape() const;

	/// @brief Check if any of the input shapes has been modified.
	/// @return Whether there has any modified object
	[[nodiscard]] AMCAX_API bool HasModified() const;

	/// @brief Check if there are shapes been genereted during the operation.
	/// @return Whether there are shapes been generated.
	[[nodiscard]] AMCAX_API bool HasGenerated() const;

	/// @brief Check if there are any shapes been deleted.
	/// @return Whether there are any shapes been deleted.
	[[nodiscard]] AMCAX_API bool HasDeleted() const;

	/// @brief Get the shapes modified from the given shape
	/// @param s The given shape
	/// @return The list of modified shapes
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s);

	/// @brief Get the shapes generated from the given shape
	/// @param s The given shape
	/// @return The list of generated shapes
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s);

	/// @brief Is the given shape deleted
	/// @param s The given shape
	/// @return True if the given shape is deleted
	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) const;

private:
	ShapeFixToolContext(const ShapeFixToolContext&) = delete;
	ShapeFixToolContext(ShapeFixToolContext&&) noexcept = delete;
	ShapeFixToolContext& operator=(const ShapeFixToolContext&) = delete;
	ShapeFixToolContext& operator=(ShapeFixToolContext&&) noexcept = delete;

	TopoShape myShape;
	double myPreci;
	double myMaxTol;

	std::list<TopoShape> modified;
	std::list<TopoShape> generated;

	std::unique_ptr<ShapeFixToolContextHistory> history;
};
} // namespace AMCAX

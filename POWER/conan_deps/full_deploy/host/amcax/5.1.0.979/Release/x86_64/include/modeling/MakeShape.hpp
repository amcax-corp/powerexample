/// @file      MakeShape.hpp
/// @brief     Base class of making shapes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>

#include <modeling/MakeShapeError.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Base class of making shapes
class AMCAX_CLASS_API MakeShape
{
public:
	/// @brief Copy constructor
	AMCAX_API MakeShape(const MakeShape&);

	/// @brief Move constructor
	AMCAX_API MakeShape(MakeShape&&) noexcept;

	/// @brief Destructor
	AMCAX_API virtual ~MakeShape() noexcept;

	/// @brief Copy assignment operator
	/// @return The reference to self
	AMCAX_API MakeShape& operator=(const MakeShape&);

	/// @brief Move assignment operator
	/// @return The reference to self
	AMCAX_API MakeShape& operator=(MakeShape&&) noexcept;

	/// @brief Is the construction algorithm done
	/// @return True if the construction algorithm has no error
	[[nodiscard]] AMCAX_API virtual bool IsDone() const noexcept;

	/// @brief Perform the algorithm
	AMCAX_API virtual void Build();

	/// @brief Get the resulting shape
	/// @return The resulting shape
	[[nodiscard]] AMCAX_API virtual const TopoShape& Shape();

	/// @brief Get the resulting shape
	/// @return The resulting shape
	[[nodiscard]] AMCAX_API operator TopoShape();

	/// @brief Get the shapes generated from the given shape
	/// @param s The given shape
	/// @return The list of generated shapes
	[[nodiscard]] AMCAX_API virtual const std::list<TopoShape>& Generated(const TopoShape& s);

	/// @brief Get the shapes modified from the given shape
	/// @param s The given shape
	/// @return The list of modified shapes
	[[nodiscard]] AMCAX_API virtual const std::list<TopoShape>& Modified(const TopoShape& s);

	/// @brief Is the given shape deleted
	/// @param s The given shape
	/// @return True if the given shape is deleted
	[[nodiscard]] AMCAX_API virtual bool IsDeleted(const TopoShape& s);

protected:
	/// @brief Default constructor
	AMCAX_API MakeShape();

	/// @brief Set the status by done
	void Done() noexcept;

	/// @brief Set the status by not done
	void NotDone() noexcept;

	/// @brief The resulting shape
	TopoShape shape;

	/// @brief The generated sub-shapes
	std::list<TopoShape> generated;

private:
	/// @brief Is the algorithm done
	bool done = false;
};
} // namespace AMCAX

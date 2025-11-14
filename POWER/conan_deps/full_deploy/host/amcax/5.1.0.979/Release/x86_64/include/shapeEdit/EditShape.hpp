/// @file      EditShape.hpp
/// @brief     Base class of edit shapes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <topology/TopoShape.hpp>

namespace AMCAX {

namespace GeomE {
class EditTrace;

/// @brief Base class of editing shapes
class AMCAX_CLASS_API EditShape
{
public:
	/// @brief Destructor
	virtual ~EditShape() = default;

	/// @brief Get the shapes generated from the given shape
	/// @param[in] s The given shape
	/// @return The list of generated shapes
	AMCAX_API virtual const std::list<TopoShape> &Generated(const TopoShape &s);

	/// @brief Get the shapes modified from the given shape
	/// @param[in] s The given shape
	/// @return The list of modified shapes
	AMCAX_API virtual const std::list<TopoShape> &Modified(const TopoShape &s);

	/// @brief Is the given shape deleted
	/// @param[in] s The given shape
	/// @return True if the given shape is deleted
	AMCAX_API virtual bool IsDeleted(const TopoShape &s);

#ifndef DOXYGEN_SKIP
	std::shared_ptr<EditTrace> trace;
#endif

protected:
	/// @brief A list used to represent an empty collection of shapes. Typically
	/// returned when there are no generated or modified shapes.
	std::list<TopoShape> emptyShapeList;
};

} // namespace GeomE

} // namespace AMCAX
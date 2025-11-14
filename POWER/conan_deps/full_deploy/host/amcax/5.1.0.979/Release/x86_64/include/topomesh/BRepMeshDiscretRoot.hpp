/// @file      BRepMeshDiscretRoot.hpp
/// @brief     Base class of meshing
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Base class of meshing
class BRepMeshDiscretRoot
{
public:
	/// @brief Default constructor
	AMCAX_API BRepMeshDiscretRoot() noexcept;

	/// @brief Copy constructor
	AMCAX_API BRepMeshDiscretRoot(const BRepMeshDiscretRoot&) noexcept;

	/// @brief Move constructor
	AMCAX_API BRepMeshDiscretRoot(BRepMeshDiscretRoot&&) noexcept;

	/// @brief Destructor
	AMCAX_API virtual ~BRepMeshDiscretRoot() noexcept;

	/// @brief Copy assignment operator
	/// @return The reference to self
	AMCAX_API BRepMeshDiscretRoot& operator=(const BRepMeshDiscretRoot&) noexcept;

	/// @brief Move assignment operator
	/// @return The reference to self
	AMCAX_API BRepMeshDiscretRoot& operator=(BRepMeshDiscretRoot&&) noexcept;

	/// @brief Set the shape to be meshed
	/// @param shape The shape
	AMCAX_API void SetShape(const TopoShape& shape) noexcept;

	/// @brief Get the shape
	/// @return The shape
	[[nodiscard]] AMCAX_API const TopoShape& Shape() const noexcept;

	/// @brief Is the meshing algorithm done
	/// @return True if the meshing process is succeed
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

	/// @brief Perform the algorithm
	AMCAX_API virtual void Perform() = 0;

protected:
	/// @brief Set the status as done
	void SetDone() noexcept;

	/// @brief Set the status as not done
	void SetNotDone() noexcept;

	/// @brief Initialize the algorithm
	virtual void Init() noexcept;

	/// @brief The shape to be meshed
	TopoShape shape;

	/// @brief Is the algorithm done
	bool isDone = false;
};
} // namespace AMCAX

/// @file      BRepMeshIncrementalMesh.hpp
/// @brief     Class of meshing
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topomesh/BRepMeshDiscretRoot.hpp>
#include <topomesh/MeshToolsParameters.hpp>

namespace AMCAX
{
class MeshToolsContext;

/// @brief Class of meshing
/// @details The resulting mesh is stored in the faces and edges of the shape
class AMCAX_CLASS_API BRepMeshIncrementalMesh : public BRepMeshDiscretRoot
{
public:
	/// @brief Default constructor
	AMCAX_API BRepMeshIncrementalMesh() noexcept;

	/// @brief Construct a mesh from a shape with given linear and angle deflection
	/// @param shape The shape to be meshed
	/// @param linDeflection The linear deflection
	/// @param isRelative Determine whether the deflection is computed relatively
	/// @param angDeflection The angle deflection
	AMCAX_API BRepMeshIncrementalMesh(const TopoShape& shape, double linDeflection, bool isRelative = false, double angDeflection = 0.5);

	/// @brief Construct a mesh from a shape with given parameters
	/// @param shape The shape to be meshed
	/// @param parameters The parameters used in meshing algorithm
	AMCAX_API BRepMeshIncrementalMesh(const TopoShape& shape, const MeshToolsParameters& parameters);

	/// @brief Perform the algorithm
	AMCAX_API void Perform() override;

#ifndef DOXYGEN_SKIP

	/// @internal
	/// @brief Perform the algorithm with a context
	/// @param context The context
	void Perform(const std::shared_ptr<MeshToolsContext>& context);

#endif

	/// @brief Get the parameters of the meshing algorithm
	/// @return The parameters of the meshing algorithm
	[[nodiscard]] AMCAX_API const MeshToolsParameters& Parameters() const noexcept;

	/// @brief Get the parameters of the meshing algorithm
	/// @return The parameters of the meshing algorithm
	[[nodiscard]] AMCAX_API MeshToolsParameters& Parameters() noexcept;

	/// @brief Get the status flags
	/// @return The status flags
	[[nodiscard]] AMCAX_API int GetStatusFlags() const noexcept;

private:
	void InitParameters();

	MeshToolsParameters parameters;
	int status = 0;
};
} // namespace AMCAX

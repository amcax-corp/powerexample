/// @file       STEPTool.hpp
/// @brief		Utility class for operations on STEP shape data structures.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <memory>
#include <string>
#include <vector>

#include <step/ShapeRepresentationType.hpp>

namespace AMCAX
{
class TopoShape;
#ifdef AMCAXMeshing_Enable_EigenTraits
namespace Meshing::Mesh
{
class TriSoupTraits_Eigen;
}
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
namespace Meshing::Mesh
{
class TriSoupTraits_Coord;
}
#endif

namespace STEP
{
class STEPProduct;
class STEPStyledProduct;
class STEPLabelProduct;

template<typename T>
class STEPMeshProduct;

/// @brief Utility class for operations on STEP shape data structures.
class STEPTool
{
public:
	/// @brief Create a copy of the STEPProduct tree, applying transformations to all shapes.
	/// @param shapes The STEPProduct tree as a list.
	/// @return A new std::vector<std::shared_ptr<STEPProduct>> with the same structure, but transformations applied.
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPProduct>>
	ApplyTrsf(const std::vector<std::shared_ptr<STEPProduct>>& shapes);

	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPStyledProduct>>
	ApplyTrsf(const std::vector<std::shared_ptr<STEPStyledProduct>>& shapes);

	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPLabelProduct>>
	ApplyTrsf(const std::vector<std::shared_ptr<STEPLabelProduct>>& shapes);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>
	ApplyTrsf(const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& shapes);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>
	ApplyTrsf(const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& shapes);
#endif

	/// @brief Apply transformations to all definite shapes in the STEPProduct tree, in place.
	/// @param shapes The STEPProduct tree as a list.
	/// @return Reference to the input std::vector<std::shared_ptr<STEPProduct>>, modified in place.
	AMCAX_API static std::vector<std::shared_ptr<STEPProduct>>&
	ApplyTrsfInplace(std::vector<std::shared_ptr<STEPProduct>>& shapes);

	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPStyledProduct>>&
	ApplyTrsfInplace(std::vector<std::shared_ptr<STEPStyledProduct>>& shapes);

	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPLabelProduct>>&
	ApplyTrsfInplace(std::vector<std::shared_ptr<STEPLabelProduct>>& shapes);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>&
	ApplyTrsfInplace(std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& shapes);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>&
	ApplyTrsfInplace(std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& shapes);
#endif

	/// @brief Create a flattened, one-dimensional copy of a STEPProduct tree.
	/// @param shapes The STEPProduct tree as a list.
	/// @param unrolling Whether to allow each node to contain zero or multiple shapes.
	/// @return A new std::vector<std::shared_ptr<STEPProduct>> containing all definite shapes, transformations applied.
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPProduct>>
	Flatten(const std::vector<std::shared_ptr<STEPProduct>>& shapes, bool unrolling = true);

	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPStyledProduct>>
	Flatten(const std::vector<std::shared_ptr<STEPStyledProduct>>& shapes, bool unrolling = true);

	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPLabelProduct>>
	Flatten(const std::vector<std::shared_ptr<STEPLabelProduct>>& shapes, bool unrolling = true);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>
	Flatten(const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& shapes,
		bool unrolling = true);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>
	Flatten(const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& shapes,
		bool unrolling = true);
#endif

	/// @brief Flatten a STEPProduct tree into a one-dimensional array, in place.
	/// @param shapes The STEPProduct tree as a list.
	/// @param unrolling Whether to allow each node to contain zero or multiple shapes.
	/// @return Reference to the input std::vector<std::shared_ptr<STEPProduct>>, now flattened.
	AMCAX_API static std::vector<std::shared_ptr<STEPProduct>>&
	FlattenInplace(std::vector<std::shared_ptr<STEPProduct>>& shapes, bool unrolling = true);

	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPStyledProduct>>&
	FlattenInplace(std::vector<std::shared_ptr<STEPStyledProduct>>& shapes, bool unrolling = true);

	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPLabelProduct>>&
	FlattenInplace(std::vector<std::shared_ptr<STEPLabelProduct>>& shapes, bool unrolling = true);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>&
	FlattenInplace(std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& shapes,
		bool unrolling = true);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>&
	FlattenInplace(std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& shapes,
		bool unrolling = true);
#endif

	/// @brief Create a TopoShape by combining all shapes in a STEPProduct tree.
	///
	/// If the tree contains only one shape, the shape itself is returned.
	/// @param root The root node of the STEPProduct tree.
	/// @return A compound TopoShape representing the combined shape(s).
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(const std::shared_ptr<STEPProduct>& root);

	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(const std::shared_ptr<STEPStyledProduct>& root);

	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(const std::shared_ptr<STEPLabelProduct>& root);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>& root);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>& root);
#endif

	/// @brief Create a TopoShape by combining all shapes in a vector of STEPProduct nodes.
	///
	/// If the list contains only one shape, the shape itself is returned.
	/// @param shapes The std::vector<std::shared_ptr<STEPProduct>> to combine.
	/// @return A compound TopoShape representing the combined shape(s).
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::vector<std::shared_ptr<STEPProduct>>& shapes);

	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::vector<std::shared_ptr<STEPStyledProduct>>& shapes);

	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::vector<std::shared_ptr<STEPLabelProduct>>& shapes);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& shapes);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	[[nodiscard]] AMCAX_API static AMCAX::TopoShape MakeCompound(
		const std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& shapes);
#endif

	/// @brief Create a STEPProduct tree from a TopoShape.
	/// @param shape The input TopoShape.
	/// @param emptyroot Whether to create an empty root node (used when the shape's PrivateLocation is not identity).
	/// @return A shared pointer to the root of the new STEPProduct tree.
	[[nodiscard]] AMCAX_API static std::shared_ptr<STEPProduct> MakeSTEPProduct(const AMCAX::TopoShape& shape,
		const bool emptyroot = true);

	/// @brief Create a std::vector<std::shared_ptr<STEPProduct>> from an array of TopoShape objects.
	/// @param shapes An array of TopoShape objects.
	/// @return A std::vector<std::shared_ptr<STEPProduct>> containing STEPProduct nodes for each shape.
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPProduct>>
	MakeSTEPProducts(const std::vector<AMCAX::TopoShape>& shapes);

	/// @brief Extract a subset of a std::vector<std::shared_ptr<STEPProduct>> containing only specified ShapeRepresentation types.
	/// @param shapes The std::vector<std::shared_ptr<STEPProduct>> to filter. May be modified if erase is true.
	/// @param reptype The shape representation type to include.
	/// @param erase Whether to remove empty product nodes from the original vector if true.
	/// @return A std::vector<std::shared_ptr<STEPProduct>> containing only nodes of the specified representation type.
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPProduct>> ExtractRepresentation(
		std::vector<std::shared_ptr<STEPProduct>>& shapes,
		ShapeRepresentationType reptype,
		bool erase = true);

	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPStyledProduct>> ExtractRepresentation(
		std::vector<std::shared_ptr<STEPStyledProduct>>& shapes,
		ShapeRepresentationType reptype,
		bool erase = true);

	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPLabelProduct>> ExtractRepresentation(
		std::vector<std::shared_ptr<STEPLabelProduct>>& shapes,
		ShapeRepresentationType reptype,
		bool erase = true);

#ifdef AMCAXMeshing_Enable_EigenTraits
	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>> ExtractRepresentation(
		std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>>>& shapes,
		ShapeRepresentationType reptype,
		bool erase = true);
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	/// @overload
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>> ExtractRepresentation(
		std::vector<std::shared_ptr<STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>>>& shapes,
		ShapeRepresentationType reptype,
		bool erase = true);
#endif

	/// @brief Write a TopoShape to a stream in STEP format.
	/// @param s The TopoShape to write.
	/// @param os The output stream.
	/// @retval true At least one shape representation was written successfully.
	/// @retval false No representation could be written.
	AMCAX_API static bool Write(const AMCAX::TopoShape& s, std::ostream& os);

	/// @brief Read a TopoShape from a stream in STEP format.
	/// @param s The TopoShape to populate.
	/// @param is The input stream.
	/// @retval true The shape was read successfully.
	/// @retval false Failed to read a valid shape.
	AMCAX_API static bool Read(AMCAX::TopoShape& s, std::istream& is);

	/// @brief Write a TopoShape to a file in STEP format.
	/// @param s The TopoShape to write.
	/// @param file The output file path.
	/// @retval true At least one shape representation was written successfully.
	/// @retval false No representation could be written.
	AMCAX_API static bool Write(const AMCAX::TopoShape& s, const std::string& file);

	/// @brief Read a TopoShape from a file in STEP format.
	/// @param s The TopoShape to populate.
	/// @param file The input file path.
	/// @retval true The shape was read successfully.
	/// @retval false Failed to read a valid shape.
	AMCAX_API static bool Read(AMCAX::TopoShape& s, const std::string& file);
};
} // namespace STEP
} // namespace AMCAX

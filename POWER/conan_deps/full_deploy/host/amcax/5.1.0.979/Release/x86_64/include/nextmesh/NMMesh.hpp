/// @file      NMMesh.hpp
/// @brief     Class of NextMesh Mesh
/// @details   Operations related to the generated mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>
#include <iostream>
#include <memory>
#include <nextmesh/Macros.hpp>
#include <vector>

#ifdef INTERNAL_TEST
	#include <nextmesh/MeshData.h>
#endif

namespace AMCAX {
namespace NextMesh {

class MeshDataImpl;

/**
 * @brief Class of mesh in NextMesh
 */
class NMMesh
{
public:
#ifdef INTERNAL_TEST
	AMCAX_TEST_API void            Reload(const MeshData &nmd);
	AMCAX_TEST_API const MeshData &ExportData() const;
#endif

	AMCAX_API ~NMMesh();

	/**
	 * @brief determine whether the mesh is valid
	 * @return mesh validity
	 */
	AMCAX_API bool IsValid();

	/**
	 * @brief Write the mesh to the file in the specified format
	 * @param filename full filename
	 * @param ft filetype, the file format depends on ft if it is not AUTO, else
	 * the suffix of filename
	 * @param outP output control parameters
	 */
	AMCAX_API void Write(const std::string &fileName,
	                     const OutFileType  ft   = OutFileType::AUTO,
	                     const OutParams   &outP = {});

	/**
	 * @brief Write the mesh to the file in the GMsh format(.msh)
	 * @param fileName The name of the output file
	 * @param binary A flag indicating whether to write the file in binary format
	 * (true) or ASCII format (false)
	 * @param saveParametric A flag indicating whether to save parametric data
	 * @param version The version of Gmsh file
	 * @param outP The parameters that control the output
	 */
	AMCAX_API void WriteGmsh(const std::string &fileName, const bool binary,
	                         const bool       saveParametric,
	                         const double     version = 4.1,
	                         const OutParams &outP    = {});

	/**
	 * @brief Get the number of the elements in the mesh
	 * @return The number of the elements in the mesh
	 */
	AMCAX_API Indext GetElementCount() const;

	/**
	 * @brief Get the element of the mesh by index
	 * @param elemIdx Element index : [0, GetElementCount())
	 * @return The handle of element
	 */
	AMCAX_API NMMeshElem GetElementByIndex(const Indext &elemIdx) const;

	/**
	 * @brief Get the global id of the element
	 * @param elem Element
	 * @return The global id of the element
	 */
	AMCAX_API Indext ElementGetID(const NMMeshElem &elem) const;

	/**
	 * @brief Get the type of the element
	 * @param elem Element
	 * @return The type of the element
	 */
	AMCAX_API ElemType ElementGetType(const NMMeshElem &elem) const;
	/**
	 * @brief Get the number of the nodes in the element
	 * @param elem Element
	 * @return The number of the nodes in the element
	 */
	AMCAX_API Indext   ElementGetNodeCount(const NMMeshElem &elem) const;

	/**
	 * @brief Get the node at the index in the element
	 * @param elem Element
	 * @param nodeIdx The node index in the element
	 * @return The node at the index
	 */
	AMCAX_API NMMeshNode ElementGetNode(const NMMeshElem &elem,
	                                    const Indext     &nodeIdx) const;

	/**
	 * @brief Get the number of elements within the entity, excluding those on the
	 * boundary
	 * @param ent Entity
	 * @return the number of elements
	 */
	AMCAX_API Indext EntityGetElementCount(const NMEntity &ent) const;

	/**
	 * @brief Get the element of entity by index
	 * @param ent Entity
	 * @param elemIdx Element index : [0, EntityGetElementCount(ent))
	 * @return Element
	 */
	AMCAX_API NMMeshElem EntityGetElementByIndex(const NMEntity &ent,
	                                             const Indext   &elemIdx) const;

	/**
	 * @brief Get the number of the nodes in the mesh
	 * @return The number of the nodes in the mesh
	 */
	AMCAX_API Indext GetNodeCount() const;

	/**
	 * @brief Get the node of the mesh by index
	 * @param nodeIdx Node index : [0, GetNodeCount())
	 * @return The handle of node
	 */
	AMCAX_API NMMeshNode GetNodeByIndex(const Indext &nodeIdx) const;

	/**
	 * @brief Get the global id of the node
	 * @param node Node
	 * @return The global id of the node
	 */
	AMCAX_API Indext   NodeGetID(const NMMeshNode &node) const;
	/**
	 * @brief Get the position of the node
	 * @param node The node
	 * @return The position of the node
	 */
	AMCAX_API NMPoint3 NodeGetPosition(const NMMeshNode &node) const;

	/**
	 * @brief Get the first parameter of the node. This interface is only valid
	 * for the nodes on edge and face.
	 * @param node Node
	 * @return The first parameter. If the node locates on vertex or solid, throw
	 * exception.
	 */
	AMCAX_API [[deprecated]] double
	NodeGetFirstParameter(const NMMeshNode &node) const;

	/**
	 * @brief Get the second parameter of the node. This interface is only valid
	 * for the nodes on face.
	 * @param node Node
	 * @return The second parameter. If the node locates on vertex, edge or solid,
	 * throw exception.
	 */
	AMCAX_API [[deprecated]] double
	NodeGetSecondParameter(const NMMeshNode &node) const;

	/**
	 * @brief Get the entity where the node is located
	 * @param node Node
	 * @return The entity containing the node
	 */
	AMCAX_API NMEntity NodeGetEntity(const NMMeshNode &node) const;

	/**
	 * @brief Get the number of nodes within the entity, excluding those on the
	 * boundary
	 * @param ent Entity
	 * @return The number of nodes
	 */
	AMCAX_API Indext EntityGetNodeCount(const NMEntity &ent) const;

	/**
	 * @brief Get the node of entity by index
	 * @param ent Entity
	 * @param nodeIdx The node index : [0, EntityGetNodeCount(ent))
	 * @return Node
	 */
	AMCAX_API NMMeshNode EntityGetNodeByIndex(const NMEntity &ent,
	                                          const Indext   &nodeIdx) const;

	/// @brief Refine the mesh by subdivision
	/// @param onGeom Whether it is attached to the geometry
	AMCAX_API void Refine(const bool onGeom);

	/// @brief compute the element quality with a specified quality type
	/// @param elem The mesh element
	/// @param qtye The type of the mesh quality
	/// @param cstye The type of the commercial software
	/// @return The Element quality
	AMCAX_API double ComputeQuality(const NMMeshElem        &elem,
	                                const QualityType        qtye,
	                                const CommercialSoftware cstye);

	/**
	 * @brief Create and add an element into the entity
	 * @param ent Entity
	 * @param etye Element type
	 * @param vs The ordered mesh nodes in the element
	 * @return The mesh element
	 */
	AMCAX_API [[deprecated]] NMMeshElem
	EntityAddElement(NMEntity ent, const ElemType etye,
	                 const std::vector<NMMeshNode> &vs);

	/**
	 * @brief Create and add a node into the entity.
	 * @param ent Entity
	 * @param pos Position of the node
	 * @return The mesh node
	 */
	AMCAX_API [[deprecated]] NMMeshNode EntityAddNode(NMEntity        ent,
	                                                  const NMPoint3 &pos);
#ifdef INTERNAL_TEST

	///**
	// * @brief Create and add a node into the entity. Only 0, 1, and 2 parameters
	// * are valid in 0, 1, and 2 dimensions, respectively.
	// * @param ent Entity
	// * @param u The parameter in the first dimension
	// * @param v The parameter in the second dimension
	// * @return The mesh node
	// */
	// AMCAX_TEST_API NMMeshNode EntityAddNode(NMEntity ent, double u, double v);
#endif // INTERNAL_TEST

private:
	NMMesh();
	std::shared_ptr<MeshDataImpl> mDatImpl = nullptr;
	friend class NMAPIModel;
};

} // namespace NextMesh
} // namespace AMCAX
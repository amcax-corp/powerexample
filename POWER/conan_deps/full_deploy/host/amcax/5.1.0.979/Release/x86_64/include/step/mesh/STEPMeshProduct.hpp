/// @file		STEPMeshProduct.hpp
/// @brief		Product node representing a STEP entity with associated mesh data.
/// @copyright	Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par		This file is part of AMCAX kernel.
#pragma once

#include <common/Macros.hpp>

#include <unordered_map>

#include <step/PNode.hpp>
#include <step/ShapeProperty.hpp>
#include <step/mesh/STEPMesh.hpp>

#include <mesh/TriSoup.hpp>

namespace AMCAX
{
namespace STEP
{
/// @brief Product node representing a STEP entity with associated mesh data.
/// @details
/// This class extends the common PNode base with additional storage
/// for per-shape properties and meshing results.
/// The template parameter @p Traits defines the mesh traits (e.g. Eigen or Coord).
template<typename Traits>
class STEPMeshProduct : public PNode<STEPMeshProduct<Traits>>
{
private:
	std::vector<std::unordered_map<TopoShape, ShapeProperty>> m_properties; ///< Properties for each shape.
	std::vector<std::vector<STEPMesh<Traits>>> m_meshes;					///< Meshes for each shape.

public:
	/// @brief Construct an empty STEPMeshProduct object.
	AMCAX_API STEPMeshProduct();

	/// @brief Copy constructor.
	/// @param orig Object to copy.
	AMCAX_API STEPMeshProduct(const STEPMeshProduct<Traits>& orig);

	/// @brief Move constructor.
	/// @param orig Object to move.
	AMCAX_API STEPMeshProduct(STEPMeshProduct<Traits>&& orig) noexcept;

	/// @brief Construct from shared pointer.
	/// @param orig Shared pointer to object to copy.
	AMCAX_API STEPMeshProduct(const std::shared_ptr<STEPMeshProduct<Traits>>& orig);

	/// @brief Virtual destructor.
	AMCAX_API virtual ~STEPMeshProduct() noexcept;

	/// @brief Get all shapes in this product.
	/// @details Delegates to target node if this is a shadow.
	/// @return Const reference to shapes.
	AMCAX_API const std::vector<TopoShape>& Shapes() const;

	/// @brief Get the number of shapes in this product.
	/// @details Delegates to target node if this is a shadow.
	/// @return Number of shapes.
	AMCAX_API size_t ShapesSize() const;

	/// @brief Get a specific shape by index.
	/// @details Delegates to target node if this is a shadow.
	/// @param index Index of the shape.
	/// @return Const reference to the shape.
	AMCAX_API const TopoShape& ShapeAt(size_t index) const;

	/// @overload
	AMCAX_API TopoShape& ShapeAt(size_t index);

private:
	/// @brief Get shapes owned by this node (ignoring shadow indirection).
	/// @return Const reference to owned shapes.
	AMCAX_API const std::vector<TopoShape>& OwnedShapes() const;

	/// @brief Get the number of owned shapes.
	/// @return Number of owned shapes.
	AMCAX_API size_t OwnedShapesSize() const;

	/// @brief Get an owned shape by index.
	/// @param index Index of the shape.
	/// @return Const reference to the shape.
	AMCAX_API const TopoShape& OwnedShapeAt(size_t index) const;

	/// @overload
	AMCAX_API TopoShape& OwnedShapeAt(size_t index);

public:
	/// @brief Get properties for all shapes.
	/// @details Delegates to target node if this is a shadow.
	/// @return Const reference to shape property maps.
	AMCAX_API const std::vector<std::unordered_map<TopoShape, ShapeProperty>>& Properties() const;

	/// @brief Get the number of property sets (one per shape).
	/// @details Delegates to target node if this is a shadow.
	/// @return Number of property maps.
	AMCAX_API size_t PropertiesSize() const;

	/// @brief Get properties for a specific shape.
	/// @details Delegates to target node if this is a shadow.
	/// @param index Index of shape (and its associated property map).
	/// @return Const reference to the property map.
	AMCAX_API const std::unordered_map<TopoShape, ShapeProperty>& PropertyAt(size_t index) const;

	/// @overload
	AMCAX_API std::unordered_map<TopoShape, ShapeProperty>& PropertyAt(size_t index);

private:
	/// @brief Get owned property maps for all shapes.
	/// @return Const reference to owned maps.
	AMCAX_API const std::vector<std::unordered_map<TopoShape, ShapeProperty>>& OwnedProperties() const;

	/// @brief Get number of owned property maps.
	/// @return Number of owned maps.
	AMCAX_API size_t OwnedPropertiesSize() const;

	/// @brief Get an owned property map by index.
	/// @param index Index of the map.
	/// @return Const reference to the map.
	AMCAX_API const std::unordered_map<TopoShape, ShapeProperty>& OwnedPropertyAt(size_t index) const;

	/// @overload
	AMCAX_API std::unordered_map<TopoShape, ShapeProperty>& OwnedPropertyAt(size_t index);

public:
	/// @brief Get all length factors.
	/// @details Delegates to target node if this is a shadow.
	/// @note Not affected by STEPReader::SetUnit().
	/// @return Const reference to factors.
	AMCAX_API const std::vector<ShapeFactors>& Factors() const;

	/// @brief Get number of length factors.
	/// @details Delegates if shadow.
	/// @return Count of factors.
	AMCAX_API size_t FactorsSize() const;

	/// @brief Get a length factor by index.
	/// @details Delegates if shadow.
	/// @param index Index of the factor.
	/// @return Const reference to factor.
	AMCAX_API const ShapeFactors& FactorAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeFactors& FactorAt(size_t index);

private:
	/// @brief Get length factors owned by this node.
	/// @return Const reference to owned factors.
	AMCAX_API const std::vector<ShapeFactors>& OwnedFactors() const;

	/// @brief Get number of owned factors.
	/// @return Count of owned factors.
	AMCAX_API size_t OwnedFactorsSize() const;

	/// @brief Get an owned factor by index.
	/// @param index Index.
	/// @return Const reference to factor.
	AMCAX_API const ShapeFactors& OwnedFactorAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeFactors& OwnedFactorAt(size_t index);

public:
	/// @brief Get representation types for shapes.
	/// @details Delegates if shadow.
	/// @return Const reference to representation types.
	AMCAX_API const std::vector<ShapeRepresentationType>& ShapeRepresentations() const;

	/// @brief Get number of representation types.
	/// @details Delegates if shadow.
	/// @return Count of representation types.
	AMCAX_API size_t ShapeRepresentationsSize() const;

	/// @brief Get representation type by index.
	/// @details Delegates if shadow.
	/// @param index Index.
	/// @return Const reference to type.
	AMCAX_API const ShapeRepresentationType& ShapeRepresentationAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeRepresentationType& ShapeRepresentationAt(size_t index);

private:
	/// @brief Get representation types owned by this node.
	/// @return Const reference to owned types.
	AMCAX_API const std::vector<ShapeRepresentationType>& OwnedShapeRepresentations() const;

	/// @brief Get number of owned representation types.
	/// @return Count of owned types.
	AMCAX_API size_t OwnedShapeRepresentationsSize() const;

	/// @brief Get owned representation type by index.
	/// @param index Index.
	/// @return Const reference to type.
	AMCAX_API const ShapeRepresentationType& OwnedShapeRepresentationAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeRepresentationType& OwnedShapeRepresentationAt(size_t index);

public:
	/// @brief Get the product name.
	/// @details Delegates if shadow.
	/// @return Name string.
	AMCAX_API const std::string& ProductName() const;

	/// @brief Set product name.
	/// @details Delegates if shadow.
	/// @param product_name The new name.
	AMCAX_API void SetProductName(const std::string& product_name);

private:
	/// @brief Get owned product name.
	/// @return Name string.
	AMCAX_API const std::string& OwnedProductName() const;

	/// @brief Set owned product name.
	/// @param product_name The new name.
	AMCAX_API void SetOwnedProductName(const std::string& product_name);

public:
	/// @brief Get description.
	/// @details Delegates if shadow.
	/// @return Description string.
	AMCAX_API const std::string& Description() const;

	/// @brief Set description.
	/// @details Delegates if shadow.
	/// @param description The new description.
	AMCAX_API void SetDescription(const std::string& description);

private:
	/// @brief Get owned description.
	/// @return Description string.
	AMCAX_API const std::string& OwnedDescription() const;

	/// @brief Set owned description.
	/// @param description The new description.
	AMCAX_API void SetOwnedDescription(const std::string& description);

public:
	/// @brief Get location of this product node.
	/// @return Const reference to location.
	AMCAX_API const TopoLocation& Location() const;

	/// @brief Set location.
	/// @param location New location.
	AMCAX_API void SetLocation(const TopoLocation& location);

	/// @brief Clear location.
	AMCAX_API void ClearLocation();

	/// @brief Get all child products.
	/// @details If this is a shadow node, returns from the target node.
	/// @return Const reference to child product list.
	AMCAX_API const std::vector<std::shared_ptr<STEPMeshProduct<Traits>>>& Children() const;

	/// @brief Get the number of child products.
	/// @details If this is a shadow node, returns from the target node.
	/// @return Number of children.
	AMCAX_API size_t ChildrenSize() const;

	/// @brief Get a specific child product by index.
	/// @details If this is a shadow node, accesses the target node.
	/// @param index Index of the child.
	/// @return Const reference to the child product pointer.
	AMCAX_API const std::shared_ptr<STEPMeshProduct<Traits>>& ChildAt(size_t index) const;

	/// @overload
	AMCAX_API std::shared_ptr<STEPMeshProduct<Traits>>& ChildAt(size_t index);

	/// @brief Add a child product node.
	/// @details If this is a shadow node, adds to the target node.
	/// @param child The child node to add.
	AMCAX_API void AddChild(const std::shared_ptr<STEPMeshProduct<Traits>>& child);

	/// @brief Remove a child at specific index.
	/// @param index Index of the child.
	AMCAX_API void RemoveChildAt(size_t index);

	/// @brief Remove all child nodes.
	/// @details If this is a shadow node, clears the target node.
	AMCAX_API void ClearChildren();

private:
	/// @brief Get child products owned by this node (not via shadow indirection).
	/// @return Const reference to the owned children.
	AMCAX_API const std::vector<std::shared_ptr<STEPMeshProduct<Traits>>>& OwnedChildren() const;

	/// @brief Get the number of owned children.
	/// @return Number of owned children.
	AMCAX_API size_t OwnedChildrenSize() const;

	/// @brief Get specific owned child by index.
	/// @param index Index of the child.
	/// @return Const reference to the child product pointer.
	AMCAX_API const std::shared_ptr<STEPMeshProduct<Traits>>& OwnedChildAt(size_t index) const;

	/// @overload
	AMCAX_API std::shared_ptr<STEPMeshProduct<Traits>>& OwnedChildAt(size_t index);

	/// @brief Add a child node to this product node directly.
	/// @param child The child node to add.
	AMCAX_API void AddOwnedChild(const std::shared_ptr<STEPMeshProduct<Traits>>& child);

	/// @brief Remove a child at specific index.
	/// @param index Index of the child.
	AMCAX_API void RemoveOwnedChildAt(size_t index);

	/// @brief Remove all child nodes from this product node.
	AMCAX_API void ClearOwnedChildren();

public:
	/// @brief Add a shape object to this product node.
	/// @details If this is a shadow node, adds to the target node instead.
	/// @param shape Shape to add.
	/// @param chain Property chain for the shape.
	/// @param factors ShapeFactors for the shape.
	/// @param reptype Shape representation type.
	/// @note An empty label is also added as placeholder.
	AMCAX_API void AddShape(const TopoShape& shape,
		const std::unordered_map<TopoShape, ShapeProperty>& chain =
			std::unordered_map<TopoShape, ShapeProperty>(),
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove a shape by index.
	/// @details If this is a shadow node, removes from the target node.
	/// @param index Index of the shape to remove.
	AMCAX_API void RemoveShapeAt(size_t index);

	/// @brief Remove all shapes.
	/// @details If this is a shadow node, clears the target node's shapes.
	/// @note Also removes all property chains, labels, factors, and representation types.
	AMCAX_API void ClearShapes();

private:
	/// @brief Add a shape to this product node directly (not via shadow indirection).
	/// @param shape Shape to add.
	/// @param chain Property chain.
	/// @param factors ShapeFactors.
	/// @param reptype Representation type.
	/// @note An empty label will be added as a placeholder.
	AMCAX_API void AddOwnedShape(const TopoShape& shape,
		const std::unordered_map<TopoShape, ShapeProperty>& chain =
			std::unordered_map<TopoShape, ShapeProperty>(),
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove a specific owned shape by index.
	/// @param index Index of the shape to remove.
	AMCAX_API void RemoveOwnedShapeAt(size_t index);

	/// @brief Remove all shapes from this product node.
	/// @note Also removes all property chains, labels, factors, and representation types.
	AMCAX_API void ClearOwnedShapes();

public:
	/// @brief Get the pointer to the target (referenced) node if this is a shadow node.
	/// @details Returns nullptr if this is not a shadow node.
	/// @return Const reference to the pointer to the target node.
	AMCAX_API const std::shared_ptr<STEPMeshProduct<Traits>>& Target() const;

	/// @brief Mark this node as a shadow node.
	/// @details Shadow nodes only hold location; other data is redirected.
	/// @param target Pointer to the target node. If null, this node becomes a normal node.
	/// @param clear If true, clears all shapes, properties etc from this node.
	AMCAX_API void MarkShadow(const std::shared_ptr<STEPMeshProduct<Traits>>& target, bool clear = false);

	/// @brief Convert a shadow node back to a normal node.
	/// @param clone If true, deep-copies the target node's data (including children).
	AMCAX_API void MarkNormal(bool clone = true);

	/// @brief Check whether this node is a shadow node.
	/// @retval true If this node is a shadow node.
	/// @retval false Otherwise.
	AMCAX_API bool IsShadow() const;

	/// @brief Create a composite TopoShape of all shapes in this (sub)tree.
	/// @details If this is a shadow node, returns the target node's composite shape.
	/// @param recursive If true, includes children recursively.
	/// @return The composite TopoShape.
	AMCAX_API TopoShape OneShape(bool recursive = false) const;

	/// @brief Create a copy of this node, excluding children.
	/// @return A new instance copied from this node (no children).
	AMCAX_API std::shared_ptr<STEPMeshProduct<Traits>> EmptyCopy() const;

	/// @brief Get Representation Items
	/// @return Representation Items
	AMCAX_API const std::map<std::string, std::vector<RepItem>>& RepItems() const;

	/// @overload
	AMCAX_API std::map<std::string, std::vector<RepItem>>& RepItems();

	/// @brief Get the number of Representation Items.
	/// @return Number of Representation Items.
	AMCAX_API size_t RepItemsSize() const;

	/// @brief Add a Representation Item to this product node.
	/// @param name The name of the Representation Item.
	/// @param items The items.
	AMCAX_API void AddRepItem(const std::string& name, const std::vector<RepItem>& items);

	/// @brief Setter for Representation Items
	/// @param items The Representation items
	AMCAX_API void SetRepItems(const std::map<std::string, std::vector<RepItem>>& items);

	/// @brief Remove all the Representation Items.
	AMCAX_API void ClearRepItems();

private:
	/// @brief Get Representation Items
	/// @return Representation Items
	AMCAX_API const std::map<std::string, std::vector<RepItem>>& OwnedRepItems() const;

	/// @overload
	AMCAX_API std::map<std::string, std::vector<RepItem>>& OwnedRepItems();
	/// @brief Get the number of Representation Items.
	/// @return Number of Representation Items.
	AMCAX_API size_t OwnedRepItemsSize() const;

	/// @brief Add a Representation Item to this product node.
	/// @param name The name of the Representation Item.
	/// @param items The items.
	AMCAX_API void AddOwnedRepItem(const std::string& name, const std::vector<RepItem>& items);

	/// @brief Setter for Representation Items
	/// @param items The Representation items
	AMCAX_API void SetOwnedRepItems(const std::map<std::string, std::vector<RepItem>>& items);

	/// @brief Remove all the Representation Items.
	AMCAX_API void ClearOwnedRepItems();

public:
	/// @brief Create a deep copy of a list of STEPStyledProduct nodes.
	/// @details If a shadow node is present, its target node is also copied.
	/// @param orig The original list of STEPStyledProduct nodes.
	/// @return Deep-copied list.
	AMCAX_API static std::vector<std::shared_ptr<STEPMeshProduct<Traits>>>
	DeepCopy(const std::vector<std::shared_ptr<STEPMeshProduct<Traits>>>& orig);

	/// @brief Create a composite TopoShape from a list of STEPStyledProduct nodes.
	/// @param nodes List of STEPStyledProduct nodes.
	/// @return The composite TopoShape.
	AMCAX_API static TopoShape OneShape(const std::vector<std::shared_ptr<STEPMeshProduct<Traits>>>& nodes);

	/// @brief Count the number of solids.
	/// @param recursive If true, include child nodes.
	/// @return Number of solids.
	AMCAX_API size_t SolidCount(const bool recursive = true) const;

	/// @brief Count the number of meshes.
	/// @param recursive If true, include child nodes.
	/// @return Number of meshes.
	AMCAX_API size_t MeshCount(const bool recursive = true) const;

	/// @brief Perform meshing on this product node.
	/// @param recursive If true, include children.
	/// @param linDeflection Linear deflection.
	/// @param isRelative True to compute relative deflection.
	/// @retval true If meshing succeeded on at least one shell.
	/// @retval false Otherwise.
	AMCAX_API bool Perform(const bool recursive = true,
		const double& linDeflection = 1e-2,
		bool isRelative = true);

	/// @overload
	/// @param angDeflection Angular deflection.
	AMCAX_API bool Perform(const bool recursive,
		const double& linDeflection,
		bool isRelative,
		double angDeflection);

	/// @brief Get all meshes.
	/// @return Const reference to mesh list.
	AMCAX_API const std::vector<std::vector<STEPMesh<Traits>>>& Meshes() const;

	/// @brief Get number of mesh sets (per shape).
	/// @return Count of meshes.
	AMCAX_API size_t MeshesSize() const;

	/// @brief Get meshes for a specific shape.
	/// @param index Index of the shape.
	/// @return Const reference to mesh vector.
	AMCAX_API const std::vector<STEPMesh<Traits>>& MeshAt(size_t index) const;

	/// @overload
	AMCAX_API std::vector<STEPMesh<Traits>>& MeshAt(size_t index);
};
} // namespace STEP
} // namespace AMCAX

namespace AMCAX
{
namespace STEP
{
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAX_CLASS_API STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAX_CLASS_API STEPMeshProduct<Meshing::Mesh::TriSoupTraits_Coord>;
#endif
} // namespace STEP
} // namespace AMCAX

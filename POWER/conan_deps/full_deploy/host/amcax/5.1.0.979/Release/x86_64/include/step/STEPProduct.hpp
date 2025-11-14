/// @file       STEPProduct.hpp
/// @brief		Represents a product node in the STEP standard (topology / geometry only, no style).
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <step/PNode.hpp>

namespace AMCAX
{
namespace STEP
{
/// @brief Represents a product node in the STEP standard (topology / geometry only, no style).
class AMCAX_CLASS_API STEPProduct : public PNode<STEPProduct>
{
public:
	/// @brief Default constructor. All members are initialized as empty.
	AMCAX_API STEPProduct();

	/// @brief Construct with a TopoShape and optional product name.
	/// @param s The TopoShape to store in this product node.
	/// @param n Optional name for this product node.
	AMCAX_API explicit STEPProduct(const TopoShape& s,
		const std::string& n = std::string());

	/// @brief Copy constructor.
	/// @param other The STEPProduct object to copy.
	AMCAX_API explicit STEPProduct(const STEPProduct& other);

	/// @brief Copy constructor from shared pointer.
	/// @param other Shared pointer to the STEPProduct object to copy.
	AMCAX_API explicit STEPProduct(const std::shared_ptr<STEPProduct>& other);

	/// @brief Move constructor.
	/// @param other The STEPProduct object to move from.
	AMCAX_API explicit STEPProduct(STEPProduct&& other) noexcept;

	/// @brief Virtual destructor.
	AMCAX_API virtual ~STEPProduct() noexcept;

	/// @brief Get all shapes in this product.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the list of shapes.
	AMCAX_API const std::vector<TopoShape>& Shapes() const;

	/// @brief Get the number of shapes in this product.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of shapes.
	AMCAX_API size_t ShapesSize() const;

	/// @brief Get a specific shape by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index of the shape.
	/// @return Const reference to the shape at the given index.
	AMCAX_API const TopoShape& ShapeAt(size_t index) const;

	/// @overload
	AMCAX_API TopoShape& ShapeAt(size_t index);

	/// @brief Get shapes owned by this node (ignoring shadow indirection).
	/// @return Const reference to the owned shapes.
	AMCAX_API const std::vector<TopoShape>& OwnedShapes() const;

	/// @brief Get the number of owned shapes in this node.
	/// @return Number of owned shapes.
	AMCAX_API size_t OwnedShapesSize() const;

	/// @brief Get a specific owned shape by index.
	/// @param index Index of the shape.
	/// @return Const reference to the owned shape at the given index.
	AMCAX_API const TopoShape& OwnedShapeAt(size_t index) const;

	/// @overload
	AMCAX_API TopoShape& OwnedShapeAt(size_t index);

	/// @brief Get all length factors for each shape.
	/// @details Delegates to the target node if this is a shadow.
	/// @note Result is not affected by STEPReader::SetUnit().
	/// @return Const reference to the list of factors.
	AMCAX_API const std::vector<ShapeFactors>& Factors() const;

	/// @brief Get the number of length factors.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of length factors.
	AMCAX_API size_t FactorsSize() const;

	/// @brief Get a specific length factor by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index corresponding to the shape.
	/// @return Const reference to the factor.
	AMCAX_API const ShapeFactors& FactorAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeFactors& FactorAt(size_t index);

	/// @brief Get length factors owned by this node.
	/// @note Result is not affected by STEPReader::SetUnit().
	/// @return Const reference to the owned factors.
	AMCAX_API const std::vector<ShapeFactors>& OwnedFactors() const;

	/// @brief Get the number of owned length factors.
	/// @return Number of owned factors.
	AMCAX_API size_t OwnedFactorsSize() const;

	/// @brief Get a specific owned length factor by index.
	/// @param index Index of the factor.
	/// @return Const reference to the factor.
	AMCAX_API const ShapeFactors& OwnedFactorAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeFactors& OwnedFactorAt(size_t index);

	/// @brief Get the representation type for each shape.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the list of representation types.
	AMCAX_API const std::vector<ShapeRepresentationType>& ShapeRepresentations() const;

	/// @brief Get the number of representation types.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of representation types.
	AMCAX_API size_t ShapeRepresentationsSize() const;

	/// @brief Get a specific representation type by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index corresponding to the shape.
	/// @return Const reference to the representation type.
	AMCAX_API const ShapeRepresentationType& ShapeRepresentationAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeRepresentationType& ShapeRepresentationAt(size_t index);

	/// @brief Get representation types owned by this node.
	/// @return Const reference to the owned representation types.
	AMCAX_API const std::vector<ShapeRepresentationType>& OwnedShapeRepresentations() const;

	/// @brief Get the number of owned representation types.
	/// @return Number of owned representation types.
	AMCAX_API size_t OwnedShapeRepresentationsSize() const;

	/// @brief Get a specific owned representation type by index.
	/// @param index Index of the representation type.
	/// @return Const reference to the type.
	AMCAX_API const ShapeRepresentationType& OwnedShapeRepresentationAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeRepresentationType& OwnedShapeRepresentationAt(size_t index);

	/// @brief Get the product node's name.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the product name.
	AMCAX_API const std::string& ProductName() const;

	/// @brief Set the product node's name.
	/// @details Delegates to the target node if this is a shadow.
	/// @param product_name New product name.
	AMCAX_API void SetProductName(const std::string& product_name);

	/// @brief Get the name owned by this product node.
	/// @return Const reference to the owned product name.
	AMCAX_API const std::string& OwnedProductName() const;

	/// @brief Set the name of this product node.
	/// @param product_name New product name.
	AMCAX_API void SetOwnedProductName(const std::string& product_name);

	/// @brief Get the product node's description.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the product description.
	AMCAX_API const std::string& Description() const;

	/// @brief Set the product node's description.
	/// @details Delegates to the target node if this is a shadow.
	/// @param description New description.
	AMCAX_API void SetDescription(const std::string& description);

	/// @brief Get the description owned by this node.
	/// @return Const reference to the owned description.
	AMCAX_API const std::string& OwnedDescription() const;

	/// @brief Set the description of this product node.
	/// @param description New description.
	AMCAX_API void SetOwnedDescription(const std::string& description);

	/// @brief Get the location of this product node.
	/// @return Const reference to the location.
	AMCAX_API const TopoLocation& Location() const;

	/// @brief Set the location of this product node.
	/// @param location New location.
	AMCAX_API void SetLocation(const TopoLocation& location);

	/// @brief Clear the location of this product node.
	AMCAX_API void ClearLocation();

	/// @brief Get all child products.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the child product list.
	AMCAX_API const std::vector<std::shared_ptr<STEPProduct>>& Children() const;

	/// @brief Get the number of child products.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of children.
	AMCAX_API size_t ChildrenSize() const;

	/// @brief Get a specific child product by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index of the child.
	/// @return Const reference to the child pointer.
	AMCAX_API const std::shared_ptr<STEPProduct>& ChildAt(size_t index) const;

	/// @overload
	AMCAX_API std::shared_ptr<STEPProduct>& ChildAt(size_t index);

	/// @brief Add a child product node.
	/// @details Delegates to the target node if this is a shadow.
	/// @param child The child node to add.
	AMCAX_API void AddChild(const std::shared_ptr<STEPProduct>& child);

	/// @brief Remove a child at a specific index.
	/// @param index Index of the child.
	AMCAX_API void RemoveChildAt(size_t index);

	/// @brief Remove all child nodes.
	/// @details Delegates to the target node if this is a shadow.
	AMCAX_API void ClearChildren();

	/// @brief Get child products owned by this node (ignoring shadow indirection).
	/// @return Const reference to the owned children.
	AMCAX_API const std::vector<std::shared_ptr<STEPProduct>>& OwnedChildren() const;

	/// @brief Get the number of owned children.
	/// @return Number of owned children.
	AMCAX_API size_t OwnedChildrenSize() const;

	/// @brief Get a specific owned child by index.
	/// @param index Index of the child.
	/// @return Const reference to the owned child pointer.
	AMCAX_API const std::shared_ptr<STEPProduct>& OwnedChildAt(size_t index) const;

	/// @overload
	AMCAX_API std::shared_ptr<STEPProduct>& OwnedChildAt(size_t index);

	/// @brief Add a child node directly to this product node.
	/// @param child The child node to add.
	AMCAX_API void AddOwnedChild(const std::shared_ptr<STEPProduct>& child);

	/// @brief Remove an owned child at a specific index.
	/// @param index Index of the child.
	AMCAX_API void RemoveOwnedChildAt(size_t index);

	/// @brief Remove all owned child nodes.
	AMCAX_API void ClearOwnedChildren();

	/// @brief Add a shape to this product node.
	/// @details Delegates to the target node if this is a shadow.
	/// @param shape Shape to add.
	/// @param factors Shape factors.
	/// @param reptype Shape representation type.
	/// @note An empty label is also added as placeholder.
	AMCAX_API void AddShape(const TopoShape& shape,
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove a shape by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index of the shape to remove.
	AMCAX_API void RemoveShapeAt(size_t index);

	/// @brief Remove all shapes.
	/// @details Delegates to the target node if this is a shadow.
	/// @note Also removes all factors and representation types.
	AMCAX_API void ClearShapes();

	/// @brief Add a shape directly to this product node (ignoring shadow indirection).
	/// @param shape Shape to add.
	/// @param factors Shape factors.
	/// @param reptype Representation type.
	/// @note An empty label will be added as placeholder.
	AMCAX_API void AddOwnedShape(const TopoShape& shape,
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove an owned shape by index.
	/// @param index Index of the shape to remove.
	AMCAX_API void RemoveOwnedShapeAt(size_t index);

	/// @brief Remove all owned shapes from this product node.
	/// @note Also removes all factors and representation types.
	AMCAX_API void ClearOwnedShapes();

	/// @brief Get the pointer to the target node if this is a shadow.
	/// @details Returns nullptr if this is not a shadow node.
	/// @return Const reference to the pointer to the target node.
	AMCAX_API const std::shared_ptr<STEPProduct>& Target() const;

	/// @brief Mark this node as a shadow node.
	/// @details Shadow nodes only hold location; all other data is delegated.
	/// @param target Pointer to the target node. If null, this node becomes a normal node.
	/// @param clear If true, clears all shapes, factors, and representation types from this node.
	AMCAX_API void MarkShadow(const std::shared_ptr<STEPProduct>& target, bool clear = false);

	/// @brief Convert a shadow node back to a normal node.
	/// @param clone If true, deep-copies the target node's data (including children).
	AMCAX_API void MarkNormal(bool clone = true);

	/// @brief Check whether this node is a shadow node.
	/// @retval true If this node is a shadow.
	/// @retval false Otherwise.
	AMCAX_API bool IsShadow() const;

	/// @brief Create a composite TopoShape of all shapes in this (sub)tree.
	/// @details Delegates to the target node if this is a shadow.
	/// @param recursive If true, includes children recursively.
	/// @return The composite TopoShape.
	AMCAX_API TopoShape OneShape(bool recursive = false) const;

	/// @brief Create a copy of this node, excluding children.
	/// @return A new instance copied from this node (without children).
	AMCAX_API std::shared_ptr<STEPProduct> EmptyCopy() const;

	/// @brief Get representation items.
	/// @return Const reference to the map of representation items.
	AMCAX_API const std::map<std::string, std::vector<RepItem>>& RepItems() const;

	/// @overload
	AMCAX_API std::map<std::string, std::vector<RepItem>>& RepItems();

	/// @brief Get the number of representation items.
	/// @return Number of map entries.
	AMCAX_API size_t RepItemsSize() const;

	/// @brief Add representation items under a given name.
	/// @param name The key name.
	/// @param items The list of representation items.
	AMCAX_API void AddRepItem(const std::string& name, const std::vector<RepItem>& items);

	/// @brief Replace the entire representation items map.
	/// @param items The new items map.
	AMCAX_API void SetRepItems(const std::map<std::string, std::vector<RepItem>>& items);

	/// @brief Remove all representation items.
	AMCAX_API void ClearRepItems();

	/// @brief Get owned representation items.
	/// @return Const reference to the owned map of representation items.
	AMCAX_API const std::map<std::string, std::vector<RepItem>>& OwnedRepItems() const;

	/// @overload
	AMCAX_API std::map<std::string, std::vector<RepItem>>& OwnedRepItems();

	/// @brief Get the number of owned representation items.
	/// @return Number of owned map entries.
	AMCAX_API size_t OwnedRepItemsSize() const;

	/// @brief Add owned representation items under a given name.
	/// @param name The key name.
	/// @param items The list of representation items.
	AMCAX_API void AddOwnedRepItem(const std::string& name, const std::vector<RepItem>& items);

	/// @brief Replace the entire owned representation items map.
	/// @param items The new items map.
	AMCAX_API void SetOwnedRepItems(const std::map<std::string, std::vector<RepItem>>& items);

	/// @brief Remove all owned representation items.
	AMCAX_API void ClearOwnedRepItems();

	/// @brief Create a deep copy of a list of STEPProduct nodes.
	/// @details If a shadow node is present, its target node is also copied.
	/// @param orig The original list of STEPProduct nodes.
	/// @return Deep-copied list.
	AMCAX_API static std::vector<std::shared_ptr<STEPProduct>> DeepCopy(const std::vector<std::shared_ptr<STEPProduct>>& orig);

	/// @brief Create a composite TopoShape from a list of STEPProduct nodes.
	/// @param nodes List of STEPProduct nodes.
	/// @return The composite TopoShape.
	AMCAX_API static TopoShape OneShape(const std::vector<std::shared_ptr<STEPProduct>>& nodes);
};
} // namespace STEP
} // namespace AMCAX

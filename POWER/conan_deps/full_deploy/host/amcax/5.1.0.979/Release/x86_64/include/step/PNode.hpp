/// @file       PNode.hpp
/// @brief		CRTP base class providing storage and operations for STEP product nodes.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <map>
#include <string>
#include <vector>

#include <topology/TopoLocation.hpp>
#include <topology/TopoShape.hpp>

#include <step/ShapeFactors.hpp>
#include <step/ShapeRepresentationType.hpp>
#include <step/repitem/RepItem.hpp>

namespace AMCAX::STEP
{
/// @brief CRTP base class providing storage and operations for STEP product nodes.
/// @details
/// This class implements all internal data members and low-level accessors/mutators
/// used by concrete product classes (e.g. STEPProduct, STEPStyledProduct, STEPLabelProduct).
/// It is not intended for direct use.
///
/// To keep documentation focused on public APIs, most of the members are wrapped with
/// `#ifndef DOXYGEN_SKIP` so they do not appear in generated user documentation.
template<typename T>
class PNode
{
#ifndef DOXYGEN_SKIP
private:
	// Shape, factors, representation types, and metadata.
	std::vector<TopoShape> m_shapes;
	std::vector<ShapeFactors> m_factors;
	std::vector<ShapeRepresentationType> m_rep_types;
	std::string m_productName;
	std::string m_description;
	TopoLocation m_location;

	// Tree structure.
	std::vector<std::shared_ptr<T>> m_children;
	std::shared_ptr<T> m_target;

	// Representation items.
	std::map<std::string, std::vector<RepItem>> m_rep_items;

protected:
	/// @brief Virtual destructor.
	virtual ~PNode() noexcept;

	/// @brief Default constructor. Initializes all members to empty/default state.
	PNode();

	/// @brief Construct with a TopoShape and optional product name.
	/// @param s Shape to add.
	/// @param n Optional product name.
	explicit PNode(const TopoShape& s, const std::string& n = std::string());

	/// @brief Copy constructor.
	/// @param other The node to copy.
	explicit PNode(const PNode& other);

	/// @brief Shared pointer copy constructor.
	/// @param other The node to copy (shared pointer).
	explicit PNode(const std::shared_ptr<PNode>& other);

	/// @brief Move constructor.
	/// @param other The node to move.
	explicit PNode(PNode&& other) noexcept;

	/// @brief Get number of shapes in this product.
	/// @details If this is a shadow node, returns the size from the target node.
	/// @return Number of shapes.
	const std::vector<TopoShape>& PrivateShapes() const;

	/// @brief Get number of shapes in this product.
	/// @details If this is a shadow node, returns the size from the target node.
	/// @return Number of shapes.
	size_t PrivateShapesSize() const;

	/// @brief Get specific shape by index.
	/// @details If this is a shadow node, accesses the shape from the target node.
	/// @param index Index of the shape.
	/// @return Const reference to the shape at the given index.
	const TopoShape& PrivateShapeAt(size_t index) const;

	/// @overload
	TopoShape& PrivateShapeAt(size_t index);

	/// @brief Get shapes owned by this product node (not considering shadow node indirection).
	/// @return Const reference to the owned shapes.
	const std::vector<TopoShape>& PrivateOwnedShapes() const;

	/// @brief Get the number of owned shapes in this node.
	/// @return Number of shapes owned by this node.
	size_t PrivateOwnedShapesSize() const;

	/// @brief Get specific owned shape by index.
	/// @param index Index of the shape.
	/// @return Const reference to the shape at the given index.
	const TopoShape& PrivateOwnedShapeAt(size_t index) const;

	/// @overload
	TopoShape& PrivateOwnedShapeAt(size_t index);

	/// @brief Get all length factors for each shape.
	/// @details If this is a shadow node, returns data from the target node.
	/// @note Result is not affected by StepReader::SetUnit()/Set().
	/// @return Const reference to the factors.
	const std::vector<ShapeFactors>& PrivateFactors() const;

	/// @brief Get the number of length factors.
	/// @details If this is a shadow node, returns size from the target node.
	/// @return Number of length factors.
	size_t PrivateFactorsSize() const;

	/// @brief Get specific length factor by index.
	/// @details If this is a shadow node, accesses the target node.
	/// @param index Index of the factor (corresponds to the shape at the same index).
	/// @return Const reference to the factor at the given index.
	const ShapeFactors& PrivateFactorAt(size_t index) const;

	/// @overload
	ShapeFactors& PrivateFactorAt(size_t index);

	/// @brief Get length factors owned by this product node.
	/// @note Result is not affected by StepReader::SetUnit()/Set().
	/// @return Const reference to the owned factors.
	const std::vector<ShapeFactors>& PrivateOwnedFactors() const;

	/// @brief Get the number of owned length factors.
	/// @return Number of factors owned by this node.
	size_t PrivateOwnedFactorsSize() const;

	/// @brief Get specific owned length factor by index.
	/// @param index Index of the factor.
	/// @return Const reference to the factor at the given index.
	const ShapeFactors& PrivateOwnedFactorAt(size_t index) const;

	/// @overload
	ShapeFactors& PrivateOwnedFactorAt(size_t index);

	/// @brief Get the representation type for each shape.
	/// @details If this is a shadow node, returns data from the target node.
	/// @return Const reference to the representation types.
	const std::vector<ShapeRepresentationType>& PrivateShapeRepresentations() const;

	/// @brief Get the number of representation types.
	/// @details If this is a shadow node, returns size from the target node.
	/// @return Number of representation types.
	size_t PrivateShapeRepresentationsSize() const;

	/// @brief Get specific representation type by index.
	/// @details If this is a shadow node, accesses the target node.
	/// @param index Index of the representation type (corresponds to the shape at the same index).
	/// @return Const reference to the representation type.
	const ShapeRepresentationType& PrivateShapeRepresentationAt(size_t index) const;

	/// @overload
	ShapeRepresentationType& PrivateShapeRepresentationAt(size_t index);

	/// @brief Get representation types owned by this product node.
	/// @return Const reference to the owned representation types.
	const std::vector<ShapeRepresentationType>& PrivateOwnedShapeRepresentations() const;

	/// @brief Get the number of owned representation types.
	/// @return Number of representation types owned by this node.
	size_t PrivateOwnedShapeRepresentationsSize() const;

	/// @brief Get specific owned representation type by index.
	/// @param index Index of the representation type.
	/// @return Const reference to the representation type.
	const ShapeRepresentationType& PrivateOwnedShapeRepresentationAt(size_t index) const;

	/// @overload
	ShapeRepresentationType& PrivateOwnedShapeRepresentationAt(size_t index);

	/// @brief Get the product node's name.
	/// @details If this is a shadow node, returns from the target node.
	/// @return Const reference to the product name.
	const std::string& PrivateProductName() const;

	/// @brief Set the product node's name.
	/// @details If this is a shadow node, updates the target node.
	/// @param product_name New product name.
	void PrivateSetProductName(const std::string& product_name);

	/// @brief Get the name owned by this product node.
	/// @return Const reference to the owned product name.
	const std::string& PrivateOwnedProductName() const;

	/// @brief Set the name of this product node.
	/// @param product_name New product name.
	void PrivateSetOwnedProductName(const std::string& product_name);

	/// @brief Get the product node's description.
	/// @details If this is a shadow node, returns from the target node.
	/// @return Const reference to the product description.
	const std::string& PrivateDescription() const;

	/// @brief Set the product node's description.
	/// @details If this is a shadow node, updates the target node.
	/// @param description New description.
	void PrivateSetDescription(const std::string& description);

	/// @brief Get the description owned by this product node.
	/// @return Const reference to the owned description.
	const std::string& PrivateOwnedDescription() const;

	/// @brief Set the description of this product node.
	/// @param description New description.
	void PrivateSetOwnedDescription(const std::string& description);

	/// @brief Get the location of this product node.
	/// @return Const reference to the location.
	const TopoLocation& PrivateLocation() const;

	/// @brief Set the location of this product node.
	/// @param location New location.
	void PrivateSetLocation(const TopoLocation& location);

	/// @brief Clear the location of this product node.
	void PrivateClearLocation();

	/// @brief Get all child products.
	/// @details If this is a shadow node, returns from the target node.
	/// @return Const reference to child product list.
	const std::vector<std::shared_ptr<T>>& PrivateChildren() const;

	/// @brief Get the number of child products.
	/// @details If this is a shadow node, returns from the target node.
	/// @return Number of children.
	size_t PrivateChildrenSize() const;

	/// @brief Get a specific child product by index.
	/// @details If this is a shadow node, accesses the target node.
	/// @param index Index of the child.
	/// @return Const reference to the child product pointer.
	const std::shared_ptr<T>& PrivateChildAt(size_t index) const;

	/// @overload
	std::shared_ptr<T>& PrivateChildAt(size_t index);

	/// @brief Add a child product node.
	/// @details If this is a shadow node, adds to the target node.
	/// @param child The child node to add.
	void PrivateAddChild(const std::shared_ptr<T>& child);

	/// @brief Remove a child at specific index.
	/// @param index Index of the child.
	void PrivateRemoveChildAt(size_t index);

	/// @brief Remove all child nodes.
	/// @details If this is a shadow node, clears the target node.
	void PrivateClearChildren();

	/// @brief Get child products owned by this node (not via shadow indirection).
	/// @return Const reference to the owned children.
	const std::vector<std::shared_ptr<T>>& PrivateOwnedChildren() const;

	/// @brief Get the number of owned children.
	/// @return Number of owned children.
	size_t PrivateOwnedChildrenSize() const;

	/// @brief Get specific owned child by index.
	/// @param index Index of the child.
	/// @return Const reference to the child product pointer.
	const std::shared_ptr<T>& PrivateOwnedChildAt(size_t index) const;

	/// @overload
	std::shared_ptr<T>& PrivateOwnedChildAt(size_t index);

	/// @brief Add a child node to this product node directly.
	/// @param child The child node to add.
	void PrivateAddOwnedChild(const std::shared_ptr<T>& child);

	/// @brief Remove a child at specific index.
	/// @param index Index of the child.
	void PrivateRemoveOwnedChildAt(size_t index);

	/// @brief Remove all child nodes from this product node.
	void PrivateClearOwnedChildren();

	/// @brief Add a shape object to this product node.
	/// @details If this is a shadow node, adds to the target node instead.
	/// @param shape Shape to add.
	/// @param chain Property chain for the shape.
	/// @param factors ShapeFactors for the shape.
	/// @param reptype Shape representation type.
	/// @note An empty label is also added as placeholder.
	virtual void PrivateAddShape(const TopoShape& shape,
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove a shape by index.
	/// @details If this is a shadow node, removes from the target node.
	/// @param index Index of the shape to remove.
	virtual void PrivateRemoveShapeAt(size_t index);

	/// @brief Remove all shapes.
	/// @details If this is a shadow node, clears the target node's shapes.
	/// @note Also removes all property chains, labels, factors, and representation types.
	virtual void PrivateClearShapes();

	/// @brief Add a shape to this product node directly (not via shadow indirection).
	/// @param shape Shape to add.
	/// @param chain Property chain.
	/// @param factors ShapeFactors.
	/// @param reptype Representation type.
	/// @note An empty label will be added as a placeholder.
	virtual void PrivateAddOwnedShape(const TopoShape& shape,
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove a specific owned shape by index.
	/// @param index Index of the shape to remove.
	void PrivateRemoveOwnedShapeAt(size_t index);

	/// @brief Remove all shapes from this product node.
	/// @note Also removes all property chains, labels, factors, and representation types.
	void PrivateClearOwnedShapes();

	/// @brief Get the pointer to the target (referenced) node if this is a shadow node.
	/// @details Returns nullptr if this is not a shadow node.
	/// @return Const reference to the pointer to the target node.
	const std::shared_ptr<T>& PrivateTarget() const;

	/// @brief Mark this node as a shadow node.
	/// @details Shadow nodes only hold location; other data is redirected.
	/// @param target Pointer to the target node. If null, this node becomes a normal node.
	/// @param clear If true, clears all shapes, properties etc from this node.
	void PrivateMarkShadow(const std::shared_ptr<T>& target, bool clear = false);

	/// @brief Convert a shadow node back to a normal node.
	/// @param clone If true, deep-copies the target node's data (including children).
	void PrivateMarkNormal(bool clone = true);

	/// @brief Check whether this node is a shadow node.
	/// @retval true If this node is a shadow node.
	/// @retval false Otherwise.
	bool PrivateIsShadow() const;

	/// @brief Create a composite TopoShape of all shapes in this (sub)tree.
	/// @details If this is a shadow node, returns the target node's composite shape.
	/// @param recursive If true, includes children recursively.
	/// @return The composite TopoShape.
	TopoShape PrivateOneShape(bool recursive = false) const;

	/// @brief Create a copy of this node, excluding children.
	/// @return A new instance copied from this node (no children).
	std::shared_ptr<T> PrivateEmptyCopy() const;

	/// @brief Get Representation Items
	/// @return Representation Items
	const std::map<std::string, std::vector<RepItem>>& PrivateRepItems() const;

	/// @overload
	std::map<std::string, std::vector<RepItem>>& PrivateRepItems();

	/// @brief Get the number of Representation Items.
	/// @return Number of Representation Items.
	size_t PrivateRepItemsSize() const;

	/// @brief Add a Representation Item to this product node.
	/// @param name The name of the Representation Item.
	/// @param items The items.
	void PrivateAddRepItem(const std::string& name, const std::vector<RepItem>& items);

	/// @brief Setter for Representation Items
	/// @param items The Representation items
	void PrivateSetRepItems(const std::map<std::string, std::vector<RepItem>>& items);

	/// @brief Remove all the Representation Items.
	void PrivateClearRepItems();

	/// @brief Get Representation Items
	/// @return Representation Items
	const std::map<std::string, std::vector<RepItem>>& PrivateOwnedRepItems() const;

	/// @overload
	std::map<std::string, std::vector<RepItem>>& PrivateOwnedRepItems();
	/// @brief Get the number of Representation Items.
	/// @return Number of Representation Items.
	size_t PrivateOwnedRepItemsSize() const;

	/// @brief Add a Representation Item to this product node.
	/// @param name The name of the Representation Item.
	/// @param items The items.
	void PrivateAddOwnedRepItem(const std::string& name, const std::vector<RepItem>& items);

	/// @brief Setter for Representation Items
	/// @param items The Representation items
	void PrivateSetOwnedRepItems(const std::map<std::string, std::vector<RepItem>>& items);

	/// @brief Remove all the Representation Items.
	void PrivateClearOwnedRepItems();

	/// @brief Create a deep copy of a list of PNode nodes.
	/// @details If a shadow node is present, its target node is also copied.
	/// @param orig The original list of PNode nodes.
	/// @return Deep-copied list.
	static std::vector<std::shared_ptr<T>> PrivateDeepCopy(const std::vector<std::shared_ptr<T>>& orig);

	/// @brief Create a composite TopoShape from a list of PNode nodes.
	/// @param nodes List of PNode nodes.
	/// @return The composite TopoShape.
	static TopoShape PrivateOneShape(const std::vector<std::shared_ptr<T>>& nodes);
#endif // !DOXYGEN_SKIP
};

} // namespace AMCAX::STEP

/// @file       STEPLabelProduct.hpp
/// @brief		Represents a STEP product that is backed by Labels.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <af/label/Label.hpp>
#include <step/PNode.hpp>

namespace AMCAX::STEP
{
/// @brief Represents a STEP product that is backed by Labels.
class AMCAX_CLASS_API STEPLabelProduct : public PNode<STEPLabelProduct>
{
private:
	std::vector<Label> _Labels;

public:
	/// @brief Default constructor. All members are initialized as empty.
	AMCAX_API STEPLabelProduct();

	/// @brief Construct with a TopoShape and optional product name.
	/// @param s The TopoShape to store in this product node.
	/// @param n Optional name for this product node.
	AMCAX_API explicit STEPLabelProduct(const TopoShape& s,
		const std::string& n = std::string());

	/// @brief Construct with a Label and optional product name.
	/// @param s The Label to store in this product node.
	/// @param n Optional name for this product node.
	AMCAX_API explicit STEPLabelProduct(const Label& s,
		const std::string& n = std::string());

	/// @brief Copy constructor.
	/// @param other The STEPLabelProduct to copy.
	AMCAX_API explicit STEPLabelProduct(const STEPLabelProduct& other);

	/// @brief Copy constructor from shared pointer.
	/// @param other Shared pointer to the STEPLabelProduct to copy.
	AMCAX_API explicit STEPLabelProduct(const std::shared_ptr<STEPLabelProduct>& other);

	/// @brief Move constructor.
	/// @param other The STEPLabelProduct to move from.
	AMCAX_API explicit STEPLabelProduct(STEPLabelProduct&& other) noexcept;

	/// @brief Virtual destructor.
	AMCAX_API virtual ~STEPLabelProduct() noexcept;

	/// @brief Get all labels.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the labels.
	AMCAX_API const std::vector<Label>& Labels() const;

	/// @brief Get the number of labels.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of labels.
	AMCAX_API size_t LabelsSize() const;

	/// @brief Get a specific label by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index of the label.
	/// @return Const reference to the label.
	AMCAX_API const Label& LabelAt(size_t index) const;

	/// @overload
	AMCAX_API Label& LabelAt(size_t index);

	/// @brief Get labels owned by this node.
	/// @return Const reference to the owned labels.
	AMCAX_API const std::vector<Label>& OwnedLabels() const;

	/// @brief Get the number of owned labels.
	/// @return Number of owned labels.
	AMCAX_API size_t OwnedLabelsSize() const;

	/// @brief Get a specific owned label by index.
	/// @param index Index of the label.
	/// @return Const reference to the owned label.
	AMCAX_API const Label& OwnedLabelAt(size_t index) const;

	/// @overload
	AMCAX_API Label& OwnedLabelAt(size_t index);

	/// @brief Get all length factors for each label.
	/// @details Delegates to the target node if this is a shadow.
	/// @note Result is not affected by STEPReader::SetUnit().
	/// @return Const reference to the factors.
	AMCAX_API const std::vector<ShapeFactors>& Factors() const;

	/// @brief Get the number of length factors.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of length factors.
	AMCAX_API size_t FactorsSize() const;

	/// @brief Get a specific length factor by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index corresponding to the label.
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

	/// @brief Get the representation type for each label.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Const reference to the representation types.
	AMCAX_API const std::vector<ShapeRepresentationType>& ShapeRepresentations() const;

	/// @brief Get the number of representation types.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of representation types.
	AMCAX_API size_t ShapeRepresentationsSize() const;

	/// @brief Get a specific representation type by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index corresponding to the label.
	/// @return Const reference to the representation type.
	AMCAX_API const ShapeRepresentationType& ShapeRepresentationAt(size_t index) const;

	/// @overload
	AMCAX_API ShapeRepresentationType& ShapeRepresentationAt(size_t index);

	/// @brief Get representation types owned by this node.
	/// @return Const reference to the owned representation types.
	AMCAX_API const std::vector<ShapeRepresentationType>& OwnedShapeRepresentations() const;

	/// @brief Get the number of owned representation types.
	/// @return Number of owned types.
	AMCAX_API size_t OwnedShapeRepresentationsSize() const;

	/// @brief Get a specific owned representation type by index.
	/// @param index Index of the type.
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

	/// @brief Get the owned product name.
	/// @return Const reference to the owned name.
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

	/// @brief Get the owned description.
	/// @return Const reference to the owned description.
	AMCAX_API const std::string& OwnedDescription() const;

	/// @brief Set the description of this node.
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
	/// @return Const reference to the child list.
	AMCAX_API const std::vector<std::shared_ptr<STEPLabelProduct>>& Children() const;

	/// @brief Get the number of child products.
	/// @details Delegates to the target node if this is a shadow.
	/// @return Number of children.
	AMCAX_API size_t ChildrenSize() const;

	/// @brief Get a specific child product by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index of the child.
	/// @return Const reference to the child pointer.
	AMCAX_API const std::shared_ptr<STEPLabelProduct>& ChildAt(size_t index) const;

	/// @overload
	AMCAX_API std::shared_ptr<STEPLabelProduct>& ChildAt(size_t index);

	/// @brief Add a child product node.
	/// @details Delegates to the target node if this is a shadow.
	/// @param child The child node to add.
	AMCAX_API void AddChild(const std::shared_ptr<STEPLabelProduct>& child);

	/// @brief Remove a child at a specific index.
	/// @param index Index of the child.
	AMCAX_API void RemoveChildAt(size_t index);

	/// @brief Remove all child nodes.
	/// @details Delegates to the target node if this is a shadow.
	AMCAX_API void ClearChildren();

	/// @brief Get child products owned by this node (ignoring shadow indirection).
	/// @return Const reference to the owned children.
	AMCAX_API const std::vector<std::shared_ptr<STEPLabelProduct>>& OwnedChildren() const;

	/// @brief Get the number of owned children.
	/// @return Number of owned children.
	AMCAX_API size_t OwnedChildrenSize() const;

	/// @brief Get a specific owned child by index.
	/// @param index Index of the child.
	/// @return Const reference to the owned child pointer.
	AMCAX_API const std::shared_ptr<STEPLabelProduct>& OwnedChildAt(size_t index) const;

	/// @overload
	AMCAX_API std::shared_ptr<STEPLabelProduct>& OwnedChildAt(size_t index);

	/// @brief Add a child node directly to this product node.
	/// @param child The child node to add.
	AMCAX_API void AddOwnedChild(const std::shared_ptr<STEPLabelProduct>& child);

	/// @brief Remove an owned child at a specific index.
	/// @param index Index of the child.
	AMCAX_API void RemoveOwnedChildAt(size_t index);

	/// @brief Remove all owned child nodes.
	AMCAX_API void ClearOwnedChildren();

	/// @brief Add a label to this product node.
	/// @details Delegates to the target node if this is a shadow.
	/// @param label Label to add.
	/// @param factors Shape factors.
	/// @param reptype Shape representation type.
	/// @note An empty placeholder shape will also be added.
	AMCAX_API void AddLabel(const Label& label,
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove a label by index.
	/// @details Delegates to the target node if this is a shadow.
	/// @param index Index of the label to remove.
	AMCAX_API void RemoveLabelAt(size_t index);

	/// @brief Remove all labels.
	/// @details Delegates to the target node if this is a shadow.
	/// @note Also removes all labels, factors, and representation types.
	AMCAX_API void ClearLabels();

	/// @brief Add a label directly to this node (ignoring shadow indirection).
	/// @param label Label to add.
	/// @param factors Shape factors.
	/// @param reptype Representation type.
	/// @note An empty placeholder shape will also be added.
	AMCAX_API void AddOwnedLabels(const Label& label,
		const ShapeFactors& factors = ShapeFactors(),
		const ShapeRepresentationType& reptype = ShapeRepresentationType::UNSPECIFIED);

	/// @brief Remove an owned label by index.
	/// @param index Index of the label to remove.
	AMCAX_API void RemoveOwnedLabelAt(size_t index);

	/// @brief Remove all owned labels from this node.
	/// @note Also removes all labels, factors, and representation types.
	AMCAX_API void ClearOwnedLabels();

	/// @brief Get the pointer to the target node if this is a shadow.
	/// @details Returns nullptr if this is not a shadow node.
	/// @return Const reference to the pointer to the target node.
	AMCAX_API const std::shared_ptr<STEPLabelProduct>& Target() const;

	/// @brief Mark this node as a shadow node.
	/// @details Shadow nodes hold only location; all other data is delegated.
	/// @param target Pointer to the target node. If null, this node becomes a normal node.
	/// @param clear If true, clears local content from this node.
	AMCAX_API void MarkShadow(const std::shared_ptr<STEPLabelProduct>& target, bool clear = false);

	/// @brief Convert a shadow node back to a normal node.
	/// @param clone If true, deep-copies the target node's data (including children).
	AMCAX_API void MarkNormal(bool clone = true);

	/// @brief Check whether this node is a shadow node.
	/// @retval true If this node is a shadow.
	/// @retval false Otherwise.
	AMCAX_API bool IsShadow() const;

	/// @brief Create a composite TopoShape of all labels in this (sub)tree.
	/// @details Delegates to the target node if this is a shadow.
	/// @param recursive If true, includes children recursively.
	/// @return The composite TopoShape.
	AMCAX_API TopoShape OneShape(bool recursive = false);

	/// @brief Create a copy of this node, excluding children.
	/// @return A new instance copied from this node (without children).
	AMCAX_API std::shared_ptr<STEPLabelProduct> EmptyCopy() const;

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

	/// @brief Create a deep copy of a list of STEPLabelProduct nodes.
	/// @details If a shadow node is present, its target node is also copied.
	/// @param orig The original list of STEPLabelProduct nodes.
	/// @return Deep-copied list.
	AMCAX_API static std::vector<std::shared_ptr<STEPLabelProduct>> DeepCopy(const std::vector<std::shared_ptr<STEPLabelProduct>>& orig);

	/// @brief Create a composite TopoShape from a list of STEPLabelProduct nodes.
	/// @param nodes List of STEPLabelProduct nodes.
	/// @return The composite TopoShape.
	AMCAX_API static TopoShape OneShape(const std::vector<std::shared_ptr<STEPLabelProduct>>& nodes);
};
} // namespace AMCAX::STEP

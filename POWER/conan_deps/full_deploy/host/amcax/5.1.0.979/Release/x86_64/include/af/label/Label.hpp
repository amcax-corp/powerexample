/// @file      Label.hpp
/// @brief     The class of Label
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/label/Macros.hpp>
#include <af/attribute/Attribute.hpp>
#include <common/Macros.hpp>
#include <memory>
#include <topology/TopoShape.hpp>
#include <unordered_set>
#include <functional>
#include <vector>
namespace AMCAX
{
class LabelNode;
class WithAttrBase;
class LabelFactory;
class AttributeTool;
class LabelTool;
class ChildIterator;
enum class NotifyType;

/// @brief The class of Label
/// @details Label is the core data struct of AF, it It associates a topoShape with some attributes
class Label
{
#ifndef DOXYGEN_SKIP
    friend LabelFactory;
    friend AttributeTool;
    friend WithAttrBase;
    friend LabelTool;
    friend ChildIterator;
    friend std::hash<Label>;
#endif

public:
    /// @brief Construct a empty Label
    /// @details An empty label is used as out parameter
    [[nodiscard]] explicit AMCAX_API Label();

    /// @brief Overload The operator== for label judgment
    /// @param rhs the label to be compared
    /// @return True if the two labels are equal, otherwise return false
    [[nodiscard]] AMCAX_API bool operator==(const Label& rhs) const;

public:
    /// @brief Check if the toposhape on the label is null
    /// @return True if the label is null, otherwise return false
    AMCAX_API bool IsNull() const noexcept;
    
    /// @brief Get referenced labels of the label
    /// @return The referenced labels
    [[nodiscard]] AMCAX_API const std::vector<Label> ReferencedBy() const;

    /// @brief Get referenced labels of the label
    /// @return The referenced labels
    [[nodiscard]] AMCAX_API std::vector<Label> ReferencedBy(); 

    /// @brief Get the child size of the label
    /// @return The number of child label
    AMCAX_API size_t ChildSize() const;

    /// @brief Remove all child label of the label
    /// @details This function is used by WithAttr
    AMCAX_API void Clear();

    /// @brief Get the number of attribute attached on the label
    /// @return The number of attributes on the label
    AMCAX_API size_t GetAttributesSize() const;

    /// @brief Add attribute on the label
    /// @param attribute The attribute to add
    /// @return True if id of the attribute is not existing, otherwise return false.
    AMCAX_API bool AddAttribute(const std::shared_ptr<Attribute> attribute);

    /// @brief Delete attribute on the label
    /// @param attribute The attribute to delete, if it is not on the label, nothing will do
    AMCAX_API void DelAttribute(const std::shared_ptr<Attribute> attribute);

    /// @brief Update the attribute of the label, if the attribute of given id is not existing, return false
    /// @param attr The input attribute
    /// @return True if the attribute is updated, otherwise return false
    AMCAX_API bool UpdateAttribute(const std::shared_ptr<Attribute> attr);

    /// @brief Set the attribute of the label, if the attribute of given id is not existing then add it, otherwise update it.
    /// @param attr The input attribute
    AMCAX_API void SetAttribute(const std::shared_ptr<Attribute> attr);

    /// @brief Delete the attribute with given guid on the label
    /// @param guid The given guid, if it is not on the label, nothing will do
    AMCAX_API void DelAttribute(const std::string& guid);

    /// @brief Check if the attribute list has at least one attribute
    /// @return True if the label has at least one attribute, otherwise return false
    AMCAX_API bool HasAtLeastOneAttribute() const;

    /// @brief Check if the label has an attribute with guid
    /// @param guid The input guid
    /// @return True if the label has the attribute with given guid, otherwise return false
    AMCAX_API bool HasAttribute(const std::string& guid) const;

    /// @brief Find an attribute with specified guid
    /// @param guid the specified guid
    /// @return The pointer of the found attribute, if not find return nullptr
    AMCAX_API std::shared_ptr<Attribute> FindAttribute(const std::string& guid) const;

    /// @brief Find all attributes on the label
    /// @return The result attribute vector
    AMCAX_API std::vector<std::shared_ptr<Attribute>> FindAllAttributes() const;
    
    /// @brief Get the toposhape on the label
    /// @return The toposhape on the label
    AMCAX_API TopoShape GetShape() const;

    /// @brief Check if the toposhape on the label is same with toposhape on given label
    /// @param label The label to be compared
    /// @return True if they are same, otherwise return false
    AMCAX_API bool HasSameShape(const Label& label) const;

    /// @brief Check if the toposhape on the label is equal with toposhape on given label
    /// @param label The label to be compared
    /// @return True if they are equal, otherwise return false
    AMCAX_API bool HasEqualShape(const Label& label) const;
    
    /// @brief Get all compound labels on the label
    /// @return All compound labels
    AMCAX_API std::vector<Label> GetCompoundLabels() const;

    /// @brief Get all compound solid labels on the label
    /// @return All compound solid labels
    AMCAX_API std::vector<Label> GetCompSolidLabels() const;
    
    /// @brief Get all solid labels on the label
    /// @return All solid labels
    AMCAX_API std::vector<Label> GetSolidLabels() const;

    /// @brief Get all shell labels on the label
    /// @return All shell labels
    AMCAX_API std::vector<Label> GetShellLabels() const;

    /// @brief Get all face labels on the label
    /// @return All face labels
    AMCAX_API std::vector<Label> GetFaceLabels() const;
    
    /// @brief Get all wire labels on the label
    /// @return All wire labels
    AMCAX_API std::vector<Label> GetWireLabels() const;

    /// @brief Get all edge labels on the label
    /// @return All edge labels
    AMCAX_API std::vector<Label> GetEdgeLabels() const;

    /// @brief Get all vertex labels on the label
    /// @return All vertex labels
    AMCAX_API std::vector<Label> GetVertexLabels() const;

    /// @brief Get the label by toposhape
    /// @param shape The toposhape
    /// @return The label
    AMCAX_API Label GetLabelByTopoShape(const TopoShape& shape) const;
    /// @brief Get the number of attribute with specified type on the label
    /// @param type The specified attribute type
    /// @return The number of attribute with specified type on the label
    AMCAX_API size_t GetAttributesSize(AttributeType type) const;

    /// @brief Find all attributes with specified type on the label
    /// @param type The specified attribute type
    /// @return The attribute vector with specified type on the label
    AMCAX_API std::vector<std::shared_ptr<Attribute>> FindAttributes(AttributeType type) const;

    /// @brief Delete all attributes with specified type on the label
    /// @param type The specified attribute type
    AMCAX_API void DelAttribute(AttributeType type);

    /// @brief Check if the label has an attribute with specified type
    /// @param type The specified attribute type
    /// @return True if the label has the attribute with given type, otherwise return false
    AMCAX_API bool HasAttribute(AttributeType type) const;

private:
     /// @brief Destory `*the` and all descendant.
     /// @note Use it only when you want to destroy entire Label tree (or a subtree)
    void Destroy();

     /**
     * @brief Make `*the` null without delete underlying memory.
     * @note Use it carefully and make sure the origin `*the` have a ancestor you can access (e.g. Root).
     */
    void Nulltify();

    void AddReferencedLabel(Label label);

    /// @brief Find Child by local id
    /// @param id The input local id of the child label
    /// @return The child label
    Label Child(LocalId id);

    /// @brief Find Child by local id
    /// @param id The input local id of the child label
    /// @return The child label
    const Label Child(LocalId id) const;

    /// @brief Create a new child Label of the label
    /// @param id The input local id of the new child label
    /// @return The new child label
    Label NewChild(LocalId id) const;

    /// @brief Add a child Label to the label
    /// @param id The child local label id
    /// @param child The child label
    void AddChild(LocalId id, const Label& child);

    /// @brief Notify a connected slot with the label
    /// @param type Notification type, currenty [ RebuildRequired, AttributeUpdated ]
    /// @param guid The guid of the attribute
    void Notify(NotifyType type, const std::string& guid) const;

    /// @brief Connect to a signal slot.
    /// @param slotFunc passed by user for trigger
    void Connect(std::function<void(NotifyType, const std::string& guid, Label&)> slotFunc);

    /// @brief Disconnect the signal slot
    /// @details Used for turnning off cascading updates
    void Disconnect();

    /// @brief Update the toposhape on the label
    /// @param newShape The new toposhape to be updated on the label
    AMCAX_API void UpdateShape(const TopoShape& newShape);

private:
    /// @brief Used by fatories only, they will all be friend classes. Construct a non-default label by user directly is strictly forbidden.
    [[nodiscard]] AMCAX_API Label(std::shared_ptr<LabelNode> node);
    std::shared_ptr<LabelNode> _myNode;
    
};

} // namespace AMCAX

/// @brief Specialization of std::hash for AMCAX::Label
template<>
struct std::hash<AMCAX::Label>
{
    /// @brief Hash function for AMCAX::Label
    /// @param label The label to hash
    /// @return The hash value of the label
	AMCAX_API size_t operator()(const AMCAX::Label& label) const noexcept;
};

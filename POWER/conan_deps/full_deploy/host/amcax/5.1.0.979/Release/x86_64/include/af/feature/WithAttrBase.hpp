/// @file WithAttrBase.hpp
/// @brief The base class of WithAttr
/// @details This class provides the basic functionalities for the WithAttr feature, such as adding and deleting attributes, checking attributes, and getting labels by TopoShape
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include "af/attribute/Attribute.hpp"
#include "af/label/SignalType.hpp"
#include <af/label/Label.hpp>
#include <af/label/LabelIterator.hpp>
#include <af/attribute/AttributeTool.hpp>
#include <cassert>
#include <common/Macros.hpp>
#include <string>
#include <topology/TopoExplorer.hpp>
#include <topology/TopoIterator.hpp>
#include <topology/TopoShape.hpp>
#include <unordered_map>

namespace AMCAX {
/// @brief The class of WithAttrBase
AMCAX_CLASS_API class WithAttrBase
{
public:
    /// @brief Get label build by WithAttr
    /// @param keepTrack Whether to keep track Cascading Updates
    /// @return The result label built by method build
    AMCAX_API virtual Label& GetResultLabel(bool keepTrack = false);

    /// @brief Perform the modeling build
    AMCAX_API virtual void Build();

    /// @brief Add the attribute to the label
    /// @param attribute The one should be added
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API void AddAttribute(const std::shared_ptr<Attribute> attribute);

    /// @brief Delete the attribute on the label
    /// @param attribute The one should be deleted
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API void DelAttribute(const std::shared_ptr<Attribute> attribute);

    /// @brief Delete the attribute with guid on the label
    /// @param guid The id of deleted attribute
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API void DelAttribute(const std::string& guid);

    /// @brief Check if the label has at least one attribute
    /// @return True if the label has at least one attribute, otherwise return false
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API bool HasAtLeastOneAttribute();

    /// @brief Check if the label has the attribute with guid
    /// @param guid The input id
    /// @return True if the label has an attribute with given guid, otherwise return false
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API bool HasAttribute(const std::string& guid);

    /// @brief Find the attribute with given guid
    /// @param guid The input id of the attribute
    /// @return The result attribute pointer
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::shared_ptr<Attribute> FindAttribute(const std::string& guid);

    /// @brief Get a label by given topoShape, the given topoShape is the sub-shape of the built shape
    /// @param topoShape The input TopoShape
    /// @param label The found label
    /// @return Return true if the label is found, false otherwise
    AMCAX_API bool GetLabelByTopoShape(const TopoShape& topoShape, Label& label);

    /// @brief Get all the solid labels
    /// @return All solid labels
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::vector<Label> GetAllSolidLabel();

    /// @brief Get all the shell labels
    /// @return All shell labels
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::vector<Label> GetAllShellLabel();

    /// @brief Get all the face labels
    /// @return All face labels
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::vector<Label> GetAllFaceLabel();

    /// @brief Get all the wire labels
    /// @return All wire labels
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::vector<Label> GetAllWireLabel();

    /// @brief Get all the edge labels
    /// @return All edge labels
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::vector<Label> GetAllEdgeLabel();

    /// @brief Get all the vertex labels
    /// @return All vertex labels
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API std::vector<Label> GetAllVertexLabel();
    
    /// @brief Get the label's shape
    /// @return The label's toposhape
    [[deprecated("Will be deprecated in the near future")]]
    AMCAX_API TopoShape Shape();

    /// @brief Check if the modeling operation is done
    /// @return True if the modeling operation is done, otherwise return false
    AMCAX_API bool IsDone() const;

private:
    /// @brief The function to build the child topologies
    void _BuildChildTopologies(Label label);

    void _BuildCompound(Label label);

    /// @brief The function to build the all solid labels
    void _BuildSoilds(Label label);

    /// @brief The function to build the all shell labels
    void _BuildShells(Label solid);

    /// @brief The function to build the all face labels
    void _BuildFaces(Label shell);

    /// @brief The function to build the all wire labels
    void _BuildWires(Label face);

    /// @brief The function to build the all edge labels
    void _BuildEdges(Label wire);

    /// @brief The function to build the all vertex labels
    void _BuildVertices(Label edge);

protected:
    Label _label;
    bool _isDone = false;
    bool _performBuild = false;
    std::vector<Label> _solids;
    std::vector<Label> _shells;
    std::vector<Label> _faces;
    std::vector<Label> _wires;
    std::vector<Label> _edges;
    std::vector<Label> _vertices;
    /// For Deduplication
    std::unordered_map<TopoShape, Label> _sharedTopoLabelMap;
    
    /// The map to store the added labels
    std::unordered_map<TopoShape, Label> _addedLabelMap;

    /// @brief The map to store the topoShape and label
    std::unordered_map<TopoShape, Label> _topoShapeLabelMap;

    /// @brief Add attributes on label source to label target
    /// @param source The source Label
    /// @param target The target Label
    void _AddAttributes(Label source, Label target);

    /// @brief Check if all vertices with attr
    /// @param vertices The vertices with attr
    /// @return True if all vertices with attr
    bool _CheckIfAllVerticesWithAttr(const std::vector<Label>& vertices) const;

    /// @brief Init the added label map
    /// @param labels The labels with attr
    void _InitAddedLabelMap(const std::vector<Label>& labels);

    /// @brief Init the added label map
    /// @param label The label with attr
    void _InitAddedLabelMap(const Label& label);

    /// @brief Check if the labels has nullable shape
    /// @param labels The shapes with attr
    /// @return True if the labels has nullable shape, otherwise return false
    bool _HasNullShape(const std::vector<Label>& labels) const;

    /// @brief Copy the label attribute from srcLabel to targetLabel
    /// @param srcLabel The source label
    /// @param targetLabel The target label
    void _CopyLabelAttribute(const Label& srcLabel, Label& targetLabel);

    /// @brief Add or update sourceAttr on targetLabel
    /// @details If the targetLabel has the attribute with same ID, then update it
    /// @param sourceAttr The source attribute to be added
    /// @param targetLabel The target label to add or update the attribute
    void _AddOrUpdateAttributeOnLabel(std::shared_ptr<Attribute> sourceAttr, Label targetLabel);

    /// @brief Connect the label to a signal slotFunc
    /// @param label The input label
    /// @param slotFunc Passed by user for trigger
    void _Connect(Label& label, std::function<void(NotifyType, const std::string&guid, Label&)> slotFunc);

    /// @brief Notify a connected slot with the label
    /// @param label The input label
    /// @param notifyType Notification type, currenty [ RebuildRequired, AttributeUpdated ]
    /// @param guid The guid of the attribute
    void _Notify(Label& label, NotifyType notifyType, const std::string& guid);

    /// @brief Update the toposhape on the result label
    /// @param shape The new toposhape to be updated on the label
    AMCAX_API void _UpdateShape(const TopoShape& shape);

    /// @brief Update the toposhape on the input label
    /// @param label The input label
    /// @param shape The new toposhape to be updated on the label
    void _UpdateShape(Label& label, const TopoShape& shape);

     /// @brief Perform the modeling rebuild
    AMCAX_API virtual void Rebuild();
    
    WithAttrBase() {}
};

/// @brief The template class of WithAttr
/// @details This class is a basic template class for all WithAttr features.
/// @tparam Op The operation for modelling
template <class Op>
class WithAttr: public WithAttrBase {};

}

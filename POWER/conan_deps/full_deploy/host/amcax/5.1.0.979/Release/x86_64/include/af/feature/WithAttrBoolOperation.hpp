/// @file       WithAttrBoolOperation.hpp
/// @brief      The class of WithAttr<BoolOperation> and its derived classes
/// @details    This file defines the WithAttr<BoolOperation> class, which is used to perform boolean operations on shapes with attributes.
/// @copyright  Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once
#include "WithAttrBase.hpp"
#include "af/attribute/Attribute.hpp"
#include "af/attribute/AttributePolicy.hpp"
#include <boolean/BOAlgoMacros.hpp>
#include <boolean/BoolBRepFuse.hpp>
#include <boolean/BoolOperation.hpp>
#include <boolean/BoolBRepCommon.hpp>
#include <boolean/BoolBRepCut.hpp>
#include <boolean/BoolBRepSplitter.hpp>
#include <common/Macros.hpp>
#include <memory>

namespace AMCAX {
/// @brief The class of WithAttr<BoolOperation>, It is the base class of BoolOperation with attribute.
template<>
class WithAttr<BoolOperation>: public WithAttrBase {
protected:
    /// @brief Construct a WithAttr<BoolOperation> with arguments and tools
    /// @param arguments The argument list
    /// @param tools The tool list
    AMCAX_API WithAttr(const std::vector<Label>& arguments, const std::vector<Label>& tools);

    /// @brief Construct a WithAttr<BoolOperation> with labels
    /// @param labels The label vector, the first label is used as arguments and the remaing are used as tools
    AMCAX_API WithAttr(const std::vector<Label>& labels);

public:
    /// @brief Check if the bool operation is done
    /// @return True if the bool operation is done, otherwise return false
    AMCAX_API bool IsDone();

    /// @brief Get the result label built by method build
    /// @param keepTrack Whether to keep track of the changing of attributes of the tools and arguments
    /// @return The result label
    AMCAX_API Label& GetResultLabel(bool keepTrack = false) override;

    /// @brief Add a attribute policy for given attribute type
    /// @param type The given attribute type
    /// @param policy The given attribute policy
    AMCAX_API void SetPolicy(AttributeType type, AttributePolicy policy);
    
    /// @brief Build the bool operation and simplify the result, remove redundant edges and faces
	/// @param isUnfiyEdges Set whether unify edges
	/// @param isUnifyFaces Set whether unify faces
	/// @param angularTol The angular tolerance for checking parallel
    AMCAX_API void BuildWithSimplifyResult(bool isUnfiyEdges=true, bool isUnifyFaces=true, double angularTol=Precision::Angular());

    /// @brief Perform the bool operation build
    AMCAX_API void Build() override;

    /// @brief Get all Labels modified from given label
    /// @param label The shape with attr
    /// @return The modified label list
    AMCAX_API std::vector<AMCAX::Label> Modified(Label label);

    /// @brief Get all Labels generated from given label
    /// @param label The shape with attr
    /// @return The generated label list
    AMCAX_API std::vector<AMCAX::Label> Generated(Label label);

    /// @brief Check if the label is deleted
    /// @param label The shape with attr
    /// @return True if the label's toposhape is deleted, otherwise return false
    AMCAX_API bool IsDeleted(Label label);

    /// @brief Check if any of the shapes with attr has been modefied
    /// @return True if the label's toposhape is modified, otherwise return false
    AMCAX_API bool HasModified();

    /// @brief Check if any of the shapes with attr has been generated
    /// @return True if the label's toposhape is generated, otherwise return false
    AMCAX_API bool HasGenerated();

    /// @brief Check if any of the shapes with attr has been deleted
    /// @return True if the label's toposhape is deleted, otherwise return false
    AMCAX_API bool HasDeleted();

private:
    /// @brief Get the modified or generated labels from @param label
    std::vector<Label> _ModifiedGenerated(Label label, const std::list<TopoShape>& toposhapeList);

    /// The implemention of build and build with simplify
    void _Build(bool SimplifyResult = false, bool isUnfiyEdges=true, bool isUnifyFaces=true, double angularTol=Precision::Angular());

    void _BuildModifiedFaceRelationMap();

    /// @brief Perform the attribute building on the bool operation result
    void _BuildAttribute();

    /// @brief Build the attribute type to attribute policy map
    void _BuildAttributeType2PolicyMap();

    /// @brief Add @param attr on faces whose toposhape is modified by @param shape
    void AddAttributeOnModifiedFaces(TopoShape shape, std::shared_ptr<Attribute> attr);

    /// @brief Add all attributes on label to the bool result label
    /// @details It is the tool function for build or update attribute on label 
    void  _AddOrUpdateAttrsOnSolid(Label label, AttributePolicy policy);

    void _AddOrUpdateAttributeToLabel(Label srcFaceLabel, Label targetFaceLabel);

    void _AddOrUpdateAttrOnModifiedLabel(Label faceLabel);

    void _DeleteAttributeOnModifiedFaces(Label faceLabel, const std::string& guid);

    std::list<TopoShape> _ModifiedHelper(TopoShape shape);

    std::pair<std::vector<Label>, std::vector<Label>> _SplitConflictToArgumentsAndTools(const std::vector<Label> conflictLabels);

    /// @brief Register the slot function
    /// @details The slot function is called by signal on label when the label's attributes or toposhape is changed 
    void _RegisterOnTargetToolChange();

protected:
    BoolOperation boolOperation;
    BoolBRepSplitter boolBRepSplitter;
    bool _isBoolOperation{true};

private:
    std::vector<Label> _arguments;
    std::vector<Label> _tools;
    /// All attr and its policy.
    std::unordered_map<AttributeType, AttributePolicy> _attrType2Policy;
    std::unordered_map<AttributeType, AttributePolicy> _settingAttrType2Policy;
    std::unordered_map<TopoShape, std::vector<Label>> _topoShapeModifiedFromLabelsMap;
    std::vector<Label> _facesFromArgs;
    std::vector<Label> _facesFromTools;
    std::function<void(NotifyType, const std::string&guid, Label&)> _onTargetToolChange;
    /// @brief The solid labels which have been handled
    std::vector<Label> _handledSolidLabels;
};

/// @brief The class of WithAttr<BoolBRepFuse>
template<>
class WithAttr<BoolBRepFuse>: public WithAttr<BoolOperation> {
public:
    /// @brief Construct a WithAttr<BoolBrepFuse> with arguments and tools
    /// @param args The input argument lists
    /// @param tools The input tool lists 
    WithAttr(const std::vector<Label>& args, const std::vector<Label>& tools):
                           WithAttr<BoolOperation>(args, tools)
    {
        boolOperation.SetOperation(BOAlgoOperation::Fuse); 
    }

    /// @brief Construct a WithAttr<BoolBrepFuse> with shapes with attr
    /// @param labels The label vector, the first label is used as arguments and the remaing are used as tools
    WithAttr(const std::vector<Label>& labels): WithAttr<BoolOperation>(labels)
    {
        boolOperation.SetOperation(BOAlgoOperation::Fuse);
    }
};

/// @brief The class of WithAttr<BoolBRepCommon>
template<>
class WithAttr<BoolBRepCommon>: public WithAttr<BoolOperation> {
public:
    /// @brief Construct a WithAttr<BoolBrepCommon> with arguments and tools
    /// @param args The input argument lists
    /// @param tools The input tool lists 
    WithAttr(const std::vector<Label>& args, const std::vector<Label>& tools):
                             WithAttr<BoolOperation>(args, tools)
    {
        boolOperation.SetOperation(BOAlgoOperation::Common);
    }
};

/// @brief The class of WithAttr<BoolBRepCut>
template<>
class WithAttr<BoolBRepCut>: public WithAttr<BoolOperation> {
public:
    /// @brief Construct a WithAttr<BoolBrepCut> with arguments and tools
    /// @param args The input argument lists
    /// @param tools The input tool lists
    WithAttr(const std::vector<Label>& args, const std::vector<Label>& tools): WithAttr<BoolOperation>(args, tools)
    {
        boolOperation.SetOperation(BOAlgoOperation::Cut);
    }
};

/// @brief The class of WithAttr<BoolBRepSplitter>
template<>
class WithAttr<BoolBRepSplitter>: public WithAttr<BoolOperation> {
public:
    /// @brief Construct a WithAttr<BoolBRepSplitter> with arguments and tools
    /// @param args The input argument lists
    /// @param tools The input tool lists
    WithAttr(const std::vector<Label>& args, const std::vector<Label>& tools):
                               WithAttr<BoolOperation>(args, tools)
    {
        _isBoolOperation = false;
    }
};
}

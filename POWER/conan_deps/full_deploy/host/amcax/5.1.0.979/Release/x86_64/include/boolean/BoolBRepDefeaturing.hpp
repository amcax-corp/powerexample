/// @file      BoolBRepDefeaturing.hpp
/// @brief     The class of removing feature faces from the shape.
/// @details   This class can be used to remove unwanted features such as holes, protrusions, chamfers, etc.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolBuilder.hpp>

namespace AMCAX
{
class BOAlgoRemoveFeatures;

/// @brief The class of removing feature faces from the shape.
/// @details This class can be used to remove unwanted features such as holes, protrusions, chamfers, etc.
class AMCAX_CLASS_API BoolBRepDefeaturing : public BoolBuilder
{
public:
	/// @brief Default constructor
	AMCAX_API BoolBRepDefeaturing();

	/// @brief Construct from a shape.
	/// @param shape The shape that require remove feature
	AMCAX_API explicit BoolBRepDefeaturing(const TopoShape& shape);

	AMCAX_API ~BoolBRepDefeaturing();

public:
	/// @brief Set the shape for remove frature algorithm
	/// @param shape The shape that contain at least one solid
	AMCAX_API void SetShape(const TopoShape& shape) noexcept;

	/// @brief Adds the face to remove from the input shape;
	/// @param face The face for removal
	AMCAX_API void AddFaceToRemove(const TopoShape& face);

	/// @brief Adds the faces to remove from the input shape;
	/// @param faces The list of faces for removal
	AMCAX_API void AddFaceToRemove(const std::list<TopoShape>& faces);

	/// @brief Perform the algorithm
	AMCAX_API void Build() override;

	AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& shape) override;

	AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& shape) override;

	AMCAX_API bool IsDeleted(const TopoShape& shape) override;

	AMCAX_API bool HasModified() const override;

	AMCAX_API bool HasGenerated() const override;

	AMCAX_API bool HasDeleted() const override;

private:
	TopoShape mInputShape;
	std::list<TopoShape> mFacesToRemove;
	std::shared_ptr<BOAlgoRemoveFeatures> featureRemovalTool;
};
} // namespace AMCAX

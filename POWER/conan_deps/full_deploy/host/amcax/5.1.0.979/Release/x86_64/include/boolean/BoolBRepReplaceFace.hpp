/// @file      BoolBRepReplaceFace.hpp
/// @brief     The class of replace the feature faces in solid with surface.
/// @details   This class can be used to implement some direct editing operations such as offset a face.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <boolean/BoolBuilder.hpp>

namespace AMCAX
{
class Geom3Surface;
class BOAlgoReplaceFace;

/// @brief The class of replace the feature faces in solid with surface. The input surface must be large enough to contain the result feature
/// @details This class can be used to implement some direct editing operations such as offset a face.
class AMCAX_CLASS_API BoolBRepReplaceFace : public BoolBuilder
{
public:
	/// @brief Default constructor
	AMCAX_API BoolBRepReplaceFace();

	/// @brief Construct from a shape.
	/// @param shape The shape that require replace face feature
	AMCAX_API explicit BoolBRepReplaceFace(const TopoShape& shape);

	AMCAX_API ~BoolBRepReplaceFace();

public:
	/// @brief Set the shape for replace face feature algorithm
	/// @param shape The shape that contain at least one solid
	AMCAX_API void SetShape(const TopoShape& shape) noexcept;

	/// @brief Adds the face to be replaced from the input shape;
	/// @param face The face to be replaced
	AMCAX_API void AddFaceToReplace(const TopoShape& face);

	/// @brief Adds the faces to be replaced from the input shape;
	/// @param faces The list of faces to be replaced
	AMCAX_API void AddFaceToReplace(const std::list<TopoShape>& faces);

	/// @brief Set the surface with which the feature face is replaced
	/// @param surface The surface with which the feature face is replaced, The surface must be large enough to contain the result feature
	AMCAX_API void SetReplaceSurface(const std::shared_ptr<Geom3Surface>& surface) noexcept;

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
	std::list<TopoShape> mFacesToReplace;
	std::shared_ptr<Geom3Surface> mSurface;
	std::shared_ptr<BOAlgoReplaceFace> featureReplaceTool;
};
} // namespace AMCAX

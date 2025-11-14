/// @file      MakeDraftAngle.hpp
/// @brief     Class of draft-adding transformations on a shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_map>

#include <common/DirectionT.hpp>
#include <modeling/ModifyShape.hpp>
#include <offset/DraftErrorStatus.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Plane;
class ReShape;
class TopoFace;
#endif

/// @brief Class of draft-adding transformations on a shape
/// @details The result is a shape with draft the input faces using the draft angle
///          Each transformation is propagated along the series of faces which are tangential to one another and which contains the face to be adding.
///          Only faces which surface type planar, cylindrical, and conical are supported.
class AMCAX_CLASS_API MakeDraftAngle : public ModifyShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeDraftAngle();

	/// @brief Constructs whit initial shape
	/// @param s The initial shape
	AMCAX_API explicit MakeDraftAngle(const TopoShape& s);

	/// @brief Cancels the results of all added transformations performed on the initial shape
	AMCAX_API void Clear();

	/// @brief Initializes whit initial shape.
	/// @param s The initial shape
	AMCAX_API void Init(const TopoShape& s);

	/// @brief Add face in initial shape and draft infomation
	/// @details If the input face is cylindrical and conical, the plane need be perpendicular to the direction.
	/// @param f The face in initial shape, only support planar, cylindrical and conical
	/// @param dir The direction Direction.
	/// @param angle The draft angle.
	/// @param neutralPlane The draft neutral plane.
	/// @param flag The flag to construct instantly
	AMCAX_API void Add(const TopoFace& f, const Direction3& dir, double angle, const Plane& neutralPlane, bool flag = true);

	/// @brief Returns true if the last addition is successful
	[[nodiscard]] AMCAX_API bool AddDone() const;

	/// @brief Cancels the added face and check shape after the removal
	/// @details This function is used when the previous call to Add fails.
	/// @param f The face to be removed
	AMCAX_API void Remove(const TopoFace& f);

	/// @brief Returns the shape on which an error occurred after an unsuccessful call to Add or when IsDone returns false.
	[[nodiscard]] AMCAX_API const TopoShape& ProblematicShape() const;

	/// @brief Returns an error status when an error has occurred
	[[nodiscard]] AMCAX_API DraftErrorStatus Status() const;

	AMCAX_API void Build() override;

	/// @brief Get all the faces connected to a given face
	/// @param f The face
	/// @return The list of connected faces
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& ConnectedFaces(const TopoFace& f) const;

	/// @brief Get all the modified faces
	/// @return The list of modified faces
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& ModifiedFaces() const;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;

	[[nodiscard]] AMCAX_API TopoShape ModifiedShape(const TopoShape& s) const override;

private:
	void CorrectWires();
	void CorrectVertexTol();
	void CorrectDegrade();
	void CorrectFaceinter();
	bool CorrectVertexcoincide();
	void SplitErrorWire(const TopoShape errorwire, std::list<TopoShape>& splitwires, TopoShape oldwire);

	std::unordered_map<TopoShape, TopoShape> vertexToReplace;
	std::shared_ptr<ReShape> subShapes;
};
} // namespace AMCAX

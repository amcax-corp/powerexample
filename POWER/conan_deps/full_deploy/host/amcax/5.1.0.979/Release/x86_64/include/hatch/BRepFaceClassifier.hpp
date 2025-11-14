/// @file      BRepFaceClassifier.hpp
/// @brief     Class for classifying geometric points with a face
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class FaceClassifierImp;
#endif

/// @brief Class for classifying geometric points with a face
class BRepFaceClassifier
{
public:
	/// @brief Construct from the face to be processed
	/// @param f The input face
	AMCAX_API explicit BRepFaceClassifier(const TopoFace& f);

	/// @brief Classify a UV point on face with tolerance
	/// @param p The uv point
	/// @param tol The tolerance
	AMCAX_API void Perform(const Point2& p, double tol);

	/// @brief Classify a point on face with tolerance
	/// @param p The point
	/// @param tol The tolerance
	AMCAX_API void Perform(const Point3& p, double tol);

	/// @brief Get the state type of the classification result
	/// @return The state type of the classification result
	[[nodiscard]] AMCAX_API StateType State() const;

private:
	BRepFaceClassifier(const BRepFaceClassifier&) = delete;
	BRepFaceClassifier& operator=(const BRepFaceClassifier&) = delete;

	TopoFace mFace;
	StateType mState = StateType::Unknown;
	std::shared_ptr<FaceClassifierImp> fClassifier;
};
} // namespace AMCAX

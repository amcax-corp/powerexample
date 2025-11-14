/// @file      HLRAlgorithmProjector.hpp
/// @brief     Class of hlr projector
/// @details   Indicates the position and orientation of the camera, and is divided into two modes: parallel projection and point projection
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/LineT.hpp>

namespace AMCAX
{
/// @brief Class of hlr projector
class HLRAlgorithmProjector
{
public:
#ifndef DOXYGEN_SKIP

	/// @brief An empty projector
	HLRAlgorithmProjector();

	/// @brief A projector with a frame, the focus is set to zero
	/// @param cs A frame used for generate transformation of camera
	explicit HLRAlgorithmProjector(const Frame3& cs);

	/// @brief A projector with a frame and a focus
	/// @param cs A frame used for generate transformation
	/// @param Focus Focus
	HLRAlgorithmProjector(const Frame3& cs, double Focus);

#endif

	/// @brief A projector with a transformation and a focus
	/// @param t Transformation of camera
	/// @param Persp Is point projection mode
	/// @param Focus Focus
	AMCAX_API HLRAlgorithmProjector(const Transformation3& t, bool Persp, double Focus);

#ifndef DOXYGEN_SKIP

	/// @brief Build a projector given minmax directions
	/// @param t Transformation of camera
	/// @param Persp Is point projection mode
	/// @param Focus Focus
	/// @param v1 Minmax directions
	/// @param v2 Minmax directions
	/// @param v3 Minmax directions
	HLRAlgorithmProjector(const Transformation3& t, bool Persp, double Focus, const Vector2& v1, const Vector2& v2, const Vector2& v3);

	/// @brief Compute trsf
	void Scaled(bool On = false);

	/// @brief Compute projected point
	/// @param P Point
	/// @param Pout projected 2D point
	void Project(const Point3& P, Point2& Pout) const;

	/// @brief Compute projected point
	/// @param P Point
	/// @param X Projected point x
	/// @param Y Projected point y
	/// @param Z Projected point z
	void Project(const Point3& P, double& X, double& Y, double& Z) const;

	/// @brief Compute projected point and vec
	/// @param P Point
	/// @param D1 Vec
	/// @param Pout Projected point
	/// @param D1out Projected vec
	void Project(const Point3& P, const Vector3& D1, Point2& Pout, Vector2& D1out) const;

	/// @brief Compute line through (x,y) and camera
	/// @param X X
	/// @param Y Y
	/// @return The line
	[[nodiscard]] Line3 Shoot(double X, double Y) const;

	/// @brief Get the minmax directions
	/// @param[out] D1,D2,D3 The minmax directions
	void Directions(Vector2& D1, Vector2& D2, Vector2& D3) const;

	/// @brief Get the full transformation
	/// @return The transformation
	[[nodiscard]] const Transformation3& FullTransformation() const;

#endif

	/// @brief Get the transformation
	/// @return The transformation
	[[nodiscard]] AMCAX_API const Transformation3& Transformation() const;

	/// @brief Is the projector perspective
	/// @return True if the projection is perspective
	[[nodiscard]] AMCAX_API bool Perspective() const;

	/// @brief Get the inverted transformation
	/// @return The inverted transformation
	[[nodiscard]] AMCAX_API const Transformation3& InvertedTransformation() const;

	/// @brief Get the focus of projector
	/// @return The focus
	[[nodiscard]] AMCAX_API double Focus() const;

	/// @brief Transform a vector
	/// @param[in,out] v The vector to be transformed
	AMCAX_API void Transform(Vector3& v) const;

	/// @brief Transform a point
	/// @param[in,out] point The point to be transformed
	AMCAX_API void Transform(Point3& point) const;

private:
	void SetDirection();

	int type;
	bool persp;
	double focus;
	Transformation3 scaledTrsf;
	Transformation3 trsf;
	Transformation3 invTrsf;
	Vector2 d1;
	Vector2 d2;
	Vector2 d3;
};
} // namespace AMCAX

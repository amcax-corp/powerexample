/// @file      Geom3Geometry.hpp
/// @brief     Base class of 3D geometry object
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <istream>
#include <memory>
#include <ostream>

#include <common/AxisT.hpp>
#include <common/FrameT.hpp>
#include <common/TransformationT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
/// @brief Base class of 3D geometry object
class AMCAX_CLASS_API Geom3Geometry
{
public:
	/// @brief Default constructor
	Geom3Geometry() noexcept = default;

	/// @brief Copy constructor
	Geom3Geometry(const Geom3Geometry&) noexcept = default;

	/// @brief Move constructor
	Geom3Geometry(Geom3Geometry&&) noexcept = default;

	/// @brief Destructor
	virtual ~Geom3Geometry() noexcept = default;

	/// @brief Copy assignment operator
	/// @return The reference to self
	Geom3Geometry& operator=(const Geom3Geometry&) noexcept = default;

	/// @brief Move assignment operator
	/// @return The reference to self
	Geom3Geometry& operator=(Geom3Geometry&&) noexcept = default;

	/// @brief Mirror the geometry object by a mirror point
	/// @param point The mirror point
	AMCAX_API void Mirror(const Point3& point);

	/// @brief Get the geometry object mirrored by a mirror point
	/// @param point The mirror point
	/// @return The mirrored geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Mirrored(const Point3& point) const;

	/// @brief Mirror the geometry object by a mirror axis
	/// @param axis The mirror axis
	AMCAX_API void Mirror(const Axis3& axis);

	/// @brief Get the geometry object mirrored by a mirror axis
	/// @param axis The mirror axis
	/// @return The mirrored geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Mirrored(const Axis3& axis) const;

	/// @brief Mirror the geometry object by a mirror frame
	/// @param frame The mirror frame
	AMCAX_API void Mirror(const Frame3& frame);

	/// @brief Get the geometry object mirrored by a mirror frame
	/// @param frame The mirror frame
	/// @return The mirrored geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Mirrored(const Frame3& frame) const;

	/// @brief Rotate the geometry object around an axis with an angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	AMCAX_API void Rotate(const Axis3& axis, double angle);

	/// @brief Get the geometry object rotated around an axis with an angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Rotated(const Axis3& axis, double angle) const;

	/// @brief Scale the geometry object by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	AMCAX_API void Scale(const Point3& point, double scale);

	/// @brief Get the geometry object scaled by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The scaled geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Scaled(const Point3& point, double scale) const;

	/// @brief Translate the geometry object by a vector
	/// @param vec The translation vector
	AMCAX_API void Translate(const Vector3& vec);

	/// @brief Get the geometry object translated by a vector
	/// @param vec The translation vector
	/// @return The translated geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Translated(const Vector3& vec) const;

	/// @brief Translate the geometry object by a vector from a source point to a target point
	/// @param p1 The source point
	/// @param p2 The target point
	AMCAX_API void Translate(const Point3& p1, const Point3& p2);

	/// @brief Get the geometry object translated by a vector from a source point to a target point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The translated geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Translated(const Point3& p1, const Point3& p2) const;

	/// @brief Transform the geometry object
	/// @param tr The transformation
	AMCAX_API virtual void Transform(const Transformation3& tr) = 0;

	/// @brief Get the transformed geometry object
	/// @param tr The transformation
	/// @return The transformed geometry object
	[[nodiscard]] AMCAX_API std::shared_ptr<Geom3Geometry> Transformed(const Transformation3& tr) const;

	/// @brief Get the copied geometry object
	/// @return The copied geometry object
	[[nodiscard]] AMCAX_API virtual std::shared_ptr<Geom3Geometry> Copy() const = 0;

	/// @brief Write the geometry object
	/// @param os The output stream
	/// @return The output stream
	AMCAX_API virtual std::ostream& Write(std::ostream& os) const = 0;

	/// @brief Read the geometry object
	/// @param is The input stream
	/// @return The input stream
	AMCAX_API virtual std::istream& Read(std::istream& is) = 0;
};
} // namespace AMCAX

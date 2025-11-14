/// @file      GlobalProperty.hpp
/// @brief     Class of general global property
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/AxisT.hpp>
#include <common/MatrixT.hpp>
#include <geometry/GlobalPrincipalProperty.hpp>

namespace AMCAX
{
/// @brief Class of general global property
class GlobalProperty
{
public:
	/// @brief Default constructor
	constexpr GlobalProperty() noexcept = default;

	/// @brief Construct from a given system location, i.e. the origin of a local frame
	/// @param systemLocation The location point
	AMCAX_API explicit GlobalProperty(const Point3& systemLocation) noexcept;

	/// @brief Add a global property with density
	/// @param item The other global property
	/// @param density The density
	AMCAX_API void Add(const GlobalProperty& item, double density = 1.0);

	/// @brief Get the mass (length of edge, area of face, or volume of solid)
	/// @return The mass
	[[nodiscard]] AMCAX_API double Mass() const noexcept;

	/// @brief Get the center of mass (center of gravity)
	/// @return The center of mass
	[[nodiscard]] AMCAX_API Point3 CenterOfMass() const noexcept;

	/// @brief Get the matrix of inertia
	/// @return The matrix of inertia
	[[nodiscard]] AMCAX_API Matrix3 MatrixOfInertia() const noexcept;

	/// @brief Get the static moments of inertia
	/// @return The static moments of inertia
	[[nodiscard]] AMCAX_API Vector3 StaticMoments() const noexcept;

	/// @brief Get the moment of inertia about a given axis
	/// @param axis The axis
	/// @return The moment of inertia
	[[nodiscard]] AMCAX_API double MomentOfInertia(const Axis3& axis) const;

	/// @brief Get the principal property
	/// @return The principal property
	[[nodiscard]] AMCAX_API GlobalPrincipalProperty PrincipalProperties() const;

	/// @brief Get the radius of gyration about a given axis
	/// @param axis The axis
	/// @return The radius of gyration
	[[nodiscard]] AMCAX_API double RadiusOfGyration(const Axis3& axis) const;

protected:
	/// @brief Local mass center
	Point3 localMassCenter;

	/// @brief Location of the local system
	Point3 location;

	/// @brief Mass of the shape
	double mass = 0.0;

	/// @brief Inertia matrix
	Matrix3 inertia;
};
} // namespace AMCAX

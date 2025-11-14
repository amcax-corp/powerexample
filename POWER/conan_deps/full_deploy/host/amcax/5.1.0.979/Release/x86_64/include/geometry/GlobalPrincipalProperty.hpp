/// @file      GlobalPrincipalProperty.hpp
/// @brief     Class of internal data structure for computing global property
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
/// @brief Class of internal data structure for computing global property
class GlobalPrincipalProperty
{
public:
	/// @brief Default constructor
	GlobalPrincipalProperty() noexcept;

	/// @brief Construct from inertia information
	/// @param ixx,iyy,izz The principal moments of inertia
	/// @param rxx,ryy,rzz The radius of gyration
	/// @param vxx The first axis of inertia
	/// @param vyy The second axis of inertia
	/// @param vzz The third axis of inertia
	/// @param g The center of gravity
	GlobalPrincipalProperty(double ixx, double iyy, double izz, double rxx, double ryy, double rzz, const Vector3& vxx, const Vector3& vyy, const Vector3& vzz, const Point3& g) noexcept;

	/// @brief Has symmetry axis
	/// @return True if the inertia system has a symmetry axis
	[[nodiscard]] bool HasSymmetryAxis() const noexcept;

	/// @brief Has symmetry axis under a tolerance
	/// @return True if the inertia system has a symmetry axis
	[[nodiscard]] bool HasSymmetryAxis(double tol) const noexcept;

	/// @brief Has symmetry point
	/// @return True if the inertia system has a symmetry point
	[[nodiscard]] bool HasSymmetryPoint() const noexcept;

	/// @brief Has symmetry point under a tolerance
	/// @return True if the inertia system has a symmetry point
	[[nodiscard]] bool HasSymmetryPoint(double tol) const noexcept;

	/// @brief Get the principal moments of inertia
	/// @param[out] ixx,iyy,izz The principal moments of inertia
	void Moments(double& ixx, double& iyy, double& izz) const noexcept;

	/// @brief Get the first axis of inertia
	/// @return The first axis of inertia
	[[nodiscard]] const Vector3& FirstAxisOfInertia() const noexcept;

	/// @brief Get the second axis of inertia
	/// @return The second axis of inertia
	[[nodiscard]] const Vector3& SecondAxisOfInertia() const noexcept;

	/// @brief Get the third axis of inertia
	/// @return The third axis of inertia
	[[nodiscard]] const Vector3& ThirdAxisOfInertia() const noexcept;

	/// @brief Get the radius of gyration
	/// @param[out] rxx,ryy,rzz The radius of gyration
	void RadiusOfGyration(double& rxx, double& ryy, double& rzz) const noexcept;

private:
	double i1;
	double i2;
	double i3;
	double r1;
	double r2;
	double r3;
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Point3 g;
};
} // namespace AMCAX

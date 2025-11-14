/// @file      SurfaceCalculation.hpp
/// @brief     Class of basic calculation for elementary surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/CircleT.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
class Cone;
class Cylinder;
class Plane;
class Sphere;
class Torus;

/// @brief Functions for basic geometric computations on elementary curves such as planes and spheres.
/// @details The calculation includes parameters, values, derivatives, and isoparametric curves.
///          The surfaces include planes, cylinders, cones, spheres, and tori.
class SurfaceCalculation
{
public:
	/// @brief Compute the point on a plane at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param plane The plane
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, double v, const Plane& plane) noexcept;

	/// @brief Compute the point on a plane at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param plane The plane
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, double v, const Plane& plane) noexcept;

	/// @brief Compute the first-order partial derivatives on a plane at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param plane The plane
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto D1(double u, double v, const Plane& plane) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a plane at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param plane The plane
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto D2(double u, double v, const Plane& plane) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a plane at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param plane The plane
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto D3(double u, double v, const Plane& plane) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a plane at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param plane The plane
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, double v, const Plane& plane, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a plane at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] plane The plane
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void D1(double u, double v, const Plane& plane, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a plane at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] plane The plane
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void D2(double u, double v, const Plane& plane, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a plane at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] plane The plane
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void D3(double u, double v, const Plane& plane, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a plane
	/// @param plane The plane
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto Parameter(const Plane& plane, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the point on a plane represented by a local frame at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the plane lies
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 PlaneValue(double u, double v, const Frame3& pos) noexcept;

	/// @brief Compute the point on a plane represented by a local frame at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the plane lies
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 PlaneD0(double u, double v, const Frame3& pos) noexcept;

	/// @brief Compute the first-order partial derivatives on a plane represented by a local frame at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the plane lies
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto PlaneD1(double u, double v, const Frame3& pos) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a plane represented by a local frame at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the plane lies
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto PlaneD2(double u, double v, const Frame3& pos) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a plane represented by a local frame at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the plane lies
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto PlaneD3(double u, double v, const Frame3& pos) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a plane represented by a local frame at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the plane lies
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 PlaneDN(double u, double v, const Frame3& pos, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a plane represented by a local frame at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the plane lies
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void PlaneD1(double u, double v, const Frame3& pos, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a plane represented by a local frame at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the plane lies
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void PlaneD2(double u, double v, const Frame3& pos, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a plane represented by a local frame at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the plane lies
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void PlaneD3(double u, double v, const Frame3& pos, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a plane represented by a local frame
	/// @param pos The local frame where the plane lies
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto PlaneParameter(const Frame3& pos, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the u isoparametric curve on a plane represented by a local frame at a given u parameter
	/// @param pos The local frame where the plane lies
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API static Line3 PlaneUIso(const Frame3& pos, double u) noexcept;

	/// @brief Compute the v isoparametric curve on a plane represented by a local frame at a given v parameter
	/// @param pos The local frame where the plane lies
	/// @param v The v parameter
	/// @return The v iso parametric curve
	[[nodiscard]] AMCAX_API static Line3 PlaneVIso(const Frame3& pos, double v) noexcept;

	/// @brief Compute the point on a cylinder at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cylinder The cylinder
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, double v, const Cylinder& cylinder) noexcept;

	/// @brief Compute the point on a cylinder at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cylinder The cylinder
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, double v, const Cylinder& cylinder) noexcept;

	/// @brief Compute the first-order partial derivatives on a cylinder at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cylinder The cylinder
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto D1(double u, double v, const Cylinder& cylinder) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a cylinder at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cylinder The cylinder
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto D2(double u, double v, const Cylinder& cylinder) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a cylinder at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cylinder The cylinder
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto D3(double u, double v, const Cylinder& cylinder) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a cylinder at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cylinder The cylinder
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, double v, const Cylinder& cylinder, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a cylinder at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] cylinder The cylinder
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void D1(double u, double v, const Cylinder& cylinder, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a cylinder at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] cylinder The cylinder
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void D2(double u, double v, const Cylinder& cylinder, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a cylinder at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] cylinder The cylinder
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void D3(double u, double v, const Cylinder& cylinder, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a cylinder
	/// @param cylinder The cylinder
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto Parameter(const Cylinder& cylinder, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the point on a cylinder represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 CylinderValue(double u, double v, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the point on a cylinder represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 CylinderD0(double u, double v, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the first-order partial derivatives on a cylinder represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto CylinderD1(double u, double v, const Frame3& pos, double radius) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a cylinder represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto CylinderD2(double u, double v, const Frame3& pos, double radius) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a cylinder represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto CylinderD3(double u, double v, const Frame3& pos, double radius) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a cylinder represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 CylinderDN(double u, double v, const Frame3& pos, double radius, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a cylinder represented by a local frame and a radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the cylinder lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void CylinderD1(double u, double v, const Frame3& pos, double radius, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a cylinder represented by a local frame and a radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the cylinder lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void CylinderD2(double u, double v, const Frame3& pos, double radius, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a cylinder represented by a local frame and a radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the cylinder lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void CylinderD3(double u, double v, const Frame3& pos, double radius, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a cylinder represented by a local frame and a radius
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto CylinderParameter(const Frame3& pos, double radius, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the u isoparametric curve on a cylinder represented by a local frame and a radius at a given u parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API static Line3 CylinderUIso(const Frame3& pos, double radius, double u) noexcept;

	/// @brief Compute the v isoparametric curve on a cylinder represented by a local frame and a radius at a given v parameter
	/// @param pos The local frame where the cylinder lies
	/// @param radius The radius
	/// @param v The v parameter
	/// @return The v iso parametric curve
	[[nodiscard]] AMCAX_API static Circle3 CylinderVIso(const Frame3& pos, double radius, double v);

	/// @brief Compute the point on a cone at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cone The cone
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, double v, const Cone& cone) noexcept;

	/// @brief Compute the point on a cone at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cone The cone
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, double v, const Cone& cone) noexcept;

	/// @brief Compute the first-order partial derivatives on a cone at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cone The cone
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto D1(double u, double v, const Cone& cone) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a cone at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cone The cone
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto D2(double u, double v, const Cone& cone) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a cone at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cone The cone
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto D3(double u, double v, const Cone& cone) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a cone at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param cone The cone
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, double v, const Cone& cone, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a cone at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] cone The cone
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void D1(double u, double v, const Cone& cone, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a cone at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] cone The cone
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void D2(double u, double v, const Cone& cone, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a cone at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] cone The cone
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void D3(double u, double v, const Cone& cone, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a cone
	/// @param cone The cone
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto Parameter(const Cone& cone, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the point on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 ConeValue(double u, double v, const Frame3& pos, double radius, double angle) noexcept;

	/// @brief Compute the point on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 ConeD0(double u, double v, const Frame3& pos, double radius, double angle) noexcept;

	/// @brief Compute the first-order partial derivatives on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto ConeD1(double u, double v, const Frame3& pos, double radius, double angle) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto ConeD2(double u, double v, const Frame3& pos, double radius, double angle) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto ConeD3(double u, double v, const Frame3& pos, double radius, double angle) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 ConeDN(double u, double v, const Frame3& pos, double radius, double angle, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the cone lies
	/// @param[in] radius The reference radius
	/// @param[in] angle The semi-angle
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void ConeD1(double u, double v, const Frame3& pos, double radius, double angle, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the cone lies
	/// @param[in] radius The reference radius
	/// @param[in] angle The semi-angle
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void ConeD2(double u, double v, const Frame3& pos, double radius, double angle, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a cone represented by a local frame, a reference radius and a semi-angle at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the cone lies
	/// @param[in] radius The reference radius
	/// @param[in] angle The semi-angle
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void ConeD3(double u, double v, const Frame3& pos, double radius, double angle, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a cone represented by a local frame, a reference radius and a semi-angle
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto ConeParameter(const Frame3& pos, double radius, double angle, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the u isoparametric curve on a cone represented by a local frame, a reference radius and a semi-angle at a given u parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API static Line3 ConeUIso(const Frame3& pos, double radius, double angle, double u);

	/// @brief Compute the v isoparametric curve on a cone represented by a local frame, a reference radius and a semi-angle at a given v parameter
	/// @param pos The local frame where the cone lies
	/// @param radius The reference radius
	/// @param angle The semi-angle
	/// @param v The v parameter
	/// @return The v iso parametric curve
	[[nodiscard]] AMCAX_API static Circle3 ConeVIso(const Frame3& pos, double radius, double angle, double v);

	/// @brief Compute the point on a sphere at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param sphere The sphere
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, double v, const Sphere& sphere) noexcept;

	/// @brief Compute the point on a sphere at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param sphere The sphere
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, double v, const Sphere& sphere) noexcept;

	/// @brief Compute the first-order partial derivatives on a sphere at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param sphere The sphere
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto D1(double u, double v, const Sphere& sphere) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a sphere at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param sphere The sphere
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto D2(double u, double v, const Sphere& sphere) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a sphere at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param sphere The sphere
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto D3(double u, double v, const Sphere& sphere) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a sphere at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param sphere The sphere
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, double v, const Sphere& sphere, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a sphere at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] sphere The sphere
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void D1(double u, double v, const Sphere& sphere, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a sphere at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] sphere The sphere
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void D2(double u, double v, const Sphere& sphere, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a sphere at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] sphere The sphere
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void D3(double u, double v, const Sphere& sphere, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a sphere
	/// @param sphere The sphere
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto Parameter(const Sphere& sphere, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the point on a sphere represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 SphereValue(double u, double v, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the point on a sphere represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 SphereD0(double u, double v, const Frame3& pos, double radius) noexcept;

	/// @brief Compute the first-order partial derivatives on a sphere represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto SphereD1(double u, double v, const Frame3& pos, double radius) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a sphere represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto SphereD2(double u, double v, const Frame3& pos, double radius) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a sphere represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto SphereD3(double u, double v, const Frame3& pos, double radius) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a sphere represented by a local frame and a radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 SphereDN(double u, double v, const Frame3& pos, double radius, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a sphere represented by a local frame and a radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the sphere lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void SphereD1(double u, double v, const Frame3& pos, double radius, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a sphere represented by a local frame and a radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the sphere lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void SphereD2(double u, double v, const Frame3& pos, double radius, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a sphere represented by a local frame and a radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the sphere lies
	/// @param[in] radius The radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void SphereD3(double u, double v, const Frame3& pos, double radius, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a sphere represented by a local frame and a radius
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto SphereParameter(const Frame3& pos, double radius, const Point3& p) noexcept -> std::pair<double, double>;

	/// @brief Compute the u isoparametric curve on a sphere represented by a local frame and a radius at a given u parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API static Circle3 SphereUIso(const Frame3& pos, double radius, double u);

	/// @brief Compute the v isoparametric curve on a sphere represented by a local frame and a radius at a given v parameter
	/// @param pos The local frame where the sphere lies
	/// @param radius The radius
	/// @param v The v parameter
	/// @return The v iso parametric curve
	[[nodiscard]] AMCAX_API static Circle3 SphereVIso(const Frame3& pos, double radius, double v);

	/// @brief Compute the point on a torus at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param torus The torus
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 Value(double u, double v, const Torus& torus) noexcept;

	/// @brief Compute the point on a torus at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param torus The torus
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 D0(double u, double v, const Torus& torus) noexcept;

	/// @brief Compute the first-order partial derivatives on a torus at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param torus The torus
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto D1(double u, double v, const Torus& torus) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a torus at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param torus The torus
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto D2(double u, double v, const Torus& torus) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a torus at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param torus The torus
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto D3(double u, double v, const Torus& torus) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a torus at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param torus The torus
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 DN(double u, double v, const Torus& torus, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a torus at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] torus The torus
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void D1(double u, double v, const Torus& torus, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a torus at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] torus The torus
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void D2(double u, double v, const Torus& torus, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a torus at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] torus The torus
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void D3(double u, double v, const Torus& torus, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a torus
	/// @param torus The torus
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto Parameter(const Torus& torus, const Point3& p) -> std::pair<double, double>;

	/// @brief Compute the point on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 TorusValue(double u, double v, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the point on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 TorusD0(double u, double v, const Frame3& pos, double majorRadius, double minorRadius) noexcept;

	/// @brief Compute the first-order partial derivatives on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The pair of du and dv derivatives
	[[nodiscard]] AMCAX_API static auto TorusD1(double u, double v, const Frame3& pos, double majorRadius, double minorRadius) noexcept -> std::pair<Vector3, Vector3>;

	/// @brief Compute the second-order partial derivatives on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The tuple of du^2, duv and dv^2 derivatives
	[[nodiscard]] AMCAX_API static auto TorusD2(double u, double v, const Frame3& pos, double majorRadius, double minorRadius) noexcept -> std::tuple<Vector3, Vector3, Vector3>;

	/// @brief Compute the third-order partial derivatives on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @return The tuple of du^3, du^2v, duv^2, dv^3 derivatives
	[[nodiscard]] AMCAX_API static auto TorusD3(double u, double v, const Frame3& pos, double majorRadius, double minorRadius) noexcept -> std::tuple<Vector3, Vector3, Vector3, Vector3>;

	/// @brief Compute the partial derivative of given order on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param u The u parameter
	/// @param v The v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param nu The order on the u direction
	/// @param nv The order on the v direction
	/// @return The partial derivative
	[[nodiscard]] AMCAX_API static Vector3 TorusDN(double u, double v, const Frame3& pos, double majorRadius, double minorRadius, int nu, int nv) noexcept;

	/// @brief Compute the point and the partial derivatives of first-order on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the torus lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	AMCAX_API static void TorusD1(double u, double v, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& vecu, Vector3& vecv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than second-order on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the torus lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	AMCAX_API static void TorusD2(double u, double v, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv) noexcept;

	/// @brief Compute the point and the partial derivatives of not more than third-order on a torus represented by a local frame, a major radius and a minor radius at given parameters
	/// @param[in] u The u parameter
	/// @param[in] v The v parameter
	/// @param[in] pos The local frame where the torus lies
	/// @param[in] majorRadius The major radius
	/// @param[in] minorRadius The minor radius
	/// @param[out] p The point
	/// @param[out] vecu The partial derivative du
	/// @param[out] vecv The partial derivative dv
	/// @param[out] vecuu The partial derivative du^2
	/// @param[out] vecuv The partial derivative duv
	/// @param[out] vecvv The partial derivative dv^2
	/// @param[out] vecuuu The partial derivative du^3
	/// @param[out] vecuuv The partial derivative du^2v
	/// @param[out] vecuvv The partial derivative duv^2
	/// @param[out] vecvvv The partial derivative dv^3
	AMCAX_API static void TorusD3(double u, double v, const Frame3& pos, double majorRadius, double minorRadius, Point3& p, Vector3& vecu, Vector3& vecv, Vector3& vecuu, Vector3& vecuv, Vector3& vecvv, Vector3& vecuuu, Vector3& vecuuv, Vector3& vecuvv, Vector3& vecvvv) noexcept;

	/// @brief Get the uv parameters of a given point on a torus represented by a local frame, a major radius and a minor radius
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param p The point
	/// @return The pair of uv parameters
	[[nodiscard]] AMCAX_API static auto TorusParameter(const Frame3& pos, double majorRadius, double minorRadius, const Point3& p) -> std::pair<double, double>;

	/// @brief Compute the u isoparametric curve on a torus represented by a local frame, a major radius and a minor radius at a given u parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param u The u parameter
	/// @return The u isoparametric curve
	[[nodiscard]] AMCAX_API static Circle3 TorusUIso(const Frame3& pos, double majorRadius, double minorRadius, double u);

	/// @brief Compute the v isoparametric curve on a torus represented by a local frame, a major radius and a minor radius at a given v parameter
	/// @param pos The local frame where the torus lies
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param v The v parameter
	/// @return The v iso parametric curve
	[[nodiscard]] AMCAX_API static Circle3 TorusVIso(const Frame3& pos, double majorRadius, double minorRadius, double v);
};
} // namespace AMCAX

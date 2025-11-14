/// @file      MakeFace.hpp
/// @brief     Class of making a face
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Cylinder;
class Cone;
class Geom3Surface;
class MakeFaceImpl;
class Plane;
class Sphere;
class TopoWire;
class Torus;
#endif

/// @brief Class of making a face
class AMCAX_CLASS_API MakeFace : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeFace();

	/// @brief construct from a face
	/// @param f The face
	AMCAX_API explicit MakeFace(const TopoFace& f);

	/// @brief Construct from a plane
	/// @param p The plane
	AMCAX_API explicit MakeFace(const Plane& p);

	/// @brief Construct from a cylinder
	/// @param c The cylinder
	AMCAX_API explicit MakeFace(const Cylinder& c);

	/// @brief Construct from a cone
	/// @param c The cone
	AMCAX_API explicit MakeFace(const Cone& c);

	/// @brief Construct from a sphere
	/// @param s The sphere
	AMCAX_API explicit MakeFace(const Sphere& s);

	/// @brief Construct from a torus
	/// @param t The torus
	AMCAX_API explicit MakeFace(const Torus& t);

	/// @brief Construct from a surface with tolerance for degenerated edges
	/// @param s The surface
	/// @param tolDegen The tolerance
	AMCAX_API MakeFace(const std::shared_ptr<Geom3Surface>& s, double tolDegen);

	/// @brief Construct from a plane with parameter bounds
	/// @param p The plane
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	AMCAX_API MakeFace(const Plane& p, double uMin, double uMax, double vMin, double vMax);

	/// @brief Construct from a cylinder with parameter bounds
	/// @param c The cylinder
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	AMCAX_API MakeFace(const Cylinder& c, double uMin, double uMax, double vMin, double vMax);

	/// @brief Construct from a cone with parameter bounds
	/// @param c The cone
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	AMCAX_API MakeFace(const Cone& c, double uMin, double uMax, double vMin, double vMax);

	/// @brief Construct from a sphere with parameter bounds
	/// @param s The sphere
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	AMCAX_API MakeFace(const Sphere& s, double uMin, double uMax, double vMin, double vMax);

	/// @brief Construct from a torus with parameter bounds
	/// @param t The torus
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	AMCAX_API MakeFace(const Torus& t, double uMin, double uMax, double vMin, double vMax);

	/// @brief Construct from a surface with parameter bounds and tolerance for degenerated edges
	/// @param s The surface
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	/// @param tolDegen The tolerance
	AMCAX_API MakeFace(const std::shared_ptr<Geom3Surface>& s, double uMin, double uMax, double vMin, double vMax, double tolDegen);

	/// @brief Construct from a wire
	/// @param w The wire
	/// @param onlyPlane If true, the surface will be a plane
	AMCAX_API explicit MakeFace(const TopoWire& w, bool onlyPlane = false);

	/// @brief Construct from a plane and a wire
	/// @param p The plane
	/// @param w The wire
	/// @param inside Whether the face is inside the wire
	AMCAX_API MakeFace(const Plane& p, const TopoWire& w, bool inside = true);

	/// @brief Construct from a cylinder and a wire
	/// @param c The cylinder
	/// @param w The wire
	/// @param inside Whether the face is inside the wire
	AMCAX_API MakeFace(const Cylinder& c, const TopoWire& w, bool inside = true);

	/// @brief Construct from a cone and a wire
	/// @param c The cone
	/// @param w The wire
	/// @param inside Whether the face is inside the wire
	AMCAX_API MakeFace(const Cone& c, const TopoWire& w, bool inside = true);

	/// @brief Construct from a sphere and a wire
	/// @param s The sphere
	/// @param w The wire
	/// @param inside Whether the face is inside the wire
	AMCAX_API MakeFace(const Sphere& s, const TopoWire& w, bool inside = true);

	/// @brief Construct from a torus and a wire
	/// @param t The torus
	/// @param w The wire
	/// @param inside Whether the face is inside the wire
	AMCAX_API MakeFace(const Torus& t, const TopoWire& w, bool inside = true);

	/// @brief Construct from a surface and a wire
	/// @param s The surface
	/// @param w The wire
	/// @param inside Whether the face is inside the wire
	AMCAX_API MakeFace(const std::shared_ptr<Geom3Surface>& s, const TopoWire& w, bool inside = true);

	/// @brief Construct from a face and a wire, the wire will be added to the face
	/// @param f The face
	/// @param w The wire
	AMCAX_API MakeFace(const TopoFace& f, const TopoWire& w);

	/// @brief Initialize and construct from a face
	/// @param f The face
	AMCAX_API void Init(const TopoFace& f);

	/// @brief Initialize and construct from a surface
	/// @param s The surface
	/// @param bound Whether a natural bound is generated
	/// @param tolDegen The tolerance for degenerated edges
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& s, bool bound, double tolDegen);

	/// @brief Initialize and construct from a surface with parameter bounds and a tolerance for degenerated edges
	/// @param s The surface
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	/// @param tolDegen The tolerance for degenerated edges
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& s, double uMin, double uMax, double vMin, double vMax, double tolDegen);

	/// @brief Add a wire to the face
	/// @param w The wire
	AMCAX_API void Add(const TopoWire& w);

	[[nodiscard]] AMCAX_API bool IsDone() const noexcept override;

	/// @brief Get the error status
	/// @return The error status
	[[nodiscard]] AMCAX_API FaceError Error() const noexcept;

	/// @brief Get the constructed face
	/// @return The constructed face
	[[nodiscard]] AMCAX_API const TopoFace& Face();

	/// @brief Get the constructed face
	/// @return The constructed face
	[[nodiscard]] AMCAX_API operator TopoFace();

private:
	std::shared_ptr<MakeFaceImpl> makeFace;
};
} // namespace AMCAX

/// @file      MakePipeShell.hpp
/// @brief     Class of making pipe shell algorithm
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <geomAlgo/GeomFillStyle.hpp>
#include <modeling/MakeSweep.hpp>
#include <offset/TransitionMode.hpp>
#include <topoOp/BRepFillMacros.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepFillPipeShell;
class TopoWire;
class TopoShape;
class TopoVertex;
class LawFunction;
#endif

/// @brief Class of making pipe shell algorithm
/// @details Sweep the profile along the spine. The result can be shell or solid.
///          Two parameters: WithContact and WithCorrection are set to transform the section (profile).
///          If WithContact is true, the profile will be transformed to contact the spine.
///          If WithCorrection is true, the profile will be rotationed to be orthogonal to the spine.
///          The default mode (WithContact = false & WithCorrection = false) can get the same result
///          with MakePipe with default GeomFillTrihedron, which means
///          if the spine and the profile don't contact, the spine will be translated.
///          The pipeline to build a pipeshell is:
///          1. MakePipeShell(input_spine_wire): set the spine wire;
///          2. Add(profile,...): set the profile and the parameters, the profile can only be vertices or wires
///          3. Build(): build shell
///          4. MakeSolid(): build solid
///          if the spine is C0 or even not continuious, do SetTransitionMode() before Build()
///          to set strategy to deal with the discontinuities
class AMCAX_CLASS_API MakePipeShell : public MakeSweep
{
public:
	/// @brief Construct from a spine wire. The default sweep method is corrected frenet.
	/// @param spine The spine wire
	AMCAX_API explicit MakePipeShell(const TopoWire& spine);

	/// @brief Construct by frenet method
	/// @param isFrenet If true, using common frenet method, else using corrected frenet method
	AMCAX_API void SetMode(bool isFrenet = false);

	/// @brief Construct by parallel sweeping
	/// @param frame The fixed frame to perform sweeping, the result face consists of parallel sections along the frame
	AMCAX_API void SetMode(const Frame3& frame);

#ifndef DOXYGEN_SKIP

	/// @internal
	void SetDiscreteMode();

	/// @internal
	void SetMode(const Direction3& biNormal);

	/// @internal
	bool SetMode(const TopoShape& spineSupport);

	/// @internal
	void SetMode(const TopoWire& auxiliarySpine, bool curvilinearEquivalence, BRepFillTypeOfContact keepContact = BRepFillTypeOfContact::NoContact);

#endif

	/// @brief Add a profile and set parameters
	/// @param profile The profile, it can only be vertices or wires
	/// @param withContact If true, the profile will be transformed to contact the spine
	/// @param withCorrection If true, the profile will be rotationed to be orthogonal to the spine
	AMCAX_API void Add(const TopoShape& profile, bool withContact = false, bool withCorrection = false);

	/// @brief Add a profile and set parameters
	/// @param location The vertex on the spine to contact with the profile
	/// @param profile The profile, it can only be vertices or wires
	/// @param withContact If true, the profile will be transformed to contact the spine
	/// @param withCorrection If true, the profile will be rotationed to be orthogonal to the spine
	AMCAX_API void Add(const TopoShape& profile, const TopoVertex& location, bool withContact = false, bool withCorrection = false);

#ifndef DOXYGEN_SKIP

	/// @internal
	void SetLaw(const TopoShape& profile, const std::shared_ptr<LawFunction>& l, bool withContact = false, bool withCorrection = false);

	/// @internal
	void SetLaw(const TopoShape& profile, const std::shared_ptr<LawFunction>& l, const TopoVertex& location, bool withContact = false, bool withCorrection = false);

#endif

	/// @brief Delete the profile
	/// @param profile The profile
	AMCAX_API void Delete(const TopoShape& profile);

	/// @brief Is profile set
	/// @return True if the profile is set
	[[nodiscard]] AMCAX_API bool IsReady() const;

	/// @brief Is build OK
	/// @return The status of making pipe
	[[nodiscard]] AMCAX_API GeomFillPipeStatus GetStatus() const;

	/// @brief Set the tolerance values
	/// @param tol3d The 3D tolerance
	/// @param boundTol The boundary tolerance
	/// @param tolAngular The angular tolerance
	AMCAX_API void SetTolerance(double tol3d = 1.0e-4, double boundTol = 1.0e-4, double tolAngular = 1.0e-2);

	/// @brief Set the maximum V degree of pipeshell
	/// @param newMaxDegree The maximum V degree
	AMCAX_API void SetMaxDegree(int newMaxDegree);

	/// @brief Set the maximum V spans of pipeshell
	/// @param newMaxSegments The maximum V spans
	AMCAX_API void SetMaxSegments(int newMaxSegments);

	/// @brief Set if approximation is forced to make pipeshell C1 (when it is C0)
	/// @param forceApproxC1 Whether to force approximating C1 continuity
	AMCAX_API void SetForceApproxC1(bool forceApproxC1);

	/// @brief Set strategy to deal with discontinuities of the spine
	/// @details The transition type includes three modes:
	///          Transformed: Ignore, make shell with multiple pieces, allow self-intersection;
	///          RightCorner: Modify the spine by extending the two spine segments around the discontinuity to intersect;
	///          RoundCorner: Create round connection. The result is valid when the two segments are connected and planar.
	///          If the condition is not satisfied, setting WithCorrection to true can always obtain a valid result.
	/// @param mode Type of transition mode
	AMCAX_API void SetTransitionMode(TransitionMode mode = TransitionMode::Transformed);

	/// @brief Get the specified number of sections of the pipe shell to make a rapid preview of the pipe shell
	/// @param[in] nSection The number of sections
	/// @param[out] result The list of section shapes
	AMCAX_API void Simulate(int nSection, std::list<TopoShape>& result);

	/// @brief Build shape
	AMCAX_API void Build() override;

	/// @brief Convert the pipe shell to solid
	/// @return Ture if the profile is not closed
	AMCAX_API bool MakeSolid();

	/// @brief Get the first shape of the swept shape
	/// @return The first shape
	[[nodiscard]] AMCAX_API TopoShape FirstShape() override;

	/// @brief Get the last shape of the swept shape
	/// @return The last shape
	[[nodiscard]] AMCAX_API TopoShape LastShape() override;

	/// @brief Get the new shapes generated by the shape which is part of the original profile
	/// @param s The given shape that can be an edge or a vertex
	/// @return The generated shapes
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

	/// @brief Get the error on surface
	/// @return The error on surface
	[[nodiscard]] AMCAX_API double ErrorOnSurface() const;

	/// @brief Get the original profiles
	/// @param[out] profiles The original profiles
	AMCAX_API void Profiles(std::list<TopoShape>& profiles);

	/// @brief Get the original spine
	/// @return The spine wire
	[[nodiscard]] AMCAX_API const TopoWire& Spine();

private:
	std::shared_ptr<BRepFillPipeShell> fillPipeShell;
};
} // namespace AMCAX

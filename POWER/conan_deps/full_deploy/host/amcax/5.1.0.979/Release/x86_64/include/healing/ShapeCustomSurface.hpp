/// @file      ShapeCustomSurface.hpp
/// @brief     Some useful tools for convert a shapes in to analytical
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include<geometry/Geom3Surface.hpp>
#include<geometry/Geom3Plane.hpp>
#include<vector>

namespace AMCAX
{

class Geom3Surface;

/// @brief Simplify the custom surface,convert it to analytical or periodic
class ShapeCustomSurface
{
public:
	AMCAX_API ShapeCustomSurface() noexcept;

	/// @brief Use custom surface for construction 
	/// @param[in] S The Geom3Surface type shared pointer 
	AMCAX_API ShapeCustomSurface(std::shared_ptr<Geom3Surface>& S) noexcept;

	/// @brief Initialize the private mySurf
	/// @param[in] S The Geom3Surface type shared pointer
	AMCAX_API void Init(std::shared_ptr<Geom3Surface>& S) noexcept;

	/// @brief Get maximal deviation of converted surface from the original
	/// @details one computed by last call to ConvertToAnalytical
	AMCAX_API double Gap() const noexcept;

	/// @brief Converts a surface to the analytical form with given
	///		   tolerance, conversion is done only the surface is bspline
	///		   or bezier and this can be approximated by some analytical
	///		   surface with that precision,after convertion,then checking coincidence
	/// @param[in] tol The tolerance
	/// @param[in] substitute The switch deteming whether to replace the surface
	/// @return new analytical surface
	AMCAX_API std::shared_ptr<Geom3Surface> ConvertToAnalytical(const double tol,
		const bool substitute) noexcept;


	/// @brief Converts a surface to the Periodic form with given precision, conversion is done only the surface is bspline
	/// @param[in] substitute The switch deteming whether to replace the surface
	/// @param[in] preci The precision 
	/// @return new periodic Geom3BSplineSurface 
	AMCAX_API std::shared_ptr<Geom3Surface> ConvertToPeriodic(const bool substitute,
		const double preci = -1) noexcept;

private:
	/// @brief Check a set of point 
	/// @param[in] Pnts The point set
	/// @param[in,out] aPln The replace plane for those point set
	/// @param[in,out] Dmax The deviation 
	/// @return whether it is near a plane
	bool NearestPlane(std::vector<Vector3>& Pnts, std::shared_ptr<Geom3Plane>& aPln, double& Dmax) noexcept;


private:
	std::shared_ptr<Geom3Surface> mySurf;
	double myGap;
};
} //AMCAX
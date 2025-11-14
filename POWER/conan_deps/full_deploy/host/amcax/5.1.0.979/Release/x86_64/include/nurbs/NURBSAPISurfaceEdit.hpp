/// @file      NURBSAPISurfaceEdit.hpp
/// @brief     Class of editing surface through curves
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3BSplineCurve.hpp>
#include <geometry/Geom3BSplineSurface.hpp>

namespace AMCAX
{
/// @brief Class of editing surface through curves (The rational B-splines are not currently supported)
/// @details Greville edit method: The number of edited curve is equal to the number of control points in u or v direction
///			 Knot edit method: The number of edited curve is equal to the number of knots that are not repetitive, it will reparameterize the surface and modify its degree to 3
class NURBSAPISurfaceEdit
{
public:
	/// @brief Constructor of edit surface by editing curve
	/// @param[in] inputSurf The input surface, it will not be modified
	/// @param[in] isGreville The greville edit flag
	AMCAX_API explicit NURBSAPISurfaceEdit(const std::shared_ptr<Geom3BSplineSurface>& inputSurf, bool isGreville = true);

	/// @brief Set the edit point is knot edit mothod (default: Greville point)
	/// @param[in] isKnotEdit The knot edit flag
	AMCAX_API void SetKnotEditMode(bool isKnotEdit);

	/// @brief Perform edit the surface by editing curves (The rational B-splines are not currently supported)
	/// @param[in] editedCurveIndex Index of the curve to be edited
	/// @param[in] trans The transformation which need to apply to edit curve
	/// @param[in] isUCrv Is the editing curve is an isoparametric curve in the U direction (i.e C(u) = S(u,vi))
	/// @return true if the surface edited
	AMCAX_API bool PerformCurveEdit(int editCurveId, const Transformation3& trans, bool isUCrv = true);

	/// @brief Get the editing curves on the surface
	/// @param[in] isUCrv Is the editing curve is an isoparametric curve in the U direction (i.e C(u) = S(u,vi))
	/// @return The editing curves on the surface
	[[nodiscard]] AMCAX_API const std::vector<std::shared_ptr<Geom3BSplineCurve>>& GetEditCurve(bool isUCrv) const;

	/// @brief Get the edited result Surface
	/// @return The edited result Surface
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3BSplineSurface>& GetSurface() const;

private:
	void UpdateEditCurve();

	bool isGreville = true;
	std::vector<std::shared_ptr<Geom3BSplineCurve>> uEditCurve;
	std::vector<std::shared_ptr<Geom3BSplineCurve>> vEditCurve;
	std::shared_ptr<Geom3BSplineSurface> mSurface = nullptr;
};
} // namespace AMCAX

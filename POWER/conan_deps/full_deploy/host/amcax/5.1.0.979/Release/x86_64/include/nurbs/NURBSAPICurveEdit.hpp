/// @file      NURBSAPICurveEdit.hpp
/// @brief     Class of editing curves through points
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3BSplineCurve.hpp>

namespace AMCAX
{
/// @brief Class of editing curves through points
/// @details Greville edit method: The number of edited points is equal to the number of control points
///			 Knot edit method: The number of edited points is equal to the number of knots that are not repetitive, it will reparameterize the curve and modify its degree to 3
class NURBSAPICurveEdit
{
public:
	/// @brief Constructor of edit curves by editing points
	/// @param[in] inputCurve The input curve, it will not be modified
	/// @param[in] isGreville The greville edit flag
	AMCAX_API explicit NURBSAPICurveEdit(const std::shared_ptr<Geom3BSplineCurve>& inputCurve, bool isGreville = true);

	/// @brief Set the edit point is knot edit mothod (default: Greville point)
	/// @param[in] isKnotEdit The knot edit flag
	AMCAX_API void SetKnotEditMode(bool isKnotEdit);

	/// @brief Perform edit the curve by editing points
	/// @param[in] editPointId Index of edit points
	/// @param[in] editedPosition The new position of the adjusted edit point
	AMCAX_API void PerformPointEdit(int editPointId, const Point3& editedPosition);

	/// @brief Get the editing points on the curve
	/// @return The editing points on the curve
	[[nodiscard]] AMCAX_API const std::vector<Point3>& GetEditPoint() const;

	/// @brief Get the edited result Curve
	/// @return The edited result Curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3BSplineCurve>& GetCurve() const;

private:
	void UpdateEditPoint();

	bool isGreville = true;
	std::vector<Point3> editPoints;
	std::shared_ptr<Geom3BSplineCurve> mCurve = nullptr;
};
} // namespace AMCAX

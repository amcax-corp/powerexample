/// @file      TMSplineCopy.hpp
/// @brief     Class of Copy TMSpline
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <map>
#include <memory>

#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
class TMSplineCopyImp;

/// @brief Class of Copy TMSpline, the copy not keep the id list
class TMSplineCopy
{
public:
	/// @brief Default constructor
	AMCAX_API TMSplineCopy();

public:
	/// @brief Clone a TMSpline with keep all is equal
	/// @param splineSrc input TMSpline
	/// @return new TMSpline
	AMCAX_API TMSpline* CloneTMSpline(const TMSpline* splineSrc);

	/// @brief Extract faces form a TMSpline to generate a new TMSpline.
	/// @param[in] splineSrc input TMSpline
	/// @param[in,out] fIds indices of the face to be extracted
	/// @return new TMSpline
	AMCAX_API TMSpline* ExtractTMSplineFace(const TMSpline* splineSrc, std::vector<int>& fIds);

	/// @brief Copy a TMSpline only keep the geomtory is same
	/// @param splineSrc input TMSpline
	/// @return new TMSpline
	AMCAX_API TMSpline* CopyTMSplineControl(const TMSpline* splineSrc);

	/// @brief Append one TMSpline to another TMSpline
	/// @param[in,out] splineFin the target TMSpline
	/// @param[in] splineAdd the from TMSpline
	AMCAX_API void AppendToTMSpline(TMSpline* splineFin, const TMSpline* splineAdd);

private:
	std::shared_ptr<TMSplineCopyImp> copyImp;
};

} // namespace TMS
} // namespace AMCAX

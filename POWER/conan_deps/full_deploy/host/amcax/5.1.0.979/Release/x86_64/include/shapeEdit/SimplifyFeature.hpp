/// @file      SimplifyFeature.hpp
/// @brief     Class of simplified geometric features
/// recognition
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.

#pragma once
#include <shapeEdit/FeatureStructs.hpp>
#include <shapeEdit/EditShape.hpp>
#include <topology/TopoShape.hpp>
#include <vector>

namespace AMCAX {
namespace GeomE {
/// @brief Class of SimplifyFeature
class AMCAX_CLASS_API SimplifyFeature : public EditShape
{
public:
	/// @brief Default constructor
	AMCAX_API SimplifyFeature();

	/// @brief Remove the 3D hole features detected from the shape.
	/// @param[in,out] shape The given shape
	/// @param[in] holeInfos 3D hole features detected from the shape
	/// @return void
	AMCAX_API void Remove3DHole(AMCAX::TopoShape& shape, std::vector<AMCAX::GeomE::HoleProperties>& holeInfos);

	/// @brief Remove the Logo features detected from the shape.
	/// @param[in,out] shape The given shape
	/// @param[in] logoInfos Logo features detected from the shape
	/// @return void
	AMCAX_API void Remove3DLogo(AMCAX::TopoShape& shape, std::vector<AMCAX::GeomE::LogoProperties>& logoInfos);

	/// @brief Remove the fillet features detected from the shape.
	/// @param[in] shape The given shape
	/// @param[in] filletInfos Fillet features detected from the shape
	/// @return Shape after fillet removal
	AMCAX_API TopoShape Remove3DFillets(const AMCAX::TopoShape& shape, const std::vector<FilletProperties>& filletInfos);

	/// @brief Remove the chamfer features detected from the shape.
	/// @param[in] shape The given shape
	/// @param[in] chamferInfos Chamfer features detected from the shape
	/// @return Shape after chamfer removal
	AMCAX_API TopoShape Remove3DChamfers(const AMCAX::TopoShape& shape, const std::vector<ChamferProperties>& chamferInfos);

};

} // namespace GeomE
} // namespace AMCAX
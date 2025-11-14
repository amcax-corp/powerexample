/**
 * @file TriSoup.hpp
 * @brief Define traits for triangle soup.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */
#pragma once

// clang-format off
#include <utilities/IndexDef.hpp>
// clang-format on

#ifdef AMCAXMeshing_Enable_StandardTraits
	#include <mesh/Common/CommonDefines.hpp>
#endif

#ifdef AMCAXMeshing_Enable_EigenTraits
	#include <utilities/DisableWarnings.hpp>

	#include <Eigen/Core>
	#include <Eigen/Dense>

	#include <utilities/EnableWarnings.hpp>
#endif

#ifdef AMCAXMeshing_Enable_CommonTraits
	#include <mesh/VecProxy.hpp>
#endif

#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Mesh {

#ifdef AMCAXMeshing_Enable_StandardTraits
class TriSoupTraits
{
public:
	using PointT    = Point3d;
	using VecT      = Vec3d;
	using NormalT   = Vec3d;
	using Tex2D     = Point2d;
	using Tex3D     = Point3d;
	using Color     = Vec3f;
	using ColorA    = Vec4f;
	using Triangle  = Vec3id;
	using Points    = std::vector<PointT>;
	using Normals   = std::vector<NormalT>;
	using Tex2Ds    = std::vector<Tex2D>;
	using Tex3Ds    = std::vector<Tex3D>;
	using Colors    = std::vector<Color>;
	using ColorAs   = std::vector<ColorA>;
	using Triangles = std::vector<Triangle>;
};
#endif

#ifdef AMCAXMeshing_Enable_EigenTraits
class TriSoupTraits_Eigen
{
public:
	using PointT    = typename Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
	using VecT      = typename Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
	using NormalT   = typename Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
	using Tex2D     = typename Eigen::Matrix<float, 2, 1, Eigen::DontAlign>;
	using Tex3D     = typename Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
	using Color     = typename Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;
	using ColorA    = typename Eigen::Matrix<float, 4, 1, Eigen::DontAlign>;
	using Triangle  = typename Eigen::Matrix<int, 3, 1, Eigen::DontAlign>;
	using Points    = std::vector<PointT>;
	using Normals   = std::vector<NormalT>;
	using Tex2Ds    = std::vector<Tex2D>;
	using Tex3Ds    = std::vector<Tex3D>;
	using Colors    = std::vector<Color>;
	using ColorAs   = std::vector<ColorA>;
	using Triangles = std::vector<Triangle>;
};
#endif

#ifdef AMCAXMeshing_Enable_CommonTraits
class TriSoupTraits_Coord
{
public:
	using PointT    = VecProxy<3, double>;
	using VecT      = VecProxy<3, double>;
	using NormalT   = VecProxy<3, double>;
	using Tex2D     = VecProxy<2, double>;
	using Tex3D     = VecProxy<3, double>;
	using Color     = VecProxy<3, float>;
	using ColorA    = VecProxy<4, float>;
	using Triangle  = VecProxy<3, int>;
	using Points    = std::vector<PointT>;
	using Normals   = std::vector<NormalT>;
	using Tex2Ds    = std::vector<Tex2D>;
	using Tex3Ds    = std::vector<Tex3D>;
	using Colors    = std::vector<Color>;
	using ColorAs   = std::vector<ColorA>;
	using Triangles = std::vector<Triangle>;
};
#endif

} // namespace Mesh
} // namespace Meshing
} // namespace AMCAX
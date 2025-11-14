/// @file      FeatureStructs.hpp
/// @brief     Defines data structures and enums for geometric feature
/// recognition
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
// #pragma once

#ifndef FEATRUE_STRUCTS
#define FEATRUE_STRUCTS

#include <topology/TopoShape.hpp>
#include <vector>

namespace AMCAX {
namespace GeomE {

/// @brief Defines the type of the hole
enum class HoleType
{
	Through, // Hole passes completely through the body
	Blind    // Hole has a closed bottom and does not pass through
};

/// @brief Defines the shape of the hole
enum class HoleShape
{
	Canoical,
	Rectange,
	Square,
	Playground,
	Other
};

/// @brief 3D hole Struct Properties‌
struct HoleProperties
{
	HoleType Bottom = HoleType::Through; // Type of the hole bottom
	HoleShape Shape  = HoleShape::Other;  // Shape of the hole
	double TopSize1 = 0;	// If Shape is Square or Rectangle, TopoSize1 represents the length of
							// the top quadrilateral sides. In other cases, TopoSize1 represents the
							// diameter of the sphere enclosed by the closed contour line at the top.
	double TopSize2 = 0;	// If Shape is Square or Rectangle, TopSize2 represents the length of the top quadrilateral sides
	double BottomSize1 = 0; // If Shape is Square or Rectangle, BottomSize1 represents the length of
							// the bottom quadrilateral sides. In other cases, TopoSize1 represents
							// the diameter of the sphere enclosed by the closed contour line at the bottom.
	double BottomSize2 = 0; // If Shape is Square or Rectangle, BottomSize2 represents the length of the bottom quadrilateral sides.
	double Height = 0;		// Height or depth of the hole
	std::vector<TopoShape> HoleFaces;      // Hole base faces
	std::vector<TopoShape> TopBoundary;    // The top contour line of the hole
	std::vector<TopoShape> BottomBoundary; // The bottom contour line of the hole
};

/// @brief  Logo Struct Properties‌
struct LogoProperties
{
	double Height  = 0; // Height of the logo
	double BoxSize = 0; // The diagonal length of the bounding box
	std::vector<TopoShape> LogoFaces;   // Logo base faces
	std::vector<TopoShape> BottomEdges; // The bottom contour line of the logo
};

/// @brief Fillet Struct Properties‌
struct FilletProperties
{
	double MinRadius = 0.0; // Minimum Fillet Radius
	double MaxRadius = 0.0; // Maximum Fillet Radius
	double MinAngle  = 0.0; // Minimum Fillet Angle
	double MaxAngle  = 0.0; // Maximum Fillet Angle
	double MinWidth  = 0.0; // Minimum Fillet Width
	double MaxWidth  = 0.0; // Maximum Fillet Width
	int UVDir = -1; // 0,U-direction fillet  1,V-direction fillet 
	bool FilletPoint = false;// True: point fillet, false: non point fillet
	bool Convexity = true;	 // True: convex fillet, false: concave fillet
	std::vector<TopoShape> FilletFaces; // Fillet base faces 
};

/// @brief Chamfer Struct Properties‌
struct ChamferProperties
{
	double MinWidth = 0.0; // Minimum chamfer width
	double MaxWidth = 0.0; // Maximum chamfer width
	double MinAngle = 0.0; // Minimum chamfer angle
	double MaxAngle = 0.0; // Maximum chamfer angle 
	bool ChamferPoint = false;// True: point chamfer, false: non point chamfer
	std::vector<TopoShape> ChamferFaces; // Chamfer base faces
	std::vector<TopoShape> SupportEdges; // Chamfer support edges
}; 

#ifdef INTERNAL_TEST 
/// @brief Information about a detected grooves
struct GrooveMessage
{
	TopoShape bottomFace;					// bottom faces of the groove
	std::vector<TopoShape> GrooveFaces;     // wall faces of the groove
	std::vector<TopoShape> PlatformFaces;   // platform faces of the groove
};
#endif
} // namespace GeomE
} // namespace AMCAX

#endif // !FEATRUE_STRUCTS
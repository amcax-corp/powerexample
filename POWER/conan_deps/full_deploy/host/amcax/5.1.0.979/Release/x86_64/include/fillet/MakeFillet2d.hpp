/// @file      MakeFillet2d.hpp
/// @brief     Class of make fillet and chamfer on a vertex of a planar face
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <fillet/ChamferFilletMacros.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class TopoEdge;
class TopoFace;
class TopoVertex;
class ChFi2dBuilder;
#endif

/// @brief Class of make fillet and chamfer on a vertex of a planar face
class AMCAX_CLASS_API MakeFillet2d : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeFillet2d();

	/// @brief Construct from a face
	/// @param f The face
	AMCAX_API explicit MakeFillet2d(const TopoFace& f);

	/// @brief Initialize the algorithm by a face
	/// @param f The face
	AMCAX_API void Init(const TopoFace& f);

	/// @brief Initialize the algorithm by a reference face and a modified face
	/// @param refFace The reference face
	/// @param modFace The modified face
	AMCAX_API void Init(const TopoFace& refFace, const TopoFace& modFace);

	/// @brief Add a vertex for making fillet with a radius
	/// @param v The vertex
	/// @param radius The radius
	/// @return The resulting edge
	AMCAX_API TopoEdge AddFillet(const TopoVertex& v, double radius);

	/// @brief Modify the edge to a new radius
	/// @param fillet The fillet edge
	/// @param radius The new radius
	/// @return The resulting edge
	AMCAX_API TopoEdge ModifyFillet(const TopoEdge& fillet, double radius);

	/// @brief Remove the fillet edge
	/// @param fillet The fillet edge
	/// @return The vertex connecting two adjacent edges
	AMCAX_API TopoVertex RemoveFillet(const TopoEdge& fillet);

	/// @brief Add a chamfer edge by two adjacent edges
	/// @param e1 The first edge
	/// @param e2 The second edge
	/// @param d1 The chamfer distance on the first edge
	/// @param d2 The chamfer distance on the second edge
	/// @return The generated chamfer edge
	AMCAX_API TopoEdge AddChamfer(const TopoEdge& e1, const TopoEdge& e2, double d1, double d2);

	/// @brief Add a chamfer edge by an edge with a vertex
	/// @param e The edge
	/// @param v The vertex to be chamfered
	/// @param d The chamfer distance on the edge
	/// @param ang The angle difference to the edge
	/// @return The generated chamfer edge
	AMCAX_API TopoEdge AddChamfer(const TopoEdge& e, const TopoVertex& v, double d, double ang);

	/// @brief Modify a chamfer edge by two edges
	/// @param chamfer The chamfer edge
	/// @param e1 The first edge
	/// @param e2 The second edge
	/// @param d1 The chamfer distance on the first edge
	/// @param d2 The chamfer distance on the second edge
	/// @return The generated chamfer edge
	AMCAX_API TopoEdge ModifyChamfer(const TopoEdge& chamfer, const TopoEdge& e1, const TopoEdge& e2, double d1, double d2);

	/// @brief Modify a chamfer edge by an edge
	/// @param chamfer The chamfer edge
	/// @param e The edge
	/// @param d The chamfer distance on the edge
	/// @param ang The angle difference to the edge
	/// @return The generated chamfer edge
	AMCAX_API TopoEdge ModifyChamfer(const TopoEdge& chamfer, const TopoEdge& e, double d, double ang);

	/// @brief Remove a chamfer edge and get the vertex connecting two adjacent edges
	/// @param chamfer The chamfer edge
	/// @return The vertex connecting two adjacent edges
	AMCAX_API TopoVertex RemoveChamfer(const TopoEdge& chamfer);

	/// @brief Is the edge modified
	/// @param e The edge
	/// @return True if the edge is modified
	[[nodiscard]] AMCAX_API bool IsModified(const TopoEdge& e) const;

	/// @brief Get the fillet edges
	/// @return The fillet edges
	[[nodiscard]] AMCAX_API const std::vector<TopoShape>& FilletEdges() const;

	/// @brief Get the number of fillets on the face
	/// @return The number of fillets
	[[nodiscard]] AMCAX_API int NFillet() const;

	/// @brief Get the chamfer edges
	/// @return The chamfer edges
	[[nodiscard]] AMCAX_API const std::vector<TopoShape>& ChamferEdges() const;

	/// @brief Get the number of chamfers on the face
	/// @return The number of chamfers
	[[nodiscard]] AMCAX_API int NChamfer() const;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& S) override;

	/// @brief Get the number of generated curves
	/// @return The number of generated curves
	[[nodiscard]] AMCAX_API int NCurves() const;

	/// @brief Get the new edges generated from the curve of given index
	/// @param i The index of curve
	/// @return The new edges
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& NewEdges(int i);

	/// @brief Does the edge has a generated edge
	/// @param e The edge
	/// @return True if there is an edge generated from the edge
	[[nodiscard]] AMCAX_API bool HasDescendant(const TopoEdge& e) const;

	/// @brief Get the edge generated from the edge
	/// @param e The edge
	/// @return The generated edge
	[[nodiscard]] AMCAX_API const TopoEdge& DescendantEdge(const TopoEdge& e) const;

	/// @brief Get the basis edge on the face of an edge
	/// @param e The edge
	/// @return The basis edge
	[[nodiscard]] AMCAX_API const TopoEdge& BasisEdge(const TopoEdge& e) const;

	/// @brief Get the error status
	/// @return The error status
	[[nodiscard]] AMCAX_API Fillet2dConstructionError Status() const;

	AMCAX_API void Build() override;

private:
	std::shared_ptr<ChFi2dBuilder> makeChFi2d;
};
} // namespace AMCAX

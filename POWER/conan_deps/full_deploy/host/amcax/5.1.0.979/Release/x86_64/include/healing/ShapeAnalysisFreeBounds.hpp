/// @file      ShapeAnalysisFreeBounds.hpp
/// @brief     Class of analyze the free bounds of faces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <unordered_map>
#include <vector>

#include <math/Plane.hpp>
#include <topology/TopoCompound.hpp>

namespace AMCAX
{
/// @brief Class of analyze the free bounds of faces
class ShapeAnalysisFreeBounds
{
public:
	/// @brief Construct from a compound of shells
	/// @param shape The input shape
	/// @param splitclosed If true, split and generate closed wires
	/// @param splitopen If true, split and generate open wires
	/// @param checkinternaledges If true, check internal edges when searching the free bounds
	AMCAX_API explicit ShapeAnalysisFreeBounds(const TopoShape& shape, bool splitclosed = false, bool splitopen = true, bool checkinternaledges = false);

	/// @brief Get the compound of closed wires
	/// @return The compound of closed wires
	[[nodiscard]] AMCAX_API const TopoCompound& GetClosedWires() const;

	/// @brief Get the compound of open wires
	/// @return The compound of open wires
	[[nodiscard]] AMCAX_API const TopoCompound& GetOpenWires() const;

	/// @brief Connect edges into seperate wires
	/// @param[in,out] edges The input edges
	/// @param[in] toler The tolerance used to connect wires
	/// @param[in] shared If true, the connection of edges is performed only when edges share the same vertex; otherwise, connect the edges if the distance of end vertices is smaller than the tolerance
	/// @param[out] wires The resulting wires
	AMCAX_API static void ConnectEdgesToWires(std::vector<TopoShape>& edges, double toler, bool shared, std::vector<TopoShape>& wires);

	/// @brief Connect disconnected wires into connected wires
	/// @param[in,out] iwires The input wires
	/// @param[in] toler The tolerance used to connect wires
	/// @param[in] shared If true, the connection of wires is performed only when wires share the same vertex; otherwise, connect the wires if the distance of end vertices is smaller than the tolerance
	/// @param[out] owires The resulting wires
	AMCAX_API static void ConnectWiresToWires(std::vector<TopoShape>& iwires, double toler, bool shared, std::vector<TopoShape>& owires);

	/// @brief Connect disconnected wires into connected wires
	/// @param[in,out] iwires The input wires
	/// @param[in] toler The tolerance used to connect wires
	/// @param[in] shared If true, the connection of wires is performed only when wires share the same vertex; otherwise, connect the wires if the distance of end vertices is smaller than the tolerance
	/// @param[out] owires The output wires
	/// @param[out] vertices The map from the original vertices to the new connecting vertices
	AMCAX_API static void ConnectWiresToWires(std::vector<TopoShape>& iwires, double toler, bool shared, std::vector<TopoShape>& owires, std::unordered_map<TopoShape, TopoShape>& vertices);

	/// @brief Split the wires into a group of closed wires and a group of open wires
	/// @param[in] wires The input wires
	/// @param[in] toler The tolerance to judge whether two vertices are coincide.
	/// @param[in] shared If true, only split wires with the same vertex; otherwise, split the wire if the distance of vertices is larger than tolerance.
	/// @param[out] closed The closed wires
	/// @param[out] open The open wires
	AMCAX_API static void SplitWires(const std::vector<TopoShape>& wires, double toler, bool shared, std::vector<TopoShape>& closed, std::vector<TopoShape>& open);

	/// @brief Dispatch the wires into a compound of closed wires and a compound of open wires
	/// @details This function does not verify the wire is real closed or open.
	/// @param[in] wires The input set of wires
	/// @param[out] closed Closed wires
	/// @param[out] open Open wires
	AMCAX_API static void DispatchWires(const std::vector<TopoShape>& wires, TopoCompound& closed, TopoCompound& open);

	/// @brief Connect the input plane edges into the some closed wires and distinguish between inner wires and outer wires. The edges that are not in the plane will be ignored
	/// @details For example, inputting four edges of a rectangle will result in an inner loop and an outer loop
	/// @param[in] edges The input edges, approximate on input plane
	/// @param[in] toler The tolerance used to connect edges
	/// @param[out] inWires The result of inner wires
	/// @param[out] outWires The result of outer wires
	/// @param[in] mPlane The reference plane for projection
	/// @return true when successful
	AMCAX_API static bool FindClosedWires(const std::vector<TopoShape>& edges, double toler, std::vector<TopoShape>& inWires, std::vector<TopoShape>& outWires, const Plane& mPlane = Plane());

	/// @brief Connect the input plane edges into the some closed wires and find the only outer wire. The edges that are not in the plane will be ignored
	/// @param[in] edges The input edges, approximate on input plane
	/// @param[in] toler The tolerance used to connect edges
	/// @param[out] wire The result of inner wires
	/// @param[in] mPlane The reference plane for projection
	/// @return true when find outer wire
	AMCAX_API static bool FindClosedOuterWire(const std::vector<TopoShape>& edges, double toler, TopoShape& wire, const Plane& mPlane = Plane());

private:
	void SplitWires();
	TopoCompound mWires;
	TopoCompound mEdges;
	double mTolerance;
	bool isShared;
	bool isSplitClosed;
	bool isSplitOpen;
};
} // namespace AMCAX

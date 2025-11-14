/// @file      TMSplineMeshing.hpp
/// @brief     Class of meshing a TMSpline to a Triangle mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSTriangleMesh.hpp>
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
class TMScdtTool;
namespace TMS
{
class TUFace;
typedef struct TR_Triangle TR_Face;

/// @brief Class of meshing a TMSpline to a Triangle mesh
class TMSplineMeshing
{
public:
	/// @brief Constructor with TMSpline and density control
	/// @param tsp input TMSpline
	/// @param subtime The number of segments divided by each edge, used for mesh density control
	AMCAX_API explicit TMSplineMeshing(TMSpline* tsp, int subtime = 4);
	AMCAX_API ~TMSplineMeshing();

public:
	/// @brief Set the number of segments divided by each edge, used for mesh density control
	/// @param subtime The number of segments divided by each edge, used for mesh density control
	AMCAX_API void SetSubtime(int subtime);

	/// @brief Meshing TMSpline, save result to draw mesh
	AMCAX_API void UpdateDrawMesh();

	/// @brief Meshing TMSpline patch by patch and calculating patch normal, save result to curvature mesh
	/// @param newSubTime The number of segments divided by each edge, used for mesh density control
	AMCAX_API void UpdateMeshForZebra(int newSubTime = 4);

	/// @brief Meshing TMSpline input faces and calculating patch normal and curvature, save result to curvature mesh
	/// @param face_index the input faces
	/// @param newSubTime The number of segments divided by each edge, used for mesh density control
	AMCAX_API void UpdateMeshForCurvatureGraph(const std::vector<int>& face_index, int newSubTime = 4);

	/// @brief Get the discretization triangle mesh of TMSpline
	/// @return The triangle mesh
	AMCAX_API const TMSTriangleMesh* GetDrawMesh() const;

	/// @brief Get the discretization curvature mesh for show Zebra and curvature of TMSpline
	/// @return The triangle mesh with curvature
	AMCAX_API const TMSTriangleMesh* GetCurvatureMesh() const;

	/// @brief Clear mesh
	AMCAX_API void ClearDrawMesh();

	/// @brief Clear mesh with curvature info
	AMCAX_API void ClearCurvatrueMesh();

	/// @brief Get mesh faces corresponding spline patch in mesh with curvature info
	/// @return mesh faces indices
	AMCAX_API const std::vector<std::vector<size_t>>& SplineFaceMeshFace() const;

private:
	void updateDrawMeshTopology();

	void meshingOneFaceShow(TMSpline* tsp_, TUFace* face,
		std::vector<std::vector<int>>& edge_index, std::vector<bool>& is_edge_search,
		std::vector<int>& vert_index);

	void UpdateCurvateMeshTopology();
	void UpdateCurvateMeshTopology(const std::vector<int>& face_index);
	void meshingOneFaceCurveture(TMSpline* tsp_, TUFace* face);

private:
	void MeshingOneFaceCDTBoundary(const size_t& boundary_num);

	void MeshingOneFaceCDTInner(TMSTriangleMesh* render_mesh, const size_t& n, TUFace* face, TR_Vert& v_temp);

	void MeshingOneFaceCDT(TMSTriangleMesh* render_mesh, const size_t& FL_Index);

private:
	TMSpline* tspline_;
	int sub_time_;

	TMSTriangleMesh* draw_mesh_ = nullptr;
	TMSTriangleMesh* curvature_mesh_ = nullptr;

	std::vector<std::vector<size_t>> Tface_Mface_list_;
	std::vector<std::vector<size_t>> Tedge_Medge_list_;

	TMScdtTool* cdtTool;

	/// Temporary variables
	std::vector<Coord2d> face_param_list;
	std::vector<CoordT<int, 2>> face_edge_list;
	std::vector<size_t> face_vert_mesh_index;
};

} // namespace TMS
} // namespace AMCAX

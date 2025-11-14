/// @file      HLRBRepInternalAlgorithm.hpp
/// @brief     Class of HLR internal algorithm
/// @details   Include the pipeline of hlr:
///            1. Load(): load shape;
///            2. Update(): prepare for hiding
///            3. Hide(): Compute the visible and hidden lines
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/IndexSet.hpp>
#include <hlr/HLRAlgorithmProjector.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepTopAdaptorTool;
class HLRBRepData;
class HLRBRepShapeBounds;
class HLRTopoOutLiner;
#endif

/// @brief Class of HLR internal algorithm
class HLRBRepInternalAlgorithm
{
public:
#ifndef DOXYGEN_SKIP
	/// @brief Create an empty algo
	HLRBRepInternalAlgorithm();

	/// @brief Load the shape into algo
	/// @param S Outlined shape
	/// @param nIso Number of isoparameter lines
	void Load(const std::shared_ptr<HLRTopoOutLiner>& S, int nIso);
#endif

	/// @brief Set the projector
	/// @param P The projector
	AMCAX_API void Projector(const HLRAlgorithmProjector& P);

	/// @brief Get the projector
	/// @return The projector
	[[nodiscard]] AMCAX_API HLRAlgorithmProjector& Projector();

	/// @brief Prepare for hidding. Compute the outlined shape. Compute the status and the bbox of the lines and faces. Classify edges by continuity.
	AMCAX_API void Update();

#ifndef DOXYGEN_SKIP
	/// @brief Get the outliner ID
	/// @param S Outline
	/// @return ID
	[[nodiscard]] AMCAX_TEST_API int Index(const std::shared_ptr<HLRTopoOutLiner>& S) const;
#endif

	/// @brief Remove the Ith shape
	/// @param I The ID of the shape to remove
	AMCAX_API void Remove(int I);

#ifndef DOXYGEN_SKIP

	/// @brief Get the Shape Bounds
	/// @return The Shape Bounds
	[[nodiscard]] AMCAX_TEST_API std::vector<HLRBRepShapeBounds>& SeqOfShapeBounds();

#endif

	/// @brief Get the number of the shapes
	/// @return Num of shapes
	[[nodiscard]] AMCAX_API int NShapes() const;

#ifndef DOXYGEN_SKIP

	/// @brief Get one specified shape bounds
	/// @param I Shape bound ID
	/// @return Shape bound
	[[nodiscard]] AMCAX_TEST_API HLRBRepShapeBounds& ShapeBounds(int I);

#endif

	/// @brief hide itself and hide with each other to get the visible and hidden lines
	AMCAX_API void Hide();

	/// @brief Only do own hiding
	AMCAX_API void PartialHide();

	/// @brief Set all the edges status to show
	AMCAX_API void ShowAll();

	/// @brief Set all the edges status to hide
	AMCAX_API void HideAll();

#ifndef DOXYGEN_SKIP

	[[nodiscard]] AMCAX_TEST_API std::shared_ptr<HLRBRepData> DataStructure() const;

#endif

private:
	void InitEdgeStatus();
	void Select();
	void Select(int I);
	void SelectEdge(int I);
	void SelectFace(int I);
	void ShowAll(int I);
	void HideAll(int I);
	void Hide(int I);
	void Hide(int I, int J);
	void HideSelected(int I, bool SideFace);

	std::shared_ptr<HLRBRepData> dataShape;
	HLRAlgorithmProjector projector;
	std::shared_ptr<std::vector<HLRBRepShapeBounds>> shapes;
	std::shared_ptr<std::unordered_map<TopoShape, BRepTopAdaptorTool>> mapOfShapeTool;
};
} // namespace AMCAX

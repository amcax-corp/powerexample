/// @file       STEPMeshProgress.hpp
/// @brief      Class used for reporting the state of the STEP process.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <step/STEPProgress.hpp>

namespace AMCAX
{
namespace STEP
{
/// @brief Progress state values for the STEP meshing process.
/// @details
/// Extends @ref STEPProgressState with meshing-specific state codes
/// ranging from 0x200 upwards. These codes allow callbacks to
/// distinguish different phases of the meshing operation.
class STEPMeshProgressState : public STEPProgressState
{
public:
	// Error states (continue numbering below WriterFailed).
	static constexpr int MeshingFailed = WriterFailed - 1; // -3

	// Normal states - Meshing
	/// @brief Meshing started. No parameters.
	static constexpr int MeshingStart = 0x200 + 0; // 512
	/// @brief Meshing initialization started. No parameters.
	static constexpr int MeshingInitStart = MeshingStart + 1; // 513
	/// @brief Meshing initialization completed. No parameters.
	static constexpr int MeshingInitComplete = MeshingInitStart + 1; // 514
	/// @brief Meshing solids started. Second payload = number of solids to be meshed.
	static constexpr int MeshingSolidStart = MeshingInitComplete + 1; // 515
	/// @brief Meshing solid in progress.
	/// First payload = index of current solid.
	/// Second payload = number of faces in the solid.
	static constexpr int MeshingSolidInProgress = MeshingSolidStart + 1; // 516
	/// @brief Meshing solid completed.
	/// First payload = index of completed solid.
	/// Second payload = total number of solids.
	static constexpr int MeshingSolidComplete = MeshingSolidInProgress + 1; // 517
	/// @brief Meshing finishing phase started. No parameters.
	static constexpr int MeshingFinishingUpStart = MeshingSolidComplete + 1; // 518
	/// @brief Meshing finishing phase completed. No parameters.
	static constexpr int MeshingFinishingUpComplete = MeshingFinishingUpStart + 1; // 519
	/// @brief Meshing completed successfully. No parameters.
	static constexpr int MeshingComplete = MeshingFinishingUpComplete + 1; // 520

	using STEP::STEPProgressState::STEPProgressState;

	/// @brief Construct from a general STEP progress state.
	STEPMeshProgressState(const STEPProgressState& state)
		: STEPProgressState(state)
	{
	}

	/// @brief Destructor.
	~STEPMeshProgressState() = default;
};

/// @brief Callback type for reporting meshing progress.
/// @param state Current state.
/// @param c1 First payload (meaning depends on the state).
/// @param c2 Second payload (meaning depends on the state).
using STEPMeshProgressCallback =
	std::function<void(const STEPMeshProgressState state,
		const STEPProgressMessage c1,
		const STEPProgressMessage c2)>;

} // namespace STEP
} // namespace AMCAX
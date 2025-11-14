/// @file       STEPOptions.hpp
/// @brief		Options that control the behavior of STEP readers and writers.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <cstdint>

namespace AMCAX::STEP
{
/// @brief Options that control the behavior of STEP readers and writers.
struct STEPOptions
{
	/// @brief Whether to add a standard header section to the STEP file automatically.
	bool WriterAutoHeader = true;

	/// @brief Whether to merge product trees when writing the STEP file.
	bool WriterMergeProductTrees = false;

	/// @brief Whether to allow oriented closed shell when writing Manifold Solid BRep.
	bool Writer_AllowOrientedClosedShellSolid = true;

	/// @brief Number of threads to use for translation.
	/// @details
	/// - If set to a negative value N, translation will use up to (hardware_concurrency() + N) child threads.
	/// - If set to 0, translation will run in the main thread only.
	/// - If set to a positive value N, translation will use up to N child threads.
	int64_t ReaderConcurrency = -1;

	/// @brief Whether to create new threads for meshing (experimental).
	bool ReaderMeshingConcurrent = false;

	/// @brief Maximum number of threads to use for meshing (experimental).
	/// @details
	/// - If set to a positive number N, uses at most N threads.
	/// - If set to a negative number -N, uses at most (hardware_concurrency() - N) threads.
	/// - If set to 0 or less than -hardware_concurrency(), uses all available hardware threads.
	/// Note: the actual number of threads may be fewer than specified.
	/// This setting is only used if @ref ReaderMeshingConcurrent is true.
	int64_t ReaderMeshingConcurrency = -1;
};

} // namespace AMCAX::STEP

/**
 * @file Logger.hpp
 * @brief Defines logger.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */
#pragma once

#include <utilities/Macros.hpp>

#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>

namespace AMCAX {
namespace Meshing {

/****************************/
/******** Logger ************/
/****************************/

class Logger
{
public:
	enum class Level
	{
		TRACE    = 1,
		DEBUG    = 2,
		INFO     = 3,
		WARN     = 4,
		CRITICAL = 5
	};

public:
	AMCAXMeshing_API static void
	initialize(Level console_level = Level::TRACE, bool file_log = false,
	           Level              file_level = Level::TRACE,
	           const std::string &file_path  = "logs/log.txt");

	AMCAXMeshing_API static void update_file_log(bool file_log, Level file_level,
	                                             const std::string &file_path);

	AMCAXMeshing_API static void trace(const std::string &msg);
	AMCAXMeshing_API static void debug(const std::string &msg);
	AMCAXMeshing_API static void info(const std::string &msg);
	AMCAXMeshing_API static void warn(const std::string &msg);
	AMCAXMeshing_API static void critical(const std::string &msg);

	/// @brief reset elapsed time.
	/// @note used in signle thread.
	AMCAXMeshing_API static void elapse_reset();

	/// @brief return the elapsed time since the last reset.
	/// @note used in signle thread.
	AMCAXMeshing_NODISCARD AMCAXMeshing_API static std::chrono::duration<double>
	                 elapsed();

	/// @brief return the current time point.
	/// @brief used in multi threads.
	AMCAXMeshing_NODISCARD AMCAXMeshing_API static std::chrono::steady_clock::
	  time_point
	  elapse_reset_mt();

	/// @brief return the eplased time between current and last time point.
	/// @brief used in multi threads.
	AMCAXMeshing_NODISCARD AMCAXMeshing_API static std::chrono::duration<double>
	elapsed_mt(const std::chrono::steady_clock::time_point &last);
};

/*****************************/
/********  Memory  ***********/
/*****************************/

AMCAXMeshing_API double getPeakMegabytesUsed();
AMCAXMeshing_API double getMegabytesUsed();

/*****************************/
/********	Time   ***********/
/*****************************/

AMCAXMeshing_API std::string getLocalTime();

} // namespace Meshing
} // namespace AMCAX
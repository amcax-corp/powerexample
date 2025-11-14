/// @file      TMSplineIO.hpp
/// @brief     Class of read and write TMSpline
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of read and write TMSpline, the file name suffix is ".tms"
class TMSplineIO
{
public:
	/// @brief return true if file can be openend and written;
	/// @param filename file name with suffix is ".tms"
	AMCAX_API bool CanWrite(const std::string& filename) const;

	/// @brief return true if file can be openend and read;
	/// @param filename file name with suffix is ".tms"
	AMCAX_API bool CanRead(const std::string& filename) const;

	/// @brief load a TMSpline form a file
	/// @param filename file name with suffix is ".tms"
	/// @param tsp the TMSpline
	/// @return true if the input process is succeed
	AMCAX_API bool LoadTMSpline(const std::string& filename, TMSpline*& tsp);

	/// @brief write a TMSpline to a file
	/// @param filename file name with suffix is ".tms"
	/// @param tsp the TMSpline
	/// @param precision the significant digits for write
	/// @return true if the output process is succeed
	AMCAX_API bool WriteTMSpline(const std::string& filename, const TMSpline* tsp, std::streamsize precision = 6);

	/// @brief load a TMSpline form a stream
	/// @param in the input stream
	/// @param tsp the TMSpline
	/// @return true if the input process is succeed
	AMCAX_API bool LoadTMSplineStream(std::istream& in, TMSpline* tsp);

	/// @brief write a TMSpline to a stream
	/// @param out the output stream
	/// @param tsp the TMSpline
	/// @param precision the significant digits for write
	/// @return true if the output process is succeed
	AMCAX_API bool WriteTMSplineStream(std::ostream& out, const TMSpline* tsp, std::streamsize precision = 6);

private:
	std::string GetExtensions() const;
};

} // namespace TMS
} // namespace AMCAX

/// @file      OCCTTool.hpp
/// @brief     Class of read and write shapes from OCCT BRep files
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <istream>
#include <ostream>

#include <common/Macros.hpp>

namespace AMCAX
{
class TopoShape;
namespace OCCTIO
{
/// @brief Class of read and write shapes from OCCT BREP files
/// @details Note that the available format versions of OCCT BREP files are 1, 2 and 3.
class OCCTTool
{
public:
	/// @brief Write a shape to a stream
	/// @param[in] s The shape
	/// @param[in,out] os The output stream
	/// @param[in] format The format version
	/// @return True if the output process is succeed
	AMCAX_API static bool Write(const TopoShape& s, std::ostream& os, int format = 3);

	/// @brief Wrtie a shape to a stream
	/// @param[in] s The shape
	/// @param[in,out] os The output stream
	/// @param[in] withTriangles Determine whether writing the triangular mesh of the shape
	/// @param[in] format The format version
	/// @return True if the output process is succeed
	AMCAX_API static bool Write(const TopoShape& s, std::ostream& os, bool withTriangles, int format = 3);

	/// @brief Read a shape from a stream
	/// @param[out] s The shape
	/// @param[in,out] is The input stream
	/// @return True if the input process is succeed
	AMCAX_API static bool Read(TopoShape& s, std::istream& is);

	/// @brief Write a shape to a file
	/// @param s The shape
	/// @param file The output file
	/// @param format The format version
	/// @return True if the output process is succeed
	AMCAX_API static bool Write(const TopoShape& s, const std::string& file, int format = 3);

	/// @brief Write a shape to a file
	/// @param s The shape
	/// @param file The output file
	/// @param withTriangles Determine whether writing the triangular mesh of the shape
	/// @param format The format version
	/// @return True if the output process is succeed
	AMCAX_API static bool Write(const TopoShape& s, const std::string& file, bool withTriangles, int format = 3);

	/// @brief Read a shape from a file
	/// @param[out] s The shape
	/// @param[in] file The input file
	/// @return True if the input process is succeed
	AMCAX_API static bool Read(TopoShape& s, const std::string& file);
};
} // namespace OCCTIO
} // namespace AMCAX

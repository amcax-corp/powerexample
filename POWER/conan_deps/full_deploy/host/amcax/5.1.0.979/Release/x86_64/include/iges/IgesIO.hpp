/// @file      IgesIO.hpp
/// @brief     Class of IgesIO
/// @details   Class for reading/writing IGES file.
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.

#pragma once
#include <istream>
#include <ostream>
#include <common/Macros.hpp>

#include "./IGESConfig.hpp"

namespace AMCAX
{
	class Label;
	class TopoShape;
	namespace IGES
	{
		/// @brief Class of read/write shapes from/to IGES files
		/// @details Note that the available format versions of IGES files 
		class AMCAX_CLASS_API IgesIO
		{
		public:

			/// @brief Read a shape from file
			/// @param s The shape
			/// @param file The input iges file
			/// @return True if the input process is succeed
			AMCAX_API static bool Read(TopoShape& s, const std::string& file);

			/// @brief Read a shape from istream
			/// @param s The shape
			/// @param iStream The input iges istream 
			/// @return True if the input process is succeed
			AMCAX_API static bool Read(TopoShape& s, std::istream& iStream);

			/// @brief Read a label from file
			/// @param lb The label
			/// @param file The input iges file
			/// @return True if the input process is succeed
			AMCAX_API static bool Read(Label& lb, const std::string& file);

			/// @brief Read a label from istream
			/// @param lb The label
			/// @param iStream The input iges istream 
			/// @return True if the input process is succeed
			AMCAX_API static bool Read(Label& lb, std::istream& iStream);

			/// @brief Write a TopoShape to file 
			/// @param s The shape
			/// @param file The output file
			/// @param format For the macro configuration definition of format, please refer to the comments in the IGESConfig.hpp file
			/// @return True if the output process is succeed
			AMCAX_API static bool Write(const TopoShape& s, const std::string& file, int format = FACE_MODE | WRITE_ATTR_DEFAULT);

			/// @brief Write a TopoShape to ostream
			/// @param s The shape
			/// @param oStream The output ostream
			/// @param format For the macro configuration definition of format, please refer to the comments in the IGESConfig.hpp file
			/// @return True if the output process is succeed
			AMCAX_API static bool Write(const TopoShape& s, std::ostream& oStream, int format = FACE_MODE | WRITE_ATTR_DEFAULT);

			/// @brief Write a Label to file
			/// @param lb The Label
			/// @param file output file
			/// @param format For the macro configuration definition of format, please refer to the comments in the IGESConfig.hpp file
			/// @return True if the output process is succeed
			AMCAX_API static bool Write(const Label& lb, const std::string& file, int format = FACE_MODE | WRITE_ATTR_DEFAULT);

			/// @brief Write a Label to ostream
			/// @param lb The Label
			/// @param oStream output stream
			/// @param format For the macro configuration definition of format, please refer to the comments in the IGESConfig.hpp file
			/// @return True if the output process is succeed
			AMCAX_API static bool Write(const Label& lb, std::ostream& oStream, int format = FACE_MODE | WRITE_ATTR_DEFAULT);
		};
	} // namespace IGES
} // namespace AMCAX
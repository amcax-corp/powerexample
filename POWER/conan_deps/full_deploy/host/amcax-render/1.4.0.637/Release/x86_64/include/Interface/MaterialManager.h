/// @file      MaterialManage.h
/// @brief     Material Management
/// @details   
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef MaterialManage_h
#define MaterialManage_h

#include <memory>
#include <Interface/Material.h>

namespace AMCAXRender {

	/// @brief Material Manager class
	class AMCAX_RENDER_API MaterialManager
	{
	public:
		/// @brief create Material
		/// @return the Material
		virtual std::shared_ptr<Material> CreateMaterial() = 0;

		/// @brief get the Material via Material ID
		/// @return the Material
		virtual std::shared_ptr<Material> GetMaterial(int id) = 0;

		/// @brief remove all the Material
		virtual void RemoveAllMaterial() = 0;

		/// @brief remove the Material via Material ID
		virtual void RemoveMaterial(int id) = 0;

		/// @brief get Material count
		/// @return the Material count
		virtual int GetMaterialCount() const = 0;

		virtual ~MaterialManager() {}
	};
}
#endif

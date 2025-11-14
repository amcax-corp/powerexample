/// @file      LightManage.h
/// @brief     Light Management
/// @details   
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef LightManage_h
#define LightManage_h

#include <memory>
#include <Interface/Light.h>

namespace AMCAXRender {

	/// @brief Light Manager class
	class AMCAX_RENDER_API LightManager
	{
	public:
		/// @brief create light
		/// @return the light
		virtual std::shared_ptr<Light> CreateLight() = 0;

		/// @brief get the light via light ID
		/// @return the light
		virtual std::shared_ptr<Light> GetLight(int id) = 0;

		/// @brief remove all the light in the scene
		virtual void RemoveAllLight() = 0;

		/// @brief remove the light via light ID
		virtual void RemoveLight(int id) = 0;

		/// @brief get light count
		/// @return the light count
		virtual int GetLightCount() const = 0;

		virtual ~LightManager() {}
	};
}
#endif

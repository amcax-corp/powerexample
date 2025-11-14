/// @file      TextureManage.h
/// @brief     Texture Management
/// @details   
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef TextureManager_h
#define TextureManager_h

#include <memory>
#include <Interface/Texture.h>

namespace AMCAXRender {

	/// @brief Texture Manager class
	class AMCAX_RENDER_API TextureManager
	{
	public:
		/// @brief create Texture
		/// @return the Texture
		virtual std::shared_ptr<Texture> CreateTexture() = 0;

		/// @brief get the Texture via Texture ID
		/// @return the Texture
		virtual std::shared_ptr<Texture> GetTexture(int id) = 0;

		/// @brief remove all the Texture
		virtual void RemoveAllTexture() = 0;

		/// @brief remove the Texture via Texture ID
		virtual void RemoveTexture(int id) = 0;

		/// @brief get Texture count
		/// @return the Texture count
		virtual int GetTextureCount() const = 0;

		virtual ~TextureManager() {}
	};
}
#endif

/// @file      Light.h
/// @brief     Light Class File
/// @details   This file defines the light class
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef Light_h
#define Light_h

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender {

	/// @brief Light class
	class AMCAX_RENDER_API Light
	{
	public:
		/// @brief set light color
		/// @param[in] rgb Color 
		virtual void SetColor(const std::array<float, 3>& color) = 0;

		/// @brief get light color
		/// @return rgb Color
		virtual std::array<float, 3> GetColor() const = 0;

		/// @brief get light position
		/// @return rgb Color
		virtual std::array<float, 3> GetPosition() const = 0;

		/// @brief set light position
		/// @param[in] light position
		virtual void SetPostion(const std::array<float, 3>& pos) = 0;

		/// @brief get the light is on or off
		virtual bool IsLightEnable() const = 0;

		/// @brief set the light is on or off
		virtual void SetLightEnable(bool enable) = 0;

		/// @brief set the light type, such as direction point and spot light
		virtual void SetType(LightType type) = 0;

		/// @brief get the light type, such as direction point and spot light
		virtual LightType GetType() const = 0;

		/// @brief get the light unique ID
		virtual int GetLightID() const = 0;

		/// @brief get the light attennuation value
		/// @param[in] atten[0] constant attenuation
		/// @param[in] atten[1] linear attenuation
		/// @param[in] atten[2] quadratic attenuation
		/// @param[in] the attenuation value: attensum = constant + distance * linear +  distance * distance * quadratic
		virtual void SetAttenuation(const std::array<float, 3>& atten) = 0;

		/// @brief set the spot light cone angle value
		virtual void SetSpotConeAngle(float angle) = 0;

		/// @brief get the spot light cone angle value
		virtual float GetSpotConeAngle() const = 0;

		/// @brief set the spot light exponent value
		virtual void SetSpotExponent(float exponent) = 0;

		/// @brief get the spot light exponent value
		virtual float GetSpotExponent() = 0;

		/// @brief set the point at which the light is shining, only used when point light and spot light
		virtual void SetFocalPoint(const std::array<float, 3>& point) = 0;

		/// @brief get the point at which the light is shining, only used when point light and spot light
		virtual std::array<float, 3> GetFocalPoint() = 0;

		virtual ~Light() {}
	};
}

#endif

/// @file      InteractionCenter.h
/// @brief     Interaction Center, Event Registration Management
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef InteractionCenter_h
#define InteractionCenter_h

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender {

    /// @brief Interaction Center Class, Manages Event Registration and Unregistration
    class AMCAX_RENDER_API InteractionCenter {
    public:
        virtual ~InteractionCenter() {}
    public:
    
        /// @brief Set Pick Event Filter
        /// @param[in] type Filter pick data type
        virtual void PickEventFilter(PickType type) = 0;

        /// @brief Set Pick Color
        /// @param[in] rgb Color components
        /// @note Color range [0,1]
        virtual void SetPickColor(double rgb[3]) = 0;

        /// @brief Register Pick Event
        /// @param[in] event Event type
        /// @param[in] command Callback function
        /// @return Returns event id 
        virtual EventId RegisterPickEvent(EventType event, Command command) = 0;

        /// @brief Unregister Pick Event by Event Id
        /// @param[in] id Event id	
        virtual void UnregisterPickEvent(EventId id) = 0;

        /// @brief Unregister Pick Event by Event Type
        /// @param[in] event Event type
        virtual void UnregisterPickEvent(EventType event) = 0;

        /// @brief Register Coordinate System Pick Event
        /// @param[in] event Coordinate system direction marker type (sail, cube)
        /// @param[in] command Callback function
        /// @return Returns event id 
        virtual EventId RegisterMarkerEvent(MarkerEvent event, MarkerCommand command) = 0;

        /// @brief Unregister Coordinate System Pick Event by Event Id
        /// @param[in] id Event id
        virtual void UnregisterMarkerEvent(EventId id) = 0;

        /// @brief Unregister Coordinate System Pick Event by Event Type
        /// @param[in] event Event type
        virtual void UnregisterMarkerEvent(MarkerEvent event) = 0;
    
        /// @brief Register Move Axes Event
        /// @param[in] command Callback
        virtual void RegisterMoveEvent(MoveAxesCommand command) = 0;

        /// @brief Get Current Mouse World Coordinates
        /// @param[out] pos World coordinates
        virtual bool GetPointByMouse(double pos[3]) = 0;
        
        /// @brief Get Current Mouse Screen Coordinates
        /// @param[in] worldPos World coordinates
        /// @param[out] mousePos Screen coordinates
        virtual bool GetPointByWorld(double worldPos[3], int mousePos[2]) = 0;

        /// @brief Set Entity Line Width
        /// @param[in] width Line width
        virtual void SetEntityLineWidth(float width) = 0;

        /// @brief Set Pick Line Width
        /// @param[in] width Line width
        virtual void SetPickLineWidth(float width) = 0;

        /// @brief Set Pick Point Size
        /// @param[in] size Point Size default size = 10
        virtual void SetPickPointSize(float size) = 0;

        /// @brief Set Rubber Band Status
        /// @param[in] status Rubber band status
        /// @see RubberBandStatus
        virtual void SetRubberBandStatus(RubberBandStatus status) = 0;

        /// @brief Register Rubber Band Zoom Event
        /// @param[in] command Callback function
        /// @see RubberBandStatus
        virtual void RegisterRubberBandZoomEvent(RubberBandZoomCallback command) = 0;

        /// @brief Unregister Rubber Band Zoom Event
        virtual void UnregisterRubberBandZoomEvent() = 0;

        /// @brief Register Rubber Band Pick Event
        /// @param[in] command Callback function
        /// @see RubberBandStatus
        virtual void RegisterRubberBandPickEvent(RubberBandPickCallback command) = 0;

        /// @brief Unregister Rubber Band Pick Event
        virtual void UnregisterRubberBandPickEvent() = 0;

        /// @brief Register Mouse Event
        /// @param[in] command Callback function
        virtual EventId RegisterMouseEvent(MouseCommand command) = 0;

        /// @brief Unregister Mouse Event
        /// @param[in] id Event id
        virtual void UnregisterMouseEvent(EventId id) = 0;
        virtual void UnregisterMouseEvent() = 0;

        /// @brief Register Focus Event
        /// @param[in] command Callback
        /// @return Event id
        virtual EventId RegisterFocusEvent(FocusCommand command) = 0;

        /// @brief Unregister Focus Event
        /// @param[in] id Event id
        virtual void UnregisterFocusEvent(EventId id) = 0;
        virtual void UnregisterFocusEvent() = 0;

        /// @brief Set Screen Shot
        /// @param[in] filename File absolute path name
        virtual void SetScreenShot(const char* filename) = 0;

        /// @brief Use Hover HighLight
        /// @param[in] value enable value
        virtual void UseHoverHighLight(bool value) = 0;

        /// @brief Enables or disables the use of rendering accuracy settings.
        /// @param enable Set to true to enable custom rendering accuracy; false to disable it.
        virtual void UseAccuracy(bool enable) = 0;

        /// @brief Get Render Accuracy
        /// @return Accuracy
        virtual double GetAccuracy() = 0;

        /// @brief Sets the rendering accuracy and invokes a callback upon completion.
        /// @param accuracy The desired rendering accuracy (typically between 0.0 and 1.0).
        ///                 Higher values indicate better visual quality at the cost of performance.
        /// @param callback A callback function to be called once the accuracy setting has been applied.
        virtual void SetAccuracy(double accuracy, const std::function<void()>& callback = std::function<void()>()) = 0;

#ifdef USE_AMCAX_KERNEL
        /// @brief Register Pick Event from Shape
        /// @deprecated This method is deprecated
        /// @param[in] event Event type
        /// @param[in] command Callback
        /// @return Event id
        virtual EventId RegisterPickEventfromShape(EventType event, ShapeCommand command) = 0;

        /// @brief Unregister Pick Event from Shape by Event Id
        /// @deprecated This method is deprecated
        /// @param[in] id Event id
        virtual void UnregisterPickEventfromShape(EventId id) = 0;

        /// @brief Unregister Pick Event from Shape by Event Type
        /// @deprecated This method is deprecated
        /// @param[in] event Event type
        virtual void UnregisterPickEventfromShape(EventType event) = 0;
#endif

        /// @brief Set Entity Edge color
        /// @param[in] rgb Edge color
        /// @note color range [0,1]
        virtual void SetEntityEdgeColor(double rgb[3]) = 0;

        /// @brief plane 
        struct CPlane {
            double n[3] = { 1,0,0}; //<nomal
            double c[3] = { 0,0,0 };//center position
        };
        /// @brief Get the world coordinates of the current mouse position on the specified plane
        /// @param[in] in plane
        /// @param[out] out world pos
        virtual void GetMouseWorldPosFromPlane(const CPlane&in, double out[3]) = 0;

    };
}
#endif
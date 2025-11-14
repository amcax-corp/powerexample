#ifndef POWERFC_APP_IDENTIFIER_H
#define POWERFC_APP_IDENTIFIER_H

#pragma once
#include <PFCGlobal.h>
#include <string_view>
#include <limits>

namespace app {
    // class PropertyContainer;
    class DocumentObject;
    class Property;

    class PFC_APP_API Identifier{

        public:
        /**
         * @brief 构造一个Identifier表示一个对象的属性的索引到的值
         * 
         * @param owner 对象
         * @param property_name 属性名
         * @param index 索引（针对列表类属性）
         * @exception base::RuntimeError 如果owner不是DocumentObject，抛出异常
         */
        explicit Identifier(const app::DocumentObject* owner = nullptr, 
                            std::string_view property_name={},
                        int index = std::numeric_limits<int>::max());
        
        /**
         * @brief 构造一个Identifier表示一个对象的属性的索引到的值
         * 
         * @param property 
         * @param index 
         * @exception base::RuntimeError 如果property的owner不是DocumentObject，抛出异常
         */
        Identifier(const app::Property& property, int index = std::numeric_limits<int>::max());

        

    };
}

#endif
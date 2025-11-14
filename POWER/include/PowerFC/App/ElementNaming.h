#ifndef POWERFC_APP_ELEMENTNAMING_H_
#define POWERFC_APP_ELEMENTNAMING_H_

#pragma once
#include <string_view>
#include <PFCGlobal.h>

namespace data{
    //标识子元素开始
    constexpr std::string_view ELEMENT_MAP_PREFIX = ";";
    //标识丢失的子元素
    constexpr std::string_view MISSING_PREFIX = "?";

    //以下标识中开头的';'表示ELEMENT_MAP_PREFIX
    constexpr std::string_view MAPPED_CHILD_ELEMENTS_PREFIX=";:R";

    constexpr std::string_view POSTFIX_TAG= ";:H";//常规Tag后缀，为16进制
    constexpr std::string_view POSTFIX_DECIMAL_TAG               = ";:T";//十进制Tag后缀
    constexpr std::string_view POSTFIX_EXTERNAL_TAG              = ";:X";//外部Tag后缀
    constexpr std::string_view POSTFIX_CHILD                     = ";:C";//子元素后缀

    /// Special postfix to mark the index of an array element
    constexpr std::string_view POSTFIX_INDEX                     = ";:I";
    constexpr std::string_view POSTFIX_UPPER                     = ";:U";
    constexpr std::string_view POSTFIX_LOWER                     = ";:L";
    constexpr std::string_view POSTFIX_MOD                       = ";:M";
    constexpr std::string_view POSTFIX_GEN                       = ";:G";
    constexpr std::string_view POSTFIX_MODGEN                    = ";:MG";
    constexpr std::string_view POSTFIX_DUPLICATE                 = ";D";



    constexpr std::string_view ELEMENT_MAP_INDEX = "_";

    /**
     * @brief 判断subname是否包含MISSING_PREFIX开头的子元素
     * 判断过程为找到最后一个'.'，然后检查'.'之后的子串是否以MISSING_PREFIX开头
     * @param str 
     * @return PFC_APP_API 
     */
    PFC_APP_API bool HasMissingElement(std::string_view subname);

    /**
     * @brief 在subname中找到开始的element name
     * "..elem0."--->"elem0."
     * "..elem0.elem1."--->"elem0."
     * "elem0."--->"elem0."
     * ";elem"--->";elem"
     * @param subname 
     * @return PFC_APP_API 
     */
    PFC_APP_API std::string_view FindElementName(std::string_view subname);



}


#endif
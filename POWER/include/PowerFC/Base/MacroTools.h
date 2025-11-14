#ifndef POWERFC_BASE_MACROTOOLS_H_
#define POWERFC_BASE_MACROTOOLS_H_
#pragma once

#define CONCATE_TWO_(a, b) a##b
#define CONCATE_TWO(a, b) CONCATE_TWO_(a, b) //中间层
#define UNIQUE_VAR(name) CONCATE_TWO(name, __COUNTER__)

// 将 x 转换为字符串
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#endif
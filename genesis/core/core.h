#pragma once
#ifdef DLL_LIB

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#else

#define DLL_API

#endif

#include <functional>
#define BIND_METHOD(method_name) std::bind(&method_name, this, std::placeholders::_1)
#pragma once

#if defined (NDEBUG)

#define SIMPLE_LOG_INFO(x)
#define RAW_LOG_INFO(x)
#define COND_LOG_INFO(bl, x)

#else

#include <iostream>
#include <iomanip>

#define SIMPLE_LOG_INFO(x)          std::cout << (x) << std::endl
#define RAW_LOG_INFO(...)           std::cout << __VA_ARGS__ << std::endl
#define TABLE_RAW_LOG_INFO(x, n)    std::cout << x << std::setw(n)
#define NC_TR_LOG(x, n)             x << std::setw(n)
#define COND_LOG_INFO(bl, x)        ___cond_log_info(bl, x)
#define POINTER_LOG_INFO(p, es, n)  ___working_log_state(p, es, n)

inline static void ___cond_log_info(bool xbl, const char* x)
{
    if (xbl) SIMPLE_LOG_INFO(x);
}

inline static void ___working_log_state(void* pointer, int enum_state, int width)
{
    switch (enum_state) {
	case 0:
		RAW_LOG_INFO(pointer << std::setw(width) << "" << std::setw(width) << "Frame");
		break;
	case 1:
		RAW_LOG_INFO(pointer << std::setw(width) << "" << std::setw(width) << "Briefcase");
		break;
	default:
		RAW_LOG_INFO(pointer << std::setw(width) << "" << std::setw(width)  << "Undefined");
	}
}

#endif



#if defined (NDEBUG)

#define LOG_INFO(x)

#else

#include <iostream>

#define SIMPLE_LOG_INFO(x) std::cout << (x) << std::endl
#define RAW_LOG_INFO(x) std::cout << x << std::endl

#endif

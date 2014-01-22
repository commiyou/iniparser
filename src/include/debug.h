#ifndef INCLUDE_DEBUG_H_
#define _INCLUDE_DEBUG_H_

//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#endif // _INCLUDE_DEBUG_H_
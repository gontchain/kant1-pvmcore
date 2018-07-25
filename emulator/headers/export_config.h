#ifndef EXTERN_CONFIG_H
#define EXTERN_CONFIG_H
// идентификатор экспортируемых функций
#ifdef WIN32
// windows specific directives
#ifdef _USRDLL
#define LIB_EXPORT __declspec(dllexport)
#else
#define LIB_EXPORT //__declspec(dllimport)
#endif  // _USRDLL
#define OLDDBG_EXPORT

#else 
#ifdef LINOS
#define LIB_EXPORT 
#else
#error platform is not supported
#endif
#endif

#endif

#ifdef LINOS
#define inline __inline__
#endif

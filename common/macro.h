#pragma once

//
// DLL export macro for common (Knot Game Common Packages)
//
#ifdef WIN32
#define KGCOMMON_API_EXPORT __declspec(dllexport)
#define KGCOMMON_API_IMPORT __declspec(dllimport)
#else
#define KGCOMMON_API_EXPORT
#define KGCOMMON_API_IMPORT
#endif

#if defined(_USRDLL) && defined(KGCOMMON_EXPORTS)
#define KGCOMMON_API			KGCOMMON_API_EXPORT
#define KGCOMMON_API_EXTERN
#else
#define KGCOMMON_API			KGCOMMON_API_IMPORT
#define KGCOMMON_API_EXTERN		extern
#endif

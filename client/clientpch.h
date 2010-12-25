// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef WIN32

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
  // Windows Header Files:
  #include <windows.h>
  #include <tchar.h>
#endif // #ifdef WIN32

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <memory.h>
#include <assert.h>
// C++ Runtime
#include <iostream>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <list>
#include <set>
#ifdef WIN32
  #include <memory>
#else
  #include <tr1/memory>
#endif

// Boost
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// OpenGL Utility
#if defined(WIN32)
#include <GL/glu.h>
#elif defined(__APPLE__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

// KGF common api
#include "commonapi.h"

//
// Aran
//
#include "AranApi.h"
#include "VideoManGl.h"
#include "AranGl.h"
#include "ArnTextureGl.h"
#include "glext.h"
#include "ArnGlExt.h"
#include "ArnPlane.h"
#include "ArnBone.h"
#include "ArnLight.h"

#if _MSC_VER >= 1500
	#define kgf_shared_ptr std::tr1::shared_ptr
#else
	#define kgf_shared_ptr boost::shared_ptr
#endif

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <tchar.h>
#endif // #ifdef WIN32

// C RunTime Header Files
#include <stdlib.h>
//#include <malloc.h>
#include <memory.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#if defined(WIN32)
#include <GL/glu.h>
#elif defined(__APPLE__)
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <assert.h>
#include <vector>
#ifdef WIN32
  #include <memory>
#else
  #include <tr1/memory>
#endif
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
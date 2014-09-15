// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once


/**
* Include OpenGL or OpenGL ES on various platforms
**/
#if defined(__ANDROID__) || defined(__EMSCRIPTEN__)
	#define GLES
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#else
	#define OpenGL
	#define USE_DEBUG_DRAW
	#include <GL/glew.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

/**
* Emscripten is SDL1 for video and quasi-SDL2 for everything else
**/
#if defined(__EMSCRIPTEN__)
	#define SDL1_VIDEO
#endif


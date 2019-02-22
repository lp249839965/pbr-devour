// This header contains necessary structures for setting up correct screen modes,
// pixel formats, audio formats, and so on.

// minify windows.h
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define VC_LEANMEAN
#define VC_EXTRALEAN

#include <windows.h>
#include <GL/gl.h>

// global resolution
#define XRES 1280
#define YRES 720

#pragma data_seg(".pixelfmt")
static const PIXELFORMATDESCRIPTOR pfd = {
#if BREAK_COMPATIBILITY
	#if POST_PASS
			0, 0, PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
			0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	#else
			0, 0, PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	#endif
#else
	sizeof(pfd), 1, PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
	32, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
#endif
};

#pragma data_seg(".screensettings")
static DEVMODE screenSettings = { 
	{0}, 0, 0, sizeof(screenSettings), 0, DM_PELSWIDTH|DM_PELSHEIGHT,
	{0}, 0, 0, 0, 0, 0, {0}, 0, 0, XRES, YRES, 0, 0,
	#if(WINVER >= 0x0400)
		0, 0, 0, 0, 0, 0,
			#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
			0, 0
		#endif
	#endif
};

#if USE_AUDIO
	#include <mmsystem.h>
	#include <mmreg.h>

	// this file is auto generated by 4klang
	#include "4klang/4klang.h"

	#pragma data_seg(".4klangout")
	static SAMPLE_TYPE lpSoundBuffer[MAX_SAMPLES * 2];
	static HWAVEOUT hWaveOut;

	#pragma data_seg(".wavefmt")
	static WAVEFORMATEX WaveFMT =
	{
	#ifdef FLOAT_32BIT	
		WAVE_FORMAT_IEEE_FLOAT,
	#else
		WAVE_FORMAT_PCM,
	#endif		
		2,                                   // channels
		SAMPLE_RATE,                         // samples per sec
		SAMPLE_RATE*sizeof(SAMPLE_TYPE) * 2, // bytes per sec
		sizeof(SAMPLE_TYPE) * 2,             // block alignment;
		sizeof(SAMPLE_TYPE) * 8,             // bits per sample
		0                                    // extension not needed
	};

	#pragma data_seg(".wavehdr")
	static WAVEHDR WaveHDR =
	{
		(LPSTR)lpSoundBuffer, MAX_SAMPLES * sizeof(SAMPLE_TYPE) * 2, 0, 0, 0, 0, 0, 0
	};

	static MMTIME MMTime =
	{
		TIME_SAMPLES, 0
	};
#endif

//extern "C" int _fltused = 0;

#ifdef EDITOR_CONTROLS
	#define FAIL_KILL false
	#define PID_QUALIFIER
#else
	#define FAIL_KILL true
	#define PID_QUALIFIER const
#endif
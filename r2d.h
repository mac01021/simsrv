
/*
static double
secondsSince(clock_t t) {
	double ticks = (double) (clock() - t);
	double ticksps = (double) CLOCKS_PER_SEC;
	return ticks / ticksps;
}

typedef struct {
	clock_t whenStarted, whenLastReset, startOfCurrentPause;
	double skipped;
} r2dClock;

r2dClock
r2dCreateClock() {
	clock_t st = clock();
	return (r2dClock){ st, st, -1, 0.0 };
}

void
r2dResetClock(r2dClock *clk) {
	clk->whenLastReset = clock();
	clk->skipped = 0.0;
	clk->startOfCurrentPause = -1;
}

void
r2dPauseClock(r2dClock *clk) {
	if (clk->startOfCurrentPause == -1) {
		clk->startOfCurrentPause = clock();
	}
}

void
r2dResumeClock(r2dClock *clk) {
	if (clk->startOfCurrentPause >= 0) {
		clk->skipped += secondsSince(clk->startOfCurrentPause);
		clk->startOfCurrentPause = -1;
	}
}

bool
r2dClockIsPaused(r2dClock *clk) {
	return clk->startOfCurrentPause >= 0;
}

double
r2dClockLifetime(r2dClock *clk) {
	return secondsSince(clk->whenStarted) - clk->skipped;
}

double
r2dClockTimeSinceLastReset(r2dClock *clk) {
	return secondsSince(clk->whenLastReset)
		- clk->skipped
		- secondsSince(clk->startOfCurrentPause);
}

double
r2dAdvanceClock(r2dClock *clk) {
	double vtr = r2dClockTimeSinceLastReset(clk);
	r2dResetClock(clk);
	return vtr;
}

*/

#define SOIL_CHECK_FOR_GL_ERRORS 0

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <wingdi.h>
	#include <GL/gl.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
	/*	I can't test this Apple stuff!	*/
	#include <OpenGL/gl.h>
	#include <Carbon/Carbon.h>
	#define APIENTRY
#else
	#include <GL/gl.h>
	#include <GL/glx.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <string.h>



typedef struct { float r, g, b, a; } r2dColor;

void
r2dSet(r2dColor *color) {
	glColor4f(color->r, color->g, color->b, color->a);
}

const r2dColor AliceBlue =         { 240.0/255.0,   248.0/255.0,   255.0/255.0 };
const r2dColor AntiqueWhite =      { 250.0/255.0,   235.0/255.0,   215.0/255.0 };
const r2dColor Aqua =              { 0.0/255.0,     255.0/255.0,   255.0/255.0 };
const r2dColor Aquamarine =        { 127.0/255.0,   255.0/255.0,   212.0/255.0 };
const r2dColor Azure =             { 240.0/255.0,   255.0/255.0,   255.0/255.0 };
const r2dColor Beige =             { 245.0/255.0,   245.0/255.0,   220.0/255.0 };
const r2dColor Bisque =            { 255.0/255.0,   228.0/255.0,   196.0/255.0 };
const r2dColor Black =             { 0.0/255.0,       0.0/255.0,   0.0/255.0 };
const r2dColor BlanchedAlmond =    { 255.0/255.0,   235.0/255.0,   205.0/255.0 };
const r2dColor Blue =              { 0.0/255.0,       0.0/255.0,   255.0/255.0 };
const r2dColor BlueViolet =        { 138.0/255.0,    43.0/255.0,   226.0/255.0 };
const r2dColor Brown =             { 165.0/255.0,    42.0/255.0,   42.0/255.0 };
const r2dColor BurlyWood =         { 222.0/255.0,   184.0/255.0,   135.0/255.0 };
const r2dColor CadetBlue =         { 95.0/255.0,    158.0/255.0,   160.0/255.0 };
const r2dColor Chartreuse =        { 127.0/255.0,   255.0/255.0,   0.0/255.0 };
const r2dColor Chocolate =         { 210.0/255.0,   105.0/255.0,   30.0/255.0 };
const r2dColor Coral =             { 255.0/255.0,   127.0/255.0,   80.0/255.0 };
const r2dColor CornflowerBlue =    { 100.0/255.0,   149.0/255.0,   237.0/255.0 };
const r2dColor Cornsilk =          { 255.0/255.0,   248.0/255.0,   220.0/255.0 };
const r2dColor Crimson =           { 220.0/255.0,    20.0/255.0,   60.0/255.0 };
const r2dColor Cyan =              { 0.0/255.0,     255.0/255.0,   255.0/255.0 };
const r2dColor DarkBlue =          { 0.0/255.0,       0.0/255.0,   139.0/255.0 };
const r2dColor DarkCyan =          { 0.0/255.0,     139.0/255.0,   139.0/255.0 };
const r2dColor DarkGoldenrod =     { 184.0/255.0,   134.0/255.0,   11.0/255.0 };
const r2dColor DarkGray =          { 169.0/255.0,   169.0/255.0,   169.0/255.0 };
const r2dColor DarkGreen =         { 0.0/255.0,     100.0/255.0,   0.0/255.0 };
const r2dColor DarkKhaki =         { 189.0/255.0,   183.0/255.0,   107.0/255.0 };
const r2dColor DarkMagenta =       { 139.0/255.0,     0.0/255.0,   139.0/255.0 };
const r2dColor DarkOliveGreen =    { 85.0/255.0,    107.0/255.0,   47.0/255.0 };
const r2dColor DarkOrange =        { 255.0/255.0,   140.0/255.0,   0.0/255.0 };
const r2dColor DarkOrchid =        { 153.0/255.0,    50.0/255.0,   204.0/255.0 };
const r2dColor DarkRed =           { 139.0/255.0,     0.0/255.0,   0.0/255.0 };
const r2dColor DarkSalmon =        { 233.0/255.0,   150.0/255.0,   122.0/255.0 };
const r2dColor DarkSeaGreen =      { 143.0/255.0,   188.0/255.0,   139.0/255.0 };
const r2dColor DarkSlateBlue =     { 72.0/255.0,     61.0/255.0,   139.0/255.0 };
const r2dColor DarkSlateGray =     { 47.0/255.0,     79.0/255.0,   79.0/255.0 };
const r2dColor DarkTurquoise =     { 0.0/255.0,     206.0/255.0,   209.0/255.0 };
const r2dColor DarkViolet =        { 148.0/255.0,     0.0/255.0,   211.0/255.0 };
const r2dColor DeepPink =          { 255.0/255.0,    20.0/255.0,   147.0/255.0 };
const r2dColor DeepSkyBlue =       { 0.0/255.0,     191.0/255.0,   255.0/255.0 };
const r2dColor DimGray =           { 105.0/255.0,   105.0/255.0,   105.0/255.0 };
const r2dColor DodgerBlue =        { 30.0/255.0,    144.0/255.0,   255.0/255.0 };
const r2dColor Firebrick =         { 178.0/255.0,    34.0/255.0,   34.0/255.0 };
const r2dColor FloralWhite =       { 255.0/255.0,   250.0/255.0,   240.0/255.0 };
const r2dColor ForestGreen =       { 34.0/255.0,    139.0/255.0,   34.0/255.0 };
const r2dColor Fuchsia =           { 255.0/255.0,     0.0/255.0,   255.0/255.0 };
const r2dColor Gainsboro =         { 220.0/255.0,   220.0/255.0,   220.0/255.0 };
const r2dColor GhostWhite =        { 248.0/255.0,   248.0/255.0,   255.0/255.0 };
const r2dColor Gold =              { 255.0/255.0,   215.0/255.0,   0.0/255.0 };
const r2dColor Goldenrod =         { 218.0/255.0,   165.0/255.0,   32.0/255.0 };
const r2dColor Gray =              { 128.0/255.0,   128.0/255.0,   128.0/255.0 };
const r2dColor Green =             { 0.0/255.0,     128.0/255.0,   0.0/255.0 };
const r2dColor GreenYellow =       { 173.0/255.0,   255.0/255.0,   47.0/255.0 };
const r2dColor Honeydew =          { 240.0/255.0,   255.0/255.0,   240.0/255.0 };
const r2dColor HotPink =           { 255.0/255.0,   105.0/255.0,   180.0/255.0 };
const r2dColor IndianRed =         { 205.0/255.0,    92.0/255.0,   92.0/255.0 };
const r2dColor Indigo =            { 75.0/255.0,      0.0/255.0,   130.0/255.0 };
const r2dColor Ivory =             { 255.0/255.0,   255.0/255.0,   240.0/255.0 };
const r2dColor Khaki =             { 240.0/255.0,   230.0/255.0,   140.0/255.0 };
const r2dColor Lavender =          { 230.0/255.0,   230.0/255.0,   250.0/255.0 };
const r2dColor LavenderBlush =     { 255.0/255.0,   240.0/255.0,   245.0/255.0 };
const r2dColor LawnGreen =         { 124.0/255.0,   252.0/255.0,   0.0/255.0 };
const r2dColor LemonChiffon =      { 255.0/255.0,   250.0/255.0,   205.0/255.0 };
const r2dColor LightBlue =         { 173.0/255.0,   216.0/255.0,   230.0/255.0 };
const r2dColor LightCoral =        { 240.0/255.0,   128.0/255.0,   128.0/255.0 };
const r2dColor LightCyan =         { 224.0/255.0,   255.0/255.0,   255.0/255.0 };
const r2dColor LightGoldenrod =    { 250.0/255.0,   250.0/255.0,   210.0/255.0 };
const r2dColor LightGray =         { 211.0/255.0,   211.0/255.0,   211.0/255.0 };
const r2dColor LightGreen =        { 144.0/255.0,   238.0/255.0,   144.0/255.0 };
const r2dColor LightPink =         { 255.0/255.0,   182.0/255.0,   193.0/255.0 };
const r2dColor LightSalmon =       { 255.0/255.0,   160.0/255.0,   122.0/255.0 };
const r2dColor LightSeaGreen =     { 32.0/255.0,    178.0/255.0,   170.0/255.0 };
const r2dColor LightSkyBlue =      { 135.0/255.0,   206.0/255.0,   250.0/255.0 };
const r2dColor LightSlateGray =    { 119.0/255.0,   136.0/255.0,   153.0/255.0 };
const r2dColor LightSteelBlue =    { 176.0/255.0,   196.0/255.0,   222.0/255.0 };
const r2dColor LightYellow =       { 255.0/255.0,   255.0/255.0,   224.0/255.0 };
const r2dColor Lime =              { 0.0/255.0,     255.0/255.0,   0.0/255.0 };
const r2dColor LimeGreen =         { 50.0/255.0,    205.0/255.0,   50.0/255.0 };
const r2dColor Linen =             { 250.0/255.0,   240.0/255.0,   230.0/255.0 };
const r2dColor Magenta =           { 255.0/255.0,     0.0/255.0,   255.0/255.0 };
const r2dColor Maroon =            { 128.0/255.0,     0.0/255.0,   0.0/255.0 };
const r2dColor MediumAquamarine =  { 102.0/255.0,   205.0/255.0,   170.0/255.0 };
const r2dColor MediumBlue =        { 0.0/255.0,       0.0/255.0,   205.0/255.0 };
const r2dColor MediumOrchid =      { 186.0/255.0,    85.0/255.0,   211.0/255.0 };
const r2dColor MediumPurple =      { 147.0/255.0,   112.0/255.0,   219.0/255.0 };
const r2dColor MediumSeaGreen =    { 60.0/255.0,    179.0/255.0,   113.0/255.0 };
const r2dColor MediumSlateBlue =   { 123.0/255.0,   104.0/255.0,   238.0/255.0 };
const r2dColor MediumSpringGreen = { 0.0/255.0,     250.0/255.0,   154.0/255.0 };
const r2dColor MediumTurquoise =   { 72.0/255.0,    209.0/255.0,   204.0/255.0 };
const r2dColor MediumVioletRed =   { 199.0/255.0,    21.0/255.0,   133.0/255.0 };
const r2dColor MidnightBlue =      { 25.0/255.0,     25.0/255.0,   112.0/255.0 };
const r2dColor MintCream =         { 245.0/255.0,   255.0/255.0,   250.0/255.0 };
const r2dColor MistyRose =         { 255.0/255.0,   228.0/255.0,   225.0/255.0 };
const r2dColor Moccasin =          { 255.0/255.0,   228.0/255.0,   181.0/255.0 };
const r2dColor NavajoWhite =       { 255.0/255.0,   222.0/255.0,   173.0/255.0 };
const r2dColor Navy =              { 0.0/255.0,       0.0/255.0,   128.0/255.0 };
const r2dColor OldLace =           { 253.0/255.0,   245.0/255.0,   230.0/255.0 };
const r2dColor Olive =             { 128.0/255.0,   128.0/255.0,   0.0/255.0 };
const r2dColor OliveDrab =         { 107.0/255.0,   142.0/255.0,   35.0/255.0 };
const r2dColor Orange =            { 255.0/255.0,   165.0/255.0,   0.0/255.0 };
const r2dColor OrangeRed =         { 255.0/255.0,    69.0/255.0,   0.0/255.0 };
const r2dColor Orchid =            { 218.0/255.0,   112.0/255.0,   214.0/255.0 };
const r2dColor PaleGoldenrod =     { 238.0/255.0,   232.0/255.0,   170.0/255.0 };
const r2dColor PaleGreen =         { 152.0/255.0,   251.0/255.0,   152.0/255.0 };
const r2dColor PaleTurquoise =     { 175.0/255.0,   238.0/255.0,   238.0/255.0 };
const r2dColor PaleVioletRed =     { 219.0/255.0,   112.0/255.0,   147.0/255.0 };
const r2dColor PapayaWhip =        { 255.0/255.0,   239.0/255.0,   213.0/255.0 };
const r2dColor PeachPuff =         { 255.0/255.0,   218.0/255.0,   185.0/255.0 };
const r2dColor Peru =              { 205.0/255.0,   133.0/255.0,   63.0/255.0 };
const r2dColor Pink =              { 255.0/255.0,   192.0/255.0,   203.0/255.0 };
const r2dColor Plum =              { 221.0/255.0,   160.0/255.0,   221.0/255.0 };
const r2dColor PowderBlue =        { 176.0/255.0,   224.0/255.0,   230.0/255.0 };
const r2dColor Purple =            { 128.0/255.0,     0.0/255.0,   128.0/255.0 };
const r2dColor Red =               { 255.0/255.0,     0.0/255.0,   0.0/255.0 };
const r2dColor RosyBrown =         { 188.0/255.0,   143.0/255.0,   143.0/255.0 };
const r2dColor RoyalBlue =         { 65.0/255.0,    105.0/255.0,   225.0/255.0 };
const r2dColor SaddleBrown =       { 139.0/255.0,    69.0/255.0,   19.0/255.0 };
const r2dColor Salmon =            { 250.0/255.0,   128.0/255.0,   114.0/255.0 };
const r2dColor SandyBrown =        { 244.0/255.0,   164.0/255.0,   96.0/255.0 };
const r2dColor SeaGreen =          { 46.0/255.0,    139.0/255.0,   87.0/255.0 };
const r2dColor SeaShell =          { 255.0/255.0,   245.0/255.0,   238.0/255.0 };
const r2dColor Sienna =            { 160.0/255.0,    82.0/255.0,   45.0/255.0 };
const r2dColor Silver =            { 192.0/255.0,   192.0/255.0,   192.0/255.0 };
const r2dColor SkyBlue =           { 135.0/255.0,   206.0/255.0,   235.0/255.0 };
const r2dColor SlateBlue =         { 106.0/255.0,    90.0/255.0,   205.0/255.0 };
const r2dColor SlateGray =         { 112.0/255.0,   128.0/255.0,   144.0/255.0 };
const r2dColor Snow =              { 255.0/255.0,   250.0/255.0,   250.0/255.0 };
const r2dColor SpringGreen =       { 0.0/255.0,     255.0/255.0,   127.0/255.0 };
const r2dColor SteelBlue =         { 70.0/255.0,    130.0/255.0,   180.0/255.0 };
const r2dColor Tan =               { 210.0/255.0,   180.0/255.0,   140.0/255.0 };
const r2dColor Teal =              { 0.0/255.0,     128.0/255.0,   128.0/255.0 };
const r2dColor Thistle =           { 216.0/255.0,   191.0/255.0,   216.0/255.0 };
const r2dColor Tomato =            { 255.0/255.0,    99.0/255.0,   71.0/255.0 };
const r2dColor TransparentBlack =  { 0.0/255.0,       0.0/255.0,   0.0/255.0 };
const r2dColor TransparentWhite =  { 255.0/255.0,   255.0/255.0,   255.0/255.0 };
const r2dColor Turquoise =         { 64.0/255.0,    224.0/255.0,   208.0/255.0 };
const r2dColor Violet =            { 238.0/255.0,   130.0/255.0,   238.0/255.0 };
const r2dColor Wheat =             { 245.0/255.0,   222.0/255.0,   179.0/255.0 };
const r2dColor White =             { 255.0/255.0,   255.0/255.0,   255.0/255.0 };
const r2dColor WhiteSmoke =        { 245.0/255.0,   245.0/255.0,   245.0/255.0 };
const r2dColor Yellow =            { 255.0/255.0,   255.0/255.0,   0.0/255.0 };
const r2dColor YellowGreen =       { 154.0/255.0,   205.0/255.0,   50.0/255.0 };







typedef struct { float x, y; }      r2dVec2d;
typedef struct { float x, y, z; }   r2dVec3d;
typedef struct { float x, y, z, w; } r2dVec4d;

r2dVec2d
r2dCreateVec2d(float x, float y) {
	return (r2dVec2d) { x, y };
}

typedef struct {
	float m11, m12, m13, m14,
	      m21, m22, m23, m24,
	      m31, m32, m33, m34,
	      m41, m42, m43, m44;
} r2dMat4d;

const r2dMat4d I4d =  { 1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};

r2dMat4d
r2dCreateRotationX(float radians) {
	float a = cosf(radians);
	float b = sinf(radians);
	return (r2dMat4d) {
		1,  0, 0, 0,
		0,  a, b, 0,
		0, -b, a, 0,
		0,  0, 0, 1};
}

r2dMat4d
r2dCreateRotationY(float radians) {
	float a = cosf(radians);
	float b = sinf(radians);
	return (r2dMat4d) {
		a, 0, -b, 0,
		0, 1,  0, 0,
		b, 0,  a, 0,
		0, 0,  0, 1};
}

r2dMat4d
r2dCreateRotationZ(float radians) {
	float a = cosf(radians);
	float b = sinf(radians);
	return (r2dMat4d) {
		 a, b, 0, 0,
		-b, a, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1};
}

r2dMat4d
r2dCreateScale(float x, float y, float z) {
	return (r2dMat4d) {
		 x, 0, 0, 0,
		 0, y, 0, 0,
		 0, 0, z, 0,
		 0, 0, 0, 1};
}

r2dMat4d
r2dCreateUniformScale(float f) {
	return r2dCreateScale(f, f, f);
}

void
r2dAddMat4dIntoMat4d(r2dMat4d *dst, r2dMat4d *src) {
	dst->m11 += src->m11;
	dst->m12 += src->m12;
	dst->m13 += src->m13;
	dst->m14 += src->m14;
	dst->m21 += src->m21;
	dst->m22 += src->m22;
	dst->m23 += src->m23;
	dst->m24 += src->m24;
	dst->m31 += src->m31;
	dst->m32 += src->m32;
	dst->m33 += src->m33;
	dst->m34 += src->m34;
	dst->m41 += src->m41;
	dst->m42 += src->m42;
	dst->m43 += src->m43;
	dst->m44 += src->m44;
}

void
r2dAddScalarIntoMat4d(r2dMat4d *dst, float src) {
	dst->m11 += src;
	dst->m12 += src;
	dst->m13 += src;
	dst->m14 += src;
	dst->m21 += src;
	dst->m22 += src;
	dst->m23 += src;
	dst->m24 += src;
	dst->m31 += src;
	dst->m32 += src;
	dst->m33 += src;
	dst->m34 += src;
	dst->m41 += src;
	dst->m42 += src;
	dst->m43 += src;
	dst->m44 += src;
}

void
r2dScaleMat4d(r2dMat4d *m, float f) {
	m->m11 *= f;
	m->m12 *= f;
	m->m13 *= f;
	m->m14 *= f;
	m->m21 *= f;
	m->m22 *= f;
	m->m23 *= f;
	m->m24 *= f;
	m->m31 *= f;
	m->m32 *= f;
	m->m33 *= f;
	m->m34 *= f;
	m->m41 *= f;
	m->m42 *= f;
	m->m43 *= f;
	m->m44 *= f;
}

void
r2dApplyMat4dToMat4d(r2dMat4d *targ, r2dMat4d *xform) {
	r2dMat4d tmp;
	tmp.m11 = xform->m11 * targ->m11
		+ xform->m12 * targ->m21
		+ xform->m13 * targ->m31
		+ xform->m14 * targ->m41;

	tmp.m12 = xform->m11 * targ->m12
		+ xform->m12 * targ->m22
		+ xform->m13 * targ->m32
		+ xform->m14 * targ->m42;

	tmp.m13 = xform->m11 * targ->m13
		+ xform->m12 * targ->m23
		+ xform->m13 * targ->m33
		+ xform->m14 * targ->m43;

	tmp.m14 = xform->m11 * targ->m14
		+ xform->m12 * targ->m24
		+ xform->m13 * targ->m34
		+ xform->m14 * targ->m44;

	tmp.m21 = xform->m21 * targ->m11
		+ xform->m22 * targ->m21
		+ xform->m23 * targ->m31
		+ xform->m24 * targ->m41;

	tmp.m22 = xform->m21 * targ->m12
		+ xform->m22 * targ->m22
		+ xform->m23 * targ->m32
		+ xform->m24 * targ->m42;

	tmp.m23 = xform->m21 * targ->m13
		+ xform->m22 * targ->m23
		+ xform->m23 * targ->m33
		+ xform->m24 * targ->m43;

	tmp.m24 = xform->m21 * targ->m14
		+ xform->m22 * targ->m24
		+ xform->m23 * targ->m34
		+ xform->m24 * targ->m44;

	tmp.m31 = xform->m31 * targ->m11
		+ xform->m32 * targ->m21
		+ xform->m33 * targ->m31
		+ xform->m34 * targ->m41;

	tmp.m32 = xform->m31 * targ->m12
		+ xform->m32 * targ->m22
		+ xform->m33 * targ->m32
		+ xform->m34 * targ->m42;

	tmp.m33 = xform->m31 * targ->m13
		+ xform->m32 * targ->m23
		+ xform->m33 * targ->m33
		+ xform->m34 * targ->m43;

	tmp.m34 = xform->m31 * targ->m14
		+ xform->m32 * targ->m24
		+ xform->m33 * targ->m34
		+ xform->m34 * targ->m44;

	tmp.m41 = xform->m41 * targ->m11
		+ xform->m42 * targ->m21
		+ xform->m43 * targ->m31
		+ xform->m44 * targ->m41;

	tmp.m42 = xform->m41 * targ->m12
		+ xform->m42 * targ->m22
		+ xform->m43 * targ->m32
		+ xform->m44 * targ->m42;

	tmp.m43 = xform->m41 * targ->m13
		+ xform->m42 * targ->m23
		+ xform->m43 * targ->m33
		+ xform->m44 * targ->m43;

	tmp.m44 = xform->m41 * targ->m14
		+ xform->m42 * targ->m24
		+ xform->m43 * targ->m34
		+ xform->m44 * targ->m44;

	*targ = tmp;
}



typedef struct{ float x, y, width, height; } r2dRectangle;

r2dRectangle
r2dCreateRectangle(float x, float y, float w, float h) {
	return (r2dRectangle) { x, y, w, h};
}

float
r2dRectangleTop(r2dRectangle *r) {
	return r->y;
}

float
r2dRectangleBottom(r2dRectangle *r) {
	return r->y + r->height;
}

float
r2dRectangleLeft(r2dRectangle *r) {
	return r->x;
}

float
r2dRectangleRight(r2dRectangle *r) {
	return r->x + r->width;
}

float
r2dRectangleMidX(r2dRectangle *r) {
	return (r2dRectangleRight(r) + r2dRectangleLeft(r)) / 2;
}

float
r2dRectangleMidY(r2dRectangle *r) {
	return (r2dRectangleBottom(r) + r2dRectangleTop(r)) / 2;
}

float
r2dRectangleWidth(r2dRectangle *r) {
	return r->width;
}

float
r2dRectangleHeight(r2dRectangle *r) {
	return r->height;
}

float
r2dRectangleDiagonal(r2dRectangle *r) {
	float w = r->width;
	float h = r->height;
	return sqrt(w*w + h*h);
}

r2dVec2d
r2dRectangleTopLeft(r2dRectangle *r) {
	return r2dCreateVec2d(r->x, r->y);
};

r2dVec2d
r2dRectangleTopRight(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleRight(r), r->y);
};

r2dVec2d
r2dRectangleBottomLeft(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleLeft(r), r2dRectangleBottom(r));
};

r2dVec2d
r2dRectangleBottomRight(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleRight(r), r2dRectangleBottom(r));
};

r2dVec2d
r2dRectangleTopCenter(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleMidX(r), r2dRectangleTop(r));
};

r2dVec2d
r2dRectangleBottomCenter(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleMidX(r), r2dRectangleBottom(r));
};

r2dVec2d
r2dRectangleCenterLeft(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleLeft(r), r2dRectangleMidY(r));
};

r2dVec2d
r2dRectangleCenterRight(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleRight(r), r2dRectangleMidY(r));
};

r2dVec2d
r2dRectangleCenter(r2dRectangle *r) {
	return r2dCreateVec2d(r2dRectangleMidX(r), r2dRectangleMidY(r));
};




#define SOIL_RGB_S3TC_DXT1		0x83F0
#define SOIL_RGBA_S3TC_DXT1		0x83F1
#define SOIL_RGBA_S3TC_DXT3		0x83F2
#define SOIL_RGBA_S3TC_DXT5		0x83F3

#define SOIL_TEXTURE_RECTANGLE_ARB				0x84F5
#define SOIL_MAX_RECTANGLE_TEXTURE_SIZE_ARB		0x84F8



#define SOIL_TEXTURE_WRAP_R			0x8072
#define SOIL_CLAMP_TO_EDGE			0x812F
#define SOIL_NORMAL_MAP				0x8511
#define SOIL_REFLECTION_MAP			0x8512
#define SOIL_TEXTURE_CUBE_MAP			0x8513
#define SOIL_TEXTURE_BINDING_CUBE_MAP		0x8514
#define SOIL_TEXTURE_CUBE_MAP_POSITIVE_X	0x8515
#define SOIL_TEXTURE_CUBE_MAP_NEGATIVE_X	0x8516
#define SOIL_TEXTURE_CUBE_MAP_POSITIVE_Y	0x8517
#define SOIL_TEXTURE_CUBE_MAP_NEGATIVE_Y	0x8518
#define SOIL_TEXTURE_CUBE_MAP_POSITIVE_Z	0x8519
#define SOIL_TEXTURE_CUBE_MAP_NEGATIVE_Z	0x851A
#define SOIL_PROXY_TEXTURE_CUBE_MAP		0x851B
#define SOIL_MAX_CUBE_MAP_TEXTURE_SIZE		0x851C


enum {
	SOIL_CAPABILITY_UNKNOWN = -1,
	SOIL_CAPABILITY_NONE = 0,
	SOIL_CAPABILITY_PRESENT = 1
};


static int has_NPOT_capability = SOIL_CAPABILITY_UNKNOWN;
static int has_tex_rectangle_capability = SOIL_CAPABILITY_UNKNOWN;
static int has_DXT_capability = SOIL_CAPABILITY_UNKNOWN;

char *result_string_pointer = "SOIL initialized";

/**
	The format of images that may be loaded (force_channels).
	SOIL_LOAD_AUTO leaves the image in whatever format it was found.
	SOIL_LOAD_L forces the image to load as Luminous (greyscale)
	SOIL_LOAD_LA forces the image to load as Luminous with Alpha
	SOIL_LOAD_RGB forces the image to load as Red Green Blue
	SOIL_LOAD_RGBA forces the image to load as Red Green Blue Alpha
**/
enum {
	SOIL_LOAD_AUTO = 0,
	SOIL_LOAD_L = 1,
	SOIL_LOAD_LA = 2,
	SOIL_LOAD_RGB = 3,
	SOIL_LOAD_RGBA = 4
};

/**
	Passed in as reuse_texture_ID, will cause SOIL to
	register a new texture ID using glGenTextures().
	If the value passed into reuse_texture_ID > 0 then
	SOIL will just re-use that texture ID (great for
	reloading image assets in-game!)
**/
enum { SOIL_CREATE_NEW_ID = 0 };

/**
	flags you can pass into SOIL_load_OGL_texture()
	and SOIL_create_OGL_texture().
	(note that if SOIL_FLAG_DDS_LOAD_DIRECT is used
	the rest of the flags with the exception of
	SOIL_FLAG_TEXTURE_REPEATS will be ignored while
	loading already-compressed DDS files.)

	SOIL_FLAG_POWER_OF_TWO: force the image to be POT
	SOIL_FLAG_MIPMAPS: generate mipmaps for the texture
	SOIL_FLAG_TEXTURE_REPEATS: otherwise will clamp
	SOIL_FLAG_MULTIPLY_ALPHA: for using (GL_ONE,GL_ONE_MINUS_SRC_ALPHA) blending
	SOIL_FLAG_INVERT_Y: flip the image vertically
	SOIL_FLAG_COMPRESS_TO_DXT: if the card can display them, will convert RGB to DXT1, RGBA to DXT5
	SOIL_FLAG_DDS_LOAD_DIRECT: will load DDS files directly without _ANY_ additional processing
	SOIL_FLAG_NTSC_SAFE_RGB: clamps RGB components to the range [16,235]
	SOIL_FLAG_CoCg_Y: Google YCoCg; RGB=>CoYCg, RGBA=>CoCgAY
	SOIL_FLAG_TEXTURE_RECTANGE: uses ARB_texture_rectangle ; pixel indexed & no repeat or MIPmaps or cubemaps
**/
enum {
	SOIL_FLAG_POWER_OF_TWO = 1,
	SOIL_FLAG_MIPMAPS = 2,
	SOIL_FLAG_TEXTURE_REPEATS = 4,
	SOIL_FLAG_MULTIPLY_ALPHA = 8,
	SOIL_FLAG_INVERT_Y = 16,
	SOIL_FLAG_COMPRESS_TO_DXT = 32,
	SOIL_FLAG_DDS_LOAD_DIRECT = 64,
	SOIL_FLAG_NTSC_SAFE_RGB = 128,
	SOIL_FLAG_CoCg_Y = 256,
	SOIL_FLAG_TEXTURE_RECTANGLE = 512
};

/**
	The types of images that may be saved.
	(TGA supports uncompressed RGB / RGBA)
	(BMP supports uncompressed RGB)
	(DDS supports DXT1 and DXT5)
**/
enum { SOIL_SAVE_TYPE_TGA = 0, SOIL_SAVE_TYPE_BMP = 1, SOIL_SAVE_TYPE_DDS = 2 };

/**
	Defines the order of faces in a DDS cubemap.
	I recommend that you use the same order in single
	image cubemap files, so they will be interchangeable
	with DDS cubemaps when using SOIL.
**/
#define SOIL_DDS_CUBEMAP_FACE_ORDER "EWUDNS"

/**
	The types of internal fake HDR representations

	SOIL_HDR_RGBE:		RGB * pow( 2.0, A - 128.0 )
	SOIL_HDR_RGBdivA:	RGB / A
	SOIL_HDR_RGBdivA2:	RGB / (A*A)
**/
enum { SOIL_HDR_RGBE = 0, SOIL_HDR_RGBdivA = 1, SOIL_HDR_RGBdivA2 = 2 };


int
query_tex_rectangle_capability( void ) {
	/*	check for the capability	*/
	if( has_tex_rectangle_capability == SOIL_CAPABILITY_UNKNOWN ) {
		/*	we haven't yet checked for the capability, do so	*/
		if( (NULL == strstr( (char const*)glGetString( GL_EXTENSIONS ),
				"GL_ARB_texture_rectangle" ) )
			&& (NULL == strstr( (char const*)glGetString( GL_EXTENSIONS ),
				"GL_EXT_texture_rectangle" ) )
			&& (NULL == strstr( (char const*)glGetString( GL_EXTENSIONS ),
				"GL_NV_texture_rectangle" ) )) {
			/*	not there, flag the failure	*/
			has_tex_rectangle_capability = SOIL_CAPABILITY_NONE;
		} else {
			/*	it's there!	*/
			has_tex_rectangle_capability = SOIL_CAPABILITY_PRESENT;
		}
	}
	/*	let the user know if we can do texture rectangles or not	*/
	return has_tex_rectangle_capability;
}


int
scale_image_RGB_to_NTSC_safe(unsigned char* orig, int width, int height, int channels) {
	const float scale_lo = 16.0f - 0.499f;
	const float scale_hi = 235.0f + 0.499f;
	int i, j;
	int nc = channels;
	unsigned char scale_LUT[256];
	/*	error check	*/
	if( (width < 1) || (height < 1) || (channels < 1) || (orig == NULL) ) {
		/*	nothing to do	*/
		return 0;
	}
	/*	set up the scaling Look Up Table	*/
	for( i = 0; i < 256; ++i ) {
		scale_LUT[i] = (unsigned char)((scale_hi - scale_lo) * i / 255.0f + scale_lo);
	}
	/*	for channels = 2 or 4, ignore the alpha component	*/
	nc -= 1 - (channels & 1);
	/*	OK, go through the image and scale any non-alpha components	*/
	for( i = 0; i < width*height*channels; i += channels ) {
		for( j = 0; j < nc; ++j ) {
			orig[i+j] = scale_LUT[orig[i+j]];
		}
	}
	return 1;
}

int query_NPOT_capability( void ) {
	/*	check for the capability	*/
	if( has_NPOT_capability == SOIL_CAPABILITY_UNKNOWN ) {
		/*	we haven't yet checked for the capability, do so	*/
		if( (NULL == strstr( (char const*)glGetString( GL_EXTENSIONS ),
				"GL_ARB_texture_non_power_of_two" ) )) {
			/*	not there, flag the failure	*/
			has_NPOT_capability = SOIL_CAPABILITY_NONE;
		} else {
			/*	it's there!	*/
			has_NPOT_capability = SOIL_CAPABILITY_PRESENT;
		}
	}
	/*	let the user know if we can do non-power-of-two textures or not	*/
	return has_NPOT_capability;
}

int
up_scale_image(const unsigned char* const orig,
		int width, int height, int channels,
		unsigned char* resampled,
		int resampled_width, int resampled_height) {
	float dx, dy;
	int x, y, c;

    /* error(s) check	*/
    if ( 	(width < 1) || (height < 1) ||
            (resampled_width < 2) || (resampled_height < 2) ||
            (channels < 1) ||
            (NULL == orig) || (NULL == resampled) ) {
        /*	signify badness	*/
        return 0;
    }
    /*
		for each given pixel in the new map, find the exact location
		from the original map which would contribute to this guy
	*/
    dx = (width - 1.0f) / (resampled_width - 1.0f);
    dy = (height - 1.0f) / (resampled_height - 1.0f);
    for ( y = 0; y < resampled_height; ++y ) {
    	/* find the base y index and fractional offset from that	*/
    	float sampley = y * dy;
    	int inty = (int)sampley;
	if( inty > height - 2 ) { inty = height - 2; }
	sampley -= inty;
        for ( x = 0; x < resampled_width; ++x ) {
			float samplex = x * dx;
			int intx = (int)samplex;
			int base_index;
			/* find the base x index and fractional offset from that	*/
			/*	if( intx < 0 ) { intx = 0; } else	*/
			if( intx > width - 2 ) { intx = width - 2; }
			samplex -= intx;
			/*	base index into the original image	*/
			base_index = (inty * width + intx) * channels;
            for ( c = 0; c < channels; ++c ) {
            	/*	do the sampling	*/
		float value = 0.5f;
		value += orig[base_index]
					*(1.0f-samplex)*(1.0f-sampley);
		value += orig[base_index+channels]
					*(samplex)*(1.0f-sampley);
		value += orig[base_index+width*channels]
					*(1.0f-samplex)*(sampley);
		value += orig[base_index+width*channels+channels]
					*(samplex)*(sampley);
		/*	move to the next channel	*/
		++base_index;
            	/*	save the new value	*/
            	resampled[y*resampled_width*channels+x*channels+c] =
						(unsigned char)(value);
            }
        }
    }
    /*	done	*/
    return 1;
}

int
mipmap_image( const unsigned char* const orig,
		int width, int height, int channels,
		unsigned char* resampled,
		int block_size_x, int block_size_y) {
	int mip_width, mip_height;
	int i, j, c;

	/*	error check	*/
	if( (width < 1) || (height < 1) ||
		(channels < 1) || (orig == NULL) ||
		(resampled == NULL) ||
		(block_size_x < 1) || (block_size_y < 1) ) {
		/*	nothing to do	*/
		return 0;
	}
	mip_width = width / block_size_x;
	mip_height = height / block_size_y;
	if( mip_width < 1 ) {
		mip_width = 1;
	}
	if( mip_height < 1 ) {
		mip_height = 1;
	}
	for( j = 0; j < mip_height; ++j ) {
		for( i = 0; i < mip_width; ++i ) {
			for( c = 0; c < channels; ++c ) {
				const int index = (j*block_size_y)*width*channels + (i*block_size_x)*channels + c;
				int sum_value;
				int u,v;
				int u_block = block_size_x;
				int v_block = block_size_y;
				int block_area;
				/*	do a bit of checking so we don't over-run the boundaries
					(necessary for non-square textures!)	*/
				if( block_size_x * (i+1) > width ) {
					u_block = width - i*block_size_y;
				}
				if( block_size_y * (j+1) > height ) {
					v_block = height - j*block_size_y;
				}
				block_area = u_block*v_block;
				/*	for this pixel, see what the average
					of all the values in the block are.
					note: start the sum at the rounding value, not at 0	*/
				sum_value = block_area >> 1;
				for( v = 0; v < v_block; ++v )
				for( u = 0; u < u_block; ++u ) {
					sum_value += orig[index + v*width*channels + u*channels];
				}
				resampled[j*mip_width*channels + i*channels + c] = sum_value / block_area;
			}
		}
	}
	return 1;
}


unsigned char clamp_byte( int x ) {
	return ( (x) < 0 ? (0)
			 : ( (x) > 255 ? 255
				       : (x) ) );
}


int
convert_RGB_to_YCoCg ( unsigned char* orig, int width, int height, int channels) {
	int i;
	/*	error check	*/
	if( (width < 1) || (height < 1) ||
		(channels < 3) || (channels > 4) || (orig == NULL) ) {
		/*	nothing to do	*/
		return -1;
	}
	/*	do the conversion	*/
	if( channels == 3 ) {
		for( i = 0; i < width*height*3; i += 3 ) {
			int r = orig[i+0];
			int g = (orig[i+1] + 1) >> 1;
			int b = orig[i+2];
			int tmp = (2 + r + b) >> 2;
			/*	Co	*/
			orig[i+0] = clamp_byte( 128 + ((r - b + 1) >> 1) );
			/*	Y	*/
			orig[i+1] = clamp_byte( g + tmp );
			/*	Cg	*/
			orig[i+2] = clamp_byte( 128 + g - tmp );
		}
	} else {
		for( i = 0; i < width*height*4; i += 4 ) {
			int r = orig[i+0];
			int g = (orig[i+1] + 1) >> 1;
			int b = orig[i+2];
			unsigned char a = orig[i+3];
			int tmp = (2 + r + b) >> 2;
			/*	Co	*/
			orig[i+0] = clamp_byte( 128 + ((r - b + 1) >> 1) );
			/*	Cg	*/
			orig[i+1] = clamp_byte( 128 + g - tmp );
			/*	Alpha	*/
			orig[i+2] = a;
			/*	Y	*/
			orig[i+3] = clamp_byte( g + tmp );
		}
	}
	/*	done	*/
	return 0;
}


#if SOIL_CHECK_FOR_GL_ERRORS
void
check_for_GL_errors( const char *calling_location ) {
	/*	check for errors	*/
	GLenum err_code = glGetError();
	while( GL_NO_ERROR != err_code ) {
		printf( "OpenGL Error @ %s: %i", calling_location, err_code );
		err_code = glGetError();
	}
}
#else
void
check_for_GL_errors( const char *calling_location ) {
	/*	no check for errors	*/
}
#endif


void
SOIL_free_image_data ( unsigned char *img_data) {
	free( (void*)img_data );
}



int convert_bit_range( int c, int from_bits, int to_bits )
{
	int b = (1 << (from_bits - 1)) + c * ((1 << to_bits) - 1);
	return (b + (b >> from_bits)) >> from_bits;
}

int rgb_to_565( int r, int g, int b )
{
	return
		(convert_bit_range( r, 8, 5 ) << 11) |
		(convert_bit_range( g, 8, 6 ) << 05) |
		(convert_bit_range( b, 8, 5 ) << 00);
}

void rgb_888_from_565( unsigned int c, int *r, int *g, int *b )
{
	*r = convert_bit_range( (c >> 11) & 31, 5, 8 );
	*g = convert_bit_range( (c >> 05) & 63, 6, 8 );
	*b = convert_bit_range( (c >> 00) & 31, 5, 8 );
}

void compute_color_line_STDEV(
		const unsigned char *const uncompressed,
		int channels,
		float point[3], float direction[3] )
{
	const float inv_16 = 1.0f / 16.0f;
	int i;
	float sum_r = 0.0f, sum_g = 0.0f, sum_b = 0.0f;
	float sum_rr = 0.0f, sum_gg = 0.0f, sum_bb = 0.0f;
	float sum_rg = 0.0f, sum_rb = 0.0f, sum_gb = 0.0f;
	/*	calculate all data needed for the covariance matrix
		( to compare with _rygdxt code)	*/
	for( i = 0; i < 16*channels; i += channels )
	{
		sum_r += uncompressed[i+0];
		sum_rr += uncompressed[i+0] * uncompressed[i+0];
		sum_g += uncompressed[i+1];
		sum_gg += uncompressed[i+1] * uncompressed[i+1];
		sum_b += uncompressed[i+2];
		sum_bb += uncompressed[i+2] * uncompressed[i+2];
		sum_rg += uncompressed[i+0] * uncompressed[i+1];
		sum_rb += uncompressed[i+0] * uncompressed[i+2];
		sum_gb += uncompressed[i+1] * uncompressed[i+2];
	}
	/*	convert the sums to averages	*/
	sum_r *= inv_16;
	sum_g *= inv_16;
	sum_b *= inv_16;
	/*	and convert the squares to the squares of the value - avg_value	*/
	sum_rr -= 16.0f * sum_r * sum_r;
	sum_gg -= 16.0f * sum_g * sum_g;
	sum_bb -= 16.0f * sum_b * sum_b;
	sum_rg -= 16.0f * sum_r * sum_g;
	sum_rb -= 16.0f * sum_r * sum_b;
	sum_gb -= 16.0f * sum_g * sum_b;
	/*	the point on the color line is the average	*/
	point[0] = sum_r;
	point[1] = sum_g;
	point[2] = sum_b;
	#if USE_COV_MAT
	/*
		The following idea was from ryg.
		(https://mollyrocket.com/forums/viewtopic.php?t=392)
		The method worked great (less RMSE than mine) most of
		the time, but had some issues handling some simple
		boundary cases, like full green next to full red,
		which would generate a covariance matrix like this:

		| 1  -1  0 |
		| -1  1  0 |
		| 0   0  0 |

		For a given starting vector, the power method can
		generate all zeros!  So no starting with {1,1,1}
		as I was doing!  This kind of error is still a
		slight posibillity, but will be very rare.
	*/
	/*	use the covariance matrix directly
		(1st iteration, don't use all 1.0 values!)	*/
	sum_r = 1.0f;
	sum_g = 2.718281828f;
	sum_b = 3.141592654f;
	direction[0] = sum_r*sum_rr + sum_g*sum_rg + sum_b*sum_rb;
	direction[1] = sum_r*sum_rg + sum_g*sum_gg + sum_b*sum_gb;
	direction[2] = sum_r*sum_rb + sum_g*sum_gb + sum_b*sum_bb;
	/*	2nd iteration, use results from the 1st guy	*/
	sum_r = direction[0];
	sum_g = direction[1];
	sum_b = direction[2];
	direction[0] = sum_r*sum_rr + sum_g*sum_rg + sum_b*sum_rb;
	direction[1] = sum_r*sum_rg + sum_g*sum_gg + sum_b*sum_gb;
	direction[2] = sum_r*sum_rb + sum_g*sum_gb + sum_b*sum_bb;
	/*	3rd iteration, use results from the 2nd guy	*/
	sum_r = direction[0];
	sum_g = direction[1];
	sum_b = direction[2];
	direction[0] = sum_r*sum_rr + sum_g*sum_rg + sum_b*sum_rb;
	direction[1] = sum_r*sum_rg + sum_g*sum_gg + sum_b*sum_gb;
	direction[2] = sum_r*sum_rb + sum_g*sum_gb + sum_b*sum_bb;
	#else
	/*	use my standard deviation method
		(very robust, a tiny bit slower and less accurate)	*/
	direction[0] = sqrt( sum_rr );
	direction[1] = sqrt( sum_gg );
	direction[2] = sqrt( sum_bb );
	/*	which has a greater component	*/
	if( sum_gg > sum_rr )
	{
		/*	green has greater component, so base the other signs off of green	*/
		if( sum_rg < 0.0f )
		{
			direction[0] = -direction[0];
		}
		if( sum_gb < 0.0f )
		{
			direction[2] = -direction[2];
		}
	} else
	{
		/*	red has a greater component	*/
		if( sum_rg < 0.0f )
		{
			direction[1] = -direction[1];
		}
		if( sum_rb < 0.0f )
		{
			direction[2] = -direction[2];
		}
	}
	#endif
}



void LSE_master_colors_max_min(
		int *cmax, int *cmin,
		int channels,
		const unsigned char *const uncompressed )
{
	int i, j;
	/*	the master colors	*/
	int c0[3], c1[3];
	/*	used for fitting the line	*/
	float sum_x[] = { 0.0f, 0.0f, 0.0f };
	float sum_x2[] = { 0.0f, 0.0f, 0.0f };
	float dot_max = 1.0f, dot_min = -1.0f;
	float vec_len2 = 0.0f;
	float dot;
	/*	error check	*/
	if( (channels < 3) || (channels > 4) )
	{
		return;
	}
	compute_color_line_STDEV( uncompressed, channels, sum_x, sum_x2 );
	vec_len2 = 1.0f / ( 0.00001f +
			sum_x2[0]*sum_x2[0] + sum_x2[1]*sum_x2[1] + sum_x2[2]*sum_x2[2] );
	/*	finding the max and min vector values	*/
	dot_max =
			(
				sum_x2[0] * uncompressed[0] +
				sum_x2[1] * uncompressed[1] +
				sum_x2[2] * uncompressed[2]
			);
	dot_min = dot_max;
	for( i = 1; i < 16; ++i )
	{
		dot =
			(
				sum_x2[0] * uncompressed[i*channels+0] +
				sum_x2[1] * uncompressed[i*channels+1] +
				sum_x2[2] * uncompressed[i*channels+2]
			);
		if( dot < dot_min )
		{
			dot_min = dot;
		} else if( dot > dot_max )
		{
			dot_max = dot;
		}
	}
	/*	and the offset (from the average location)	*/
	dot = sum_x2[0]*sum_x[0] + sum_x2[1]*sum_x[1] + sum_x2[2]*sum_x[2];
	dot_min -= dot;
	dot_max -= dot;
	/*	post multiply by the scaling factor	*/
	dot_min *= vec_len2;
	dot_max *= vec_len2;
	/*	OK, build the master colors	*/
	for( i = 0; i < 3; ++i )
	{
		/*	color 0	*/
		c0[i] = (int)(0.5f + sum_x[i] + dot_max * sum_x2[i]);
		if( c0[i] < 0 )
		{
			c0[i] = 0;
		} else if( c0[i] > 255 )
		{
			c0[i] = 255;
		}
		/*	color 1	*/
		c1[i] = (int)(0.5f + sum_x[i] + dot_min * sum_x2[i]);
		if( c1[i] < 0 )
		{
			c1[i] = 0;
		} else if( c1[i] > 255 )
		{
			c1[i] = 255;
		}
	}
	/*	down_sample (with rounding?)	*/
	i = rgb_to_565( c0[0], c0[1], c0[2] );
	j = rgb_to_565( c1[0], c1[1], c1[2] );
	if( i > j )
	{
		*cmax = i;
		*cmin = j;
	} else
	{
		*cmax = j;
		*cmin = i;
	}
}




void
	compress_DDS_color_block
	(
		int channels,
		const unsigned char *const uncompressed,
		unsigned char compressed[8]
	)
{
	/*	variables	*/
	int i;
	int next_bit;
	int enc_c0, enc_c1;
	int c0[4], c1[4];
	float color_line[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float vec_len2 = 0.0f, dot_offset = 0.0f;
	/*	stupid order	*/
	int swizzle4[] = { 0, 2, 3, 1 };
	/*	get the master colors	*/
	LSE_master_colors_max_min( &enc_c0, &enc_c1, channels, uncompressed );
	/*	store the 565 color 0 and color 1	*/
	compressed[0] = (enc_c0 >> 0) & 255;
	compressed[1] = (enc_c0 >> 8) & 255;
	compressed[2] = (enc_c1 >> 0) & 255;
	compressed[3] = (enc_c1 >> 8) & 255;
	/*	zero out the compressed data	*/
	compressed[4] = 0;
	compressed[5] = 0;
	compressed[6] = 0;
	compressed[7] = 0;
	/*	reconstitute the master color vectors	*/
	rgb_888_from_565( enc_c0, &c0[0], &c0[1], &c0[2] );
	rgb_888_from_565( enc_c1, &c1[0], &c1[1], &c1[2] );
	/*	the new vector	*/
	vec_len2 = 0.0f;
	for( i = 0; i < 3; ++i )
	{
		color_line[i] = (float)(c1[i] - c0[i]);
		vec_len2 += color_line[i] * color_line[i];
	}
	if( vec_len2 > 0.0f )
	{
		vec_len2 = 1.0f / vec_len2;
	}
	/*	pre-proform the scaling	*/
	color_line[0] *= vec_len2;
	color_line[1] *= vec_len2;
	color_line[2] *= vec_len2;
	/*	compute the offset (constant) portion of the dot product	*/
	dot_offset = color_line[0]*c0[0] + color_line[1]*c0[1] + color_line[2]*c0[2];
	/*	store the rest of the bits	*/
	next_bit = 8*4;
	for( i = 0; i < 16; ++i )
	{
		/*	find the dot product of this color, to place it on the line
			(should be [-1,1])	*/
		int next_value = 0;
		float dot_product =
			color_line[0] * uncompressed[i*channels+0] +
			color_line[1] * uncompressed[i*channels+1] +
			color_line[2] * uncompressed[i*channels+2] -
			dot_offset;
		/*	map to [0,3]	*/
		next_value = (int)( dot_product * 3.0f + 0.5f );
		if( next_value > 3 )
		{
			next_value = 3;
		} else if( next_value < 0 )
		{
			next_value = 0;
		}
		/*	OK, store this value	*/
		compressed[next_bit >> 3] |= swizzle4[ next_value ] << (next_bit & 7);
		next_bit += 2;
	}
	/*	done compressing to DXT1	*/
}

void
	compress_DDS_alpha_block
	(
		const unsigned char *const uncompressed,
		unsigned char compressed[8]
	)
{
	/*	variables	*/
	int i;
	int next_bit;
	int a0, a1;
	float scale_me;
	/*	stupid order	*/
	int swizzle8[] = { 1, 7, 6, 5, 4, 3, 2, 0 };
	/*	get the alpha limits (a0 > a1)	*/
	a0 = a1 = uncompressed[3];
	for( i = 4+3; i < 16*4; i += 4 )
	{
		if( uncompressed[i] > a0 )
		{
			a0 = uncompressed[i];
		} else if( uncompressed[i] < a1 )
		{
			a1 = uncompressed[i];
		}
	}
	/*	store those limits, and zero the rest of the compressed dataset	*/
	compressed[0] = a0;
	compressed[1] = a1;
	/*	zero out the compressed data	*/
	compressed[2] = 0;
	compressed[3] = 0;
	compressed[4] = 0;
	compressed[5] = 0;
	compressed[6] = 0;
	compressed[7] = 0;
	/*	store the all of the alpha values	*/
	next_bit = 8*2;
	scale_me = 7.9999f / (a0 - a1);
	for( i = 3; i < 16*4; i += 4 )
	{
		/*	convert this alpha value to a 3 bit number	*/
		int svalue;
		int value = (int)((uncompressed[i] - a1) * scale_me);
		svalue = swizzle8[ value&7 ];
		/*	OK, store this value, start with the 1st byte	*/
		compressed[next_bit >> 3] |= svalue << (next_bit & 7);
		if( (next_bit & 7) > 5 )
		{
			/*	spans 2 bytes, fill in the start of the 2nd byte	*/
			compressed[1 + (next_bit >> 3)] |= svalue >> (8 - (next_bit & 7) );
		}
		next_bit += 3;
	}
	/*	done compressing to DXT1	*/
}











typedef void (APIENTRY * P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data);
P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC soilGlCompressedTexImage2D = NULL;







int
query_DXT_capability( void ) {
	/*	check for the capability	*/
	if( has_DXT_capability == SOIL_CAPABILITY_UNKNOWN ) {
		/*	we haven't yet checked for the capability, do so	*/
		if( NULL == strstr(
				(char const*)glGetString( GL_EXTENSIONS ),
				"GL_EXT_texture_compression_s3tc" ) ) {
			/*	not there, flag the failure	*/
			has_DXT_capability = SOIL_CAPABILITY_NONE;
		} else {
			/*	and find the address of the extension function	*/
			P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC ext_addr = NULL;
			#ifdef WIN32
				ext_addr = (P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC)
						wglGetProcAddress
						(
							"glCompressedTexImage2DARB"
						);
			#elif defined(__APPLE__) || defined(__APPLE_CC__)
				/*	I can't test this Apple stuff!	*/
				CFBundleRef bundle;
				CFURLRef bundleURL =
					CFURLCreateWithFileSystemPath(
						kCFAllocatorDefault,
						CFSTR("/System/Library/Frameworks/OpenGL.framework"),
						kCFURLPOSIXPathStyle,
						true );
				CFStringRef extensionName =
					CFStringCreateWithCString(
						kCFAllocatorDefault,
						"glCompressedTexImage2DARB",
						kCFStringEncodingASCII );
				bundle = CFBundleCreate( kCFAllocatorDefault, bundleURL );
				assert( bundle != NULL );
				ext_addr = (P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC)
						CFBundleGetFunctionPointerForName
						(
							bundle, extensionName
						);
				CFRelease( bundleURL );
				CFRelease( extensionName );
				CFRelease( bundle );
			#else
				ext_addr = (P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC)
						glXGetProcAddressARB
						(
							(const GLubyte *)"glCompressedTexImage2DARB"
						);
			#endif
			/*	Flag it so no checks needed later	*/
			if( NULL == ext_addr ) {
				/*	hmm, not good!!  This should not happen, but does on my
					laptop's VIA chipset.  The GL_EXT_texture_compression_s3tc
					spec requires that ARB_texture_compression be present too.
					this means I can upload and have the OpenGL drive do the
					conversion, but I can't use my own routines or load DDS files
					from disk and upload them directly [8^(	*/
				has_DXT_capability = SOIL_CAPABILITY_NONE;
			} else {
				/*	all's well!	*/
				soilGlCompressedTexImage2D = ext_addr;
				has_DXT_capability = SOIL_CAPABILITY_PRESENT;
			}
		}
	}
	/*	let the user know if we can do DXT or not	*/
	return has_DXT_capability;
}




unsigned char* convert_image_to_DXT1(
		const unsigned char *const uncompressed,
		int width, int height, int channels,
		int *out_size )
{
	unsigned char *compressed;
	int i, j, x, y;
	unsigned char ublock[16*3];
	unsigned char cblock[8];
	int index = 0, chan_step = 1;
	int block_count = 0;
	/*	error check	*/
	*out_size = 0;
	if( (width < 1) || (height < 1) ||
		(NULL == uncompressed) ||
		(channels < 1) || (channels > 4) )
	{
		return NULL;
	}
	/*	for channels == 1 or 2, I do not step forward for R,G,B values	*/
	if( channels < 3 )
	{
		chan_step = 0;
	}
	/*	get the RAM for the compressed image
		(8 bytes per 4x4 pixel block)	*/
	*out_size = ((width+3) >> 2) * ((height+3) >> 2) * 8;
	compressed = (unsigned char*)malloc( *out_size );
	/*	go through each block	*/
	for( j = 0; j < height; j += 4 )
	{
		for( i = 0; i < width; i += 4 )
		{
			/*	copy this block into a new one	*/
			int idx = 0;
			int mx = 4, my = 4;
			if( j+4 >= height )
			{
				my = height - j;
			}
			if( i+4 >= width )
			{
				mx = width - i;
			}
			for( y = 0; y < my; ++y )
			{
				for( x = 0; x < mx; ++x )
				{
					ublock[idx++] = uncompressed[(j+y)*width*channels+(i+x)*channels];
					ublock[idx++] = uncompressed[(j+y)*width*channels+(i+x)*channels+chan_step];
					ublock[idx++] = uncompressed[(j+y)*width*channels+(i+x)*channels+chan_step+chan_step];
				}
				for( x = mx; x < 4; ++x )
				{
					ublock[idx++] = ublock[0];
					ublock[idx++] = ublock[1];
					ublock[idx++] = ublock[2];
				}
			}
			for( y = my; y < 4; ++y )
			{
				for( x = 0; x < 4; ++x )
				{
					ublock[idx++] = ublock[0];
					ublock[idx++] = ublock[1];
					ublock[idx++] = ublock[2];
				}
			}
			/*	compress the block	*/
			++block_count;
			compress_DDS_color_block( 3, ublock, cblock );
			/*	copy the data from the block into the main block	*/
			for( x = 0; x < 8; ++x )
			{
				compressed[index++] = cblock[x];
			}
		}
	}
	return compressed;
}


unsigned char* convert_image_to_DXT5(
		const unsigned char *const uncompressed,
		int width, int height, int channels,
		int *out_size )
{
	unsigned char *compressed;
	int i, j, x, y;
	unsigned char ublock[16*4];
	unsigned char cblock[8];
	int index = 0, chan_step = 1;
	int block_count = 0, has_alpha;
	/*	error check	*/
	*out_size = 0;
	if( (width < 1) || (height < 1) ||
		(NULL == uncompressed) ||
		(channels < 1) || ( channels > 4) )
	{
		return NULL;
	}
	/*	for channels == 1 or 2, I do not step forward for R,G,B vales	*/
	if( channels < 3 )
	{
		chan_step = 0;
	}
	/*	# channels = 1 or 3 have no alpha, 2 & 4 do have alpha	*/
	has_alpha = 1 - (channels & 1);
	/*	get the RAM for the compressed image
		(16 bytes per 4x4 pixel block)	*/
	*out_size = ((width+3) >> 2) * ((height+3) >> 2) * 16;
	compressed = (unsigned char*)malloc( *out_size );
	/*	go through each block	*/
	for( j = 0; j < height; j += 4 )
	{
		for( i = 0; i < width; i += 4 )
		{
			/*	local variables, and my block counter	*/
			int idx = 0;
			int mx = 4, my = 4;
			if( j+4 >= height )
			{
				my = height - j;
			}
			if( i+4 >= width )
			{
				mx = width - i;
			}
			for( y = 0; y < my; ++y )
			{
				for( x = 0; x < mx; ++x )
				{
					ublock[idx++] = uncompressed[(j+y)*width*channels+(i+x)*channels];
					ublock[idx++] = uncompressed[(j+y)*width*channels+(i+x)*channels+chan_step];
					ublock[idx++] = uncompressed[(j+y)*width*channels+(i+x)*channels+chan_step+chan_step];
					ublock[idx++] =
						has_alpha * uncompressed[(j+y)*width*channels+(i+x)*channels+channels-1]
						+ (1-has_alpha)*255;
				}
				for( x = mx; x < 4; ++x )
				{
					ublock[idx++] = ublock[0];
					ublock[idx++] = ublock[1];
					ublock[idx++] = ublock[2];
					ublock[idx++] = ublock[3];
				}
			}
			for( y = my; y < 4; ++y )
			{
				for( x = 0; x < 4; ++x )
				{
					ublock[idx++] = ublock[0];
					ublock[idx++] = ublock[1];
					ublock[idx++] = ublock[2];
					ublock[idx++] = ublock[3];
				}
			}
			/*	now compress the alpha block	*/
			compress_DDS_alpha_block( ublock, cblock );
			/*	copy the data from the compressed alpha block into the main buffer	*/
			for( x = 0; x < 8; ++x )
			{
				compressed[index++] = cblock[x];
			}
			/*	then compress the color block	*/
			++block_count;
			compress_DDS_color_block( 4, ublock, cblock );
			/*	copy the data from the compressed color block into the main buffer	*/
			for( x = 0; x < 8; ++x )
			{
				compressed[index++] = cblock[x];
			}
		}
	}
	return compressed;
}












unsigned int
SOIL_internal_create_OGL_texture(const unsigned char *const data,
				 int width, int height, int channels,
				 unsigned int reuse_texture_ID,
				 unsigned int flags,
				 unsigned int opengl_texture_type,
				 unsigned int opengl_texture_target,
				 unsigned int texture_check_size_enum) {
	/*	variables	*/
	unsigned char* img;
	unsigned int tex_id;
	unsigned int internal_texture_format = 0, original_texture_format = 0;
	int DXT_mode = SOIL_CAPABILITY_UNKNOWN;
	int max_supported_size;

	/*	If the user wants to use the texture rectangle I kill a few flags	*/
	if( flags & SOIL_FLAG_TEXTURE_RECTANGLE ) {
		/*	well, the user asked for it, can we do that?	*/
		if( query_tex_rectangle_capability() == SOIL_CAPABILITY_PRESENT ) {
			/*	only allow this if the user in _NOT_ trying to do a cubemap!	*/
			if( opengl_texture_type == GL_TEXTURE_2D ) {
				/*	clean out the flags that cannot be used with texture rectangles	*/
				flags &= ~(
						SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS |
						SOIL_FLAG_TEXTURE_REPEATS
					);
				/*	and change my target	*/
				opengl_texture_target = SOIL_TEXTURE_RECTANGLE_ARB;
				opengl_texture_type = SOIL_TEXTURE_RECTANGLE_ARB;
			} else {
				/*	not allowed for any other uses (yes, I'm looking at you, cubemaps!)	*/
				flags &= ~SOIL_FLAG_TEXTURE_RECTANGLE;
			}

		} else {
			/*	can't do it, and that is a breakable offense (uv coords use pixels instead of [0,1]!)	*/
			result_string_pointer = "Texture Rectangle extension unsupported";
			return 0;
		}
	}
	/*	create a copy the image data	*/
	img = (unsigned char*)malloc( width*height*channels );
	memcpy( img, data, width*height*channels );
	/*	does the user want me to invert the image?	*/
	if( flags & SOIL_FLAG_INVERT_Y ) {
		int i, j;
		for( j = 0; j*2 < height; ++j ) {
			int index1 = j * width * channels;
			int index2 = (height - 1 - j) * width * channels;
			for( i = width * channels; i > 0; --i ) {
				unsigned char temp = img[index1];
				img[index1] = img[index2];
				img[index2] = temp;
				++index1;
				++index2;
			}
		}
	}
	/*	does the user want me to scale the colors into the NTSC safe RGB range?	*/
	if( flags & SOIL_FLAG_NTSC_SAFE_RGB ) {
		scale_image_RGB_to_NTSC_safe( img, width, height, channels );
	}
	/*	does the user want me to convert from straight to pre-multiplied alpha?
		(and do we even _have_ alpha?)	*/
	if( flags & SOIL_FLAG_MULTIPLY_ALPHA ) {
		int i;
		switch( channels ) {
		case 2:
			for( i = 0; i < 2*width*height; i += 2 ) {
				img[i] = (img[i] * img[i+1] + 128) >> 8;
			}
			break;
		case 4:
			for( i = 0; i < 4*width*height; i += 4 ) {
				img[i+0] = (img[i+0] * img[i+3] + 128) >> 8;
				img[i+1] = (img[i+1] * img[i+3] + 128) >> 8;
				img[i+2] = (img[i+2] * img[i+3] + 128) >> 8;
			}
			break;
		default:
			/*	no other number of channels contains alpha data	*/
			break;
		}
	}
	/*	if the user can't support NPOT textures, make sure we force the POT option	*/
	if((query_NPOT_capability() == SOIL_CAPABILITY_NONE) &&
	   !(flags & SOIL_FLAG_TEXTURE_RECTANGLE)) {
		/*	add in the POT flag */
		flags |= SOIL_FLAG_POWER_OF_TWO;
	}
	/*	how large of a texture can this OpenGL implementation handle?	*/
	/*	texture_check_size_enum will be GL_MAX_TEXTURE_SIZE or SOIL_MAX_CUBE_MAP_TEXTURE_SIZE	*/
	glGetIntegerv( texture_check_size_enum, &max_supported_size );
	/*	do I need to make it a power of 2? */
	if((flags & SOIL_FLAG_POWER_OF_TWO) ||	/* user asked for it */
	   (flags & SOIL_FLAG_MIPMAPS) ||	/* need it for the MIP-maps */
	   (width > max_supported_size) ||	/* it's too big, (make sure it's */
	   (height > max_supported_size) ) {	/* 2^n for later down-sampling) */
		int new_width = 1;
		int new_height = 1;
		while( new_width < width ) {
			new_width *= 2;
		}
		while( new_height < height ) {
			new_height *= 2;
		}
		/*	still?	*/
		if( (new_width != width) || (new_height != height) ) {
			/*	yep, resize	*/
			unsigned char *resampled = (unsigned char*)malloc( channels*new_width*new_height );
			up_scale_image(
					img, width, height, channels,
					resampled, new_width, new_height );
			/*	OJO	this is for debug only!	*/
			/*
			SOIL_save_image( "\\showme.bmp", SOIL_SAVE_TYPE_BMP,
							new_width, new_height, channels,
							resampled );
			*/
			/*	nuke the old guy, then point it at the new guy	*/
			SOIL_free_image_data( img );
			img = resampled;
			width = new_width;
			height = new_height;
		}
	}
	/*	now, if it is too large...	*/
	if( (width > max_supported_size) || (height > max_supported_size) ) {
		/*	I've already made it a power of two, so simply use the MIPmapping
			code to reduce its size to the allowable maximum.	*/
		unsigned char *resampled;
		int reduce_block_x = 1, reduce_block_y = 1;
		int new_width, new_height;
		if( width > max_supported_size ) {
			reduce_block_x = width / max_supported_size;
		}
		if( height > max_supported_size ) {
			reduce_block_y = height / max_supported_size;
		}
		new_width = width / reduce_block_x;
		new_height = height / reduce_block_y;
		resampled = (unsigned char*)malloc( channels*new_width*new_height );
		/*	perform the actual reduction	*/
		mipmap_image(	img, width, height, channels,
						resampled, reduce_block_x, reduce_block_y );
		/*	nuke the old guy, then point it at the new guy	*/
		SOIL_free_image_data( img );
		img = resampled;
		width = new_width;
		height = new_height;
	}
	/*	does the user want us to use YCoCg color space?	*/
	if( flags & SOIL_FLAG_CoCg_Y ) {
		/*	this will only work with RGB and RGBA images */
		convert_RGB_to_YCoCg( img, width, height, channels );
		/*
		save_image_as_DDS( "CoCg_Y.dds", width, height, channels, img );
		*/
	}
	/*	create the OpenGL texture ID handle
    	(note: allowing a forced texture ID lets me reload a texture)	*/
    tex_id = reuse_texture_ID;
    if( tex_id == 0 ) {
		glGenTextures( 1, &tex_id );
    }
	check_for_GL_errors( "glGenTextures" );
	/* Note: sometimes glGenTextures fails (usually no OpenGL context)	*/
	if( tex_id ) {
		/*	and what type am I using as the internal texture format?	*/
		switch( channels ) {
		case 1:
			original_texture_format = GL_LUMINANCE;
			break;
		case 2:
			original_texture_format = GL_LUMINANCE_ALPHA;
			break;
		case 3:
			original_texture_format = GL_RGB;
			break;
		case 4:
			original_texture_format = GL_RGBA;
			break;
		}
		internal_texture_format = original_texture_format;
		/*	does the user want me to, and can I, save as DXT?	*/
		if( flags & SOIL_FLAG_COMPRESS_TO_DXT ) {
			DXT_mode = query_DXT_capability();
			if( DXT_mode == SOIL_CAPABILITY_PRESENT ) {
				/*	I can use DXT, whether I compress it or OpenGL does	*/
				if( (channels & 1) == 1 ) {
					/*	1 or 3 channels = DXT1	*/
					internal_texture_format = SOIL_RGB_S3TC_DXT1;
				} else {
					/*	2 or 4 channels = DXT5	*/
					internal_texture_format = SOIL_RGBA_S3TC_DXT5;
				}
			}
		}
		/*  bind an OpenGL texture ID	*/
		glBindTexture( opengl_texture_type, tex_id );
		check_for_GL_errors( "glBindTexture" );
		/*  upload the main image	*/
		if( DXT_mode == SOIL_CAPABILITY_PRESENT ) {
			/*	user wants me to do the DXT conversion!	*/
			int DDS_size;
			unsigned char *DDS_data = NULL;
			if( (channels & 1) == 1 ) {
				/*	RGB, use DXT1	*/
				DDS_data = convert_image_to_DXT1( img, width, height, channels, &DDS_size );
			} else {
				/*	RGBA, use DXT5	*/
				DDS_data = convert_image_to_DXT5( img, width, height, channels, &DDS_size );
			}
			if( DDS_data ) {
				soilGlCompressedTexImage2D(
					opengl_texture_target, 0,
					internal_texture_format, width, height, 0,
					DDS_size, DDS_data );
				check_for_GL_errors( "glCompressedTexImage2D" );
				SOIL_free_image_data( DDS_data );
				/*	printf( "Internal DXT compressor\n" );	*/
			} else {
				/*	my compression failed, try the OpenGL driver's version	*/
				glTexImage2D(
					opengl_texture_target, 0,
					internal_texture_format, width, height, 0,
					original_texture_format, GL_UNSIGNED_BYTE, img );
				check_for_GL_errors( "glTexImage2D" );
				/*	printf( "OpenGL DXT compressor\n" );	*/
			}
		} else {
			/*	user want OpenGL to do all the work!	*/
			glTexImage2D(
				opengl_texture_target, 0,
				internal_texture_format, width, height, 0,
				original_texture_format, GL_UNSIGNED_BYTE, img );
			check_for_GL_errors( "glTexImage2D" );
			/*printf( "OpenGL DXT compressor\n" );	*/
		}
		/*	are any MIPmaps desired?	*/
		if( flags & SOIL_FLAG_MIPMAPS ) {
			int MIPlevel = 1;
			int MIPwidth = (width+1) / 2;
			int MIPheight = (height+1) / 2;
			unsigned char *resampled = (unsigned char*)malloc( channels*MIPwidth*MIPheight );
			while( ((1<<MIPlevel) <= width) || ((1<<MIPlevel) <= height) ) {
				/*	do this MIPmap level	*/
				mipmap_image(
						img, width, height, channels,
						resampled,
						(1 << MIPlevel), (1 << MIPlevel) );
				/*  upload the MIPmaps	*/
				if( DXT_mode == SOIL_CAPABILITY_PRESENT ) {
					/*	user wants me to do the DXT conversion!	*/
					int DDS_size;
					unsigned char *DDS_data = NULL;
					if( (channels & 1) == 1 ) {
						/*	RGB, use DXT1	*/
						DDS_data = convert_image_to_DXT1(
								resampled, MIPwidth, MIPheight, channels, &DDS_size );
					} else {
						/*	RGBA, use DXT5	*/
						DDS_data = convert_image_to_DXT5(
								resampled, MIPwidth, MIPheight, channels, &DDS_size );
					}
					if( DDS_data ) {
						soilGlCompressedTexImage2D(
							opengl_texture_target, MIPlevel,
							internal_texture_format, MIPwidth, MIPheight, 0,
							DDS_size, DDS_data );
						check_for_GL_errors( "glCompressedTexImage2D" );
						SOIL_free_image_data( DDS_data );
					} else {
						/*	my compression failed, try the OpenGL driver's version	*/
						glTexImage2D(
							opengl_texture_target, MIPlevel,
							internal_texture_format, MIPwidth, MIPheight, 0,
							original_texture_format, GL_UNSIGNED_BYTE, resampled );
						check_for_GL_errors( "glTexImage2D" );
					}
				} else {
					/*	user want OpenGL to do all the work!	*/
					glTexImage2D(
						opengl_texture_target, MIPlevel,
						internal_texture_format, MIPwidth, MIPheight, 0,
						original_texture_format, GL_UNSIGNED_BYTE, resampled );
					check_for_GL_errors( "glTexImage2D" );
				}
				/*	prep for the next level	*/
				++MIPlevel;
				MIPwidth = (MIPwidth + 1) / 2;
				MIPheight = (MIPheight + 1) / 2;
			}
			SOIL_free_image_data( resampled );
			/*	instruct OpenGL to use the MIPmaps	*/
			glTexParameteri( opengl_texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( opengl_texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			check_for_GL_errors( "GL_TEXTURE_MIN/MAG_FILTER" );
		} else {
			/*	instruct OpenGL _NOT_ to use the MIPmaps	*/
			glTexParameteri( opengl_texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( opengl_texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			check_for_GL_errors( "GL_TEXTURE_MIN/MAG_FILTER" );
		}
		/*	does the user want clamping, or wrapping?	*/
		if( flags & SOIL_FLAG_TEXTURE_REPEATS ) {
			glTexParameteri( opengl_texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( opengl_texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT );
			if( opengl_texture_type == SOIL_TEXTURE_CUBE_MAP ) {
				/*	SOIL_TEXTURE_WRAP_R is invalid if cubemaps aren't supported	*/
				glTexParameteri( opengl_texture_type, SOIL_TEXTURE_WRAP_R, GL_REPEAT );
			}
			check_for_GL_errors( "GL_TEXTURE_WRAP_*" );
		} else {
			/*	unsigned int clamp_mode = SOIL_CLAMP_TO_EDGE;	*/
			unsigned int clamp_mode = GL_CLAMP;
			glTexParameteri( opengl_texture_type, GL_TEXTURE_WRAP_S, clamp_mode );
			glTexParameteri( opengl_texture_type, GL_TEXTURE_WRAP_T, clamp_mode );
			if( opengl_texture_type == SOIL_TEXTURE_CUBE_MAP )
			{
				/*	SOIL_TEXTURE_WRAP_R is invalid if cubemaps aren't supported	*/
				glTexParameteri( opengl_texture_type, SOIL_TEXTURE_WRAP_R, clamp_mode );
			}
			check_for_GL_errors( "GL_TEXTURE_WRAP_*" );
		}
		/*	done	*/
		result_string_pointer = "Image loaded as an OpenGL texture";
	} else {
		/*	failed	*/
		result_string_pointer = "Failed to generate an OpenGL texture name; missing OpenGL context?";
	}
	SOIL_free_image_data( img );
	return tex_id;
}













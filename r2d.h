
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

#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SOIL/SOIL.h"



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

void
r2dAddVec2dIntoVec2d(r2dVec2d *dst, r2dVec2d *src) {
	dst->x += src->x;
	dst->y += src->y;
}

void
r2dSubtractVec2dFromVec2d(r2dVec2d *dst, r2dVec2d *src) {
	dst->x -= src->x;
	dst->y -= src->y;
}


void
r2dAddScalarIntoVec2d(r2dVec2d *dst, float s) {
	dst->x += s;
	dst->y += s;
}

void
r2dScaleVec2d(r2dVec2d *dst, float f)  {
	dst->x *= f;
	dst->y *= f;
}

float
r2dMagnitudeOfVec2d(r2dVec2d *v) {
	float x = v->x;
	float y = v-> y;
	return sqrt(x*x + y*y);
}

float
r2dSquareMagnitudeOfVec2d(r2dVec2d *v) {
	float x = v->x;
	float y = v-> y;
	return x*x + y*y;
}

float
r2dDotProductVec2d(r2dVec2d *u, r2dVec2d *v) {
	return u->x * v->x   +   u->y * v->y;
}

float
r2dAngleBetweenVec2d(r2dVec2d *u, r2dVec2d *v) {
	float dot = r2dDotProductVec2d(u, v),
	      magU = r2dMagnitudeOfVec2d(u),
	      magV = r2dMagnitudeOfVec2d(v);
	return acosf(dot / (magU * magV));
}

void
r2dRotateVec2d(r2dVec2d *v, float radians) {
	float tmp = v->x * cosf(radians) - v->y * sinf(radians);
	v->y = v->y * cosf(radians) + v->x * sinf(radians);
	v->x = tmp;
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


typedef struct {
	GLuint glid;
	int width;
	int height;
} r2dTexture;


GLuint r2dACTIVE_TEXTURE_GLID = 0;

GLuint
r2dLoadGlTextureFromFile(char *filename, int *width, int *height, GLenum filter) {
	printf("Calling soil...\n");
	GLuint texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_RGBA,
							 SOIL_CREATE_NEW_ID,
							 SOIL_FLAG_INVERT_Y);
	printf("soil returned.\n");
	r2dACTIVE_TEXTURE_GLID = texture;
	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	return texture;
}



r2dTexture
r2dLoadTextureFromFile(char *filename, GLenum filter) {
	r2dTexture t;
	t.glid = r2dLoadGlTextureFromFile(filename, &(t.width), &(t.height), filter);
	return t;
}



void
r2dDrawFromTexture(r2dTexture *texture,
		   r2dRectangle *frame,
		   r2dRectangle *sprite, float rotation) {
	r2dVec2d v[4] = { r2dRectangleTopLeft(frame),
			  r2dRectangleTopRight(frame),
			  r2dRectangleBottomRight(frame),
			  r2dRectangleBottomLeft(frame) };

	r2dVec2d center = r2dRectangleCenter(frame);

	for (int i = 0; i < 4; i += 1) {
		r2dSubtractVec2dFromVec2d(&v[i], &center);
		r2dRotateVec2d(&v[i], -rotation);
		r2dAddVec2dIntoVec2d(&v[i], &center);
	}

	r2dVec2d tex[4] = { r2dRectangleTopLeft(sprite),
			    r2dRectangleTopRight(sprite),
			    r2dRectangleBottomRight(sprite),
			    r2dRectangleBottomLeft(sprite) };

	r2dVec2d scale = r2dCreateVec2d(1.0f / texture->width,
					1.0f / texture->height);
	for (int i = 0; i < 4; i++) {
		tex[i].x *= scale.x;
		tex[i].y = 1.0f - tex[i].y * scale.y;
	}
	

	// Enable features
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	// Setup blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Bind texture only if not already bound
	if(r2dACTIVE_TEXTURE_GLID != texture->glid) {
		r2dACTIVE_TEXTURE_GLID = texture->glid;
		glBindTexture(GL_TEXTURE_2D, r2dACTIVE_TEXTURE_GLID);
	}
	
	// Set vertices
	glVertexPointer(2, GL_FLOAT, 0, v);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);
	
	// Draw image
	glDrawArrays(GL_QUADS, 0, 4);
	
	// Disable features
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void
r2dDrawWholeTexture(r2dTexture *texture, r2dRectangle *frame, float rotation) {
	r2dRectangle whole = r2dCreateRectangle(0, 0, texture->width, texture->height);
	r2dDrawFromTexture(texture, frame, &whole, rotation);
}


/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
// mathlib.h
#pragma once
#ifndef MATHLIB_H
#define MATHLIB_H
#include <math.h>
#include "vector_classes.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

struct mplane_s;

extern vec3_t vec3_origin;

#ifdef XASH_IRIX
#undef isnan
#endif
#ifdef isnan // check for C99 isnan
#define IS_NAN isnan
#else
#define IS_NAN(x)		(((*(int *)&x) & (255<<23)) == (255<<23))
#endif

void VectorMA (const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc);

vec_t _DotProduct (vec3_t v1, vec3_t v2);
void _VectorSubtract (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorAdd (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorCopy (vec3_t in, vec3_t out);

int VectorCompare (const vec3_t v1, const vec3_t v2);
float Length (const vec3_t v);
void CrossProduct (const vec3_t v1, const vec3_t v2, vec3_t cross);
float VectorNormalize (vec3_t v);		// returns vector length
void VectorInverse (vec3_t v);
void VectorScale (const vec3_t in, vec_t scale, vec3_t out);

void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4]);

void AngleVectors (const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
void AngleVectorsTranspose (const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
#define AngleIVectors	AngleVectorsTranspose

void AngleMatrix (const vec3_t angles, float (*matrix)[4] );
void AngleIMatrix (const vec3_t angles, float (*matrix)[4] );
void VectorTransform (const vec3_t in1, float in2[3][4], vec3_t out);

void NormalizeAngles( vec3_t angles );
void InterpolateAngles( vec3_t start, vec3_t end, vec3_t output, float frac );
float AngleBetweenVectors( const vec3_t v1, const vec3_t v2 );

void VectorMatrix( vec3_t forward, vec3_t right, vec3_t up);
void VectorAngles( const vec3_t forward, vec3_t angles );

int InvertMatrix( const float * m, float *out );

int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct mplane_s *plane);
float	anglemod(float a);

#define BOX_ON_PLANE_SIDE(emins, emaxs, p)	\
	(((p)->type < 3)?						\
	(										\
		((p)->dist <= (emins)[(p)->type])?	\
			1								\
		:									\
		(									\
			((p)->dist >= (emaxs)[(p)->type])?\
				2							\
			:								\
				3							\
		)									\
	)										\
	:										\
		BoxOnPlaneSide( (emins), (emaxs), (p)))
#endif // MATHLIB_H

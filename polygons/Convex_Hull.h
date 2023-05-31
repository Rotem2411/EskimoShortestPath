#pragma once

#include <math.h>

#define pi 3.14159
#define Multiplyer 1000.0

typedef struct
{
	int x, y;
} vertex;


int process_vertices(int n, vertex* v);
void swap(vertex* v1, vertex* v2);
int orientation(vertex p, vertex q, vertex r);
int distSq(vertex p1, vertex p2);
int compare(const void* vp1, const void* vp2);
vertex* Convex_Hull(vertex* v, int* count);


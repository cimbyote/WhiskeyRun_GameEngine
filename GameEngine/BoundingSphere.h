#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "Vect.h"
#include "UnitModel.h"

struct Sphere
{
	Vect center;
	float radius;
	float padding[3];  // love and hate this new compiler
};

void RitterSphere(Sphere &s, Vect *pt, int numPts);

#endif
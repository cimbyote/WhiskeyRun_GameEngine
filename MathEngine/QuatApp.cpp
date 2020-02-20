//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#include "MathEngine.h"
#include "MathApp.h"
#include <math.h>

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

void QuatApp::Slerp(Quat &result, const Quat &src, const Quat &tar, const float t)
{
	Quat srcTemp = src;
	Quat tarTemp = tar;

	float temp = srcTemp.dot(tarTemp);

	if (temp < 0)
	{
		temp = -temp;
		tarTemp = -tarTemp;
	}

	if (temp == 0)
	{
		result = srcTemp;
	}
	
	else if (Util::isEqual(temp, 1, 0.00001f))
	{
		result = tarTemp;
	}
	else {
		temp = acosf(temp);
		float sinTemp = sinf(temp);

		//temp = 0;
		result = (srcTemp * ((sinf((1 - t) * temp)) / sinTemp));
		result += (tarTemp * (sinf(temp*t) / sinTemp));

		assert(result.qx() == result.qx());
	}
};


void QuatApp::SlerpArray(Quat *out, const Quat *a, const Quat *b, const float t, const int numQuats)
{
	for (int i = 0; i < numQuats; i++)
	{
		Slerp(out[i], a[i], b[i], t);
	}

};

// ---  End of File ---------------

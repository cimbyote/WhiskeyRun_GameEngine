//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h>

#include "Align16.h"
#include "Constants.h"
#include "Enum.h"

// forward declare
class Matrix;
class Quat;

class Vect final : public Align16
{
	friend class Matrix;
public:

	// Do your magic here
	Vect(); //constructor
	Vect(const float inX, const float inY, const float inZ, const float inW = 1.0f);


	Vect(const Vect &inVect); //copy
	Vect operator = (const Vect &inVect); //assign
	~Vect(); //destructor

	//get operators
	float operator[] (x_enum) const;
	float operator[] (y_enum) const;
	float operator[] (z_enum) const;
	float operator[] (w_enum) const;

	float& operator[] (x_enum);
	float& operator[] (y_enum);
	float& operator[] (z_enum);
	float& operator[] (w_enum);

	float& x();
	float& y();
	float& z();
	float& w();

	const float& x() const;
	const float& y() const;
	const float& z() const;
	const float& w() const;

	//set operators
	void set(Vect inVect);
	void set(const float inX, const float inY, const float inZ);
	void set(const float inX, const float inY, const float inZ, const float inW);

	//add operators
	Vect operator + (Vect inVect) const;
	void operator += (const Vect &inVect);
	Vect operator + () const;

	//sub operators
	Vect operator - (Vect inVect) const;
	void operator -= (const Vect &inVect);
	Vect const operator - () const; //negation

									//mult operators
	Vect operator * (Vect &inVect) const;
	Vect operator * (const float inNum) const;
	void operator *= (Vect &inVect);
	void operator *= (const float &inNum);

	friend Vect operator * (float inNum, Vect inVect);

	Vect operator * (Matrix inMatrix) const;
	void operator *= (Matrix inMatrix);

	Vect operator * (Quat &inQuat) const;
	void operator *= (Quat &inQuat);

	//div operators
	Vect operator / (Vect &inVect);
	void operator /= (const Vect &inVect);

	//util bool wrappers
	bool isEqual(Vect& other, const float epsilon = MATH_TOLERANCE);
	bool isNotEqual(Vect other, const float epsilon);
	bool isOne(const float epsilon);
	bool isNonZero(const float epsilon);
	bool isZero(const float epsilon = MATH_TOLERANCE);

	//functions
	float dot(Vect inVect);
	Vect cross(Vect inVect) const;
	void norm(void);
	Vect getNorm(void);
	float mag();
	float magSqr();
	float getAngle(Vect inVect);

private:

	union 
	{
		__m128	_mv;

		// anonymous struct
		struct 
			{
			float _vx;
			float _vy;
			float _vz;
			float _vw;
			};
	};

};


#endif

// ---  End of File ---------------

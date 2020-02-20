//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Matrix.h"
#include "Vect.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------

class Quat final : public Align16
{
	friend class Matrix;
public:

	// Do your magic here
	//Big Four
	Quat(); //constructor
	Quat operator = (const Quat &inQuat);
	Quat(const Quat & inQuat);
	~Quat();


	Quat(const float inX, const float inY, const float inZ, const float inW = 1.0f);
	Quat(Vect inVect, float w);
	Quat(Matrix inMatrix);
	Quat(MatrixSpecialType type);
	Quat(RotType rotType, float inFloat);

	Quat(const RotAxisAngleType type, const Vect &axis, const float angle);

	Quat(RotOrientType rotType, Vect inVect1, Vect inVect2);
	Quat(Rot3AxisType rotType, float inFloat1, float inFloat2, float inFloat3);

	//add operators
	Quat operator + (Quat &inQuat);
	Quat operator + () const;
	Quat operator + (float inFloat);
	void operator += (const Quat &inQuat);
	Quat operator += (float inFloat);
	friend Quat operator+(float inFloat, const Quat &inQuat);

	//sub operators
	Quat operator - (Quat &inQuat);
	Quat operator - () const;
	Quat operator - (float inFloat);
	void operator -= (const Quat &inQuat);
	Quat operator -= (float inFloat);
	friend Quat operator-(float inFloat, const Quat &inQuat);

	//mult operators
	Quat operator * (const Quat &inQuat);
	Quat operator * (const float inNum);
	void operator *= (Quat &inQuat);
	void operator *= (const float &inNum);
	friend Quat operator*(float inFloat, const Quat &inQuat);

	Quat operator * (Vect &inVect);
	Quat operator *= (Vect &inVect);
	Matrix operator * (Matrix inMatrix);
	void operator *= (Matrix inMatrix);

	Quat multByElement(Quat &inQuat);

	//divide operators
	Quat operator / (const Quat &inQuat);
	Quat operator / (const float inNum);
	void operator /= (Quat &inQuat);
	void operator /= (const float &inNum);
	friend Quat operator/(float inFloat, const Quat &inQuat);

	Quat operator / (Vect &inVect);
	Quat operator /= (Vect &inVect);
	Quat operator / (Matrix &inMatrix);
	Quat operator /= (Matrix &inMatrix);


	//util bool wrappers
	bool isIdentity(float tolerance = MATH_TOLERANCE);
	bool isNormalized(float tolerance = MATH_TOLERANCE);
	bool isZero(float tolerance = MATH_TOLERANCE);
	bool isEqual(Quat other, const float epsilon = MATH_TOLERANCE);
	bool isConjugateEqual(Quat other, const float epsilon = MATH_TOLERANCE);
	bool isEquivalent(Quat other, const float epsilon = MATH_TOLERANCE);
	bool isNegEqual(Quat other, const float epsilon = MATH_TOLERANCE);
	bool isNotEqual(Quat other, const float epsilon = MATH_TOLERANCE);



	//functions
	Quat getConj();
	void conj();

	Quat getT();
	void T();

	float mag();
	float magSquared();
	float invMag();
	float dot(Quat &inQuat);
	//Quat cross(Quat inVect);

	Quat getNorm();
	Quat norm();

	Quat getInv();
	void inv();

	void Lqcvq(const Vect inVect1, Vect &inVect2);
	void Lqvqc(const Vect inVect1, Vect &inVect2);
	
	//set operators
	void set(float x, float y, float z, float w);
	void set(Vect inVect, float w);

	void set(Matrix inMatrix);

	void set(MatrixSpecialType inMatrix);

	
	void set(const RotType type, const float angle);
	void set(const RotAxisAngleType rotType, const float inFloat);
	void set(const RotAxisAngleType type, const Vect &axis, const float angle);

	//void set(RotAxisAngleType rotType, Vect inVect, float rotation);
	//void set(RotOrientType rotType, Vect inVect1, Vect inVect2);
	void set(const RotOrientType type, Vect &dof, Vect & up);
	void set(const Rot3AxisType type, const float rx, const float ry, const float rz);

	void setVect(Vect inVect);
	void getVect(Vect &inVect);
	float getAngle();
	void getAxis(Vect &inVect);

	//get operators
	float operator[] (x_enum) const;
	float operator[] (y_enum) const;
	float operator[] (z_enum) const;
	float operator[] (w_enum) const;

	float& operator[] (x_enum);
	float& operator[] (y_enum);
	float& operator[] (z_enum);
	float& operator[] (w_enum);

	float& qx();
	float& qy();
	float& qz();
	float& qw();
	float& real();

	const float& qx() const;
	const float& qy() const;
	const float& qz() const;
	const float& qw() const;
	const float& real() const;
	



private:

	// anonymous union
	union
	{
		__m128	_mq;

		// anonymous struct
		struct
		{
			float _qx;
			float _qy;
			float _qz;
			float _qw;
		};
	};

};


#endif 

// ---  End of File ---------------

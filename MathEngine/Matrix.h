//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

// SIMD includes
#include <xmmintrin.h>
#include <smmintrin.h> 
#include "Constants.h"

#include "Vect.h"
//#include "Quat.h"

class Quat;

class Matrix final : public Align16
{
public:

	// Do your magic here
	Matrix();
	Matrix(MatrixSpecialType type);
	Matrix(Vect v0, Vect v1, Vect v2, Vect v3);
	Matrix(MatrixTransType type, float inX, float inY, float inZ);
	Matrix(MatrixTransType type, Vect inVect);
	Matrix(MatrixScaleType type, float inX, float inY, float inZ);
	Matrix(MatrixScaleType type, Vect inVect);
	Matrix(RotType type, float inFloat);

	Matrix(Rot3AxisType type, const float inFloat1, const float inFloat2, const float inFloat3);

	Matrix(RotAxisAngleType type, Vect inVect, float tolerance = MATH_TOLERANCE);
	Matrix(RotOrientType type, Vect inVect1, Vect inVect2, float tolerance = MATH_TOLERANCE);
	Matrix(Quat inQuat, RotType type, float inFloat);
	Matrix(Quat inQuat);

	Matrix(const Matrix &inMatrix);
	Matrix& operator = (const Matrix &inMatrix);
	~Matrix();

	//add operators
	Matrix operator + (Matrix &inMatrix);
	void operator += (const Matrix &inMatrix);
	Matrix operator + ();

	//sub operators
	Matrix operator - (Matrix &inMatrix);
	void operator -= (const Matrix &inMatrix);
	Matrix operator - () const;

	//mult operators
	Matrix operator * (const Matrix &inMatrix);
	Matrix operator * (const float inNum);
	void operator *= (Matrix &inMatrix);
	void operator *= (const float &inNum);

	Matrix operator * (Vect &inVect);
	Matrix operator *= (Vect &inVect);
	Matrix operator * (const Quat &inQuat);
	void operator *= (const Quat &inQuat);

	friend Matrix operator * (float inNum, Matrix inMatrix);

	//div operators
	Matrix operator / (Matrix &inMatrix);
	void operator /= (const Matrix &inMatrix);
	void operator /= (const float &inNum);

	//util bool wrappers
	bool isIdentity(float tolerance = MATH_TOLERANCE);
	bool isEqual(Matrix other, const float epsilon = MATH_TOLERANCE);
	bool isNotEqual(Matrix other, const float epsilon = MATH_TOLERANCE);

	//functions
	float det();
	void T();
	Matrix getT();
	void inv();
	Matrix getInv();

	//set operators
	void set(Matrix inMatrix);
	void set(Vect v0, Vect v1, Vect v2, Vect v3);

	void set(MatrixSpecialType type);

	void set(MatrixTransType type, float inX, float inY, float inZ);
	void set(MatrixTransType type, Vect inVect);

	void set(MatrixScaleType type, float inX, float inY, float inZ);
	void set(MatrixScaleType type, Vect inVect);

	void set(RotType type, float inFloat);
	void set(MatrixRowType type, Vect &inVect);

	void set(Quat inQuat, Vect inVect, float inFloat);
	void set(Quat inQuat);

	void set(RotAxisAngleType type, Vect inVect, float infloat);
	void set(RotOrientType type, Vect &inVect1, Vect &inVect2);
	void set(Rot3AxisType type, const float inFloat1, const float inFloat2, const float inFloat3);

	//get operators

	Vect get(MatrixRowType type);

	float& operator[] (m0_enum);
	float& operator[] (m1_enum);
	float& operator[] (m2_enum);
	float& operator[] (m3_enum);
	float& operator[] (m4_enum);
	float& operator[] (m5_enum);
	float& operator[] (m6_enum);
	float& operator[] (m7_enum);
	float& operator[] (m8_enum);
	float& operator[] (m9_enum);
	float& operator[] (m10_enum);
	float& operator[] (m11_enum);
	float& operator[] (m12_enum);
	float& operator[] (m13_enum);
	float& operator[] (m14_enum);
	float& operator[] (m15_enum);

	float operator[] (m0_enum) const;
	float operator[] (m1_enum) const;
	float operator[] (m2_enum) const;
	float operator[] (m3_enum) const;
	float operator[] (m4_enum) const;
	float operator[] (m5_enum) const;
	float operator[] (m6_enum) const;
	float operator[] (m7_enum) const;
	float operator[] (m8_enum) const;
	float operator[] (m9_enum) const;
	float operator[] (m10_enum) const;
	float operator[] (m11_enum) const;
	float operator[] (m12_enum) const;
	float operator[] (m13_enum) const;
	float operator[] (m14_enum) const;
	float operator[] (m15_enum) const;

	float& m0();
	float& m1();
	float& m2();
	float& m3();
	float& m4();
	float& m5();
	float& m6();
	float& m7();
	float& m8();
	float& m9();
	float& m10();
	float& m11();
	float& m12();
	float& m13();
	float& m14();
	float& m15();

	const float& m0() const;
	const float& m1() const;
	const float& m2() const;
	const float& m3() const;
	const float& m4() const;
	const float& m5() const;
	const float& m6() const;
	const float& m7() const;
	const float& m8() const;
	const float& m9() const;
	const float& m10() const;
	const float& m11() const;
	const float& m12() const;
	const float& m13() const;
	const float& m14() const;
	const float& m15() const;


private:

	union
	{
		struct
		{
			Vect _v0;
			Vect _v1;
			Vect _v2;
			Vect _v3;
		};

		struct
		{
			float _m0;
			float _m1;
			float _m2;
			float _m3;
			float _m4;
			float _m5;
			float _m6;
			float _m7;
			float _m8;
			float _m9;
			float _m10;
			float _m11;
			float _m12;
			float _m13;
			float _m14;
			float _m15;
		};
	};
};

#endif

// ---  End of File ---------------

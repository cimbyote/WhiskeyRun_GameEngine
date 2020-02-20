//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#include <math.h>

#include "MathEngine.h"

#define ShutUP(v) ((void )v)
/*
   _____                _                   _                 
  / ____|              | |                 | |                
 | |     ___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __ ___ 
 | |    / _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__/ __|
 | |___| (_) | | | \__ \ |_| |  | |_| | (__| || (_) | |  \__ \
  \_____\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|  |___/
*/
Matrix::Matrix()
{
	this->set(ZERO);
}

Matrix::Matrix(Vect v0, Vect v1, Vect v2, Vect v3)
{
	this->_v0 = v0;
	this->_v1 = v1;
	this->_v2 = v2;
	this->_v3 = v3;

	this->_m0 = _v0._vx;
	this->_m1 = _v0._vy;
	this->_m2 = _v0._vz;
	this->_m3 = _v0._vw;

	this->_m4 = _v1._vx;
	this->_m5 = _v1._vy;
	this->_m6 = _v1._vz;
	this->_m7 = _v1._vw;

	this->_m8 = _v2._vx;
	this->_m9 = _v2._vy;
	this->_m10 = _v2._vz;
	this->_m11 = _v2._vw;


	this->_m12 = _v3._vx;
	this->_m13 = _v3._vy;
	this->_m14 = _v3._vz;
	this->_m15 = _v3._vw;
}

Matrix::Matrix(MatrixTransType type, float inX, float inY, float inZ)
{
	if (type == MatrixTransType::TRANS)
	{
		this->set(IDENTITY);

		this->_m12 = inX;
		this->_m13 = inY;
		this->_m14 = inZ;
	}
}

Matrix::Matrix(MatrixTransType type, Vect inVect)
{
	if (type == MatrixTransType::TRANS)
	{
		this->set(IDENTITY);

		this->_m12 = inVect._vx;
		this->_m13 = inVect._vy;
		this->_m14 = inVect._vz;
	}
}
Matrix::Matrix(MatrixScaleType type, float inX, float inY, float inZ)
{
	if (type == MatrixScaleType::SCALE)
	{
		this->set(IDENTITY);

		this->_m0 = inX;
		this->_m5 = inY;
		this->_m10 = inZ;
	}
}

Matrix::Matrix(MatrixScaleType type, Vect inVect)
{
	if (type == MatrixScaleType::SCALE)
	{
		this->set(IDENTITY);

		this->_m0 = inVect._vx;
		this->_m5 = inVect._vy;
		this->_m10 = inVect._vz;
	}
}

Matrix::Matrix(RotType type, float inFloat)
{
	float cosTemp = cosf(inFloat);
	float sinTemp = sinf(inFloat);

	if (type == RotType::ROT_X)
	{
		this->set(IDENTITY);

		this->_m5 = cosTemp;
		this->_m6 = sinTemp;
		this->_m9 = -sinTemp;
		this->_m10 = cosTemp;
	}
	else if (type == RotType::ROT_Y)
	{
		this->set(IDENTITY);

		this->_m0 = cosTemp;
		this->_m2 = -sinTemp;
		this->_m8 = sinTemp;
		this->_m10 = cosTemp;
	}

	else if (type == RotType::ROT_Z)
	{
		this->set(IDENTITY);

		this->_m0 = cosTemp;
		this->_m1 = sinTemp;
		this->_m4 = -sinTemp;
		this->_m5 = cosTemp;
	}
}


Matrix::Matrix(MatrixSpecialType type)
{

	if (type == MatrixSpecialType::IDENTITY)
	{
		this->_m0 = 1.0f;
		this->_m5 = 1.0f;
		this->_m10 = 1.0f;
		this->_m15 = 1.0f;
	}
	else if (type == MatrixSpecialType::ZERO)
	{
		this->_m0 = 0.0f;
		this->_m5 = 0.0f;
		this->_m10 = 0.0f;
		this->_m15 = 0.0f;
	}
	else
	{
		assert(0);
	}
	this->_m1 = 0.0f;
	this->_m2 = 0.0f;
	this->_m3 = 0.0f;

	this->_m4 = 0.0f;
	this->_m6 = 0.0f;
	this->_m7 = 0.0f;

	this->_m8 = 0.0f;
	this->_m9 = 0.0f;
	this->_m11 = 0.0f;
	this->_m12 = 0.0f;
	this->_m13 = 0.0f;
	this->_m14 = 0.0f;

	this->_v0 = Vect(_m0, _m1, _m2, _m3);
	this->_v1 = Vect(_m4, _m5, _m6, _m7);
	this->_v2 = Vect(_m8, _m9, _m10, _m11);
	this->_v3 = Vect(_m12, _m13, _m14, _m15);
}

Matrix::Matrix(const Matrix &inMatrix)
{
	this->_v0 = inMatrix._v0;
	this->_v1 = inMatrix._v1;
	this->_v2 = inMatrix._v2;
	this->_v3 = inMatrix._v3;

	this->_m0 = _v0._vx;
	this->_m1 = _v0._vy;
	this->_m2 = _v0._vz;
	this->_m3 = _v0._vw;

	this->_m4 = _v1._vx;
	this->_m5 = _v1._vy;
	this->_m6 = _v1._vz;
	this->_m7 = _v1._vw;

	this->_m8 = _v2._vx;
	this->_m9 = _v2._vy;
	this->_m10 = _v2._vz;
	this->_m11 = _v2._vw;

	this->_m12 = _v3._vx;
	this->_m13 = _v3._vy;
	this->_m14 = _v3._vz;
	this->_m15 = _v3._vw;
}
Matrix::Matrix(Quat inQuat, RotType type, float inFloat)
{
	ShutUP(inQuat);
	ShutUP(inFloat);
	ShutUP(type);
}
Matrix::Matrix(Quat q)
{
	this->_m0 = 1 - 2 * ((q._qy*q._qy) + (q._qz*q._qz));
	this->_m1 = 2 * ((q._qx*q._qy) + (q._qw*q._qz));
	this->_m2 = 2 * ((q._qx*q._qz) - (q._qw*q._qy));
	this->_m3 = 0.0f;

	this->_m4 = 2 * ((q.qx()*q.qy()) - (q.qw()*q.qz()));
	this->_m5 = 1 - 2 * ((q.qx()*q.qx()) + (q.qz()*q.qz()));
	this->_m6 = 2 * ((q._qy * q._qz) + (q._qw*q._qx));
	this->_m7 = 0.0f;

	this->_m8 = 2 * ((q.qx()*q.qz()) + (q.qw()*q.qy()));
	this->_m9 = 2 * ((q._qy * q._qz) - (q._qw*q._qx));
	this->_m10 = 1 - 2 * ((q.qx()*q.qx()) + (q.qy()*q.qy()));
	this->_m11 = 0.0f;

	this->_m12 = 0.0f;
	this->_m13 = 0.0f;
	this->_m14 = 0.0f;
	this->_m15 = 1.0f;
}
Matrix::Matrix(Rot3AxisType type, float inFloat1, float inFloat2, float inFloat3)
{
	this->set(type, inFloat1, inFloat2, inFloat3);
}

Matrix::Matrix(RotAxisAngleType type, Vect inVect, float tolerance)
{
	this->set(type, inVect, tolerance);
}

Matrix::Matrix(RotOrientType type, Vect inVect1, Vect inVect2, float tolerance)
{
	ShutUP(tolerance);
	this->set(type, inVect1, inVect2);
}

Matrix& Matrix::operator = (const Matrix &inMatrix)
{
	this->_v0 = inMatrix._v0;
	this->_v1 = inMatrix._v1;
	this->_v2 = inMatrix._v2;
	this->_v3 = inMatrix._v3;

	this->_m0 = _v0._vx;
	this->_m1 = _v0._vy;
	this->_m2 = _v0._vz;
	this->_m3 = _v0._vw;

	this->_m4 = _v1._vx;
	this->_m5 = _v1._vy;
	this->_m6 = _v1._vz;
	this->_m7 = _v1._vw;

	this->_m8 = _v2._vx;
	this->_m9 = _v2._vy;
	this->_m10 = _v2._vz;
	this->_m11 = _v2._vw;


	this->_m12 = _v3._vx;
	this->_m13 = _v3._vy;
	this->_m14 = _v3._vz;
	this->_m15 = _v3._vw;
	return *this;
}

Matrix::~Matrix()
{

}
/*
             _     _ _ _   _             
     /\      | |   | (_) | (_)            
    /  \   __| | __| |_| |_ _  ___  _ __  
   / /\ \ / _` |/ _` | | __| |/ _ \| '_ \ 
  / ____ \ (_| | (_| | | |_| | (_) | | | |
 /_/    \_\__,_|\__,_|_|\__|_|\___/|_| |_|
*/
Matrix Matrix::operator + (Matrix &inMatrix)
{
	return Matrix(
		Vect(this->_m0 + inMatrix._m0, this->_m1 + inMatrix._m1, this->_m2 + inMatrix._m2, this->_m3 + inMatrix._m3),
		Vect(this->_m4 + inMatrix._m4, this->_m5 + inMatrix._m5, this->_m6 + inMatrix._m6, this->_m7 + inMatrix._m7),
		Vect(this->_m8 + inMatrix._m8, this->_m9 + inMatrix._m9, this->_m10 + inMatrix._m10, this->_m11 + inMatrix._m11),
		Vect(this->_m12 + inMatrix._m12, this->_m13 + inMatrix._m13, this->_m14 + inMatrix._m14, this->_m15 + inMatrix._m15));
}

void Matrix::operator += (const Matrix &inMatrix)
{
	this->_m0 = inMatrix._v0._vx + this->_m0;
	this->_m1 = inMatrix._v0._vy + this->_m1;
	this->_m2 = inMatrix._v0._vz + this->_m2;
	this->_m3 = inMatrix._v0._vw + this->_m3;

	this->_m4 = inMatrix._v1._vx + this->_m4;
	this->_m5 = inMatrix._v1._vy + this->_m5;
	this->_m6 = inMatrix._v1._vz + this->_m6;
	this->_m7 = inMatrix._v1._vw + this->_m7;

	this->_m8 = inMatrix._v2._vx + this->_m8;
	this->_m9 = inMatrix._v2._vy + this->_m9;
	this->_m10 = inMatrix._v2._vz + this->_m10;
	this->_m11 = inMatrix._v2._vw + this->_m11;

	this->_m12 = inMatrix._v3._vx + this->_m12;
	this->_m13 = inMatrix._v3._vy + this->_m13;
	this->_m14 = inMatrix._v3._vz + this->_m14;
	this->_m15 = inMatrix._v3._vw + this->_m15;
}

Matrix Matrix::operator + ()
{
	return *this;
}

/*
   _____       _     _                  _   _             
  / ____|     | |   | |                | | (_)            
 | (___  _   _| |__ | |_ _ __ __ _  ___| |_ _  ___  _ __  
  \___ \| | | | '_ \| __| '__/ _` |/ __| __| |/ _ \| '_ \ 
  ____) | |_| | |_) | |_| | | (_| | (__| |_| | (_) | | | |
 |_____/ \__,_|_.__/ \__|_|  \__,_|\___|\__|_|\___/|_| |_|
*/
Matrix Matrix::operator - (Matrix &inMatrix)
{
	return Matrix(
		Vect(this->_m0 - inMatrix._m0, this->_m1 - inMatrix._m1, this->_m2 - inMatrix._m2, this->_m3 - inMatrix._m3),
		Vect(this->_m4 - inMatrix._m4, this->_m5 - inMatrix._m5, this->_m6 - inMatrix._m6, this->_m7 - inMatrix._m7),
		Vect(this->_m8 - inMatrix._m8, this->_m9 - inMatrix._m9, this->_m10 - inMatrix._m10, this->_m11 - inMatrix._m11),
		Vect(this->_m12 - inMatrix._m12, this->_m13 - inMatrix._m13, this->_m14 - inMatrix._m14, this->_m15 - inMatrix._m15));
}

void Matrix::operator -= (const Matrix &inMatrix)
{
	this->_m0 = this->_m0 - inMatrix._v0._vx;
	this->_m1 = this->_m1 - inMatrix._v0._vy;
	this->_m2 = this->_m2 - inMatrix._v0._vz;
	this->_m3 = this->_m3 - inMatrix._v0._vw;

	this->_m4 = this->_m4 - inMatrix._v1._vx;
	this->_m5 = this->_m5 - inMatrix._v1._vy;
	this->_m6 = this->_m6 - inMatrix._v1._vz;
	this->_m7 = this->_m7 - inMatrix._v1._vw;

	this->_m8 = this->_m8 - inMatrix._v2._vx;
	this->_m9 = this->_m9 - inMatrix._v2._vy;
	this->_m10 = this->_m10 - inMatrix._v2._vz;
	this->_m11 = this->_m11 - inMatrix._v2._vw;

	this->_m12 = this->_m12 - inMatrix._v3._vx;
	this->_m13 = this->_m13 - inMatrix._v3._vy;
	this->_m14 = this->_m14 - inMatrix._v3._vz;
	this->_m15 = this->_m15 - inMatrix._v3._vw;
}

Matrix Matrix::operator - () const
{
	return Matrix(
		Vect(-this->_m0, -this->_m1, -this->_m2, -this->_m3),
		Vect(-this->_m4, -this->_m5, -this->_m6, -this->_m7),
		Vect(-this->_m8, -this->_m9, -this->_m10, -this->_m11),
		Vect(-this->_m12, -this->_m13, -this->_m14, -this->_m15));

}

/*
  __  __       _ _   _       _ _           _   _             
 |  \/  |     | | | (_)     | (_)         | | (_)            
 | \  / |_   _| | |_ _ _ __ | |_  ___ __ _| |_ _  ___  _ __  
 | |\/| | | | | | __| | '_ \| | |/ __/ _` | __| |/ _ \| '_ \ 
 | |  | | |_| | | |_| | |_) | | | (_| (_| | |_| | (_) | | | |
 |_|  |_|\__,_|_|\__|_| .__/|_|_|\___\__,_|\__|_|\___/|_| |_|
                      | |                                    
                      |_|                                    
*/
Matrix Matrix::operator * (const Matrix &t)
{
	Matrix A;

	A._m0 = (_m0*t._m0) + (_m1*t._m4) + (_m2*t._m8) + (_m3*t._m12);
	A._m1 = (_m0*t._m1) + (_m1*t._m5) + (_m2*t._m9) + (_m3*t._m13);
	A._m2 = (_m0*t._m2) + (_m1*t._m6) + (_m2*t._m10) + (_m3*t._m14);
	A._m3 = (_m0*t._m3) + (_m1*t._m7) + (_m2*t._m11) + (_m3*t._m15);

	A._m4 = (_m4*t._m0) + (_m5*t._m4) + (_m6*t._m8) + (_m7*t._m12);
	A._m5 = (_m4*t._m1) + (_m5*t._m5) + (_m6*t._m9) + (_m7*t._m13);
	A._m6 = (_m4*t._m2) + (_m5*t._m6) + (_m6*t._m10) + (_m7*t._m14);
	A._m7 = (_m4*t._m3) + (_m5*t._m7) + (_m6*t._m11) + (_m7*t._m15);

	A._m8 = (_m8*t._m0) + (_m9*t._m4) + (_m10*t._m8) + (_m11*t._m12);
	A._m9 = (_m8*t._m1) + (_m9*t._m5) + (_m10*t._m9) + (_m11*t._m13);
	A._m10 = (_m8*t._m2) + (_m9*t._m6) + (_m10*t._m10) + (_m11*t._m14);
	A._m11 = (_m8*t._m3) + (_m9*t._m7) + (_m10*t._m11) + (_m11*t._m15);

	A._m12 = (_m12*t._m0) + (_m13*t._m4) + (_m14*t._m8) + (_m15*t._m12);
	A._m13 = (_m12*t._m1) + (_m13*t._m5) + (_m14*t._m9) + (_m15*t._m13);
	A._m14 = (_m12*t._m2) + (_m13*t._m6) + (_m14*t._m10) + (_m15*t._m14);
	A._m15 = (_m12*t._m3) + (_m13*t._m7) + (_m14*t._m11) + (_m15*t._m15);

	return A;

}

Matrix Matrix::operator * (const float inNum) //
{
	return Matrix(
		Vect(this->_m0 * inNum, this->_m1 * inNum, this->_m2 * inNum, this->_m3 * inNum),
		Vect(this->_m4 * inNum, this->_m5 * inNum, this->_m6 * inNum, this->_m7 * inNum),
		Vect(this->_m8 * inNum, this->_m9 * inNum, this->_m10* inNum, this->_m11* inNum),
		Vect(this->_m12* inNum, this->_m13* inNum, this->_m14* inNum, this->_m15* inNum
		));
}

void Matrix::operator *= (Matrix &t)
{

	float x = this->_m0;
	float y = this->_m1;
	float z = this->_m2;
	float w = this->_m3;

	this->_m0 = x*t._m0 + y*t._m4 + z*t._m8 + w*t._m12;
	this->_m1 = x*t._m1 + y*t._m5 + z*t._m9 + w*t._m13;
	this->_m2 = x*t._m2 + y*t._m6 + z*t._m10 + w*t._m14;
	this->_m3 = x*t._m3 + y*t._m7 + z*t._m11 + w*t._m15;

	x = this->_m4;
	y = this->_m5;
	z = this->_m6;
	w = this->_m7;

	this->_m4 = x*t._m0 + y*t._m4 + z*t._m8 + w*t._m12;
	this->_m5 = x*t._m1 + y*t._m5 + z*t._m9 + w*t._m13;
	this->_m6 = x*t._m2 + y*t._m6 + z*t._m10 + w*t._m14;
	this->_m7 = x*t._m3 + y*t._m7 + z*t._m11 + w*t._m15;

	x = this->_m8;
	y = this->_m9;
	z = this->_m10;
	w = this->_m11;

	this->_m8 = x*t._m0 + y*t._m4 + z*t._m8 + w*t._m12;
	this->_m9 = x*t._m1 + y*t._m5 + z*t._m9 + w*t._m13;
	this->_m10 = x*t._m2 + y*t._m6 + z*t._m10 + w*t._m14;
	this->_m11 = x*t._m3 + y*t._m7 + z*t._m11 + w*t._m15;

	x = this->_m12;
	y = this->_m13;
	z = this->_m14;
	w = this->_m15;


	this->_m12 = x*t._m0 + y*t._m4 + z*t._m8 + w*t._m12;
	this->_m13 = x*t._m1 + y*t._m5 + z*t._m9 + w*t._m13;
	this->_m14 = x*t._m2 + y*t._m6 + z*t._m10 + w*t._m14;
	this->_m15 = x*t._m3 + y*t._m7 + z*t._m11 + w*t._m15;

}

void Matrix::operator *= (const float &inNum)
{
	this->_m0 *= inNum;
	this->_m1 *= inNum;
	this->_m2 *= inNum;
	this->_m3 *= inNum;

	this->_m4 *= inNum;
	this->_m5 *= inNum;
	this->_m6 *= inNum;
	this->_m7 *= inNum;

	this->_m8 *= inNum;
	this->_m9 *= inNum;
	this->_m10 *= inNum;
	this->_m11 *= inNum;

	this->_m12 *= inNum;
	this->_m13 *= inNum;
	this->_m14 *= inNum;
	this->_m15 *= inNum;

}

Matrix Matrix::operator * (Vect &inVect)
{
	ShutUP(inVect);

	return *this;
}

Matrix Matrix::operator *= (Vect &inVect)
{
	ShutUP(inVect);

	return *this;
}

Matrix Matrix::operator * (const Quat &inQuat) 
{
	Matrix temp(inQuat);
	return(*this * temp);
}
void Matrix::operator *= (const Quat &inQuat) 
{
	Matrix temp(inQuat);
	*this *= temp;
}

Matrix operator * (float inNum, Matrix inMatrix)
{
	inMatrix._m0 = inMatrix._m0  * inNum;
	inMatrix._m1 = inMatrix._m1  * inNum;
	inMatrix._m2 = inMatrix._m2  * inNum;
	inMatrix._m3 = inMatrix._m3  * inNum;

	inMatrix._m4 = inMatrix._m4  * inNum;
	inMatrix._m5 = inMatrix._m5  * inNum;
	inMatrix._m6 = inMatrix._m6  * inNum;
	inMatrix._m7 = inMatrix._m7  * inNum;

	inMatrix._m8 = inMatrix._m8  * inNum;
	inMatrix._m9 = inMatrix._m9  * inNum;
	inMatrix._m10 = inMatrix._m10* inNum;
	inMatrix._m11 = inMatrix._m11* inNum;

	inMatrix._m12 = inMatrix._m12* inNum;
	inMatrix._m13 = inMatrix._m13* inNum;
	inMatrix._m14 = inMatrix._m14* inNum;
	inMatrix._m15 = inMatrix._m15* inNum;

	return inMatrix;
}


/*
  _____  _       _     _             
 |  __ \(_)     (_)   (_)            
 | |  | |___   ___ ___ _  ___  _ __  
 | |  | | \ \ / / / __| |/ _ \| '_ \ 
 | |__| | |\ V /| \__ \ | (_) | | | |
 |_____/|_| \_/ |_|___/_|\___/|_| |_|
*/
Matrix Matrix::operator / (Matrix &inMatrix)
{
	ShutUP(inMatrix);

	return *this;
}

void Matrix::operator /= (const float &inNum)
{
	this->_m0 = this->_m0 / inNum;
	this->_m1 = this->_m1 / inNum;
	this->_m2 = this->_m2 / inNum;
	this->_m3 = this->_m3 / inNum;

	this->_m4 = this->_m4 / inNum;
	this->_m5 = this->_m5 / inNum;
	this->_m6 = this->_m6 / inNum;
	this->_m7 = this->_m7 / inNum;

	this->_m8 = this->_m8 / inNum;
	this->_m9 = this->_m9 / inNum;
	this->_m10 = this->_m10 / inNum;
	this->_m11 = this->_m11 / inNum;

	this->_m12 = this->_m12 / inNum;
	this->_m13 = this->_m13 / inNum;
	this->_m14 = this->_m14 / inNum;
	this->_m15 = this->_m15 / inNum;

}

void Matrix::operator /= (const Matrix &t)
{
	float x = this->_m0;
	float y = this->_m1;
	float z = this->_m2;
	float w = this->_m3;

	this->_m0 = x / t._m0 + y / t._m4 + z / t._m8 + w / t._m12;
	this->_m1 = x / t._m1 + y / t._m5 + z / t._m9 + w / t._m13;
	this->_m2 = x / t._m2 + y / t._m6 + z / t._m10 + w / t._m14;
	this->_m3 = x / t._m3 + y / t._m7 + z / t._m11 + w / t._m15;

	x = this->_m4;
	y = this->_m5;
	z = this->_m6;
	w = this->_m7;

	this->_m4 = x / t._m0 + y / t._m4 + z / t._m8 + w / t._m12;
	this->_m5 = x / t._m1 + y / t._m5 + z / t._m9 + w / t._m13;
	this->_m6 = x / t._m2 + y / t._m6 + z / t._m10 + w / t._m14;
	this->_m7 = x / t._m3 + y / t._m7 + z / t._m11 + w / t._m15;

	x = this->_m8;
	y = this->_m9;
	z = this->_m10;
	w = this->_m11;

	this->_m8 = x / t._m0 + y / t._m4 + z / t._m8 + w / t._m12;
	this->_m9 = x / t._m1 + y / t._m5 + z / t._m9 + w / t._m13;
	this->_m10 = x / t._m2 + y / t._m6 + z / t._m10 + w / t._m14;
	this->_m11 = x / t._m3 + y / t._m7 + z / t._m11 + w / t._m15;

	x = this->_m12;
	y = this->_m13;
	z = this->_m14;
	w = this->_m15;


	this->_m12 = x / t._m0 + y / t._m4 + z / t._m8 + w / t._m12;
	this->_m13 = x / t._m1 + y / t._m5 + z / t._m9 + w / t._m13;
	this->_m14 = x / t._m2 + y / t._m6 + z / t._m10 + w / t._m14;
	this->_m15 = x / t._m3 + y / t._m7 + z / t._m11 + w / t._m15;
}

/*
  _    _ _   _ _   ____              _     
 | |  | | | (_) | |  _ \            | |    
 | |  | | |_ _| | | |_) | ___   ___ | |___ 
 | |  | | __| | | |  _ < / _ \ / _ \| / __|
 | |__| | |_| | | | |_) | (_) | (_) | \__ \
  \____/ \__|_|_| |____/ \___/ \___/|_|___/
*/
bool Matrix::isIdentity(float tolerance)
{
	if (
		Util::isOne(this->_m0, tolerance) &&
		Util::isZero(this->_m1, tolerance) &&
		Util::isZero(this->_m2, tolerance) &&
		Util::isZero(this->_m3, tolerance) &&
		Util::isZero(this->_m4, tolerance) &&
		Util::isOne(this->_m5, tolerance) &&
		Util::isZero(this->_m6, tolerance) &&
		Util::isZero(this->_m7, tolerance) &&
		Util::isZero(this->_m8, tolerance) &&
		Util::isZero(this->_m9, tolerance) &&
		Util::isOne(this->_m10, tolerance) &&
		Util::isZero(this->_m11, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Matrix::isEqual(Matrix other, const float tolerance)
{
	if (
		Util::isEqual(this->_m0, other._m0, tolerance) &&
		Util::isEqual(this->_m1, other._m1, tolerance) &&
		Util::isEqual(this->_m2, other._m2, tolerance) &&
		Util::isEqual(this->_m3, other._m3, tolerance) &&
		Util::isEqual(this->_m4, other._m4, tolerance) &&
		Util::isEqual(this->_m5, other._m5, tolerance) &&
		Util::isEqual(this->_m6, other._m6, tolerance) &&
		Util::isEqual(this->_m7, other._m7, tolerance) &&
		Util::isEqual(this->_m8, other._m8, tolerance) &&
		Util::isEqual(this->_m9, other._m9, tolerance) &&
		Util::isEqual(this->_m10, other._m10, tolerance) &&
		Util::isEqual(this->_m11, other._m11, tolerance) &&
		Util::isEqual(this->_m12, other._m12, tolerance) &&
		Util::isEqual(this->_m13, other._m13, tolerance) &&
		Util::isEqual(this->_m14, other._m14, tolerance) &&
		Util::isEqual(this->_m15, other._m15, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Matrix::isNotEqual(Matrix other, const float tolerance)
{
	if (
		Util::isNotEqual(this->_m0, other._m0, tolerance) &&
		Util::isNotEqual(this->_m1, other._m1, tolerance) &&
		Util::isNotEqual(this->_m2, other._m2, tolerance) &&
		Util::isNotEqual(this->_m3, other._m3, tolerance) &&
		Util::isNotEqual(this->_m4, other._m4, tolerance) &&
		Util::isNotEqual(this->_m5, other._m5, tolerance) &&
		Util::isNotEqual(this->_m6, other._m6, tolerance) &&
		Util::isNotEqual(this->_m7, other._m7, tolerance) &&
		Util::isNotEqual(this->_m8, other._m8, tolerance) &&
		Util::isNotEqual(this->_m9, other._m9, tolerance) &&
		Util::isNotEqual(this->_m10, other._m10, tolerance) &&
		Util::isNotEqual(this->_m11, other._m11, tolerance) &&
		Util::isNotEqual(this->_m12, other._m12, tolerance) &&
		Util::isNotEqual(this->_m13, other._m13, tolerance) &&
		Util::isNotEqual(this->_m14, other._m14, tolerance) &&
		Util::isNotEqual(this->_m15, other._m15, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
  ______                _   _                 
 |  ____|              | | (_)                
 | |__ _   _ _ __   ___| |_ _  ___  _ __  ___ 
 |  __| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 | |  | |_| | | | | (__| |_| | (_) | | | \__ \
 |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/                                      
*/
float Matrix::det()
{
	float ta = ((this->_m10*this->_m15) - (this->_m11* this->_m14));
	float tb = ((this->_m9 *this->_m15) - (this->_m11* this->_m13));
	float tc = ((this->_m9 *this->_m14) - (this->_m10* this->_m13));
	float td = ((this->_m8 *this->_m15) - (this->_m11* this->_m12));
	float te = ((this->_m8 *this->_m13) - (this->_m9* this->_m12));
	float tf = ((this->_m8 *this->_m14) - (this->_m10* this->_m12));


	return ((this->_m0 * (((this->_m5 * ta) - (this->_m6 * tb)) + (this->_m7 * tc)))
		- (this->_m1 * (((this->_m4 * ta) - (this->_m6 * td)) + (this->_m7 * tf)))
		+ (this->_m2 * (((this->_m4 * tb) - (this->_m5 * td)) + (this->_m7 * te)))
		- (this->_m3 * (((this->_m4 * tc) - (this->_m5 * tf)) + (this->_m6 * te)))
		);

}

void Matrix::T()
{
	float temp;

	temp = _m1;
	this->_m1 = this->_m4;
	this->_m4 = temp;

	temp = _m2;
	this->_m2 = this->_m8;
	this->_m8 = temp;

	temp = _m3;
	this->_m3 = this->_m12;
	this->_m12 = temp;

	temp = _m6;
	this->_m6 = this->_m9;
	this->_m9 = temp;

	temp = _m7;
	this->_m7 = this->_m13;
	this->_m13 = temp;

	temp = _m11;
	this->_m11 = this->_m14;
	this->_m14 = temp;
}

Matrix Matrix::getT()
{
	Matrix tempMatrix = *this;

	float temp;

	temp = _m1;
	tempMatrix._m1 = tempMatrix._m4;
	tempMatrix._m4 = temp;

	temp = _m2;
	tempMatrix._m2 = tempMatrix._m8;
	tempMatrix._m8 = temp;

	temp = _m3;
	tempMatrix._m3 = tempMatrix._m12;
	tempMatrix._m12 = temp;

	temp = _m6;
	tempMatrix._m6 = tempMatrix._m9;
	tempMatrix._m9 = temp;

	temp = _m7;
	tempMatrix._m7 = tempMatrix._m13;
	tempMatrix._m13 = temp;

	temp = _m11;
	tempMatrix._m11 = tempMatrix._m14;
	tempMatrix._m14 = temp;

	return tempMatrix;
}

void Matrix::inv()
{
	Matrix temp;
	float deter = this->det();
	if (fabs(deter) < 0.0001)
	{
		// do nothing, Matrix is not invertable
		temp.set(ZERO);
	}
	else
	{
		float b0 = (_m5*((_m10*_m15) - (_m11*_m14))) - (_m6*((_m9*_m15) - (_m11*_m13))) + (_m7*((_m9*_m14) - (_m10*_m13)));
		float b1 = -((_m1*((_m10*_m15) - (_m11*_m14))) - (_m2*((_m9*_m15) - (_m11*_m13))) + (_m3*((_m9*_m14) - (_m10*_m13))));
		//float b2 = (_m1*((_m6* _m15) - (_m7* _m14))) - (_m2*((_m4*_m15) - (_m7* _m13))) + (_m3*((_m5*_m14) - (_m6* _m13)));

		float b2 = ((_m2*_m7*_m13) - (_m3*_m6*_m13) + (_m3*_m5*_m14) - (_m1*_m7*_m14) - (_m2 * _m5* _m15) + (_m1*_m6*_m15));

		float b3 = -((_m1*((_m6* _m11) - (_m7* _m10))) - (_m2*((_m5*_m11) - (_m7* _m9))) + (_m3*((_m5*_m10) - (_m6* _m9))));
		float b4 = -((_m4*((_m10*_m15) - (_m11*_m14))) - (_m6*((_m8*_m15) - (_m11*_m12))) + (_m7*((_m8*_m14) - (_m10*_m12))));
		float b5 = (_m0*((_m10*_m15) - (_m11*_m14))) - (_m2*((_m8*_m15) - (_m11*_m12))) + (_m3*((_m8*_m14) - (_m10*_m12)));
		//float b6 = -((_m0*((_m6* _m15) - (_m7* _m14))) - (_m2*((_m4*_m15) - (_m7* _m13))) + (_m3*((_m4*_m14) - (_m6* _m13))));

		float b6 = ((_m3*_m6*_m12) - (_m2*_m7*_m12) - (_m3*_m4*_m14) + (_m0*_m7*_m14) + (_m2 * _m4* _m15) - (_m0*_m6*_m15));

		float b7 = (_m0*((_m6* _m11) - (_m7* _m10))) - (_m2*((_m4*_m11) - (_m7 *_m8))) + (_m3*((_m4*_m10) - (_m6* _m8)));
		float b8 = (_m4*((_m9* _m15) - (_m11*_m13))) - (_m5*((_m8*_m15) - (_m11*_m12))) + (_m7*((_m8*_m13) - (_m9* _m12)));
		float b9 = -((_m0*((_m9* _m15) - (_m11*_m13))) - (_m1*((_m8*_m15) - (_m11*_m12))) + (_m3*((_m8*_m13) - (_m9* _m12))));
		//float b10 = (_m0*((_m5* _m15) - (_m7* _m13))) - (_m1*((_m4*_m15) - (_m7* _m13))) + (_m3*((_m4*_m14) - (_m5* _m13)));

		float b10 = ((_m1*_m7*_m12) - (_m3*_m5*_m12) + (_m3*_m4*_m13) - (_m0*_m7*_m13) - (_m1 * _m4* _m15) + (_m0*_m5*_m15));

		float b11 = -((_m0*((_m5* _m11) - (_m7* _m9))) - (_m1*((_m4*_m11) - (_m7* _m8))) + (_m3*((_m4*_m9) - (_m5* _m8))));
		float b12 = -((_m4*((_m9* _m14) - (_m10*_m13))) - (_m5*((_m8*_m14) - (_m10*_m12))) + (_m6*((_m8*_m13) - (_m9* _m12))));
		float b13 = (_m0*((_m9* _m14) - (_m10*_m13))) - (_m1*((_m8*_m14) - (_m10*_m12))) + (_m2*((_m8*_m13) - (_m9* _m12)));
		//float b14 = -((_m0*((_m5* _m14) - (_m6* _m13))) - (_m1*((_m4*_m14) - (_m6* _m12))) + (_m3*((_m4*_m13) - (_m5* _m12))));

		float b14 = ((_m2*_m5*_m12) - (_m1*_m6*_m12) - (_m2*_m4*_m13) + (_m0*_m6*_m13) + (_m1 * _m4* _m14) - (_m0*_m5*_m15));

		float b15 = (_m0*((_m5* _m10) - (_m6* _m9))) - (_m1*((_m4*_m10) - (_m6* _m8))) + (_m2*((_m4*_m9) - (_m5* _m8)));
		temp.set(
			Vect(b0, b1, b2, b3),
			Vect(b4, b5, b6, b7),
			Vect(b8, b9, b10, b11),
			Vect(b12, b13, b14, b15));

		temp /= deter;
	}

	*this = temp;
}

Matrix Matrix::getInv()
{
	Matrix temp;
	float deter = this->det();
	if (fabs(deter) < 0.0001)
	{
		// do nothing, Matrix is not invertable
		temp.set(ZERO);
	}
	else
	{
		float b0 = (_m5*((_m10*_m15) - (_m11*_m14))) - (_m6*((_m9*_m15) - (_m11*_m13))) + (_m7*((_m9*_m14) - (_m10*_m13)));
		float b1 = -((_m1*((_m10*_m15) - (_m11*_m14))) - (_m2*((_m9*_m15) - (_m11*_m13))) + (_m3*((_m9*_m14) - (_m10*_m13))));
		//float b2 = (_m1*((_m6* _m15) - (_m7* _m14))) - (_m2*((_m4*_m15) - (_m7* _m13))) + (_m3*((_m5*_m14) - (_m6* _m13)));

		float b2 = ((_m2*_m7*_m13) - (_m3*_m6*_m13) + (_m3*_m5*_m14) - (_m1*_m7*_m14) - (_m2 * _m5* _m15) + (_m1*_m6*_m15));

		float b3 = -((_m1*((_m6* _m11) - (_m7* _m10))) - (_m2*((_m5*_m11) - (_m7* _m9))) + (_m3*((_m5*_m10) - (_m6* _m9))));
		float b4 = -((_m4*((_m10*_m15) - (_m11*_m14))) - (_m6*((_m8*_m15) - (_m11*_m12))) + (_m7*((_m8*_m14) - (_m10*_m12))));
		float b5 = (_m0*((_m10*_m15) - (_m11*_m14))) - (_m2*((_m8*_m15) - (_m11*_m12))) + (_m3*((_m8*_m14) - (_m10*_m12)));
		//float b6 = -((_m0*((_m6* _m15) - (_m7* _m14))) - (_m2*((_m4*_m15) - (_m7* _m13))) + (_m3*((_m4*_m14) - (_m6* _m13))));

		float b6 = ((_m3*_m6*_m12) - (_m2*_m7*_m12) - (_m3*_m4*_m14) + (_m0*_m7*_m14) + (_m2 * _m4* _m15) - (_m0*_m6*_m15));

		float b7 = (_m0*((_m6* _m11) - (_m7* _m10))) - (_m2*((_m4*_m11) - (_m7 *_m8))) + (_m3*((_m4*_m10) - (_m6* _m8)));
		float b8 = (_m4*((_m9* _m15) - (_m11*_m13))) - (_m5*((_m8*_m15) - (_m11*_m12))) + (_m7*((_m8*_m13) - (_m9* _m12)));
		float b9 = -((_m0*((_m9* _m15) - (_m11*_m13))) - (_m1*((_m8*_m15) - (_m11*_m12))) + (_m3*((_m8*_m13) - (_m9* _m12))));
		//float b10 = (_m0*((_m5* _m15) - (_m7* _m13))) - (_m1*((_m4*_m15) - (_m7* _m13))) + (_m3*((_m4*_m14) - (_m5* _m13)));

		float b10 = ((_m1*_m7*_m12) - (_m3*_m5*_m12) + (_m3*_m4*_m13) - (_m0*_m7*_m13) - (_m1 * _m4* _m15) + (_m0*_m5*_m15));

		float b11 = -((_m0*((_m5* _m11) - (_m7* _m9))) - (_m1*((_m4*_m11) - (_m7* _m8))) + (_m3*((_m4*_m9) - (_m5* _m8))));
		float b12 = -((_m4*((_m9* _m14) - (_m10*_m13))) - (_m5*((_m8*_m14) - (_m10*_m12))) + (_m6*((_m8*_m13) - (_m9* _m12))));
		float b13 = (_m0*((_m9* _m14) - (_m10*_m13))) - (_m1*((_m8*_m14) - (_m10*_m12))) + (_m2*((_m8*_m13) - (_m9* _m12)));
		//float b14 = -((_m0*((_m5* _m14) - (_m6* _m13))) - (_m1*((_m4*_m14) - (_m6* _m12))) + (_m3*((_m4*_m13) - (_m5* _m12))));

		float b14 = ((_m2*_m5*_m12) - (_m1*_m6*_m12) - (_m2*_m4*_m13) + (_m0*_m6*_m13) + (_m1 * _m4* _m14) - (_m0*_m5*_m15));

		float b15 = (_m0*((_m5* _m10) - (_m6* _m9))) - (_m1*((_m4*_m10) - (_m6* _m8))) + (_m2*((_m4*_m9) - (_m5* _m8)));
		temp.set(
			Vect(b0, b1, b2, b3),
			Vect(b4, b5, b6, b7),
			Vect(b8, b9, b10, b11),
			Vect(b12, b13, b14, b15));

		temp /= deter;
	}

	return temp;
}

/*
   _____      _       
  / ____|    | |      
 | (___   ___| |_ ___ 
  \___ \ / _ \ __/ __|
  ____) |  __/ |_\__ \
 |_____/ \___|\__|___/            
*/
void Matrix::set(Matrix inMatrix)
{
	this->_v0 = inMatrix._v0;
	this->_v1 = inMatrix._v1;
	this->_v2 = inMatrix._v2;
	this->_v3 = inMatrix._v3;

	this->_m0 = _v0._vx;
	this->_m1 = _v0._vy;
	this->_m2 = _v0._vz;
	this->_m3 = _v0._vw;

	this->_m4 = _v1._vx;
	this->_m5 = _v1._vy;
	this->_m6 = _v1._vz;
	this->_m7 = _v1._vw;

	this->_m8 = _v2._vx;
	this->_m9 = _v2._vy;
	this->_m10 = _v2._vz;
	this->_m11 = _v2._vw;


	this->_m12 = _v3._vx;
	this->_m13 = _v3._vy;
	this->_m14 = _v3._vz;
	this->_m15 = _v3._vw;
}

void Matrix::set(Vect v0, Vect v1, Vect v2, Vect v3)
{
	this->_v0 = v0;
	this->_v1 = v1;
	this->_v2 = v2;
	this->_v3 = v3;

	this->_m0 = _v0._vx;
	this->_m1 = _v0._vy;
	this->_m2 = _v0._vz;
	this->_m3 = _v0._vw;

	this->_m4 = _v1._vx;
	this->_m5 = _v1._vy;
	this->_m6 = _v1._vz;
	this->_m7 = _v1._vw;

	this->_m8 = _v2._vx;
	this->_m9 = _v2._vy;
	this->_m10 = _v2._vz;
	this->_m11 = _v2._vw;


	this->_m12 = _v3._vx;
	this->_m13 = _v3._vy;
	this->_m14 = _v3._vz;
	this->_m15 = _v3._vw;
}

void Matrix::set(MatrixSpecialType type)
{

	if (type == MatrixSpecialType::IDENTITY)
	{
		this->_m0 = 1.0f;
		this->_m5 = 1.0f;
		this->_m10 = 1.0f;
		this->_m15 = 1.0f;
	}
	else if (type == MatrixSpecialType::ZERO)
	{
		this->_m0 = 0.0f;
		this->_m5 = 0.0f;
		this->_m10 = 0.0f;
		this->_m15 = 0.0f;
	}
	else
	{
		assert(0);
	}
	this->_m1 = 0.0f;
	this->_m2 = 0.0f;
	this->_m3 = 0.0f;

	this->_m4 = 0.0f;
	this->_m6 = 0.0f;
	this->_m7 = 0.0f;

	this->_m8 = 0.0f;
	this->_m9 = 0.0f;
	this->_m11 = 0.0f;
	this->_m12 = 0.0f;
	this->_m13 = 0.0f;
	this->_m14 = 0.0f;

	this->_v0 = Vect(_m0, _m1, _m2, _m3);
	this->_v1 = Vect(_m4, _m5, _m6, _m7);
	this->_v2 = Vect(_m8, _m9, _m10, _m11);
	this->_v3 = Vect(_m12, _m13, _m14, _m15);
}

void Matrix::set(MatrixTransType type, float inX, float inY, float inZ)
{
	if (type == MatrixTransType::TRANS)
	{
		this->set(IDENTITY);

		this->_m12 = inX;
		this->_m13 = inY;
		this->_m14 = inZ;
	}
}

void Matrix::set(MatrixTransType type, Vect inVect)
{
	if (type == MatrixTransType::TRANS)
	{
		this->set(IDENTITY);

		this->_m12 = inVect._vx;
		this->_m13 = inVect._vy;
		this->_m14 = inVect._vz;
	}
}

void Matrix::set(MatrixScaleType type, float inX, float inY, float inZ)
{
	if (type == MatrixScaleType::SCALE)
	{
		this->set(IDENTITY);

		this->_m0 = inX;
		this->_m5 = inY;
		this->_m10 = inZ;
	}
}

void Matrix::set(MatrixScaleType type, Vect inVect)
{
	if (type == MatrixScaleType::SCALE)
	{
		this->set(IDENTITY);

		this->_m0 = inVect._vx;
		this->_m5 = inVect._vy;
		this->_m10 = inVect._vz;
	}
}

void  Matrix::set(RotType type, float inFloat)
{
	float cosTemp = cosf(inFloat);
	float sinTemp = sinf(inFloat);

	if (type == RotType::ROT_X)
	{
		this->set(IDENTITY);

		this->_m5 = cosTemp;
		this->_m6 = sinTemp;
		this->_m9 = -sinTemp;
		this->_m10 = cosTemp;
	}
	else if (type == RotType::ROT_Y)
	{
		this->set(IDENTITY);

		this->_m0 = cosTemp;
		this->_m2 = -sinTemp;
		this->_m8 = sinTemp;
		this->_m10 = cosTemp;
	}

	else if (type == RotType::ROT_Z)
	{
		this->set(IDENTITY);

		this->_m0 = cosTemp;
		this->_m1 = sinTemp;
		this->_m4 = -sinTemp;
		this->_m5 = cosTemp;
	}
}
void  Matrix::set(MatrixRowType type, Vect &inVect)
{
	if (type == MatrixRowType::ROW_0)
	{
		this->_v0 = inVect;
	}
	else if (type == MatrixRowType::ROW_1)
	{
		this->_v1 = inVect;
	}
	else if (type == MatrixRowType::ROW_2)
	{
		this->_v2 = inVect;
	}
	else if (type == MatrixRowType::ROW_3)
	{
		this->_v3 = inVect;
	}
	else
	{
		assert(0);
		inVect = Vect(0, 0, 0, 0);
	}
}
void Matrix::set(Quat q)
{
	this->_m0 = 1 - 2 * ((q._qy*q._qy) + (q._qz*q._qz));
	this->_m1 = 2 * ((q._qx*q._qy) + (q._qw*q._qz));
	this->_m2 = 2 * ((q._qx*q._qz) - (q._qw*q._qy));
	this->_m3 = 0.0f;

	this->_m4 = 2 * ((q.qx()*q.qy()) - (q.qw()*q.qz()));
	this->_m5 = 1 - 2 * ((q.qx()*q.qx()) + (q.qz()*q.qz()));
	this->_m6 = 2 * ((q._qy * q._qz) + (q._qw*q._qx)); 
	this->_m7 = 0.0f;

	this->_m8 = 2 * ((q.qx()*q.qz()) + (q.qw()*q.qy()));
	this->_m9 = 2 * ((q._qy * q._qz) - (q._qw*q._qx));
	this->_m10 = 1 - 2 * ((q.qx()*q.qx()) + (q.qy()*q.qy()));
	this->_m11 = 0.0f;

	this->_m12 = 0.0f;
	this->_m13 = 0.0f;
	this->_m14 = 0.0f;
	this->_m15 = 1.0f;
}
void Matrix::set(Quat inQuat, Vect inVect, float inFloat) 
{
	ShutUP(inQuat);
	ShutUP(inVect);
	ShutUP(inFloat);
}

void Matrix::set(RotAxisAngleType type, Vect inVect, float inFloat)
{
	if (type == ROT_AXIS_ANGLE)
	{
		Quat tempQuat(type, inVect, inFloat);

		this->set(tempQuat);
	}
}
void Matrix::set(RotOrientType type, Vect &vect_dof, Vect &vect_up)
{
	if (type == ROT_ORIENT)
	{
		Vect rz = vect_dof.getNorm();
		rz._vw = 0.0f;

		Vect rx = vect_up.cross(rz);
		rx.norm();
		rx._vw = 0.0f;

		Vect ry = rz.cross(rx);
		ry.norm();
		ry._vw = 0.0f;

		this->set(rx, ry, rz, Vect(0.0f, 0.0f, 0.0f, 1.0f));

	}
	else if (type == RotOrientType::ROT_INVERSE_ORIENT)
	{
		Vect rz = vect_dof.getNorm();
		
		Vect rx = vect_up.cross(rz);
		rx.norm();

		Vect ry = rz.cross(rx);
		ry.norm();

		Vect vectTemp = Vect(0.0f, 0.0f, 0.0f, 1.0f);

		this->set(rx, ry, rz, vectTemp);
		this->T();
		this->set(ROW_3, vectTemp);
	}
}

void Matrix::set(Rot3AxisType type, const float inFloat1, const float inFloat2, const float inFloat3)
{
	if(type == Rot3AxisType::ROT_XYZ)
	{
		Quat tempQuat(type, inFloat1, inFloat2, inFloat3);

		this->set(tempQuat);
	}

}


/*
   _____      _       
  / ____|    | |      
 | |  __  ___| |_ ___ 
 | | |_ |/ _ \ __/ __|
 | |__| |  __/ |_\__ \
  \_____|\___|\__|___/
*/
Vect Matrix::get(MatrixRowType type)
{
	if (type == MatrixRowType::ROW_0)
	{
		return this->_v0;
	}
	else if (type == MatrixRowType::ROW_1)
	{
		return this->_v1;
	}
	else if (type == MatrixRowType::ROW_2)
	{
		return this->_v2;
	}
	else if (type == MatrixRowType::ROW_3)
	{
		return this->_v3;
	}
	else
	{
		assert(0);
		return Vect(0, 0, 0, 0);
	}

}

const float& Matrix::m0() const { return this->_m0; }
const float& Matrix::m1() const { return this->_m1; }
const float& Matrix::m2() const { return this->_m2; }
const float& Matrix::m3() const { return this->_m3; }
const float& Matrix::m4() const { return this->_m4; }
const float& Matrix::m5() const { return this->_m5; }
const float& Matrix::m6() const { return this->_m6; }
const float& Matrix::m7() const { return this->_m7; }
const float& Matrix::m8() const { return this->_m8; }
const float& Matrix::m9() const { return this->_m9; }
const float& Matrix::m10() const { return this->_m10; }
const float& Matrix::m11() const { return this->_m11; }
const float& Matrix::m12() const { return this->_m12; }
const float& Matrix::m13() const { return this->_m13; }
const float& Matrix::m14() const { return this->_m14; }
const float& Matrix::m15() const { return this->_m15; }

float& Matrix::m0() { return this->_m0; }
float& Matrix::m1() { return this->_m1; }
float& Matrix::m2() { return this->_m2; }
float& Matrix::m3() { return this->_m3; }
float& Matrix::m4() { return this->_m4; }
float& Matrix::m5() { return this->_m5; }
float& Matrix::m6() { return this->_m6; }
float& Matrix::m7() { return this->_m7; }
float& Matrix::m8() { return this->_m8; }
float& Matrix::m9() { return this->_m9; }
float& Matrix::m10() { return this->_m10; }
float& Matrix::m11() { return this->_m11; }
float& Matrix::m12() { return this->_m12; }
float& Matrix::m13() { return this->_m13; }
float& Matrix::m14() { return this->_m14; }
float& Matrix::m15() { return this->_m15; }

float Matrix::operator[] (m0_enum)  const { return this->_m0; }
float Matrix::operator[] (m1_enum)  const { return this->_m1; }
float Matrix::operator[] (m2_enum)  const { return this->_m2; }
float Matrix::operator[] (m3_enum)  const { return this->_m3; }
float Matrix::operator[] (m4_enum)  const { return this->_m4; }
float Matrix::operator[] (m5_enum)  const { return this->_m5; }
float Matrix::operator[] (m6_enum)  const { return this->_m6; }
float Matrix::operator[] (m7_enum)  const { return this->_m7; }
float Matrix::operator[] (m8_enum)  const { return this->_m8; }
float Matrix::operator[] (m9_enum)  const { return this->_m9; }
float Matrix::operator[] (m10_enum) const { return this->_m10; }
float Matrix::operator[] (m11_enum) const { return this->_m11; }
float Matrix::operator[] (m12_enum) const { return this->_m12; }
float Matrix::operator[] (m13_enum) const { return this->_m13; }
float Matrix::operator[] (m14_enum) const { return this->_m14; }
float Matrix::operator[] (m15_enum) const { return this->_m15; }

float& Matrix::operator[] (m0_enum) { return this->_m0; }
float& Matrix::operator[] (m1_enum) { return this->_m1; }
float& Matrix::operator[] (m2_enum) { return this->_m2; }
float& Matrix::operator[] (m3_enum) { return this->_m3; }
float& Matrix::operator[] (m4_enum) { return this->_m4; }
float& Matrix::operator[] (m5_enum) { return this->_m5; }
float& Matrix::operator[] (m6_enum) { return this->_m6; }
float& Matrix::operator[] (m7_enum) { return this->_m7; }
float& Matrix::operator[] (m8_enum) { return this->_m8; }
float& Matrix::operator[] (m9_enum) { return this->_m9; }
float& Matrix::operator[] (m10_enum) { return this->_m10; }
float& Matrix::operator[] (m11_enum) { return this->_m11; }
float& Matrix::operator[] (m12_enum) { return this->_m12; }
float& Matrix::operator[] (m13_enum) { return this->_m13; }
float& Matrix::operator[] (m14_enum) { return this->_m14; }
float& Matrix::operator[] (m15_enum) { return this->_m15; }
// ---  End of File ---------------

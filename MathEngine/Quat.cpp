//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#include <math.h>
#include <assert.h>

#include "MathEngine.h"
#define Shutup(v) ((void )v)

//Big Four
Quat::Quat()
{
	this->_qx = 0.0f;
	this->_qy = 0.0f;
	this->_qz = 0.0f;
	this->_qw = 1.0f;
}
Quat::Quat(const Quat &inQuat)
{
	_qx = inQuat._qx;
	_qy = inQuat._qy;
	_qz = inQuat._qz;
	_qw = inQuat._qw;
}

Quat Quat::operator = (const Quat &inQuat)
{
	_qx = inQuat._qx;
	_qy = inQuat._qy;
	_qz = inQuat._qz;
	_qw = inQuat._qw;
	return *this;
}

Quat::~Quat()
{

}

/*
   _____                _                   _                 
  / ____|              | |                 | |                
 | |     ___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __ ___ 
 | |    / _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__/ __|
 | |___| (_) | | | \__ \ |_| |  | |_| | (__| || (_) | |  \__ \
  \_____\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|  |___/
*/

Quat::Quat(float inX, float inY, float inZ, float inW) 
{
	this->set(inX, inY, inZ, inW);
}
Quat::Quat(Vect inVect, float w) 
{
	this->set(inVect.x(), inVect.y(), inVect.z(), w);
}
Quat::Quat(Matrix M) 
{
	this->set(M);
}
Quat::Quat(MatrixSpecialType type)
{
	this->set(type);
}
Quat::Quat(RotAxisAngleType rotType, const Vect &axis, float angle) 
{
	this->set(rotType, axis, angle);
}
Quat::Quat(RotOrientType rotType, Vect inVect1, Vect inVect2) 
{
	this->set(rotType, inVect1, inVect2);
}
Quat::Quat(RotType type, float angle)
{
	this->set(type, angle);
}
Quat::Quat(Rot3AxisType rotType, float inFloat1, float inFloat2, float inFloat3)
{
	this->set(rotType, inFloat1, inFloat2, inFloat3);

	//assert(this->isEqual(*this));
}

/*
             _     _ _ _   _             
     /\      | |   | (_) | (_)            
    /  \   __| | __| |_| |_ _  ___  _ __  
   / /\ \ / _` |/ _` | | __| |/ _ \| '_ \ 
  / ____ \ (_| | (_| | | |_| | (_) | | | |
 /_/    \_\__,_|\__,_|_|\__|_|\___/|_| |_|
*/
Quat Quat::operator + (Quat &inQuat) 
{
	return Quat(this->qx() + inQuat.qx(), this->qy() + inQuat.qy(), this->qz() + inQuat.qz(), this->qw() + inQuat.qw());
}
Quat Quat::operator + () const
{
	return Quat(this->qx(), this->qy(), this->qz(), this->qw());
}
void Quat::operator += (const Quat &inQuat) 
{
	this->qx() = this->qx() + inQuat.qx();
	this->qy() = this->qy() + inQuat.qy();
	this->qz() = this->qz() + inQuat.qz();
	this->qw() = this->qw() + inQuat.qw();
}

Quat Quat::operator + (float inFloat)
{
	return Quat(this->qx() + inFloat, this->qy() + inFloat, this->qz() + inFloat, this->qw() + inFloat);
}
Quat Quat::operator += (float inFloat)
{
	this->qx() = this->qx() + inFloat;
	this->qy() = this->qy() + inFloat;
	this->qz() = this->qz() + inFloat;
	this->qw() = this->qw() + inFloat;

	return *this;
}

Quat operator+(float inFloat, const Quat &inQuat)
{
	return Quat(inQuat.qx() + inFloat, inQuat.qy() + inFloat, inQuat.qz() + inFloat, inQuat.qw() + inFloat);

}

/*
   _____       _     _                  _   _             
  / ____|     | |   | |                | | (_)            
 | (___  _   _| |__ | |_ _ __ __ _  ___| |_ _  ___  _ __  
  \___ \| | | | '_ \| __| '__/ _` |/ __| __| |/ _ \| '_ \ 
  ____) | |_| | |_) | |_| | | (_| | (__| |_| | (_) | | | |
 |_____/ \__,_|_.__/ \__|_|  \__,_|\___|\__|_|\___/|_| |_|
*/
Quat Quat::operator - (Quat &inQuat)
{
	return Quat(this->qx() - inQuat.qx(), this->qy() - inQuat.qy(), this->qz() - inQuat.qz(), this->qw() - inQuat.qw());
}
Quat Quat::operator - () const
{
	return Quat(-this->qx(), -this->qy(), -this->qz(), -this->qw());
}
void Quat::operator -= (const Quat &inQuat)
{
	this->qx() = this->qx() - inQuat.qx();
	this->qy() = this->qy() - inQuat.qy();
	this->qz() = this->qz() - inQuat.qz();
	this->qw() = this->qw() - inQuat.qw();
}

Quat Quat::operator - (float inFloat)
{
	return Quat(this->qx() - inFloat, this->qy() - inFloat, this->qz() - inFloat, this->qw() - inFloat);
}
Quat Quat::operator -= (float inFloat)
{
	this->qx() = this->qx() - inFloat;
	this->qy() = this->qy() - inFloat;
	this->qz() = this->qz() - inFloat;
	this->qw() = this->qw() - inFloat;

	return *this;
}

Quat operator-(float inFloat, const Quat &inQuat)
{
	return Quat(inFloat - inQuat.qx(), inFloat - inQuat.qy(), inFloat - inQuat.qz(), inFloat - inQuat.qw());

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

Quat Quat::operator * (const Quat &inQuat) 
{
	Vect pVect(this->_qx, this->_qy, this->_qz, this->_qw);
	Vect qVect(inQuat._qx, inQuat._qy, inQuat._qz, inQuat._qw);

	const float pScalar = this->_qw;
	const float qScalar = inQuat._qw;

	Vect temp1(qVect);
	
	temp1 = temp1.cross(pVect);

	Vect temp2( qScalar * pVect);
	Vect temp3( pScalar * qVect);

	Vect temp4(pVect);

	return Quat((temp1.x() + temp2.x() + temp3.x()),
		(temp1.y() + temp2.y() + temp3.y()),
		(temp1.z() + temp2.z() + temp3.z()),
		qScalar * pScalar - (qVect.dot(pVect)));

}
Quat Quat::operator * (const float inFloat)
{
	return Quat(this->qx() * inFloat, this->qy() * inFloat, this->qz() * inFloat, this->qw() * inFloat);
}
void Quat::operator *= (Quat &inQuat) 
{
	Vect pVect(this->_qx, this->_qy, this->_qz, this->_qw);
	Vect qVect(inQuat._qx, inQuat._qy, inQuat._qz, inQuat._qw);

	const float pScalar = this->_qw;
	const float qScalar = inQuat._qw;

	Vect temp1(qVect);

	temp1 = temp1.cross(pVect);

	Vect temp2(qScalar * pVect);
	Vect temp3(pScalar * qVect);

	Vect temp4(pVect);

	this->set((temp1.x() + temp2.x() + temp3.x()),
		(temp1.y() + temp2.y() + temp3.y()),
		(temp1.z() + temp2.z() + temp3.z()),
		qScalar * pScalar - (qVect.dot(pVect)));
}
void Quat::operator *= (const float &inNum) 
{
	this->_qx *= inNum;
	this->_qy *= inNum;
	this->_qz *= inNum;
	this->_qw *= inNum;
}
Quat operator*(float inFloat, const Quat &inQuat)
{
	return Quat(inFloat * inQuat.qx(), inFloat * inQuat.qy(), inFloat * inQuat.qz(), inFloat * inQuat.qw());

}
Quat Quat::operator * (Vect &inVect) 
{
	Shutup(inVect);

	//Quat temp2(0, 0, 0, 0);
	//temp2.set(*this * inVect * this->getConj());

	return Quat();
}
Quat Quat::operator *= (Vect &inVect) 
{
	Shutup(inVect);
	return Quat(IDENTITY);
}

Matrix Quat::operator * (Matrix inMatrix)
{
	//Matrix temp(inQuat);
	//return(*this * temp);

	Matrix temp(*this);
	return(temp * inMatrix);
}

void Quat::operator *= (Matrix inMatrix)
{
	Quat temp(inMatrix);
	*this*=temp;
		
	//if (this->_qw < 0.0f) {
	//	*this *= -1.0f;
	//}
}

Quat Quat::multByElement(Quat &inQuat)
{
	return Quat(this->qx() * inQuat.qx(), this->qy() * inQuat.qy(), this->qz() * inQuat.qz(), this->qw() * inQuat.qw());
}


/*
  _____  _       _     _             
 |  __ \(_)     (_)   (_)            
 | |  | |___   ___ ___ _  ___  _ __  
 | |  | | \ \ / / / __| |/ _ \| '_ \ 
 | |__| | |\ V /| \__ \ | (_) | | | |
 |_____/|_| \_/ |_|___/_|\___/|_| |_|
*/
Quat Quat::operator / (const Quat &inQuat)
{
	return Quat(this->qx() / inQuat.qx(), this->qy() / inQuat.qy(), this->qz() / inQuat.qz(), this->qw() / inQuat.qw());

}
Quat Quat::operator / (const float inFloat)
{
	return Quat(this->qx() / inFloat, this->qy() / inFloat, this->qz() / inFloat, this->qw() / inFloat);

}
void Quat::operator /= (Quat &inQuat)
{
	this->_qx /= inQuat._qx;
	this->_qy /= inQuat._qy;
	this->_qz /= inQuat._qz;
	this->_qw /= inQuat._qw;
}
void Quat::operator /= (const float &inNum)
{
	this->_qx /= inNum;
	this->_qy /= inNum;
	this->_qz /= inNum;
	this->_qw /= inNum;
}
Quat operator/(float inFloat, const Quat &inQuat)
{
	return Quat(inFloat / inQuat.qx(), inFloat / inQuat.qy(), inFloat / inQuat.qz(), inFloat / inQuat.qw());

}
Quat Quat::operator / (Vect &inVect)
{
	Shutup(inVect);
	return Quat(IDENTITY);
}
Quat Quat::operator /= (Vect &inVect)
{
	Shutup(inVect);
	return Quat(IDENTITY);
}
Quat Quat::operator / (Matrix &inMatrix)
{
	Shutup(inMatrix);
	return Quat(IDENTITY);
}
Quat Quat::operator /= (Matrix &inMatrix)
{
	Shutup(inMatrix);
	return Quat(IDENTITY);
}


/*
  _    _ _   _ _   ____              _     
 | |  | | | (_) | |  _ \            | |    
 | |  | | |_ _| | | |_) | ___   ___ | |___ 
 | |  | | __| | | |  _ < / _ \ / _ \| / __|
 | |__| | |_| | | | |_) | (_) | (_) | \__ \
  \____/ \__|_|_| |____/ \___/ \___/|_|___/
*/
bool Quat::isIdentity(float tolerance)
{
	if (
		Util::isZero(this->_qx, tolerance) &&
		Util::isZero(this->_qy, tolerance) &&
		Util::isZero(this->_qz, tolerance) &&
		 Util::isOne(this->_qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Quat::isZero(float tolerance)
{
	if (
		Util::isZero(this->_qx, tolerance) &&
		Util::isZero(this->_qy, tolerance) &&
		Util::isZero(this->_qz, tolerance) &&
		Util::isZero(this->_qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Quat::isEqual(Quat other, const float tolerance)
{
	if (
		Util::isEqual(this->_qx, other._qx, tolerance) &&
		Util::isEqual(this->_qy, other._qy, tolerance) &&
		Util::isEqual(this->_qz, other._qz, tolerance) &&
		Util::isEqual(this->_qw, other._qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Quat::isConjugateEqual(Quat other, const float tolerance)
{
	if (
		Util::isEqual(this->_qx, -other._qx, tolerance) &&
		Util::isEqual(this->_qy, -other._qy, tolerance) &&
		Util::isEqual(this->_qz, -other._qz, tolerance) &&
		Util::isEqual(this->_qw, other._qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Quat::isNegEqual(Quat other, const float tolerance)
{
	if (
		Util::isEqual(this->_qx, -other._qx, tolerance) &&
		Util::isEqual(this->_qy, -other._qy, tolerance) &&
		Util::isEqual(this->_qz, -other._qz, tolerance) &&
		Util::isEqual(this->_qw, -other._qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool  Quat::isEquivalent(Quat other, const float tolerance)
{
	if (
		Util::isEqual(this->_qx, other._qx, tolerance) &&
		Util::isEqual(this->_qy, other._qy, tolerance) &&
		Util::isEqual(this->_qz, other._qz, tolerance) &&
		Util::isEqual(this->_qw, other._qw, tolerance))
	{
		return true;
	}
	else if (
		Util::isEqual(this->_qx, -other._qx, tolerance) &&
		Util::isEqual(this->_qy, -other._qy, tolerance) &&
		Util::isEqual(this->_qz, -other._qz, tolerance) &&
		Util::isEqual(this->_qw, -other._qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Quat::isNotEqual(Quat other, const float tolerance)
{
	if (
		Util::isNotEqual(this->_qx, other._qx, tolerance) &&
		Util::isNotEqual(this->_qy, other._qy, tolerance) &&
		Util::isNotEqual(this->_qz, other._qz, tolerance) &&
		Util::isNotEqual(this->_qw, other._qw, tolerance))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Quat::isNormalized(float tolerance)
{
	
	if (Util::isEqual(this->mag(), 1, tolerance))
	{
		return true;
	}
	return false;
}

/*
  ______                _   _                 
 |  ____|              | | (_)                
 | |__ _   _ _ __   ___| |_ _  ___  _ __  ___ 
 |  __| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 | |  | |_| | | | | (__| |_| | (_) | | | \__ \
 |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/                                      
*/
Quat Quat::getConj()
{
	return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
}
void Quat::conj()
{
	this->_qx = -this->_qx;
	this->_qy = -this->_qy;
	this->_qz = -this->_qz;

}
Quat Quat::getT()
{
	return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);

}
void Quat::T()
{
	this->_qx = -this->_qx;
	this->_qy = -this->_qy;
	this->_qz = -this->_qz;
}

float Quat::mag()
{
	return sqrtf((this->qx() * this->qx()) + (this->qy() * this->qy()) + (this->qz() * this->qz()) + (this->qw() * this->qw()));
}
float Quat::magSquared()
{
	return this->mag() * this->mag();
}
float Quat::invMag() 
{
	return this->getInv().mag();
}
float Quat::dot(Quat &inQuat)
{
	return ((this->qx() * inQuat.qx()) + (this->qy() * inQuat.qy()) + (this->qz() * inQuat.qz()) + (this->qw() * inQuat.qw()));

}
Quat Quat::norm()
{
	float mag = this->mag();

	this->_qx /= mag;
	this->_qy /= mag;
	this->_qz /= mag;
	this->_qw /= mag;

	return *this;
}

Quat Quat::getNorm()
{
	float mag = this->mag();

	return Quat(this->qx() / mag, this->qy() / mag, this->qz() / mag, this->qw() / mag);
}

void Quat::inv()
{
	if (this->isNormalized(0.1f))
	{
		this->conj();
	}
	else
	{

		Quat temp = this->getConj();

		Quat temp2 = *this * temp;

		*this /= temp2._qw;

		this->conj();
	}
}

Quat Quat::getInv()
{
	if (this->isNormalized(0.1f))
	{
		return(this->getConj());
	}
	else
	{
		Quat conj = this->getConj();

		Quat temp = *this;

		temp = *this * conj;

		return((*this / temp._qw).getConj());
	}
}

void Quat::Lqcvq(const Vect V, Vect &vOut)
{
	float qw = this->_qw;
	Vect qV(this->_qx, this->_qy, this->_qz);

	Vect out1 = (2 *qw) * (qV.cross(V));
	float tempFloat = qV.dot(qV);
	Vect out2 = ((qw * qw) - tempFloat) * V;

	Vect out3 = (2 * (qV.dot(V))) * qV;

	vOut = out1 + out2 + out3;
}

void Quat::Lqvqc(Vect V, Vect &vOut)
{
	float qw = this->_qw;
	Vect qV(this->_qx, this->_qy, this->_qz);

	Vect out1 = (2 * qw) * (V.cross(qV));
	float tempFloat = qV.dot(qV);
	Vect out2 = ((qw * qw) - tempFloat) * V;

	Vect out3 = (2 * (qV.dot(V))) * qV;

	vOut = out1 + out2 + out3;
	
}

/*
   _____      _       
  / ____|    | |      
 | (___   ___| |_ ___ 
  \___ \ / _ \ __/ __|
  ____) |  __/ |_\__ \
 |_____/ \___|\__|___/            
*/

void Quat::set(float inX, float inY, float inZ, float inW)
{
	this->_qx = inX;
	this->_qy = inY;
	this->_qz = inZ;
	this->_qw = inW;
}
void Quat::set(Vect inVect, float w) 
{
	this->_qx = inVect.x();
	this->_qy = inVect.y();
	this->_qz = inVect.z();
	this->_qw = w;
}
void Quat::set(Matrix M) 
{
	float tr = M.m0() + M.m5() + M.m10();
	float S;
	if (tr > 0.0f)
	{
		S = 2 * sqrtf(tr + 1.0f);
		this->_qw = 0.25f * S;
		this->_qx = -(M.m9() - M.m6()) / S;
		this->_qy = -(M.m2() - M.m8()) / S;
		this->_qz = -(M.m4() - M.m1()) / S;
	}
	else if ((M.m0() > M.m5()) && (M.m0() > M.m10()))
	{
		S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
		this->_qw = -(M.m9() - M.m6()) / S;
		this->_qx = 0.25f * S;
		this->_qy = (M.m1() + M.m4()) / S;
		this->_qz = (M.m2() + M.m8()) / S;
	}
	else if (M.m5() > M.m10())
	{
		S = 2 * sqrtf(1.0f + M.m5() - M.m0() - M.m10());
		this->_qw = -(M.m2() - M.m8()) / S;
		this->_qx = (M.m1() + M.m4()) / S;
		this->_qy = 0.25f * S;
		this->_qz = (M.m6() + M.m9()) / S;
	}
	else
	{
		S = 2 * sqrtf(1.0f + M.m10() - M.m0() - M.m5());
		this->_qw = -(M.m4() - M.m1()) / S;
		this->_qx = (M.m2() + M.m8()) / S;
		this->_qy = (M.m6() + M.m9()) / S;
		this->_qz = 0.25f * S;
	}
}

void Quat::set(MatrixSpecialType inMatrix)
{

	if (inMatrix == IDENTITY)
	{

		this->qx() = 0.0f;
		this->qy() = 0.0f;
		this->qz() = 0.0f;
		this->qw() = 1.0f;
	}
	else if (inMatrix == ZERO)
	{

		this->qx() = 0.0f;
		this->qy() = 0.0f;
		this->qz() = 0.0f;
		this->qw() = 0.0f;
	}
}
void Quat::set(const RotType rotType, const float angle)
{

	Vect temp(0.0f, 0.0f, 0.0f);

	if (rotType == RotType::ROT_X)
	{
		temp.x() = 1.0f;
	}
	else if (rotType == RotType::ROT_Y)
	{
		temp.y() = 1.0f;
	}
	else if (rotType == RotType::ROT_Z)
	{
		temp.z() = 1.0f;
	}

	const float angle_a = angle * 0.5f;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_a);
	sin_a = sinf(angle_a);

	//temp.norm();
	temp *= sin_a;

	this->_qx = temp[x];
	this->_qy = temp[y];
	this->_qz = temp[z];
	this->_qw = cos_a;
}
void Quat::set(const RotAxisAngleType rotType, const float angle)
{
	Vect temp(0.0f, 0.0f, 0.0f);

	if (rotType == RotType::ROT_X)
	{
		temp.x() = 1.0f;
	}
	else if (rotType == RotType::ROT_Y)
	{
		temp.y() = 1.0f;
	}
	else if (rotType == RotType::ROT_Z)
	{
		temp.z() = 1.0f;
	}

	const float angle_a = angle * 0.5f;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_a);
	sin_a = sinf(angle_a);

	temp.norm();
	temp *= sin_a;

	this->_qx = temp[x];
	this->_qy = temp[y];
	this->_qz = temp[z];
	this->_qw = cos_a;
}

void Quat::set(const RotAxisAngleType type, const Vect &axis, const float angle)
{
	Shutup(type);

	const float angle_a = angle * 0.5f;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_a);
	sin_a = sinf(angle_a);

	Vect qV = axis;
	qV.norm();
	qV *= sin_a;

	this->_qx = qV[x];
	this->_qy = qV[y];
	this->_qz = qV[z];
	this->_qw = cos_a;
}

void Quat::set(const Rot3AxisType type, const float rx, const float ry, const float rz)
{
	if (type == Rot3AxisType::ROT_XYZ)
	{
		this->_qx = 0.0f;
		this->_qy = 0.0f;
		this->_qz = 0.0f;
		this->_qw = 1.0f;

		Quat qx(ROT_X, rx);
		Quat qy(ROT_Y, ry);
		Quat qz(ROT_Z, rz);

		Quat qtmp;

		qtmp = qx * qy * qz;
		this->set(qtmp.qx(), qtmp.qy(), qtmp.qz(), qtmp.qw());
	}
}

void Quat::set(const RotOrientType type, Vect &vect_dof, Vect & vect_up)
{
	Matrix temp(IDENTITY);
	temp.set(type, vect_dof, vect_up);
	this->set(temp);
}

void Quat::setVect(Vect inVect) 
{
	this->_qx = inVect.x();
	this->_qy = inVect.y();
	this->_qz = inVect.z();
}

void Quat::getVect(Vect &inVect)
{
	inVect.x() = this->_qx;
	inVect.y() = this->_qy;
	inVect.z() = this->_qz;
}

float Quat::getAngle() 
{
	float temp = acosf(this->_qw);
	return temp * 2;
}
void Quat::getAxis(Vect &inVect)
{
	inVect.x() = this->_qx;
	inVect.y() = this->_qy;
	inVect.z() = this->_qz;
}

/*
   _____      _       
  / ____|    | |      
 | |  __  ___| |_ ___ 
 | | |_ |/ _ \ __/ __|
 | |__| |  __/ |_\__ \
  \_____|\___|\__|___/
*/
float Quat::operator[] (x_enum) const { return this->_qx; }
float Quat::operator[] (y_enum) const { return this->_qy; }
float Quat::operator[] (z_enum) const { return this->_qz; }
float Quat::operator[] (w_enum) const { return this->_qw; }

float& Quat::operator[] (x_enum) { return this->_qx; }
float& Quat::operator[] (y_enum) { return this->_qy; }
float& Quat::operator[] (z_enum) { return this->_qz; }
float& Quat::operator[] (w_enum) { return this->_qw; }

float& Quat::qx() { return this->_qx; }
float& Quat::qy() { return this->_qy; }
float& Quat::qz() { return this->_qz; }
float& Quat::qw() { return this->_qw; }
float& Quat::real() { return this->_qw; }

const float& Quat::qx() const { return this->_qx; }
const float& Quat::qy() const { return this->_qy; }
const float& Quat::qz() const { return this->_qz; }
const float& Quat::qw() const { return this->_qw; }
const float& Quat::real() const { return this->_qw; }


// ---  End of File ---------------



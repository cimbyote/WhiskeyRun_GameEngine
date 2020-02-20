//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam575
//----------------------------------------------------------------------------- 

#include <math.h>

#include "MathEngine.h"
#define ShutUP(v) ((void )v)

// Do your magic here
Vect::Vect()
{
	this->_vx = 0.0f;
	this->_vy = 0.0f;
	this->_vz = 0.0f;
	this->_vw = 1.0f;
}

Vect::Vect(const float inX, const float inY, const float inZ, const float inW)
{
	this->_vx = inX;
	this->_vy = inY;
	this->_vz = inZ;
	this->_vw = inW;
}


Vect::Vect(const Vect &inVect)
{
	_vx = inVect._vx;
	_vy = inVect._vy;
	_vz = inVect._vz;
	_vw = inVect._vw;
}

Vect Vect::operator = (const Vect &inVect)
{

	this->_vx = inVect._vx;
	this->_vy = inVect._vy;
	this->_vz = inVect._vz;
	this->_vw = inVect._vw;

	return *this;
}


Vect::~Vect()
{

}

/*
   _____      _       
  / ____|    | |      
 | |  __  ___| |_ ___ 
 | | |_ |/ _ \ __/ __|
 | |__| |  __/ |_\__ \
  \_____|\___|\__|___/
*/
float& Vect::operator[] (x_enum) { return this->_vx; }
float& Vect::operator[] (y_enum) { return this->_vy; }
float& Vect::operator[] (z_enum) { return this->_vz; }
float& Vect::operator[] (w_enum) { return this->_vw; }

float Vect::operator[] (x_enum)const { return this->_vx; }
float Vect::operator[] (y_enum)const { return this->_vy; }
float Vect::operator[] (z_enum)const { return this->_vz; }
float Vect::operator[] (w_enum)const { return this->_vw; }

const float& Vect::x() const { return this->_vx; }
const float& Vect::y() const { return this->_vy; }
const float& Vect::z() const { return this->_vz; }
const float& Vect::w() const { return this->_vw; }

float& Vect::x() { return this->_vx; }
float& Vect::y() { return this->_vy; }
float& Vect::z() { return this->_vz; }
float& Vect::w() { return this->_vw; }

/*
   _____      _       
  / ____|    | |      
 | (___   ___| |_ ___ 
  \___ \ / _ \ __/ __|
  ____) |  __/ |_\__ \
 |_____/ \___|\__|___/            
*/
void Vect::set(Vect inVect)
{
	this->_vx = inVect._vx;
	this->_vy = inVect._vy;
	this->_vz = inVect._vz;
	this->_vw = inVect._vw;
}

void Vect::set(const float inX, const float inY, const float inZ)
{
	this->_vx = inX;
	this->_vy = inY;
	this->_vz = inZ;
	this->_vw = 1.0f;
}

void Vect::set(const float inX, const float inY, const float inZ, const float inW)
{
	this->_vx = inX;
	this->_vy = inY;
	this->_vz = inZ;
	this->_vw = inW;
}

/*
             _     _ _ _   _             
     /\      | |   | (_) | (_)            
    /  \   __| | __| |_| |_ _  ___  _ __  
   / /\ \ / _` |/ _` | | __| |/ _ \| '_ \ 
  / ____ \ (_| | (_| | | |_| | (_) | | | |
 /_/    \_\__,_|\__,_|_|\__|_|\___/|_| |_|
*/
Vect Vect::operator + (Vect inVect) const
{
	return Vect(this->_vx + inVect._vx, this->_vy + inVect._vy, this->_vz + inVect._vz, 1.0f);
}

void Vect::operator += (const Vect &inVect)
{
	this->_vx = this->_vx + inVect._vx;
	this->_vy = this->_vy + inVect._vy;
	this->_vz = this->_vz + inVect._vz;
	this->_vw = 1.0f;
}

Vect Vect::operator + () const
{
	return Vect(this->_vx, this->_vy, this->_vz, 1.0f);
}

/*
   _____       _     _                  _   _             
  / ____|     | |   | |                | | (_)            
 | (___  _   _| |__ | |_ _ __ __ _  ___| |_ _  ___  _ __  
  \___ \| | | | '_ \| __| '__/ _` |/ __| __| |/ _ \| '_ \ 
  ____) | |_| | |_) | |_| | | (_| | (__| |_| | (_) | | | |
 |_____/ \__,_|_.__/ \__|_|  \__,_|\___|\__|_|\___/|_| |_|
*/
Vect Vect::operator - (Vect inVect) const
{
	return Vect(this->_vx - inVect._vx, this->_vy - inVect._vy, this->_vz - inVect._vz, 1.0f);
}

void Vect::operator -= (const Vect &inVect)
{
	this->_vx = this->_vx - inVect._vx;
	this->_vy = this->_vy - inVect._vy;
	this->_vz = this->_vz - inVect._vz;
	this->_vw = 1.0f;
}

Vect const Vect::operator - () const //negation
{
	return Vect(-this->_vx, -this->_vy, -this->_vz, 1.0f);
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
Vect Vect::operator * (Vect &inVect) const
{
	return Vect(this->_vx * inVect._vx, this->_vy * inVect._vy, this->_vz * inVect._vz, 1.0f);
}

Vect Vect::operator * (const float inNum) const
{
	return Vect(this->_vx * inNum, this->_vy * inNum, this->_vz * inNum, 1.0f);
}

Vect operator*(float inNum, Vect inVect) //<-- the weird friend one
{
	return Vect(inVect[x] * inNum, inVect[y] * inNum, inVect[z] * inNum, 1.0f);
}

void Vect::operator *= (Vect &inVect)
{
	this->_vx = this->_vx * inVect._vx;
	this->_vy = this->_vy * inVect._vy;
	this->_vz = this->_vz * inVect._vz;
	this->_vw = 1.0f;
}

void Vect::operator *= (const float &inNum)
{
	this->_vx = this->_vx * inNum;
	this->_vy = this->_vy * inNum;
	this->_vz = this->_vz * inNum;
	this->_vw = 1.0f;
}

Vect Vect::operator * (Matrix inMatrix) const
{
	return Vect(this->_vx * inMatrix.m0() + this->_vy*inMatrix.m4() + this->_vz*inMatrix.m8() + this->_vw * inMatrix.m12(),
		this->_vx * inMatrix.m1() + this->_vy*inMatrix.m5() + this->_vz*inMatrix.m9() + this->_vw * inMatrix.m13(), 
		this->_vx * inMatrix.m2() + this->_vy*inMatrix.m6() + this->_vz*inMatrix.m10() + this->_vw *inMatrix.m14(),
		this->_vx * inMatrix.m3() + this->_vy*inMatrix.m7() + this->_vz*inMatrix.m11() + this->_vw *inMatrix.m15()
	);
}

void Vect::operator *= (Matrix inMatrix)
{
	Vect C = *this;

	this->_vx = C._vx * inMatrix.m0() + C._vy*inMatrix.m4() + C._vz*inMatrix.m8() + C._vw * inMatrix.m12();
	this->_vy = C._vx * inMatrix.m1() + C._vy*inMatrix.m5() + C._vz*inMatrix.m9() + C._vw * inMatrix.m13();
	this->_vz = C._vx * inMatrix.m2() + C._vy*inMatrix.m6() + C._vz*inMatrix.m10() + C._vw *inMatrix.m14();
	this->_vw = C._vx * inMatrix.m3() + C._vy*inMatrix.m7() + C._vz*inMatrix.m11() + C._vw *inMatrix.m15();
}
Vect Vect::operator * (Quat &inQuat) const 
{
	Quat v(this->_vx, this->_vy, this->_vz, 0.0f);
	Quat answer = inQuat.getConj() * v;
	answer = answer * inQuat;

	return Vect(answer.qx(), answer.qy(), answer.qz());
}
void Vect::operator *= (Quat &inQuat)
{
	Quat v(this->_vx, this->_vy, this->_vz, 0.0f);
	Quat answer = inQuat.getConj() * v;
	answer = answer * inQuat;

	this->set(answer.qx(), answer.qy(), answer.qz());
}
/*
  _____  _       _     _             
 |  __ \(_)     (_)   (_)            
 | |  | |___   ___ ___ _  ___  _ __  
 | |  | | \ \ / / / __| |/ _ \| '_ \ 
 | |__| | |\ V /| \__ \ | (_) | | | |
 |_____/|_| \_/ |_|___/_|\___/|_| |_|
*/
Vect Vect::operator / (Vect &inVect)
{
	return Vect(inVect._vx / this->_vx, inVect._vy / this->_vy, inVect._vz / this->_vz, inVect._vw / this->_vw);
}

void Vect::operator /= (const Vect &inVect)
{
	this->_vx = this->_vx / inVect._vx;
	this->_vy = this->_vy / inVect._vy;
	this->_vz = this->_vz / inVect._vz;
	this->_vw = this->_vw / inVect._vw;
}

/*
  _    _ _   _ _   ____              _     
 | |  | | | (_) | |  _ \            | |    
 | |  | | |_ _| | | |_) | ___   ___ | |___ 
 | |  | | __| | | |  _ < / _ \ / _ \| / __|
 | |__| | |_| | | | |_) | (_) | (_) | \__ \
  \____/ \__|_|_| |____/ \___/ \___/|_|___/
*/
bool Vect::isEqual(Vect& other, const float epsilon)
{
	if ((Util::isEqual(this->_vx, other._vx, epsilon)) &&
		(Util::isEqual(this->_vy, other._vy, epsilon)) &&
		(Util::isEqual(this->_vz, other._vz, epsilon)) &&
		(Util::isEqual(this->_vw, other._vw, epsilon)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vect::isNotEqual(Vect other, const float epsilon)
{
	if ((Util::isNotEqual(this->_vx, other._vx, epsilon)) &&
		(Util::isNotEqual(this->_vy, other._vy, epsilon)) &&
		(Util::isNotEqual(this->_vz, other._vz, epsilon)) &&
		(Util::isNotEqual(this->_vw, other._vw, epsilon)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Vect::isOne(const float epsilon)
{
	if ((Util::isOne(this->_vx, epsilon)) &&
		(Util::isOne(this->_vy, epsilon)) &&
		(Util::isOne(this->_vz, epsilon)) &&
		(Util::isOne(this->_vw, epsilon)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Vect::isNonZero(const float epsilon)
{
	if ((Util::isNonZero(this->_vx, epsilon)) &&
		(Util::isNonZero(this->_vy, epsilon)) &&
		(Util::isNonZero(this->_vz, epsilon)) &&
		(Util::isNonZero(this->_vw, epsilon)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Vect::isZero(const float epsilon)
{
	if ((Util::isZero(this->_vx, epsilon)) &&
		(Util::isZero(this->_vy, epsilon)) &&
		(Util::isZero(this->_vz, epsilon)) &&
		Util::isOne(this->_vw, epsilon))
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
float Vect::dot(Vect inVect)
{
	return ((this->x() * inVect.x()) + (this->y() * inVect.y()) + (this->z() * inVect.z()));
}

Vect Vect::cross(Vect inVect) const
{
	//float tempX = ((this->y() * inVect.z()) - (this->z() * inVect.y()));
	//float tempY = ((this->x() * inVect.z()) - (this->z() * inVect.x()));
	//float tempZ = ((this->x() * inVect.y()) - (this->y() * inVect.x()));

	return Vect(((this->y() * inVect.z()) - (this->z() * inVect.y())), 
					-((this->x() * inVect.z()) - (this->z() * inVect.x())),
						((this->x() * inVect.y()) - (this->y() * inVect.x())), 1.0f);
}

void Vect::norm(void)
{
	float mag = this->mag();

	if (mag != 0.0f)
	{
		this->x() = this->x() / mag;
		this->y() = this->y() / mag;
		this->z() = this->z() / mag;
	}
}

Vect Vect::getNorm(void)
{
	float mag = this->mag();
	if (mag == 0.0f)
	{
		return *this;
	}
	else {
		return Vect(this->x() / mag, this->y() / mag, this->z() / mag, 1.0f);
	}
}

float Vect::mag()
{
	//reciprocal of sqrt
	//or try inverse sqrt

	return sqrtf((this->x() * this->x()) + (this->y() * this->y()) + (this->z() * this->z()));
}

float Vect::magSqr()
{
	return ((this->x() * this->x()) + (this->y() * this->y()) + (this->z() * this->z()));
}

float Vect::getAngle(Vect inVect)
{
	return acosf(this->dot(inVect) / (this->mag() * inVect.mag()));
}


// ---  End of File ---------------



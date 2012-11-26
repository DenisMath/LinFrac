#ifndef MATRIX
#define MATRIX
//#include <iostream>
#include "extpair.h"
#include "extpairWT.h"
#include <math.h>

//using namespace std;
class Matrix {
private:
	float tension;
	public:

	Matrix(float x = 1,float y = 0,float z = 0,float v = 1):oo(x),ot(y),to(z),tt(v)
	{ tension = 0; }

	float oo;
	float ot;
	float to;
	float tt;

	void SetTension()
	{
		tension = sqrt(oo*oo+ot*ot+tt*tt+to*to);
	}

	float GetTension()
	{
		return tension;
	}

	Extpair multRow(const Extpair &v)//mult 2x2 matrix on row vector;
	{
		Extpair tmp( oo*(v.xKoord)+ot*(v.yKoord) , to*(v.xKoord)+tt*(v.yKoord) );
		return tmp;
	}

	friend Matrix operator-(const Matrix &a1); 
	friend Matrix operator+(const Matrix & a1, const Matrix & a2); 
	friend Matrix operator-(const Matrix & a1, const Matrix & a2); 
	friend Matrix operator*(const Matrix & a1, const Matrix & a2); 
	friend bool operator==(const Matrix & a1, const Matrix & a2); 

	Matrix & operator=(const Matrix &m){
		oo=m.oo;
		ot=m.ot;
		to=m.to;
		tt=m.tt;
return *this;
	}
};

inline
Matrix operator-(const Matrix &a1){
	Matrix tmp(-a1.oo, -a1.ot, -a1.to, -a1.tt);
	/*tmp.oo=-a1.oo;
	tmp.ot=-a1.ot;
	tmp.to=-a1.to;
	tmp.tt=-a1.tt;*/
	return tmp;
}

inline
Matrix operator+(const Matrix & a1, const Matrix & a2){
	Matrix tmp(a1.oo+a2.oo, a1.ot+a2.ot, a1.to+a2.to, a1.tt+a2.tt);
	/*tmp.oo=a1.oo+a2.oo;
	tmp.ot=a1.ot+a2.ot;
	tmp.to=a1.to+a2.to;
	tmp.tt=a1.tt+a2.tt;*/
	return tmp;
}

inline
Matrix operator-(const Matrix & a1, const Matrix & a2){
	Matrix tmp(a1.oo-a2.oo, a1.ot-a2.ot, a1.to-a2.to, a1.tt-a2.tt);
	/*tmp.oo=a1.oo-a2.oo;
	tmp.ot=a1.ot-a2.ot;
	tmp.to=a1.to-a2.to;
	tmp.tt=a1.tt-a2.tt;*/
	return tmp;
}

inline
Matrix operator*(const Matrix & a1, const Matrix & a2){
	Matrix tmp(a1.oo*a2.oo+a1.ot*a2.to, a1.oo*a2.ot+a1.ot*a2.tt, a1.to*a2.oo+a1.tt*a2.to, a1.to*a2.ot+a1.tt*a2.tt);
	/*tmp.oo=a1.oo*a2.oo+a1.ot*a2.to;
	tmp.ot=a1.oo*a2.ot+a1.ot*a2.tt;
	tmp.to=a1.to*a2.oo+a1.tt*a2.to;
	tmp.tt=a1.to*a2.ot+a1.tt*a2.tt;*/
	return tmp;
}

inline
bool operator==(const Matrix & a1, const Matrix & a2){
	
	return ((a1.oo==a2.oo)&&(a1.ot==a2.ot)&&(a1.to==a2.to)&&(a1.tt==a2.tt));
}
#endif

#ifndef MATRIX
#define MATRIX
#include <iostream>
#include "extpair.h"

using namespace std;
class Matrix {
	public:
			Matrix()
	{
		oo=1;
		ot=0;
		to=0;
		tt=1;
	}
	Matrix(float x,float y,float z,float v)
	{
		oo=x;
		ot=y;
		to=z;
		tt=v;
	}
	float oo;
	float ot;
	float to;
	float tt;
	Extpair multRow(const Extpair &v)
	{
		Extpair tmp;
		tmp.xKoord=(oo*(v.xKoord)+ot*(v.yKoord));
		tmp.yKoord=(to*(v.xKoord)+tt*(v.yKoord));
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
Matrix operator-(const Matrix &a1){
	Matrix tmp;
	tmp.oo=-a1.oo;
	tmp.ot=-a1.ot;
	tmp.to=-a1.to;
	tmp.tt=-a1.tt;
	return tmp;
}
Matrix operator+(const Matrix & a1, const Matrix & a2){
	Matrix tmp;
	tmp.oo=a1.oo+a2.oo;
	tmp.ot=a1.ot+a2.ot;
	tmp.to=a1.to+a2.to;
	tmp.tt=a1.tt+a2.tt;
	return tmp;
}
Matrix operator-(const Matrix & a1, const Matrix & a2){
	Matrix tmp;
	tmp.oo=a1.oo-a2.oo;
	tmp.ot=a1.ot-a2.ot;
	tmp.to=a1.to-a2.to;
	tmp.tt=a1.tt-a2.tt;
	return tmp;
}
Matrix operator*(const Matrix & a1, const Matrix & a2){
	Matrix tmp;
	tmp.oo=a1.oo*a2.oo+a1.ot*a2.to;
	tmp.ot=a1.oo*a2.ot+a1.ot*a2.tt;
	tmp.to=a1.to*a2.oo+a1.tt*a2.to;
	tmp.tt=a1.to*a2.ot+a1.tt*a2.tt;
	return tmp;
}
bool operator==(const Matrix & a1, const Matrix & a2){
	
	return ((a1.oo==a2.oo)&&(a1.ot==a2.ot)&&(a1.to==a2.to)&&(a1.tt==a2.tt));
}
#endif

#include <iostream>
#include "extpair.h"
//#include "matrix.h"
//#include "fractal.h"
//#include "bpoint.h"

using namespace std;
class matrix {
	public:
			matrix()
	{
		oo=1;
		ot=0;
		to=0;
		tt=1;
	}
	matrix(float x,float y,float z,float v)
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
	extpair MultRow(const extpair &v)
	{
		extpair tmp;
		tmp.xKoord=(oo*(v.xKoord)+ot*(v.yKoord));
		tmp.yKoord=(to*(v.xKoord)+tt*(v.yKoord));
		return tmp;
	}
	friend matrix operator-(const matrix &a1); 
	friend matrix operator+(const matrix & a1, const matrix & a2); 
	friend matrix operator-(const matrix & a1, const matrix & a2); 
	friend matrix operator*(const matrix & a1, const matrix & a2); 
	friend bool operator==(const matrix & a1, const matrix & a2); 
	matrix & operator=(const matrix &m){
		oo=m.oo;
		ot=m.ot;
		to=m.to;
		tt=m.tt;
return *this;
	}
};
matrix operator-(const matrix &a1){
	matrix tmp;
	tmp.oo=-a1.oo;
	tmp.ot=-a1.ot;
	tmp.to=-a1.to;
	tmp.tt=-a1.tt;
	return tmp;
};
matrix operator+(const matrix & a1, const matrix & a2){
	matrix tmp;
	tmp.oo=a1.oo+a2.oo;
	tmp.ot=a1.ot+a2.ot;
	tmp.to=a1.to+a2.to;
	tmp.tt=a1.tt+a2.tt;
	return tmp;
};
matrix operator-(const matrix & a1, const matrix & a2){
	matrix tmp;
	tmp.oo=a1.oo-a2.oo;
	tmp.ot=a1.ot-a2.ot;
	tmp.to=a1.to-a2.to;
	tmp.tt=a1.tt-a2.tt;
	return tmp;
};
matrix operator*(const matrix & a1, const matrix & a2){
	matrix tmp;
	tmp.oo=a1.oo*a2.oo+a1.ot*a2.to;
	tmp.ot=a1.oo*a2.ot+a1.ot*a2.tt;
	tmp.to=a1.to*a2.oo+a1.tt*a2.to;
	tmp.tt=a1.to*a2.ot+a1.tt*a2.tt;
	return tmp;
};
bool operator==(const matrix & a1, const matrix & a2){
	
	return ((a1.oo==a2.oo)&&(a1.ot==a2.ot)&&(a1.to==a2.to)&&(a1.tt==a2.tt));
};

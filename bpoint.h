#ifndef BPOINT
#define BPOINT
#include <iostream>
#include "matrix.h"

using namespace std;
class bpoint {
	public:
	bpoint(float x=0,float y=0,float k=1,float l=0,float m=0,float n=1)
	{
		extpair pointh(x,y);
		matrix transformh(k,l,m,n);
		point.xKoord = x;
		point.yKoord = y;
		transform.oo = 1;
		transform.ot = 0;
		transform.to = 0;
		transform.tt = 1;
	}

	extpair point;
	matrix transform;

	extpair LinearTr(const extpair &x)
	{
		matrix id(1,0,0,1);
		return transform.MultRow(x)+(id-transform).MultRow(point);
	}

	friend bool operator==(const bpoint &a1,const bpoint &a2); 

	bpoint & operator=(const bpoint & m){
	point=m.point;
	transform=m.transform;
return *this;
	}
};

bool operator==(const bpoint &a1,const bpoint &a2){
	return (a1.point==a2.point)&&(a1.transform==a2.transform);
}
#endif

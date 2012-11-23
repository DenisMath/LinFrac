#ifndef BPOINT
#define BPOINT
#include <iostream>
#include "matrix.h"

//using namespace std;
class BasicPoint {
	public:
	BasicPoint(float x=0,float y=0,float k=1,float l=0,float m=0,float n=1):point(x,y),transform(k,l,m,n)
	{ }

	Extpair point;
	Matrix transform;

	Extpair linearTr(const Extpair &x)
	{
		Matrix id(1,0,0,1);
		return transform.multRow(x)+(id-transform).multRow(point);
	}

	friend bool operator==(const BasicPoint &a1,const BasicPoint &a2); 

	BasicPoint & operator=(const BasicPoint & m){
	point=m.point;
	transform=m.transform;
return *this;
	}
};

bool operator==(const BasicPoint &a1,const BasicPoint &a2){
	return (a1.point==a2.point)&&(a1.transform==a2.transform);
}
#endif

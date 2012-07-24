#ifndef EXTPAIR
#define EXTPAIR
#include <iostream>

using namespace std;
class extpair {
	public:
	extpair()
	{
		xKoord=0;
		yKoord=0;
	}
	extpair(float x,float y)
	{
		xKoord=x;
		yKoord=y;
	}
	float xKoord;
	float yKoord;
	
	friend extpair operator+(const extpair &a1, const extpair &a2); 
	friend extpair operator-(const extpair &a1, const extpair &a2); 
	friend extpair operator*(const extpair &a1, const extpair &a2); 
	friend bool operator==(const extpair &a1, const extpair &a2); 
	friend bool operator<(const extpair &a1, const extpair &a2); 
	extpair &operator=(const extpair &m){
	xKoord=m.xKoord;
	yKoord=m.yKoord;
return *this;
	}
extpair  operator-(const extpair& a1){
	extpair tmp;
	tmp.xKoord=-a1.xKoord;
	tmp.yKoord=-a1.yKoord;
	return tmp;
}
};


inline
 extpair operator+(const extpair &a1, const extpair &a2){
	extpair tmp;
	tmp.xKoord=a1.xKoord+a2.xKoord;
	tmp.yKoord=a1.yKoord+a2.yKoord;
	return tmp;
}

inline extpair operator-(const extpair &a1, const extpair &a2){
	extpair tmp;
	tmp.xKoord=a1.xKoord-a2.xKoord;
	tmp.yKoord=a1.yKoord-a2.yKoord;
	return tmp;
}

inline bool operator==(const extpair &a1, const extpair &a2){
	
	return ((a1.xKoord==a2.xKoord)&&(a1.yKoord==a2.yKoord));
}

inline bool operator<(const extpair &a1, const extpair &a2){
	
	return ((a1.xKoord<a2.xKoord)||((a1.xKoord==a2.xKoord)&&(a1.yKoord<a2.yKoord)));
}

#endif

#ifndef EXTPAIR
#define EXTPAIR
#include <iostream>

using namespace std;
class Extpair {
	public:
	Extpair(float x=0,float y=0):xKoord=0,yKoord=0
	{ }

	float xKoord;
	float yKoord;
	
	friend Extpair operator+(const Extpair &a1, const Extpair &a2); 
	friend Extpair operator-(const Extpair &a1, const Extpair &a2); 
	friend Extpair operator*(const Extpair &a1, const Extpair &a2); 
	friend bool operator==(const Extpair &a1, const Extpair &a2); 
	friend bool operator<(const Extpair &a1, const Extpair &a2); 
	Extpair &operator=(const Extpair &m){
	xKoord=m.xKoord;
	yKoord=m.yKoord;
return *this;
	}
Extpair  operator-(const Extpair& a1){
	Extpair tmp;
	tmp.xKoord=-a1.xKoord;
	tmp.yKoord=-a1.yKoord;
	return tmp;
}
};


inline
 Extpair operator+(const Extpair &a1, const Extpair &a2){
	Extpair tmp;
	tmp.xKoord=a1.xKoord+a2.xKoord;
	tmp.yKoord=a1.yKoord+a2.yKoord;
	return tmp;
}

inline Extpair operator-(const Extpair &a1, const Extpair &a2){
	Extpair tmp;
	tmp.xKoord=a1.xKoord-a2.xKoord;
	tmp.yKoord=a1.yKoord-a2.yKoord;
	return tmp;
}

inline bool operator==(const Extpair &a1, const Extpair &a2){
	return ((a1.xKoord==a2.xKoord)&&(a1.yKoord==a2.yKoord));
}

inline bool operator<(const Extpair &a1, const Extpair &a2){
	
	return ((a1.xKoord<a2.xKoord)||((a1.xKoord==a2.xKoord)&&(a1.yKoord<a2.yKoord)));
}

#endif

#ifndef EXTPAIR
#define EXTPAIR

//#include <iostream>

//using namespace std;

class Extpair {
	public:
	Extpair(float x=0,float y=0):xKoord(x),yKoord(y)
	{ }

	Extpair(const Extpair& x)
	{ xKoord = x.xKoord;
	yKoord = x.yKoord; }

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

	Extpair  operator-(){
	Extpair tmp(-xKoord,-yKoord);
	return tmp;
	}


};


inline
 Extpair operator+(const Extpair &a1, const Extpair &a2){
	Extpair tmp(a1.xKoord+a2.xKoord,
	a1.yKoord+a2.yKoord);
	return tmp;
}

inline Extpair operator-(const Extpair &a1, const Extpair &a2){
	Extpair tmp(a1.xKoord-a2.xKoord,
	a1.yKoord-a2.yKoord);
	return tmp;
}

inline bool operator==(const Extpair &a1, const Extpair &a2){
	return ((a1.xKoord==a2.xKoord)&&(a1.yKoord==a2.yKoord));
}

inline bool operator<(const Extpair &a1, const Extpair &a2){
	
	return ((a1.xKoord<a2.xKoord)||((a1.xKoord==a2.xKoord)&&(a1.yKoord<a2.yKoord)));
}

Extpair convertToBox(Extpair x)
{
	Extpair tmp(x.xKoord / 2.0, - x.yKoord / 2.0 + 600);
	return tmp;
}

#endif

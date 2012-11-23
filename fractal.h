#ifndef FRACTAL
#define FRACTAL
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>
#include <fstream>
#include "bpoint.h"
typedef list<Extpair> FractalType; 
//typedef set<Extpair> FractalType; 

//using namespace std;
class Fractal {
public:

	vector<BasicPoint> basicpoints;
	//list<Extpair> fracset;
	FractalType fracset;
	//vector<Extpair> fracset;
	void addpoint(float x,float y,float k,float l,float m,float n);

	void build(int n);


	//	void build(int n);

	void convert(int* massive);

	void writetops(float x);

};

#endif

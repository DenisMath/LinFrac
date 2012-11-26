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
#define PI 3.14159265
//using namespace std;
typedef std::list<Extpair> FractalType; 
typedef std::list<ExtpairWT> FractalTypeW; 
//typedef set<Extpair> FractalType; 




class Fractal {
public:

	std::vector<BasicPoint> basicpoints;
	FractalType fracset;
	FractalTypeW fracsetW;
	
	void addpoint(float x,float y,float k,float l,float m,float n)
	{
		BasicPoint t( x, y, k, l, m, n);
		basicpoints.push_back(t);
	}

	void buildW(int n)
	{
		int pntsize=basicpoints.size();
		int frsize=fracsetW.size();
		ExtpairWT temp;

		fracsetW.clear();
		for(int i=0;i < pntsize; i++)
		{
			temp.extpair = basicpoints[i].point;
            basicpoints[i].transform.SetTension();
			temp.tension = basicpoints[i].transform.GetTension();
			fracsetW.push_back(temp);
		}

		for(int k=0;k < n; k++)
		{
			fracsetW.sort();
			fracsetW.unique();
			frsize=fracsetW.size();
			for(int j=0;j < frsize; j++)
			{
				for(int i=0;i < pntsize; i++)
				{
					fracsetW.push_back(basicpoints[i].linearTr(fracsetW.front()));
				}
				fracsetW.pop_front(); 
			}
			/*fracset.sort();
			fracset.unique();*/
		}
	}

	void build(int n)
	{
		int pntsize=basicpoints.size();
		int frsize=fracset.size();
		fracset.clear();
		for(int i=0;i < pntsize; i++)
		{
			fracset.push_back(basicpoints[i].point);
		}

		for(int k=0;k < n; k++)
		{
			fracset.sort();
			fracset.unique();
			frsize=fracset.size();
			for(int j=0;j < frsize; j++)
			{
				for(int i=0;i < pntsize; i++)
				{
					fracset.push_back(basicpoints[i].linearTr(fracset.front()));
				}
				fracset.pop_front(); 
			}
			/*fracset.sort();
			fracset.unique();*/
		}
	}

	/*	void build(int n)
	{
	int pntsize=basicpoints.size();
	int frsize=fracset.size();
	FractalType::iterator it;
	FractalType temp;
	fracset.clear();
	temp.clear();
	for(int i=0;i < pntsize; i++)
	{
	fracset.insert(basicpoints[i].point);
	}

	for(int k=0;k < n; k++)
	{
	for(it = fracset.begin();it != fracset.end(); it++)
	{
	for(int i=0;i < pntsize; i++)
	{
	temp.insert(basicpoints[i].linearTr(*it));
	}
	}
	fracset.swap(temp);
	temp.clear();
	}
	}*/

	void convert(int* massive)
	{
		int frsize=fracset.size();
		FractalType::iterator at;
		at=fracset.begin();
		for(int i = 0;i<frsize; i++)
		{
			massive[i<<1]= static_cast<int>(at->xKoord);
			massive[(i<<1)+1]= static_cast<int>(at->yKoord);
			at++;
		}
	}

	void convert_float(float* massive)
	{
		int frsize=fracset.size();
		FractalType::iterator at;
		at=fracset.begin();
		for(int i = 0;i<frsize; i++)
		{
			massive[i<<1]= (at->xKoord);
			massive[(i<<1)+1]= (at->yKoord);
			at++;
		}

	}

	void writetoEps( float x = 0.1 )
	{   
		int t=0;
		FractalType second;
		int frsize=fracset.size();
		second.resize(frsize);
		second.push_back(*fracset.begin());
		 transform (fracset.begin(), fracset.end(), second.begin(), convertToBox);
		 copy (second.begin(), second.end(), fracset.begin() );
		int frsize_div=fracset.size()/25000;
		int frsize_rem=fracset.size()%25000;
		int frsize_two=2*fracset.size();
		//int* result = new int[frsize_two];
		//this->convert(result);
		float* result = new float[frsize_two];
		convert_float(result);
		FILE * pFile;
		pFile = fopen ( "myfile1.eps" , "w" );
		fprintf(pFile,"%%!PS-Adobe-4.9 EPSF-3.0\
					  \n%%%%BoundingBox: 0 0 1000 1000\
					  \n/drawstack {count 2 idiv { %f 0 360 arc fill} repeat} def\
					  \n   gsave\
					  \n",x); 
		fclose (pFile);
		pFile = fopen ( "myfile1.eps" , "a" );
		int i=0;
		for(int t=0; t<frsize_div;t++)
		{
			for(int j = 0; j<25000;j++)
			{
				fprintf(pFile, " %f %f", result[i], result[i+1]);
				i+=2;
			}
			fprintf(pFile, " drawstack");
		}
		for(int t=0; t<frsize_rem;t++)
		{
			fprintf(pFile, " %f %f", result[i], result[i+1]);
			i+=2;
		}
		fprintf(pFile, " drawstack\n");
		fprintf(pFile,"  grestore\nshowpage\n%%%%EOF");
		fclose (pFile);
		
	}

	void writetops(float x = 0.1)
	{   
		int t=0;
		int frsize=fracset.size();
		int frsize_div=fracset.size()/25000;
		int frsize_rem=fracset.size()%25000;
		int frsize_two=2*fracset.size();
		//int* result = new int[frsize_two];
		//this->convert(result);
		float* result = new float[frsize_two];
		convert_float(result);
		FILE * pFile;
		pFile = fopen ( "myfile.ps" , "w" );
		fprintf(pFile,"%%!PS-Adobe-3.0\
					  \n%%%%Title:\
					  \n%%%%Creator:\
					  \n%%%%CreationDate:\
					  \n%%%%For:\
					  \n%%%%Copyright:\
					  \n%%%%Document fonts:\
					  \n%%%%BoundingBox: 0 0 596 843\
					  \n%%%%Pages: 1\
					  \n%%%%EndComments\
					  \n%%%%BeginProcSet\
					  \n/drawstack {count 2 idiv { %f 0 360 arc fill} repeat} def\
					  \n%%%% EndProcSet \
					  \n%%%%EndProlog \
					  \n%%%%Page 1 1\
					  \n",x); 
		fclose (pFile);
		pFile = fopen ( "myfile.ps" , "a" );
		int i=0;
		for(int t=0; t<frsize_div;t++)
		{
			for(int j = 0; j<25000;j++)
			{
				fprintf(pFile, " %f %f", result[i], result[i+1]);
				i+=2;
			}
			fprintf(pFile, " drawstack");
		}
		for(int t=0; t<frsize_rem;t++)
		{
			fprintf(pFile, " %f %f", result[i], result[i+1]);
			i+=2;
		}
		fprintf(pFile, " drawstack\n");
		fprintf(pFile,"showpage\n%%%%EOF");
		fclose (pFile);
		//list< Extpair >::iterator at;
		/* FractalType::iterator at;
		at=fracset.begin();
		ofstream out("cippfrc.ps");
		out <<  " /drawstack {count 2 idiv { " << x << " 0 360 arc fill} repeat} def " << endl;
		for(int i=0; i<frsize;i++)
		{ t=++t;
		if(t>25000) 
		{out << " drawstack" << endl;
		t=0;
		};
		out << " " << ((*at).xKoord)<< " " << ((*at).yKoord) ;

		++at;
		}
		out << " drawstack" << endl;
		for(int i=0; i<basicpoints.size();i++)
		{  
		out << ((basicpoints[i]).point).xKoord<<  " " << ((basicpoints[i]).point).yKoord << " 1 0 360 arc 1 0 0 setrgbcolor .25 setlinewidth stroke " << endl;

		}

		for(int i=0; i<basicpoints.size();i++)
		{  
		out << "\%\%" << i+1 << "point: (" << ((basicpoints[i]).point).xKoord<<  ", " << ((basicpoints[i]).point).yKoord<< "), " << "transform: [" << ((basicpoints[i]).transform).oo <<  ", " << ((basicpoints[i]).transform).ot << "; " << ((basicpoints[i]).transform).to << ", " << ((basicpoints[i]).transform).tt << "];" << endl;

		}*/
		/* out << "\%\%Розмірність Хаусдорфа:" <<-log(basicpoints.size()*1.0)/log(abs((basicpoints[0]).transform)) << endl;*/
		//out.close();
	}


	void writetops_int(float x = 0.1)
	{    int t=0;
	int frsize=fracset.size();
	int frsize_div=fracset.size()/25000;
	int frsize_rem=fracset.size()%25000;
	int frsize_two=2*fracset.size();
	int* result = new int[frsize_two];
	this->convert(result);
	FILE * pFile;
	pFile = fopen ( "myfile_int.ps" , "w" );
	fprintf(pFile,"%%!PS-Adobe-3.0\n");
	fprintf(pFile,
		"%%%%Title: \
		\n%%%%Creator:\
		\n%%%%CreationDate:\
		\n%%%%For:\
		\n%%%%Copyright:\
		\n%%%%Document fonts:\
		\n%%%%BoundingBox: 0 0 596 843\
		\n%%%%Pages: 1\
		\n%%%%EndComments\
		\n%%%%BeginProcSet\n%%%%\
		EndProcSet\
		\n%%%%EndProlog\
		\n%%%%Page 1 1\n"); 

	fprintf(pFile, " /drawstack {count 2 idiv { %f 0 360 arc fill} repeat} def ", x);
	fclose (pFile);
	pFile = fopen ( "myfile_int.ps" , "a" );
	int i=0;
	for(int t=0; t<frsize_div;t++)
	{
		for(int j = 0; j<25000;j++)
		{
			fprintf(pFile, " %d %d", result[i], result[i+1]);
			i+=2;
		}
		fprintf(pFile, " drawstack");
	}
	for(int t=0; t<frsize_rem;t++)
	{
		fprintf(pFile, " %d %d", result[i], result[i+1]);
		i+=2;
	}
	fprintf(pFile, " drawstack\n");
	fprintf(pFile,"showpage\
				  \n%%%%EOF");
	fclose (pFile);
	/* out << "\%\%Розмірність Хаусдорфа:" <<-log(basicpoints.size()*1.0)/log(abs((basicpoints[0]).transform)) << endl;*/
	//out.close();
	}
};

void buildFractalPolygone( Fractal &f, int numberOfVertex = 3, double tensionCoeff = 0.5, int numberOfIteration = 7 )
{
	int n = numberOfVertex;
	Extpair p(0,100),shp(280,330);
	BasicPoint bp(0,0,tensionCoeff,0,0,tensionCoeff);
	Matrix rotr(cos(2*PI/n),-sin(2*PI/n),sin(2*PI/n),cos(2*PI/n));
	int psize=n;
	(f.basicpoints).clear();
	for(int i=0; i<psize; i++)
	{ bp.point=p+shp;
	(f.basicpoints).push_back(bp);
	p=rotr.multRow(p);
	}
	//vector< vector<bpoint> > memofr;
	//memofr.clear();
	f.build(numberOfIteration);	
}

void convertFractalToPairVector(Fractal &f, std::vector<std::pair<double,double>> &VectorPair )
{
	VectorPair.clear();
	int temp1 = f.fracset.size();
	std::pair<double,double> temp;
	FractalType::iterator at = f.fracset.begin();
	for(int i = 0; i < temp1; i++)
	{ 
		temp.first = at -> xKoord;
		temp.second = at -> yKoord;
		VectorPair.push_back(temp);
		at++;
	}	
}

void wConvertFractalToPairVector(Fractal &f, std::vector<std::pair<double,double>> &VectorPair, std::vector<double> &Tension )
{
	VectorPair.clear();
	Tension.clear();
	int temp1 = f.fracsetW.size();
	std::pair<double,double> temp;
	FractalTypeW::iterator at = f.fracsetW.begin();
	for(int i = 0; i < temp1; i++)
	{ 
		temp.first = at -> extpair.xKoord;
		temp.second = at -> extpair.yKoord;
		VectorPair.push_back(temp);
		Tension.push_back( at -> tension );
		at++;
	}	
}

#endif

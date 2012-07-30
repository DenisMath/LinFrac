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

using namespace std;
class Fractal {
	public:

	vector<BasicPoint> basicpoints;
	//list<Extpair> fracset;
	FractalType fracset;
        //vector<Extpair> fracset;
	void addpoint(float x,float y,float k,float l,float m,float n)
	{
		BasicPoint t( x, y, k, l, m, n);
		basicpoints.push_back(t);
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
			       	frsize=fracset.size();
			       	for(int j=0;j < frsize; j++)
			       	{
				       	for(int i=0;i < pntsize; i++)
				       	{
					       	fracset.push_back(basicpoints[i].linearTr(fracset.front()));
				       	}
					       	fracset.pop_front(); 
				}
		fracset.sort();
		fracset.unique();
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
	void writetops(float x)
	{   
 int t=0;
             int frsize=fracset.size();
             int frsize_div=fracset.size()/25000;
             int frsize_rem=fracset.size()%25000;
	     int frsize_two=2*fracset.size();
float* result = new float[frsize_two];
//this->convert(result);
convert_float(result);
  FILE * pFile;
  pFile = fopen ( "myfile.ps" , "w" );
 fprintf(pFile,"%%!PS-Adobe-3.0\n%%%%Title:   \n%%%%Creator:\n%%%%CreationDate: \n%%%%For: \n%%%%Copyright: \n%%%%Document fonts: \n%%%%BoundingBox: 0 0 596 843 \n%%%%Pages: 1\n%%%%EndComments\n%%%%BeginProcSet\n/drawstack {count 2 idiv { %f 0 360 arc fill} repeat} def\n%%%% EndProcSet \n%%%%EndProlog \n%%%%Page 1 1\n",x); 
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
	void writetops_int(float x)
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
 fprintf(pFile,"%%%%Title:   \n%%%%Creator:\n%%%%CreationDate: \n%%%%For: \n%%%%Copyright: \n%%%%Document fonts: \n%%%%BoundingBox: 0 0 596 843 \n%%%%Pages: 1\n%%%%EndComments\n%%%%BeginProcSet\n%%%% EndProcSet \n%%%%EndProlog \n%%%%Page 1 1\n"); 
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
  fprintf(pFile,"showpage\n%%%%EOF");
  fclose (pFile);
	/* out << "\%\%Розмірність Хаусдорфа:" <<-log(basicpoints.size()*1.0)/log(abs((basicpoints[0]).transform)) << endl;*/
	 //out.close();
	}
};

#endif

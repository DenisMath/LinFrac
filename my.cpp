//#include "matrix.h"
//#include "Extpair.h"
#include "fractalout.h"
#include <cmath>
//#include "bpoint.h"
#define PI 3.14159265
int main()
{  int n;
   cout << " Input number of basic points: ";
   cin >> n;
   Extpair p(0,100),shp(280,330);
   bpoint bp(0,0,.5,0,0,.5);
   matrix rotr(cos(2*PI/n),-sin(2*PI/n),sin(2*PI/n),cos(2*PI/n));
   int psize=n;
   fractal f,g;
   (f.basicpoints).clear();
   (g.basicpoints).clear();
   for(int i=0; i<psize; i++)
   {bp.point=p+shp;
   (f.basicpoints).push_back(bp);
   p=rotr.MultRow(p);
   }
   //vector< vector<bpoint> > memofr;
   //memofr.clear();
   f.build(10);
vector<fractal> input;
input.push_back(f);
input.push_back(f);
input.push_back(f);
input.push_back(f);
//printtops_out(input,.000001);
f.writetops(.000001);
   //f.writetops_int(.000001);
}

  

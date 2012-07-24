#include "extpair.h"
#include "fractal.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
using namespace std;
int main()
{
float t1;
float t2;
fractal f;
for(int i=0;i<5;i++){
f.addpoint(10*i + 20,200 - 10*i*i,.5,0,0,.5);
}
t1 = clock();
f.build(9);
int frsize= 2*(f.fracset).size();
cout<<"frsize="<<frsize/2<<endl;
int* result = new int[frsize];
f.convert(result);
t2 = clock();
cout << "frac_time= "<<(t2-t1)/CLOCKS_PER_SEC << endl;

  FILE * pFile;
  pFile = fopen ( "myfile.txt" , "w" );
t1 = clock();
f.writetops_int(.1);
t2 = clock();
cout << "print_time= "<<(t2-t1)/CLOCKS_PER_SEC << endl;
  //fwrite (result , sizeof(int) , sizeof(result) , pFile );
  fclose (pFile);
delete[] result;

return 0;
};

#include <ctime>
#include "fractal.h"
int main()
{
Fractal fr;
for(int i=0;i<5;i++){
fr.addpoint(10*i + 20,200 - 10*i*i,.5,0,0,.5);
}
float t1,t2;
t1 = clock();
fr.build(9);
t2 = clock();
cout << "build_time= "<<(t2-t1)/CLOCKS_PER_SEC << endl;
/*t1 = clock();
fr.build1(9);
t2 = clock();
cout << "build_time1= "<<(t2-t1)/CLOCKS_PER_SEC << endl;*/
t1 = clock();
float* fPointer = new float[2*fr.fracset.size()];
fr.convert_float(fPointer);
t2 = clock();
delete[] fPointer;
cout << "convert_time= "<<(t2-t1)/CLOCKS_PER_SEC << endl;
cout << "fractal size= " << fr.fracset.size();
return 0;
}

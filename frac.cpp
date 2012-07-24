#include "fractal.h" 
int main(){ 
		 fractal fr;
cout << "Waiting..."<< endl;
(fr.basicpoints).clear();
extpair h(0,0);
(fr.fracset).push_back(h);
 fr.addpoint( 280 , 430 , 0.5 , 0.45 , -0.45 , 0.45 ); 
 fr.addpoint( 280 , 230 , 0.5 , -0.375 , .375 , 0.525 ); 
fr.build(21);
fr.writetops(0.0000001);
fr.writetops_int(0.0000001);
cout <<  " Hurrrayyy!!!" << endl;
}

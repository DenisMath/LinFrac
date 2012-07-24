//#include "matrix.h"
//#include "extpair.h"
#include "fractal.h"
#include <cmath>
//#include "bpoint.h"
#define PI 3.14159265
int main()
{  int n;
cout << " Input number of basic points: ";
   cin >> n;
   extpair p(0,100),shp(280,330);
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
   };
   vector< vector<bpoint> > memofr;
   memofr.clear();
  
 while (true)
{      
memofr.push_back(f.basicpoints);
if (memofr.size()>20) {memofr.erase(memofr.begin());};
cout << "Now you have "<< memofr.size() <<" fractal in a memory"<< endl;
       
	cout << "Current fractal has "<< (f.basicpoints).size() << " basic points. "<< endl;
 for(int i=0; i<(f.basicpoints).size();i++)
         { 
cout << endl;
cout << "Basic point number "<< i << endl;
cout << "coordinates: (" << (((f.basicpoints)[i]).point).xKoord<<  ", " << (((f.basicpoints)[i]).point).yKoord<< ")"<<endl ;
cout <<"transform matrix: [" << (((f.basicpoints)[i]).transform).oo <<  ", " << (((f.basicpoints)[i]).transform).ot << "; " << (((f.basicpoints)[i]).transform).to << ", " << (((f.basicpoints)[i]).transform).tt << "];" << endl;
	 };
cout << endl;
 cout << "Input mode:" << endl;
cout << " 0 - reset to default; 1 - modify transforms, 2 - replace transforms; "<< endl;
cout << " 3 - shift basic points; 4 - replace basic points; 5 - redraw fractal;" << endl;
cout<<" 6 - add or delete basic point; 7 - draw fractal without changes;" << endl;
cout<<" 8 - backup fractal; 9 - compress and shift fractal."<< endl;
int mode;
cin >> mode; 
switch(mode)
{
       	case 1: // modify transform
	       	{
			cout << endl;
		       	cout << "Input modify mode:" << endl; cout << "1 - modify transform matrix, 2 - modify transform angle and compression,"<< endl;
                    cout << "3 - modify all angles and compressions."<< endl;
		       	int mode1;
		       	cin >> mode1;
		       	switch(mode1)
		       	{
			       	case 1: 
					{
					       	for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	matrix mp;
						       	cout << "Input  transform number "<< i <<". "<< endl;
						       	double oo,ot,to,tt;
						       	cout << "Input 1-st element: ";
						       	cin >> oo;
						       	if(oo!=7)
						       	{
								cout << "Input 2-nd element: ";
							       	cin >> ot;
							       	cout << "Input 3-d element: ";
							       	cin >> to;
							       	cout << "Input 4-th element: ";
							       	cin >> tt;
							       	mp.oo=oo;
							       	mp.ot=ot;
							       	mp.to=to;
							       	mp.tt=tt;
							       	mp=(((f.basicpoints)[i]).transform)*mp;
							}
						       	else
						       	{
								mp=((f.basicpoints)[i]).transform;
							};
						       	((f.basicpoints)[i]).transform=mp;
					       	};
				       	};
					break;
			       	case 2:
				       	{
						for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	matrix mp;
						       	double angle=0,coeff=1;
						       	cout << "Input  transform number "<< i <<". "<< endl;
						       	double oo,ot,to,tt; cout << "Input coefficient of spreading: ";
						       	cin >> coeff;
						       	if(coeff != 7)
						       	{
							       	cout << "Input angle: ";
							       	cin >> angle;
							       	mp.oo=coeff*cos(PI*angle/180);
							       	mp.ot=-coeff*sin(PI*angle/180);
							       	mp.to=coeff*sin(PI*angle/180);
							       	mp.tt=coeff*cos(PI*angle/180);
							       	mp=(((f.basicpoints)[i]).transform)*mp;
							}
						       	else 
							{
								mp=((f.basicpoints)[i]).transform;
							};
						       	((f.basicpoints)[i]).transform=mp;
						};
				       	};
					break;
					case 3:
				       	{
                                double angle=0,coeff=1;
                                cout << "Input coefficient of spreading: ";
						       	cin >> coeff;  
                                   cout << "Input angle: ";
							       	cin >> angle;                  
						for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	matrix mp;
						       	
						       	double oo,ot,to,tt; 
						       	if(coeff != 7)
						       	{
							       	
							       	mp.oo=coeff*cos(PI*angle/180);
							       	mp.ot=-coeff*sin(PI*angle/180);
							       	mp.to=coeff*sin(PI*angle/180);
							       	mp.tt=coeff*cos(PI*angle/180);
							       	mp=(((f.basicpoints)[i]).transform)*mp;
							}
						       	else 
							{
								mp=((f.basicpoints)[i]).transform;
							};
						       	((f.basicpoints)[i]).transform=mp;
						};
				       	};
					break;
		       	};
	       	};
		break;
       	case 2:// replace transform 
		{
			cout << "Input replace mode:" << endl;
		       	cout << "1 - replace transform matrix, 2 - replace transform angle and compression."<< endl;
		       	int mode2;
		       	cin >> mode2;
		       	switch(mode2)
		       	{
			       	case 1:
				       	{
					       	for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	matrix mp;
						       	cout << "Input  transform number "<< i <<". "<< endl;
						       	double oo,ot,to,tt;
						       	cout << "Input 1-st element: ";
						       	cin >> oo;
						       	if(oo!=7) {cout << "Input 2-nd element: ";
							       	cin >> ot;
							       	cout << "Input 3-d element: ";
							       	cin >> to;
							       	cout << "Input 4-th element: ";
							       	cin >> tt;
							       	mp.oo=oo;
							       	mp.ot=ot;
							       	mp.to=to;
							       	mp.tt=tt;
							}
						       	else
						       	{
								mp=((f.basicpoints)[i]).transform;
							};
						       	((f.basicpoints)[i]).transform=mp;
					       	};
				       	};
					break;
			       	case 2:
				       	{
						for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	matrix mp;
						       	double angle=0,coeff=1;
						       	cout << "Input  transform number "<< i <<". "<< endl;
						       	double oo,ot,to,tt;
						       	cout << "Input coefficient of spreading: ";
						       	cin >> coeff;
						       	if(coeff != 7) 
							{
							       	cout << "Input angle: ";
							       	cin >> angle;
							       	mp.oo=coeff*cos(PI*angle/180);
							       	mp.ot=-coeff*sin(PI*angle/180);
							       	mp.to=coeff*sin(PI*angle/180);
							       	mp.tt=coeff*cos(PI*angle/180);
							}
						       	else
						       	{
								mp=((f.basicpoints)[i]).transform;
							};
						       	((f.basicpoints)[i]).transform=mp;
						};
				       	};
					break;
			};
		       	};
		break;

			       	case 3:
				       	{
						for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	extpair extp;
						       	double angle=0,coeff=1;
						       	cout << "Input  transform number "<< i <<". "<< endl;
						       	double xKoord,yKoord; 
							cout << "Input x-coord: ";
						       	cin >> xKoord;
						       	cout << "Input y-coord: ";
						       	cin >> yKoord;
						       	extp.xKoord=xKoord;
						       	extp.yKoord=yKoord;
						       	extp=(((f.basicpoints)[i]).point)+extp;
						       	((f.basicpoints)[i]).point=extp;
						};
				       	};
					break;
			       	case 4:
				       	{
						for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
							bpoint pp;
						       	extpair extp;
						       	double angle=0,coeff=1;
						       	cout << "Input  transform number "<< i <<". "<< endl;
						       	double xKoord,yKoord; 
							cout << "Input x-coord: ";
						       	cin >> xKoord;
						       	cout << "Input y-coord: ";
						       	cin >> yKoord;
						       	extp.xKoord=xKoord;
						       	extp.yKoord=yKoord;
						       	((f.basicpoints)[i]).point=extp;
						};
				       	};
					break;

			       	case 5:
				       	{
						cout << " Input number of basic points: ";
					       	cin >> n;
					       	matrix rotr(cos(2*PI/n),-sin(2*PI/n),sin(2*PI/n),cos(2*PI/n));
					       	(f.basicpoints).clear();
					       	for(int i=0; i<n; i++)
					       	{
							bp.point=p+shp;
						       	(f.basicpoints).push_back(bp);
						       	p=rotr.MultRow(p);
					       	};
				       	};
					break;
case 8:
     int bs,mmsize;
     cout << " Input the number of backup steps: "<< endl;
     cin >> bs;
     mmsize=memofr.size();
     if(bs<(mmsize+1))
     {(f.basicpoints).clear();
     (f.basicpoints)=memofr[mmsize-bs-1];}
  
   break;
   case 0:(f.basicpoints).clear();
   for(int i=0; i<(f.basicpoints).size(); i++)
   {bp.point=p+shp;
   (f.basicpoints).push_back(bp);
   p=rotr.MultRow(p);
   };
   memofr.clear();
   break;

					case 6: 
		       	cout << "1 - add basic point, 2 - delete basic point: " << endl;
                        int pn,pnm;
			cin >> pnm;
			switch (pnm) 
			{case 2:

					       	cout << " Input the number of point which will be deleted: ";
					       	cin >> pn;
						(f.basicpoints).erase((f.basicpoints).begin()+pn);
						break;
				case 1:
							
						       	double xKoord,yKoord; 
							cout << "Input x-coord: ";
						       	cin >> xKoord;
						       	cout << "Input y-coord: ";
						       	cin >> yKoord;
						       	f.addpoint(xKoord,yKoord,1,0,0,1);
							break;
				
				       	default: break;
			};
				case 9:
							{
									double scoef=1,xSkoord=0,ySkoord=0;

							cout<< "Input spreading coeff: "<< endl;
							cin >> scoef;
							cout<< "Input shift x-coordinate: "<< endl;
							cin >> xSkoord;
							cout<< "Input shift y-coordinate: "<< endl;
							cin >> ySkoord;
						for(int i=0; i<(f.basicpoints).size(); i++)
					       	{
						(((f.basicpoints)[i]).point).xKoord=scoef*(((f.basicpoints)[i]).point).xKoord+xSkoord;
						(((f.basicpoints)[i]).point).yKoord=scoef*(((f.basicpoints)[i]).point).yKoord+ySkoord;
						};
				       	};
						
							break;
				       	default: break;
};

	       	double m; m=.0000001;
	       	cout<< endl;
	       	cout << "Number of iterations(if 0 - break): ";
	       	cin >> n;
	       	if(n==0){break;};
	       	//cout << "Size of points: ";
	       	//cin >> m;
	       	(f.fracset).clear();
	       	cout << "Calculating..."<< endl;
	       	f.build(n);
//	       	int w=1;
		//f.display(w);

	       	cout << "Drawing..."<< endl;
	       	f.writetops(.9);
	       	cout << "I have done this work for you, master!"<< endl;
	       	//f.writecpp(5,.1);
	       	cout<< endl;
	       	cout<< endl;
	       	cout<< endl;
	       	cin.get();
	       	cin.get();
         };
}


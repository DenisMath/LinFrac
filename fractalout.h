#ifndef FRACTALOUT
#define FRACTALOUT
#include "fractal.h"
void printtops_out(vector<fractal> input,float x)
{
int in_size = input.size();
  FILE * pFile;
  pFile = fopen ( "myfile.ps" , "w" );
 fprintf(pFile,"%%!PS-Adobe-3.0\n%%%%Title:   \n%%%%Creator:\n%%%%CreationDate: \n%%%%For: \n%%%%Copyright: \n%%%%Document fonts: \n%%%%BoundingBox: 0 0 596 843 \n%%%%Pages: %d\n%%%%EndComments\n%%%%BeginProcSet\n/drawstack {count 2 idiv { %f 0 360 arc fill} repeat} def\n%%%%EndProcSet \n%%%%EndProlog \n", in_size ,x); 
  fclose (pFile);
  pFile = fopen ( "myfile.ps" , "a" );
             int t;
             int frsize;
             int frsize_div;
             int frsize_rem;
	     int frsize_two;
float* result; 
for(int i = 0; i< in_size; i++)
{
             t=0;
             frsize=input[i].fracset.size();
             frsize_div=input[i].fracset.size()/25000;
             frsize_rem=input[i].fracset.size()%25000;
	     frsize_two=2*frsize;
             result = new float[frsize_two];
input[i].convert_float(result);
int j=0;
  fprintf(pFile, "%%%%Page %d %d\n", i+1,i+1);
for(int t=0; t<frsize_div;t++)
{
for(int l = 0; l<25000;l++)
{
  fprintf(pFile, " %f %f", result[j], result[j+1]);
j+=2;
}
  fprintf(pFile, " drawstack");
}
for(int t=0; t<frsize_rem;t++)
{
  fprintf(pFile, " %f %f", result[j], result[j+1]);
j+=2;
}
  fprintf(pFile, " drawstack\n");
  fprintf(pFile,"showpage\n");
delete[] result;
}
  fprintf(pFile,"%%%%EOF");
}
#endif

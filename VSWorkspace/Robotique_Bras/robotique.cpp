#include "stdafx.h"
//typedef float]

void denavit(float thita, float d, float alpha, float a, float res[4][4])// les matrices entaires associées ?ces instances des quadruplets.
{
	
	res[0][0]=jd2(cos(thita)); res[0][1]=jd2(-sin(thita)*cos(alpha)); res[0][2]=jd2(sin(thita)*sin(alpha));  res[0][3]=jd2(a*cos(thita));
	res[1][0]=jd2(sin(thita)); res[1][1]=jd2(cos(thita)*cos(alpha));  res[1][2]=jd2(-cos(thita)*sin(alpha)); res[1][3]=jd2(a*sin(thita));
	res[2][0]=0;			   res[2][1]=jd2(sin(alpha));			  res[2][2]=jd2(cos(alpha));			 res[2][3]=d;
	res[3][0]=0;			   res[3][1]=0;						      res[3][2]=0;							 res[3][3]=1;
	return;
}

float jd2(float src)
{
	return ((int)src*100)/100.00f;
}

/*Return the distance between 2 point in the space*/
float distance(float point1[3], float point2[3])
{
    return sqrt(
    (point1[0]-point2[0])*(point1[0]-point2[0])+
    (point1[1]-point2[1])*(point1[1]-point2[1])+
    (point1[2]-point2[2])*(point1[2]-point2[2]));
}

/**/
void getCurrentPoint(float tdaa[][4], int n, float *point)
{
    float m[4][4]={0};
    float m1[4][4];
    float m2[4][ 4];
    //Init m1 with a elementary matrice
    m1[0][0]=1;
    m1[1][1]=1;
    m1[2][2]=1;
    m1[3][3]=1;
    for(int i=0; i<n; i++)
    {
        denavit(tdaa[i][0], tdaa[i][1], tdaa[i][2], tdaa[i][3], m2);
    	produit(m1, m2, m); 
        copy(m,m1);
    }
	point[0] = m[0][3];
	point[1] = m[1][3];
    point[2] = m[2][3];
	//printmatrix(m);
}

void setTDAAFromX(float thita[][2], float d[], float alpha[][2], float a[],float *x, float **tdaa, int n)
{
    for(int i=0; i<n; i++)
    {
        tdaa[i][0]=x[i]*thita[i][0]+thita[i][1];
        tdaa[i][1]=d[i];
        tdaa[i][2]=x[i]*alpha[i][0]+alpha[i][1];
        tdaa[i][3]=a[i];
    }
}
/*thita[0][0]=2, thita[0][1]=PI/2 means that thita=2*x+PI/2 which should be
    stored in thita[0][2]; 
  x is the angle to calculate.
  range[i] means the range of angle Xi.
*/
void IAA(float thita[][2], float d[], float alpha[][2], float a[], int n, int range[][2], float targetPoint[3])
{
    int i;
    //The angles to calculate
    float *x = new float[n];
    //A table of increment rate
    //if(delta(epsilon) = 0) then incrementRate/=2
    float *incRate = new float[n];
    //The coordinate of the current point
    float currentPoint[3];
    //The distance between the current point and the target point
    float dist;
    float **tdaa = new float*[n];
    //float d[][4] = new float*[n];
    //initialisation
    for(i=0; i<n; i++)
    {
        x[i] = range[i][0]+rand()%(range[i][0]-range[i][1]);
        incRate[i]=0.5;
        tdaa[i] = new float [4];
    }


    setTDAAFromX(thita, d, alpha, a, x, tdaa, n);
    dist = getCurrentPoint();
    while(true)
    {

        for(i=0; i<n; i++)
        {
            //inc
            x[i]+=(range[i][0]-range[i][1])*incRate[i];

        }
    }

}
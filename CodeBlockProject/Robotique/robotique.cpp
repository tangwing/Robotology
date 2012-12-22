#include"robotique.h"
#include"matrice.h"
#include <cstring>
#include <cstdlib>
#include <stdio.h>
using namespace std;
#define BORNE 1
void denavit(double thita, double d, double alpha, double a, double res[4][4])// les matrices entaires associées ?ces instances des quadruplets.
{
	res[0][0]=jd2(cos(thita)); res[0][1]=jd2(-sin(thita)*cos(alpha)); res[0][2]=jd2(sin(thita)*sin(alpha));  res[0][3]=jd2(a*cos(thita));
	res[1][0]=jd2(sin(thita)); res[1][1]=jd2(cos(thita)*cos(alpha));  res[1][2]=jd2(-cos(thita)*sin(alpha)); res[1][3]=jd2(a*sin(thita));
	res[2][0]=0;			   res[2][1]=jd2(sin(alpha));			  res[2][2]=jd2(cos(alpha));			 res[2][3]=jd2(d);
	res[3][0]=0;			   res[3][1]=0;						      res[3][2]=0;							 res[3][3]=1;

	//printf("a=%f,thita=%f,sin(thita)=%f,jd2=%f\n",jd2(a*sin(thita)));
	return;
}

double jd2(double src)
{
	//return src;
	return ((int)((src)*1000))/1000.0;
	//return src;
}

/*Return the distance between 2 point in the space*/
double distance(double point1[3], double point2[3])
{
    double tmp =
        (point1[0]-point2[0])*(point1[0]-point2[0])+
        (point1[1]-point2[1])*(point1[1]-point2[1])+
        (point1[2]-point2[2])*(point1[2]-point2[2]);
    double dist = sqrt(tmp);

//    for(int i=0; i<3; i++)
//    {
//        printf("(%f,%f,%f),(%f,%f,%f),tmp=%f;dist=%f.\n",point1[0],point1[1],point1[2],
//               point2[0],point2[1],point2[2],tmp, dist);
//    }
    return dist;
}

/*tdaa -> tdaa[n][4]*/
void getCurrentPoint(double *tdaa, int n, double *point)
{
    double m[4][4];
    double m1[4][4]={0};
    double m2[4][4];
    //Init m1 with a elementary matrice
    m1[0][0]=1;
    m1[1][1]=1;
    m1[2][2]=1;
    m1[3][3]=1;
    denavit(tdaa[0], tdaa[1], tdaa[2], tdaa[3], m1);
    printmatrix(m1);
    for(int i=1; i<n; i++)
    {
        denavit(tdaa[i*4+0], tdaa[i*4+1], tdaa[i*4+2], tdaa[i*4+3], m2);
        printmatrix(m2);
    	produit(m1, m2, m);
    	printmatrix(m);
    	//m->m1
    	memcpy(m1,m,16*sizeof(double));
    	printmatrix(m1);
    	printf("\n");
        //copy(m,m1);
    }
	point[0] = m[0][3];
	point[1] = m[1][3];
    point[2] = m[2][3];
	//printmatrix(m);
}

void setTDAAFromX(double thita[][2], double d[], double alpha[][2], double a[],double *x, double **tdaa, int n)
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
double* IAA(double thita[][2], double d[], double alpha[][2], double a[], int n, double range[][2], double targetPoint[3])
{
    int i;
    bool flag = true;
    //The angles to calculate
    double *x = new double[n];
    double lastX;
    //A table of increment rate
    //if(delta(epsilon) = 0) then incrementRate/=2
    double *incRate = new double[n];
    //The coordinate of the current point
    double currentPoint[3];
    //The distance between the current point and the target point
    double lastDist, newDist;
    double **tdaa = new double*[n];
    //double d[][4] = new double*[n];
    //initialisation
    for(i=0; i<n; i++)
    {
        x[i] = range[i][0]+rand()%((int)(range[i][1]-range[i][0]));
        incRate[i]=0.5;
        tdaa[i] = new double [4];
    }


    setTDAAFromX(thita, d, alpha, a, x, tdaa, n);
    getCurrentPoint((double*)tdaa,n,currentPoint);
    lastDist = distance(currentPoint, targetPoint);
    //while(flag)
    int j=0;
    while(j++<2)
    {
        for(i=0; i<n; i++)
        {
            printf("Thita %d: x_begin=%f; dis_old=%f; incRate=%f\n",i,x[i],lastDist,incRate[i]);
            lastX = x[i];
            //inc
            x[i]+=(range[i][1]-range[i][0])*incRate[i];
            //printf("\n",x[i]);
            //calculate new distance
            setTDAAFromX(thita, d, alpha, a, x, tdaa, n);
            getCurrentPoint((double*)tdaa,n,currentPoint);
            newDist = distance(currentPoint, targetPoint);
            printf("newX=%f,newpoint:(%f;%f;%f);dis=%f\n",x[i],currentPoint[0],currentPoint[1],currentPoint[2],newDist);
            if(newDist>=lastDist)
            {
                //search another possibility
                x[i]=x[i]-2*(range[i][1]-range[i][0])*incRate[i];
                //calculate new distance
                setTDAAFromX(thita, d, alpha, a, x, tdaa, n);
                getCurrentPoint((double*)tdaa,n,currentPoint);
                newDist = distance(currentPoint, targetPoint);
                if(newDist>=lastDist)
                {
                    //Keep the original value
                    x[i]=lastX;
                    //Adjust increment rate
                    incRate[i]/=2;
                    newDist = lastDist;
                }
                else
                {
                    //Keep the new value
                    lastDist=newDist;
                }
            }else
            {
                //Keep the new value
                lastDist=newDist;
            }
            printf("Thita %d:   x_end=%f; dis_new=%f; incRate=%f\n\n",i,x[i],newDist,incRate[i]);
            if(newDist<BORNE)
                flag=false;
        }
    }

    //finalisation
    delete []incRate;

    for(i=0; i<n; i++)
    {
        delete [] tdaa[i];
    }
    delete [] tdaa;
    return x;
}

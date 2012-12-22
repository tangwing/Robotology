#include "matrice.h"
#include "robotique.h"
#include <stdio.h>
#define PI 3.14159

void testMGD();
void testIAA();

int main()
{
    //testMGD();
//    double a = sin(PI/2);
//    double b = a*a;
//    int c = (int)(b*100);
//    printf("c=%f,%f\n",c/100.0,jd2(b));
    //printf("sin,%f",sin(1));
    testIAA();
//    double d = 0.009834465645234565;
//    printf("%f,%f\n",d, (int)(d*1000)/1000.0);
	return 0;
}

void testMGD()
{
    double m1[4][4];
	denavit(PI/2, 2, PI/2, 0, m1);
printmatrix(m1);
	double m2[4][4];
	denavit(0, 0, 0, 1, m2);
printmatrix(m2);
    double m3[4][4];
	denavit(0, 0, 0, 1, m3);
printmatrix(m3);
	double m12[4][4];
	produit(m1, m2, m12);
printmatrix(m12);
	double m[4][4];
	produit(m12,m3,m);

	printmatrix(m);
}

void testIAA()
{
    double thita[3][2] = {1,0,   1,0,   1,0};
    double d[3]={2,0,0};
    double alpha[3][2] = {0,PI/2,   0,0,   0,0};
    double a[3]={0,1,1};
    double range[3][2] = {0,2*PI,   0,2*PI,   0,2*PI};
    double targetPoint[3] = {0,2,2};

    double* x = IAA( thita,  d,  alpha,
                a, 3, range,  targetPoint);

    for(int i=0; i<3; i++)
    {
        printf("%f\n",x[i]);
    }
}






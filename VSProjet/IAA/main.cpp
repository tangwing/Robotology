#include "Matrice.h"
#include "Quadruplet.h"
#include "Robotique.h"
#include <iostream>
using namespace std;
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
	Quadruplet pQUAconfig[3];
	pQUAconfig[0] = Quadruplet(PI/2, 2, PI/2, 0);
    pQUAconfig[1] = Quadruplet(0, 0, 0, 1);
	pQUAconfig[2] = Quadruplet(0, 0, 0, 1);

	Matrice m = Robotique::ROBcalculMGD(pQUAconfig, 3);
	m.MATprint();
}

void testIAA()
{
	Quadruplet pQUAconfig[4];
	pQUAconfig[0] = Quadruplet(PI/2, 2, PI/2, 0,     0, PI);
    pQUAconfig[1] = Quadruplet(0,    0, 0,    1, -PI/2, PI/2);
	pQUAconfig[2] = Quadruplet(0,    0, 0,    1, -PI/2, PI/2);
	pQUAconfig[3] = Quadruplet(0,    0, 0,    1, -PI/2, PI/2);
	Point POItarget(0,0,1.5);

	bool res = Robotique::IAA( pQUAconfig, 4, POItarget);

	if( res == true)
	{
		cout<<"Final thitas:"<<endl;
		for(int i=0; i<4; i++)
		{
			printf("%f\n",pQUAconfig[i].thita);
		}
	}else
		printf("The point is not accessable.\n");
}
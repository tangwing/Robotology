#include "Matrice.h"
#include "Quadruplet.h"
#include "Robotique.h"
#include <iostream>
using namespace std;

void printResIAA(Quadruplet* pQUAconfig, int n, bool res);
void testMGD();
void testIAA();

int main()
{
    //testMGD();
    testIAA();
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
    //La configuration 5R. Le dernier organe articulaire n'intervient pas
	//Quadruplet pQUAconfig1[4];
	//pQUAconfig1[0] = Quadruplet(PI/2, 2, PI/2, 0,  0, PI);     //0, PI);
    // pQUAconfig1[1] = Quadruplet(0,    0, 0,    1,  -PI/2, PI/2);     //0, 0);
	//pQUAconfig1[2] = Quadruplet(0,    0, 0,    1,  -PI/2, PI/2);     //0,PI);//PI/4, PI*3/4);
	//pQUAconfig1[3] = Quadruplet(0,    0, 0,    1,  -PI/2, PI/2);     //0,PI);//    
	//Point POItarget1(0,2,3);

    /**A cause des limites on a imposés aux variables articulaires,
    *l'algorithme peut rencontrer des minimas locaux. Et on constate que
    *les minimas locaux apparaissent quand l'organe terminal est sur la
    *chaîne articulaire.
    */
    /*bool res = Robotique::IAA( pQUAconfig1, 4, POItarget1);
    printResIAA(pQUAconfig1, 4, res);    */

    //La configuration "2R"
    Quadruplet pQUAconfig2[2];
    pQUAconfig2[0] = Quadruplet(0, 0, 0, 1,    -PI/3, PI/3);
    pQUAconfig2[1] = Quadruplet(0, 0, 0, 0.75, -2*PI/3, PI/2);
    Point POItarget2(3,0,0);
    bool res = Robotique::IAA( pQUAconfig2, 2, POItarget2);
    printResIAA(pQUAconfig2, 2, res);
}


void printResIAA(Quadruplet* pQUAconfig, int n, bool res)
{
    if( res == true)
	{
		cout<<"Final theta:"<<endl;
		for(int i=0; i<n; i++)
		{
			printf("%f (%f degree)\n",pQUAconfig[i].theta, pQUAconfig[i].theta*180/PI);
		}
	}else
		printf("The point is not reachable.\n");
}
#include "Matrice.h"
#include "Quadruplet.h"
#include "Robotique.h"
#include <iostream>
#include <fstream>
using namespace std;

void printResIAA(Quadruplet* pQUAconfig, int n, bool res);
void testMGD();
void testIAA();
void testIAAFromFile(char* filename);

int main()
{
    //testMGD();
    //testIAA();
    testIAAFromFile("config.txt");
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

/**Just like the function testIAA, but read config info from
*config.txt.
*/
void testIAAFromFile(char* filename)
{
    //char line[100];
    int n,i;
    ifstream inputFile(filename, ifstream::in);
    if(!inputFile)
    {
        fputs("File config.txt is not valide\n", stderr);
        fputs("The format of config.txt:\n", stderr);
        fputs("#The first line is the number of quadruplet\n", stderr);
        fputs("#The 'number' lines following are the quadruplets which can represent the config of the robot.\n",stderr);
        fputs("#Each line has 6 elements: theta, d, alpha, a, minTheta and maxTheta\n", stderr);
        fputs("#The last line is the coordinates of the target point, 3 double variables\n", stderr);
        fputs("#An example:\n", stderr);
        fputs("2\n", stderr);
        fputs("0 0 0 1 -1.047 1.047\n", stderr);
        fputs("0 0 0 0.75 -2.094 1.57\n", stderr);
        fputs("1.7 0 0\n", stderr);
        printf("Press Enter to exit.\n");
        getchar();
        return;
    }
    inputFile>>n;
    cout<<n<<endl;
    inputFile.ignore(10, '\n');//CR+LF in windows
    Quadruplet* pQUAtable = new Quadruplet[n];
    double tmp[6];
    i=0;int j;
    while(inputFile.good() && i<n)
    {
       //inputFile.getline(line, 100);
       //cout<<line<<endl;
       for(j=0; j<6; j++)
       {
            inputFile>>tmp[j];
            cout<<tmp[j]<<" ";
       }
       inputFile.ignore(10, '\n');
       cout<<endl;
       pQUAtable[i].theta = tmp[0];
       pQUAtable[i].d = tmp[1];
       pQUAtable[i].alpha = tmp[2];
       pQUAtable[i].a = tmp[3];
       pQUAtable[i].minTheta = tmp[4];
       pQUAtable[i].maxTheta = tmp[5];
       i++;
    }
    Point POItarget;
    inputFile>>POItarget.dx;
    inputFile>>POItarget.dy;
    inputFile>>POItarget.dz;
    inputFile.close();
    bool res = Robotique::IAA( pQUAtable, n, POItarget);
    printResIAA(pQUAtable, n, res);
    delete [] pQUAtable;
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
    Point POItarget2(1.7,0,0);
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

    printf("Press Enter to exit.\n");
    getchar();
}
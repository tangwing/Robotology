#pragma once
#include <ctime>
#include <cstdlib>
/**La classe qui repr�sent un quadruplet dans une
* matrice denavit. De plus, il y a aussi deux attributs
* qui repr�sente la limite de theta.
*/
class Quadruplet
{
public:
	double theta;
	double d;
	double alpha;
	double a;
    //Les deux attributs suivants seront
    //utilis�s dans l'algo IAA
	double maxTheta;
	double minTheta;

	Quadruplet(){srand( (unsigned int)time(NULL) );};
	Quadruplet(double th, double d2, double al, double a2):
		theta(th),d(d2),alpha(al),a(a2){srand( (unsigned int)time(NULL) );};
	Quadruplet(double th, double d2, double al, double a2, double min, double max):
		theta(th),d(d2),alpha(al),a(a2), minTheta(min),maxTheta(max){srand( (unsigned int)time(NULL) );};
	~Quadruplet(){};
    //Affecter une valeur entre maxTheta et
    //minTheta � l'attribut theta, de mani�re al�atoire.
	void QUAset_random_theta();
};


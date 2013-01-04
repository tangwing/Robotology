
#pragma once
#include <ctime>
#include <cstdlib>
class Quadruplet
{
public:
	double thita;
	double d;
	double alpha;
	double a;
	double maxThita;
	double minThita;

	Quadruplet(){srand( time(NULL) );};
	Quadruplet(double th, double d2, double al, double a2):
		thita(th),d(d2),alpha(al),a(a2){srand( time(NULL) );};
	Quadruplet(double th, double d2, double al, double a2, double min, double max):
		thita(th),d(d2),alpha(al),a(a2), minThita(min),maxThita(max){srand( time(NULL) );};
	~Quadruplet(){};
	void QUAset_random_thita();
};


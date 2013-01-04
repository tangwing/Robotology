#pragma once
#include "Matrice.h"
#include "Quadruplet.h"
#include "Point.h"
#define PI 3.141592653589
class Robotique
{
public:
	Robotique();
	~Robotique();
	static Matrice ROBdenavit(Quadruplet QUADfour);
	static Matrice ROBcalculMGD(Quadruplet QUAn[], int iCount);
	static Point ROBgetPfromM(Matrice & MATm);
	static bool IAA(Quadruplet QUAn[], int iCount, Point POItarget);
};


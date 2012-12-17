// Robotique_Bras.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	float m1[4][4];
	denavit(PI, 2, PI/2, 5, m1);

	float m2[4][4];
	denavit(PI, 2, PI/2, 5, m2);

	float m[4][4];
	produit(m1, m2, m);   

	printmatrix(m);

	return 0;
}

void gogogo(float a, float b, float c)
{
	int i,j;
	
}




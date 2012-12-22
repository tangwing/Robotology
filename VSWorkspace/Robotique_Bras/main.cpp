// Robotique_Bras.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
   /* float p1[]={1,2,3};
    float p2[]={3,2,1};
    cout<<distance(p1,p2)<<endl;*/
	float m1[4][4];
	denavit(PI, 2, PI/2, 5, m1);

	float m2[4][4];
	denavit(PI, 2, PI/2, 5, m2);

	float m[4][4];
	produit(m1, m2, m);   

	printmatrix(m);

	return 0;
}





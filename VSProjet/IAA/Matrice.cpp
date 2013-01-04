#include "Matrice.h"
#include<iostream>
#include<iomanip>
using namespace std;

/**Initialiser la matrice avec 0.*/
Matrice::Matrice()
{
	int iBouclei, iBouclej;
	for(iBouclei=0;iBouclei<4;iBouclei++)
	{
		for(iBouclej=0 ;iBouclej<4;iBouclej++)
		{
			dMATmatrice[iBouclei][iBouclej]=0;
		}
	}
}

/**Définir la produit entre 2 matrices*/
Matrice & Matrice::operator*(Matrice & m2)
{
	Matrice m;
	m[0][0]=dMATmatrice[0][0]*m2[0][0]+dMATmatrice[0][1]*m2[1][0]+dMATmatrice[0][2]*m2[2][0]+dMATmatrice[0][3]*m2[3][0];
	m[0][1]=dMATmatrice[0][0]*m2[0][1]+dMATmatrice[0][1]*m2[1][1]+dMATmatrice[0][2]*m2[2][1]+dMATmatrice[0][3]*m2[3][1];
	m[0][2]=dMATmatrice[0][0]*m2[0][2]+dMATmatrice[0][1]*m2[1][2]+dMATmatrice[0][2]*m2[2][2]+dMATmatrice[0][3]*m2[3][2];
	m[0][3]=dMATmatrice[0][0]*m2[0][3]+dMATmatrice[0][1]*m2[1][3]+dMATmatrice[0][2]*m2[2][3]+dMATmatrice[0][3]*m2[3][3];

	m[1][0]=dMATmatrice[1][0]*m2[0][0]+dMATmatrice[1][1]*m2[1][0]+dMATmatrice[1][2]*m2[2][0]+dMATmatrice[1][3]*m2[3][0];
	m[1][1]=dMATmatrice[1][0]*m2[0][1]+dMATmatrice[1][1]*m2[1][1]+dMATmatrice[1][2]*m2[2][1]+dMATmatrice[1][3]*m2[3][1];
	m[1][2]=dMATmatrice[1][0]*m2[0][2]+dMATmatrice[1][1]*m2[1][2]+dMATmatrice[1][2]*m2[2][2]+dMATmatrice[1][3]*m2[3][2];
	m[1][3]=dMATmatrice[1][0]*m2[0][3]+dMATmatrice[1][1]*m2[1][3]+dMATmatrice[1][2]*m2[2][3]+dMATmatrice[1][3]*m2[3][3];

	m[2][0]=dMATmatrice[2][0]*m2[0][0]+dMATmatrice[2][1]*m2[1][0]+dMATmatrice[2][2]*m2[2][0]+dMATmatrice[2][3]*m2[3][0];
	m[2][1]=dMATmatrice[2][0]*m2[0][1]+dMATmatrice[2][1]*m2[1][1]+dMATmatrice[2][2]*m2[2][1]+dMATmatrice[2][3]*m2[3][1];
	m[2][2]=dMATmatrice[2][0]*m2[0][2]+dMATmatrice[2][1]*m2[1][2]+dMATmatrice[2][2]*m2[2][2]+dMATmatrice[2][3]*m2[3][2];
	m[2][3]=dMATmatrice[2][0]*m2[0][3]+dMATmatrice[2][1]*m2[1][3]+dMATmatrice[2][2]*m2[2][3]+dMATmatrice[2][3]*m2[3][3];

	m[3][0]=dMATmatrice[3][0]*m2[0][0]+dMATmatrice[3][1]*m2[1][0]+dMATmatrice[3][2]*m2[2][0]+dMATmatrice[3][3]*m2[3][0];
	m[3][1]=dMATmatrice[3][0]*m2[0][1]+dMATmatrice[3][1]*m2[1][1]+dMATmatrice[3][2]*m2[2][1]+dMATmatrice[3][3]*m2[3][1];
	m[3][2]=dMATmatrice[3][0]*m2[0][2]+dMATmatrice[3][1]*m2[1][2]+dMATmatrice[3][2]*m2[2][2]+dMATmatrice[3][3]*m2[3][2];
	m[3][3]=dMATmatrice[3][0]*m2[0][3]+dMATmatrice[3][1]*m2[1][3]+dMATmatrice[3][2]*m2[2][3]+dMATmatrice[3][3]*m2[3][3];

	return m;
}
//Matrice & Matrice::operator=(Matrice& m)
//{
//	int iBouclei, iBouclej;
//	for(iBouclei=0;iBouclei<4;iBouclei++)
//	{
//		for(iBouclej=0 ;iBouclej<4;iBouclej++)
//		{
//			dMATmatrice[iBouclei][iBouclej]=m[iBouclei][iBouclej];
//		}
//	}
//	
//	return *this;
//}

void Matrice::MATprint(Matrice & m)
{
	cout<<endl<<setw(11)<<m[0][0]<<setw(11)<<m[0][1]<<setw(11)<<m[0][2]<<setw(11)<<m[0][3]<<endl;
	cout<<setw(11)<<m[1][0]<<setw(11)<<m[1][1]<<setw(11)<<m[1][2]<<setw(11)<<m[1][3]<<endl;
	cout<<setw(11)<<m[2][0]<<setw(11)<<m[2][1]<<setw(11)<<m[2][2]<<setw(11)<<m[2][3]<<endl;
	cout<<setw(11)<<m[3][0]<<setw(11)<<m[3][1]<<setw(11)<<m[3][2]<<setw(11)<<m[3][3]<<endl;
}

void Matrice::MATprint()
{
	MATprint(*this);
}

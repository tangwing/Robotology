#pragma once
class Matrice
{
private:
	double dMATmatrice[4][4];
public:
	Matrice();
	~Matrice();
	double * operator [](int itmp)
	{
		return dMATmatrice[itmp];
	}
	Matrice & operator *(Matrice & MATm);
	//Matrice & operator =(Matrice & m);
	static void MATprint(Matrice & MATm);
	void MATprint();
};


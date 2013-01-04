#pragma once
/**La classe qui repr�sente une matrice
*/
class Matrice
{
private:
	double dMATmatrice[4][4];
public:
	Matrice();
	~Matrice(){};
	double * operator [](int itmp)
	{
		return dMATmatrice[itmp];
	}
    
    /**D�finir la produit entre 2 matrices*/
	Matrice & operator *(Matrice & MATm);

    //Afficher une matrice sur l'�cran
	static void MATprint(Matrice & MATm);
	void MATprint();
};


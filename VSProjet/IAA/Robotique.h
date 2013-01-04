#pragma once
#include "Matrice.h"
#include "Quadruplet.h"
#include "Point.h"
#define PI 3.141592653589
/**Cette classe d�fini un ensemble d'outils
* robotiques.
*/
class Robotique
{
public:
	Robotique();
	~Robotique();
    /**Retourner la matrice denavit � partir un quadruplet*/
	static Matrice ROBdenavit(Quadruplet QUADfour);

    /**Application du mod�le num�rique direct*/
	static Matrice ROBcalculMGD(Quadruplet QUAn[], int iCount);

    /**Retirer les coordonn�es du point de l'organe terminal � partir de
        la matrice obtenue du mod�le num�trique direct.   
    */
	static Point ROBgetPfromM(Matrice & MATm);

    /**L'algorithme qui v�rifie si un point est atteignable. 
    *@param QUAn Un tableau de quadruplet qui repr�sente la configuration du robot.
    *            Les valeurs QUAn[i].theta sont � chercher, dons les valeurs initiales
    *            sont ignor�s.
    *@param iCount Le nombre de quadruplet dans le tableau QUAn
    *@param POItarget Le point cible.
    *@result false Si le point cible n'est pas atteignable
    *        true  Si le point cible est atteignable, les valeurs articulaires
    *              sont affect� � QUAn[i].theta.
    */
	static bool IAA(Quadruplet QUAn[], int iCount, Point POItarget);

private:
    /**Test whether the algorithm IAA
    *falls into the "local minimum" situation. This situation 
    *often appears when we have limites for the articulars variables.
    */
    static bool testLocalMinimum(Quadruplet* QUAconfig, int n);
};


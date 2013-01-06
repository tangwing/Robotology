#include "Robotique.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

//La borne de distance qui nous permet de 
//prendre 2 points pour un seul.
#define BORNE_DIS 0.0001

inline double jd2(double dsrc)
{
	return dsrc;
	//return ((int)((dsrc)*1000))/1000.0;
}

/**Retourner la matrice denavit à partir un quadruplet*/
Matrice Robotique::ROBdenavit(Quadruplet QUAfour)
{
	Matrice MATtmp;
	MATtmp[0][0]=jd2(cos(QUAfour.theta)); MATtmp[0][1]=jd2(-sin(QUAfour.theta)*cos(QUAfour.alpha)); MATtmp[0][2]=jd2(sin(QUAfour.theta)*sin(QUAfour.alpha));  MATtmp[0][3]=jd2(QUAfour.a*cos(QUAfour.theta));
	MATtmp[1][0]=jd2(sin(QUAfour.theta)); MATtmp[1][1]=jd2(cos(QUAfour.theta)*cos(QUAfour.alpha));  MATtmp[1][2]=jd2(-cos(QUAfour.theta)*sin(QUAfour.alpha)); MATtmp[1][3]=jd2(QUAfour.a*sin(QUAfour.theta));
	MATtmp[2][0]=0;			   MATtmp[2][1]=jd2(sin(QUAfour.alpha));			  MATtmp[2][2]=jd2(cos(QUAfour.alpha));			 MATtmp[2][3]=jd2(QUAfour.d);
	MATtmp[3][0]=0;			   MATtmp[3][1]=0;						      MATtmp[3][2]=0;							 MATtmp[3][3]=1;
	return MATtmp;
}

/**Application du modèle numérique direct*/
Matrice Robotique::ROBcalculMGD(Quadruplet QUAn[], int iCount)
{
	int iBoucle;
	Matrice MATtmp, MATres;
	MATres=ROBdenavit(QUAn[0]);
	for(iBoucle=1;iBoucle<iCount;iBoucle++)
	{
		MATtmp=ROBdenavit(QUAn[iBoucle]);
		MATres=MATres*MATtmp;
	}
	return MATres;
}

/**Retirer les coordonnées du point de l'organe terminal à partir de
    la matrice obtenue du modèle numétrique direct.   
*/
Point Robotique::ROBgetPfromM(Matrice & m)
{
	Point p;
	p.dx=m[0][3];
	p.dy=m[1][3];
	p.dz=m[2][3];
	return p;
}

/*Return the distance between 2 point in the space*/
double distance(Point POIsrc, Point POIdest)
{
    double tmp =
        (POIsrc.dx-POIdest.dx)*(POIsrc.dx-POIdest.dx)+
        (POIsrc.dy-POIdest.dy)*(POIsrc.dy-POIdest.dy)+
		(POIsrc.dz-POIdest.dz)*(POIsrc.dz-POIdest.dz);
    double dist = sqrt(tmp);
    return dist;
}

/**L'algorithme qui vérifie si un point est atteignable. 
*@param QUAn Un tableau de quadruplet qui représente la configuration du robot.
*            Les valeurs QUAn[i].theta sont à chercher, dons les valeurs initiales
*            sont ignorés.
*@param iCount Le nombre de quadruplet dans le tableau QUAn
*@param POItarget Le point cible.
*@result false Si le point cible n'est pas atteignable
*        true  Si le point cible est atteignable, les valeurs articulaires
*              sont affecté à QUAn[i].theta.
*/
bool Robotique::IAA(Quadruplet QUAconfig[], int n, Point POItarget)
{
	int i;
    bool flag = true;
    double lastX;//The theta of the last time
    
	//A table of increment rate
    double *incRate = new double[n];
    
	//stop condition
	double *BORNE_RATE = new double[n];
    
	//The coordinate of the current point that we can reach
    Point POIcurrent;
    
	//The distance between the current point and the target point
    double lastDist, newDist;
    
	//Initialisation
    for(i=0; i<n; i++)
    {
		QUAconfig[i].QUAset_random_theta();
        incRate[i]=0.15;//cf the article of Abdelhak MOUSSAOUI
        //Stop condition: If the value of IncrementRate is less
        //than this threshold, and the values of theta cannot be
        //improved, then the function return false, which means that
        //the target point is not reachable.
        if(QUAconfig[i].maxTheta <= QUAconfig[i].minTheta)
        {
            incRate[i]=0;
            BORNE_RATE[i] = 0;
        }else
		    BORNE_RATE[i]=0.0001/   //precision:0.00...1°
                ((QUAconfig[i].maxTheta - QUAconfig[i].minTheta)*180/PI);
    }

	POIcurrent = ROBgetPfromM(ROBcalculMGD(QUAconfig, n));
    lastDist = distance(POIcurrent, POItarget);

    int j=0, times = 0;
    while(flag)
    {
        printf("Itération %d\t-------------------------------------------------\n", times++);
        flag = false;
		//for each value of theta
        for(i=0; i<n; i++)
        {
			printf("Theta %d, initial: theta=%f; dis=%f; incRate=%f; goalPoint=(%f,%f,%f)\n",
                i+1,QUAconfig[i].theta,lastDist,incRate[i],
                POItarget.dx, POItarget.dy, POItarget.dz);
            lastX = QUAconfig[i].theta;
            //inc
			QUAconfig[i].theta+=(QUAconfig[i].maxTheta-QUAconfig[i].minTheta)*incRate[i];
            if(QUAconfig[i].theta > QUAconfig[i].maxTheta)
                QUAconfig[i].theta = QUAconfig[i].maxTheta;

            POIcurrent = ROBgetPfromM(ROBcalculMGD(QUAconfig, n));
			newDist = distance(POIcurrent, POItarget);
            //printf("Theta %d:       newX=%f; newpoint:(%f;%f;%f); dis=%f\n", i+1, QUAconfig[i].theta,POIcurrent.dx,POIcurrent.dy,POIcurrent.dz,newDist);
            
			if (newDist < lastDist)
            {//We get a better value
                //Keep the new value
                lastDist=newDist;
                flag=true;
                //incRate[i]*=2;
            }
			else
            {
                //search another possibility
				QUAconfig[i].theta = lastX - (QUAconfig[i].maxTheta-QUAconfig[i].minTheta)*incRate[i];
                if(QUAconfig[i].theta < QUAconfig[i].minTheta)
                    QUAconfig[i].theta=QUAconfig[i].minTheta;
                //calculate new distance
                POIcurrent = ROBgetPfromM(ROBcalculMGD(QUAconfig, n));
				newDist = distance(POIcurrent, POItarget);
                if(newDist < lastDist)
                {//We get a better value
                    //Keep the new value
                    lastDist = newDist;
                    flag = true;
                    //incRate[i]*=2;
                }
				else
                {
                    //Keep the original value
                    QUAconfig[i].theta=lastX;
                    //Adjust increment rate
                    incRate[i]/=2;
                    if(incRate[i]>BORNE_RATE[i])
                       flag = true;
                    newDist = lastDist;
                }
                
            }
            printf("Theta %d,   final: theta=%f; dis=%f; incRate=%f; currPoint=(%f,%f,%f)\n\n",
                i+1,QUAconfig[i].theta,newDist,incRate[i], 
                POIcurrent.dx, POIcurrent.dy, POIcurrent.dz);
			if(newDist<BORNE_DIS)
			{
				delete []incRate;
                return true;
			}
        }
    }

    if(true == testLocalMinimum(QUAconfig, n))
    {
        printf("We've probably encountered a \"Local minimum\" situation. Try again.\n");
    }
	delete []incRate;
    return false;
}

/**Test whether the algorithm IAA
*falls into the "local minimum" situation. This situation 
*often appears when we have limites for the articulars variables.
*/
bool Robotique::testLocalMinimum(Quadruplet* QUAconfig, int n)
{
    
    int i;
    for(i=0 ; i<n; i++)
    {
        if(QUAconfig[i].theta == QUAconfig[i].maxTheta ||
            QUAconfig[i].theta == QUAconfig[i].minTheta)
            return true;
    }
    //Point POIbegin(0,0,0);
    //Point POIend;
    //double dTmp;
    //int i;
    //for(i=1 ; i<n; i++)
    //{
    //    POIend = ROBgetPfromM(ROBcalculMGD(QUAconfig, i));
		
    //    //test whether the 3 points: POIbegin, POIcurrent, POIend, 
    //    //are in the same line.
    //    dTmp = (POIend.dx - POIbegin.dx)/(POIbegin.dx - POIcurrent.dx);
    //    if( dTmp == (POIend.dy - POIbegin.dy)/(POIbegin.dy - POIcurrent.dy) &&
    //        dTmp == (POIend.dz - POIbegin.dz)/(POIbegin.dz - POIcurrent.dz))
    //        return true;
    //    else
    //    {
    //        POIbegin = POIend;
    //    }
    //}
    return false;
}
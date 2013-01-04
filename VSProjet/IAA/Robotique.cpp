#include "Robotique.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

#define BORNE_DIS 0.0001
Robotique::Robotique()
{
}


Robotique::~Robotique()
{
}

double jd2(double dsrc)
{
	return dsrc;
	//return ((int)((dsrc)*1000))/1000.0;
}

Matrice Robotique::ROBdenavit(Quadruplet QUAfour)
{
	Matrice MATtmp;
	MATtmp[0][0]=jd2(cos(QUAfour.thita)); MATtmp[0][1]=jd2(-sin(QUAfour.thita)*cos(QUAfour.alpha)); MATtmp[0][2]=jd2(sin(QUAfour.thita)*sin(QUAfour.alpha));  MATtmp[0][3]=jd2(QUAfour.a*cos(QUAfour.thita));
	MATtmp[1][0]=jd2(sin(QUAfour.thita)); MATtmp[1][1]=jd2(cos(QUAfour.thita)*cos(QUAfour.alpha));  MATtmp[1][2]=jd2(-cos(QUAfour.thita)*sin(QUAfour.alpha)); MATtmp[1][3]=jd2(QUAfour.a*sin(QUAfour.thita));
	MATtmp[2][0]=0;			   MATtmp[2][1]=jd2(sin(QUAfour.alpha));			  MATtmp[2][2]=jd2(cos(QUAfour.alpha));			 MATtmp[2][3]=jd2(QUAfour.d);
	MATtmp[3][0]=0;			   MATtmp[3][1]=0;						      MATtmp[3][2]=0;							 MATtmp[3][3]=1;
	return MATtmp;
}


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

//    for(int i=0; i<3; i++)
//    {
//        printf("(%f,%f,%f),(%f,%f,%f),tmp=%f;dist=%f.\n",point1[0],point1[1],point1[2],
//               point2[0],point2[1],point2[2],tmp, dist);
//    }
    return dist;
}

bool Robotique::IAA(Quadruplet QUAconfig[], int n, Point POItarget)
{
	int i;
    bool flag = true;
    double lastX;//The thita of the last time
    
	//A table of increment rate
    double *incRate = new double[n];
    
	//stop condition
	double *BORNE = new double[n];
    
	//The coordinate of the current point that we can reach
    Point POIcurrent;
    
	//The distance between the current point and the target point
    double lastDist, newDist;
    
	//Initialisation
    for(i=0; i<n; i++)
    {
		QUAconfig[i].QUAset_random_thita();
        incRate[i]=0.15;//cf the article of Abdelhak MOUSSAOUI
		BORNE[i]=0.000001/((QUAconfig[i].maxThita - QUAconfig[i].minThita)*180/PI);//precision:0.00...1°
    }

	POIcurrent = ROBgetPfromM(ROBcalculMGD(QUAconfig, n));
    lastDist = distance(POIcurrent, POItarget);

    int j=0;
    while(flag)
    {
        flag = false;
		//for each value of thita
        for(i=0; i<n; i++)
        {
			printf("Thita %d: thita_begin=%f; dis_old=%f; incRate=%f\n",i+1,QUAconfig[i].thita,lastDist,incRate[i]);
            lastX = QUAconfig[i].thita;
            //inc
			QUAconfig[i].thita+=(QUAconfig[i].maxThita-QUAconfig[i].minThita)*incRate[i];
            if(QUAconfig[i].thita > QUAconfig[i].maxThita)
                QUAconfig[i].thita = QUAconfig[i].maxThita;

            POIcurrent = ROBgetPfromM(ROBcalculMGD(QUAconfig, n));
			newDist = distance(POIcurrent, POItarget);
            printf("Thita %d:       newX=%f; newpoint:(%f;%f;%f); dis=%f\n", i+1, QUAconfig[i].thita,POIcurrent.dx,POIcurrent.dy,POIcurrent.dz,newDist);
            
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
				QUAconfig[i].thita = lastX - (QUAconfig[i].maxThita-QUAconfig[i].minThita)*incRate[i];
                if(QUAconfig[i].thita < QUAconfig[i].minThita)
                    QUAconfig[i].thita=QUAconfig[i].minThita;
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
                    QUAconfig[i].thita=lastX;
                    //Adjust increment rate
                    incRate[i]/=2;
                    if(incRate[i]>BORNE[i])
                       flag = true;
                    newDist = lastDist;
                }
                
            }
            printf("Thita %d:   x_end=%f; dis_new=%f; incRate=%f\n\n",i+1,QUAconfig[i].thita,newDist,incRate[i]);
			if(newDist<BORNE_DIS)
			{
				delete []incRate;
                return true;
			}
            //else if(incRate[i]>0.00001)
              //  flag = true;
        }
    }

	delete []incRate;
    return false;
}
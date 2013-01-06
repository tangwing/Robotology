#include "Quadruplet.h"

void Quadruplet::QUAset_random_theta()
{
    if(maxTheta <= minTheta)
        theta = minTheta;
    else
    	theta = minTheta+rand()%((int)(maxTheta - minTheta));
}
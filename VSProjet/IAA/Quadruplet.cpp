#include "Quadruplet.h"

void Quadruplet::QUAset_random_theta()
{
	theta = minTheta+rand()%((int)(maxTheta - minTheta));
}
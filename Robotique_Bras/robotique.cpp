#include "stdafx.h"

void denavit(float thita, float d, float alpha, float a, float res[4][4])// les matrices élémentaires associées à ces instances des quadruplets.
{
	
	res[0][0]=jd2(cos(thita)); res[0][1]=jd2(-sin(thita)*cos(alpha)); res[0][2]=jd2(sin(thita)*sin(alpha));  res[0][3]=jd2(a*cos(thita));
	res[1][0]=jd2(sin(thita)); res[1][1]=jd2(cos(thita)*cos(alpha));  res[1][2]=jd2(-cos(thita)*sin(alpha)); res[1][3]=jd2(a*sin(thita));
	res[2][0]=0;			   res[2][1]=jd2(sin(alpha));			  res[2][2]=jd2(cos(alpha));			 res[2][3]=d;
	res[3][0]=0;			   res[3][1]=0;						      res[3][2]=0;							 res[3][3]=1;
	return;
}

float jd2(float src)
{
	return ((int)src*100)/100.00f;
}
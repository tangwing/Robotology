#ifndef ROBOTIQUE_H
#define ROBOTIQUE_H
#include <cmath>
#define PI 3.14159
using namespace std;


void denavit(double thita, double d, double alpha, double a, double res[4][4]);
double jd2(double);

/*Return the distance between 2 point in the space*/
double distance(double point1[3], double point2[3]);
double* IAA(double thita[], double d[], double alpha[],
           double a[], int n, double range[][2], double targetPoint[3]);

#endif

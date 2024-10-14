#include <bits/stdc++.h>
using namespace std;
int main()
{
double* pt0=0;
double* pt1=4096;
double* pt2=(double*)4096;
void* pt3=pt1;
pt1=pt3;
pt1=(double*)pt3;
double d1=36;
const double d2=36;
double* pt4=&d1;
const double* pt5=&d1;
*pt4=2.1;
*pt5=2.1;
pt4=&d2;
pt5=&d2;
double* const pt6=&d1;
pt6=&d1;
*pt6=2.78;
double* const pt6b=&d2;
const double* const pt7=&d1;
pt7=&d1;
*pt7=2.78;
double const* pt8=&d1;
pt8=&d2;
pt8=&d1;
*pt8=3.14;
}
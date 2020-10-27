/*

This program is used to calculate the radius of a gravitational assistance from
the Earth to Saturn using Jupiter.

20 November 2020

Vehiculos Aeroespaciales

*/


#include <iostream>
#include <math.h>

//
//
//			 CONSTANTS
//
//

// general constants

const double G_CONST   = 6.67e-11; // N*m2/Kg2


// planet constants

const double EARTH_MASS   = 5.976e24;   // Kg
const double JUPITER_MASS = 1.8982e27;  // Kg
const double SATURN_MASS  = 5.6834e26;  // Kg
const double SUN_MASS     = 1.989e30;   // Kg

const double EARTH_RADIOUS   = 6.378e6;    // m
const double JUPITER_RADIOUS = 7.1492e7;   // m
const double SATURN_RADIOUS  = 6.033e7;    // m

const double EARTH_ORBIT     = 1.496e11;         // m
const double JUPITER_ORBIT   = 5.20*EARTH_ORBIT; // m
const double SATURN_ORBIT    = 9.54*EARTH_ORBIT; // m


// mission constants

const double ORBIT_TO_SATURN    = 10.5*EARTH_ORBIT;       // m
const double ORBIT_TO_JUPITER   = 5.5*EARTH_ORBIT;        // m
const double ORBIT_IN_SATURN    = 4.5e8+SATURN_RADIOUS;   // m


//
//
//			 PLANET CLASS
//
//


class Planet
{
public:

   Planet ();

private:
};



//
//
//			  MAIN METHOD
//
//


int main ()
{
   std::cout.setf(std::ios::fixed);
   std::cout.precision(4);


   double a = (EARTH_ORBIT + ORBIT_TO_JUPITER)/2;
   double e = (ORBIT_TO_JUPITER - EARTH_ORBIT) / (ORBIT_TO_JUPITER + EARTH_ORBIT);
   double tetha = acos((1/e)*((1-e*e)*a/JUPITER_ORBIT-1));
   double vr1 = sqrt(G_CONST*SUN_MASS/(a*(1-e*e)))*e*sin(tetha);
   double vtetha1 = sqrt(G_CONST*SUN_MASS/(a*(1-e*e)))*(1 + e*cos(tetha));
   double vthetaJ = sqrt(G_CONST*SUN_MASS/JUPITER_ORBIT) - vtetha1;
   double vinf = sqrt(vthetaJ*vthetaJ + vr1*vr1);

   std::cout << "a: \t" << a << std::endl;
   std::cout << "e: \t" << e << std::endl;
   std::cout << "tetha: \t" << tetha << std::endl;
   std::cout << "vr1: \t" << vr1 << std::endl;
   std::cout << "vtetha1: \t" << vtetha1 << std::endl;
   std::cout << "vthetaJ: \t" << vthetaJ << std::endl;
   std::cout << "vinf: \t" << vinf << std::endl;
}
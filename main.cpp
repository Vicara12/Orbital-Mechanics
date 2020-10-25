/*

This program is used to calculate the total deltaV needed in order to send an
object from Earth orbit to Saturn with and without the gravitational assistence
of Jupiter.

20 November 2020

Vehiculos Aeroespaciales

*/


#include <iostream>

//
//
//			 CONSTANTS
//
//

// general constants

const double G_CONST   6.67e-11; // N*m2/Kg2


// planet constants

const double EARTH_MASS   5.976e24;   // Kg
const double JUPITER_MASS 1.8982e27;  // Kg
const double SATURN_MASS  5.6834e26;  // Kg
const double SUN_MASS     1.989e30;   // Kg

const double EARTH_RADIOUS   6.378e6;    // m
const double JUPITER_RADIOUS 7.1492e7;   // m
const double SATURN_RADIOUS  6.033e7;    // m

const double EARTH_ORBIT     1.496e11;         // m
const double JUPITER_ORBIT   5.20*EARTH_ORBIT; // m
const double SATURN_ORBIT    9.54*EARTH_ORBIT; // m


// mission constants

const double ORBIT_TO_SATURN    10.5*EARTH_ORBIT;       // m
const double ORBIT_TO_JUPITER   5.5*EARTH_ORBIT;        // m
const double ORBIT_IN_SATURN    4.5e8+SATURN_RADIOUS;   // m


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
}



//
//
//			  MAIN METHOD
//
//


int main ()
{
   //
}
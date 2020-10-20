
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// general constants

#define G_CONST   6.67e-11; // N*m2/Kg2


// planet constants

#define EARTH_MASS   5.976e24;   // Kg
#define JUPITER_MASS 1.8982e27;  // Kg
#define SATURN_MASS  5.6834e26;  // Kg
#define SUN_MASS     1.989e30;   // Kg

#define EARTH_RADIOUS   6.378e6;    // m
#define JUPITER_RADIOUS 7.1492e7;   // m
#define SATURN_RADIOUS  6.033e7;    // m

#define EARTH_ORBIT     1.496e11;         // m
#define JUPITER_ORBIT   5.20*EARTH_ORBIT; // m
#define SATURN_ORBIT    9.54*EARTH_ORBIT; // m


// mission constants

#define ORBIT_TO_SATURN    10.5*EARTH_ORBIT;       // m
#define ORBIT_TO_JUPITER   5.5*EARTH_ORBIT;        // m
#define ORBIT_IN_SATURN    4.5e8+SATURN_RADIOUS;   // m


#endif
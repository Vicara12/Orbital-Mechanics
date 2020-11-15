/*

This program is used to calculate the radius of a gravitational assistance from
the Earth to Saturn using Jupiter.

20 October 2020

Vehiculos Aeroespaciales


Some default parameters for this program might be:

min:        7.1492e7  m   (Jupiter's radious)
max:        1e15      m
precision:  1         m
max iters:  1e6

The computational cost of the algorithm is log2, so greater intervals or
precission should not be a problem.

expected iterations = log2((max-min)/precision)

Output computations lets the user see how the optimal radious is being searched.

*/


#include <iostream>
#include <math.h>




//
//
//			 PARAMETERS
//
//

// all speeds are defined at the encounter point and are relative to Jupiter

const double V_r   =  3565.7818; // m/s    radial speed
const double V_ang = -5609.1811; // m/s    angular speed
const double V_inf =  6646.6316; // m/s    speed at an "infinite" distance of Jupiter

// MU values of the sun and Jupiter (G_constant * mass)

const double MU_Jupiter = 6.67e-11*1.8982e27; // N*m2/Kg2 * Kg
const double MU_Sun     = 6.67e-11*1.9890e30; // N*m2/Kg2 * Kg

const double Jupiter_orbit_r  = 5.2*1.496e11; // m    5.2 UA
const double Earth_orbit_r    = 1.496e11;    // m    1 UA

const double Jupiter_radious  = 7.1492e7;     // m

const double Target_apoapsis     = 10.5*1.496e11;   // m     target apoapsis after asistence




//
//
//			 METHODS
//
//


/*
 * Calculates the speed of the spaceship relative to the sun after the encounter
 * with Jupiter given the darious of the periapsis (from the center of Jupiter).
 */
double postAssistanceSpeed (double radious,bool pos_angle, bool display = false)
{
   // calculate excentricity of the orbit arround Jupiter
   double e = 1 + (V_inf*V_inf*radious)/MU_Jupiter;

   // calculate the turn angle of the V vector with the given radious
   double delta = 2*asin(1/e);

   if (not pos_angle) delta *= -1;

   double jupiter_speed = sqrt(MU_Sun/Jupiter_orbit_r);

   // compute the new V vector with the delta turn (relative to the sun)
   double new_V_r    = V_r*cos(delta) - V_ang*sin(delta);
   double new_V_ang  = jupiter_speed + (V_r*sin(delta) + V_ang*cos(delta));
   double new_V      = sqrt(new_V_r*new_V_r + new_V_ang*new_V_ang);


   // now calculate the parameters for the orbit after the encounter

   // a can be obtained from the energy formula for eliptical orbits
   double new_a = 1/(2/Jupiter_orbit_r - new_V*new_V/MU_Sun);

   // e can be obtained from the angular momentum formula, taking into account
   // that h = V_theta * r
   double new_e = sqrt(1-pow(new_V_ang*Jupiter_orbit_r, 2)/(MU_Sun*new_a));

   // this formula can be derived with the following formulas
   // a = (R_apoapsis + R_periapsis)/2
   // e = (R_apoapsis - R_periapsis)/(R_apoapsis + R_periapsis)
   double new_ap = new_a*(new_e+1);

   if (display)
   {
      std::cout << "delta: \t\t" << delta << " rad / " << (delta*180.0/M_PI) << " dg\n";
      std::cout << "radial speed: \t" << new_V_r << " m/s\n";
      std::cout << "angular speed: \t" << new_V_ang << " m/s\n";
      std::cout << "total speed: \t" << new_V << " m/s\n";
      std::cout << "apoapsis: \t" << new_ap << " m / " << (new_ap/Earth_orbit_r) << " UA\n";
   }
}


/*
 * Search for an optimal radious in the min and max interval. Results will be
 * placed in the opt_radious variable. The speed after the encounter shoud be at
 * a maximum distance of precision m/s from the target speed.
 * The returned value indicates wether a value of the radious that satisfies the
 * constraint could be found (if false is returned, opt_radious returns the
 * closest radious in the interval to the optimal one).
 * If verbose mode is enabled, the output will show the iteration, min, max,
 * current radious, v_after_encounter, Target_speed, the current precision and
 * the desired precssion for each iteration of the loop.
 * 
 * Computational cost of the algorithm: log2
 */
bool findRaious (double min,
                 double max,
                 double precision,
                 bool pos_angle,
                 int max_iters,
                 int& iters,
                 double& opt_radious,
                 bool verbose)
{
   if (verbose)
      std::cout << "FINDING " << (pos_angle ? "POSITIVE" : "NEGATIVE")
            << " ANGLE:\n";


   for (int i = 0; i < max_iters; i++)
   {
      iters = i;

      opt_radious = (max - min)/2 + min;

      double apoapsis_after_encounter = postAssistanceSpeed(opt_radious, pos_angle);

      // if verbose mode selected, output computations
      if (verbose)
      {
         std::cout << "\n\n\n";
         std::cout << "iteration: \t" << i << "\n";
         std::cout << "min / max: \t" << min << " m / " << max << " m\n";
         std::cout << "current radious: \t" << opt_radious << " m\n";
         std::cout << "apoapsis after encounter / target apoapsis: \t" <<
                     apoapsis_after_encounter << " m / " << Target_apoapsis << " m\n";
         std::cout << "current precision / desired precision: \t" <<
                     (abs(apoapsis_after_encounter - Target_apoapsis)) << " m / " <<
                     precision << " m\n";
      }

      // if radious is valid, return true
      if (abs(Target_apoapsis - apoapsis_after_encounter) <= precision)  return true;

      // if a new iteration is needed, readjust the values of min and max
      Target_apoapsis > apoapsis_after_encounter ?  max = opt_radious : min = opt_radious;
   }

   return false;
}


int main ()
{
   std::cout.setf(std::ios::fixed);
   std::cout.precision(4);

   double min, max, precision;
   int max_iters;
   std::string verbose;

   std::cout << "\nminimum value for radious: ";      std::cin >> min;
   std::cout << "\nmaximum value for radious: ";      std::cin >> max;
   std::cout << "\nprecission: ";                     std::cin >> precision;
   std::cout << "\nmaximum number of iterations: \t"; std::cin >> max_iters;
   std::cout << "\noutput computations(y/n): ";       std::cin >> verbose;


   // two iters, one for positive an other for negative turn angles
   for (int i = 0; i < 2; i++)
   {
      bool pos_angle = (i == 0); // indicates sign of turn angle

      std::cout << "\n\n\n* SEARCHING OPTIMAL RADIOUS FOR " <<
            (pos_angle ? "POSITIVE" : "NEGATIVE") << " TURN ANGLE\n";

      double optimal_radious;
      int iters;
      bool successful;
      
      successful = findRaious(min,
                              max,
                              precision,
                              pos_angle,
                              max_iters,
                              iters,
                              optimal_radious,
                              verbose == "y");


      // display results
      if (successful)
      {
         std::cout << "\n\nCOMPUTATION SUCCESSFUL\n";
         std::cout << "iterations: \t" << iters << "\n";
         std::cout << "radious: \t" << optimal_radious << " m\n";
         std::cout << "height: \t" << (optimal_radious - Jupiter_radious) << " m\n";

         postAssistanceSpeed(optimal_radious, pos_angle, true);
         
         std::cout << "target apoapsis: \t" << Target_apoapsis << " m\n";
      }
      else
      {
         std::cout << "\n\nCOMPUTATION FAILED\n";
         std::cout << "A suitable radious could not be found in the given ";
         std::cout << "interval with the precision and turn angle sign selected.\n\n";
         std::cout << "The closest value is:\n";

         std::cout << "radious: \t" << optimal_radious << " m\n";
         postAssistanceSpeed(optimal_radious, pos_angle, true);
      }
   }
}
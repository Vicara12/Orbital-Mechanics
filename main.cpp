/*

This program is used to calculate the radius of a gravitational assistance from
the Earth to Saturn using Jupiter.

20 November 2020

Vehiculos Aeroespaciales


Some default parameters for this program might be:

min:        7.1492e7  m   (Jupiter's radious)
max:        1e16      m
precision:  0.001     m/s

The computational cost of the algorithm is log2, so greater intervals should not
be a problem.

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

const double V_r   = 3565.7818; // m/s    radial speed
const double V_ang = 5609.1811; // m/s    angular speed
const double V_inf = 5609.1811; // m/s    speed at an "infinite" distance of Jupiter

// MU values of the sun and Jupiter (G_constant * mass)

const double MU_Jupiter = 6.67e-11*1.8982e27; // N*m2/Kg2 * Kg
const double MU_Sun     = 6.67e-11*1.9890e30; // N*m2/Kg2 * Kg

const double Jupiter_orbit_r  = 5.2*1.496e11; // m    5.2 UA

const double Jupiter_radious  = 7.1492e7;     // m

const double Target_speed     = 16019.4180;   // m/s     speed needed afer assistance




//
//
//			 METHODS
//
//


/*
 * Calculates the speed of the spaceship relative to the sun after the encounter
 * with Jupiter given the darious of the periapsis (from the center of Jupiter).
 */
double postAssistanceSpeed (double radious, bool display = false)
{
   // calculate excentricity of the orbit arround Jupiter
   double e = 1 + (V_inf*V_inf*radious)/MU_Jupiter;

   // calculate the turn angle of the V vector with the given radious
   double delta = 2*asin(1/e);

   double jupiter_speed = sqrt(MU_Sun/Jupiter_orbit_r);

   // compute the new V vector with the delta turn (relative to the sun)
   double new_V_r    = V_r*cos(delta) - V_ang*sin(delta);
   double new_V_ang  = V_r*sin(delta) + V_ang*cos(delta) + jupiter_speed;
   double new_V      = sqrt(new_V_r*new_V_r + new_V_ang*new_V_ang);

   if (display)
   {
      std::cout << "radial speed: \t" << new_V_r << " m/s\n";
      std::cout << "angular speed: \t" << new_V_ang << " m/s\n";
      std::cout << "total speed: \t" << new_V << " m/s\n";
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
                 double& opt_radious,
                 bool verbose)
{
   int iteration = 0;
   int expected = log2((max - min)/precision) + 1;

   while (1)
   {
      opt_radious = (max - min)/2 + min;

      double v_after_encounter = postAssistanceSpeed(opt_radious);

      // if verbose mode selected, output computations
      if (verbose)
      {
         std::cout << "\n\n\n";
         std::cout << "iteration / expected iters: \t" << iteration << " / " <<
                     expected << "\n";
         std::cout << "min / max: \t" << min << " m / " << max << " m\n";
         std::cout << "current radious: \t" << opt_radious << " m\n";
         std::cout << "v after encounter / target speed: \t" <<
                     v_after_encounter << " m/s / " << Target_speed << " m/s\n";
         std::cout << "current precision / desired precision: \t" <<
                     (abs(v_after_encounter - Target_speed)) << " m/s / " <<
                     precision << " m/s\n";
      }

      // if radious is valid, return true
      if (abs(Target_speed - v_after_encounter) <= precision)  return true;

      // if the remaining interval is smaller than the precission, no optimal
      // radious exists in the given interval
      if (abs(max - min) < precision)     return false;

      // if a new iteration is needed, readjust the values of min and max
      v_after_encounter < Target_speed ?  max = opt_radious : min = opt_radious;

      iteration++;
   }
}


int main ()
{
   std::cout.setf(std::ios::fixed);
   std::cout.precision(4);

   double min, max, precision;
   std::string verbose;

   std::cout << "\nminimum value for radious: "; std::cin >> min;
   std::cout << "\nmaximum value for radious: "; std::cin >> max;
   std::cout << "\nprecission: ";                std::cin >> precision;
   std::cout << "\noutput computations(y/n): ";  std::cin >> verbose;


   double optimal_radious;
   bool successful;
   
   successful = findRaious(min, max, precision, optimal_radious, verbose == "y");


   // display results
   if (successful)
   {
      std::cout << "\n\nCOMPUTATION SUCCESSFUL\n";
      std::cout << "radious: \t" << optimal_radious << " m\n";
      std::cout << "height: \t" << (optimal_radious - Jupiter_radious) << " m\n";

      postAssistanceSpeed(optimal_radious, true);
      
      std::cout << "target speed: \t" << Target_speed << " m/s\n";
   }
   else
   {
      std::cout << "\n\nCOMPUTATION FAILED\n";
      std::cout << "A suitable radious could not be found in the given ";
      std::cout << "interval with the precision selected.\n";
   }
   
}
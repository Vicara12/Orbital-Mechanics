/*

This program is used to calculate the time it takes to complete part of an
orbit (circular, eliptical or hiperbolic) given two angles or two radiuses
and the mass of the body that it orbits.

The zero angle is at the periapsis and increase with the direction of the
object's movement. The program internally works with the range [pi, -pi), but
the format [0, 2*pi) is also accepted at the input.

13 November 2020

Vehiculos Aeroespaciales

The cost of the algotirhm is linear, so very accurate precission might increase
the computational time noticeably.

*/

#include <iostream>
#include <math.h>

const double G = 6.67e-11;    //    N*m2/Kg2    Gravitational constant

// Transforms the angle format [0, 2*pi) to  [pi, -pi)
double correctAngle (double angle)
{
   if (angle > M_PI)    return angle - 2*M_PI;
   if (angle <= -M_PI)  return angle + 2*M_PI;
   return angle;
}

// Returns the delta angle between a1 and a2. If clockwise == true the angle
// measured clockwise is returned, otherwise the smaller of both is returned
double angleDiference (double a1, double a2, bool clockwise = false)
{
   bool swaped = false;
   // if a1 > a2 swap them
   if (a1 > a2)
   {
      double buff = a1;
      a1 = a2;
      a2 = buff;
      swaped = true;
   }

   if (clockwise) return (swaped ? 2*M_PI - (a2 - a1) : a2 - a1);
   else           return (a2 - a1 > M_PI ? 2*M_PI - (a2 - a1) : a2 - a1);
}


// Given an orbit and an itial and final angle intervals, computes the total
// distance and time of travel
void computeOrbit (double a_i,
                   double a_f,
                   double precission,
                   double mass,
                   double e,
                   double a,
                   double &total_distance,
                   double &total_time )
{
   total_distance = total_time = 0;

   bool ellipse = (e < 1);

   for (double ang = a_i;
        angleDiference(ang, a_f) > precission;
        ang += precission)
   {
      // using the cosinus rule we can aproximate the orbit with triangles
      double r1 = (ellipse ? 1 : -1) * a*(1-e*e)/(1+e*cos(ang));
      double r2 = (ellipse ? 1 : -1) * a*(1-e*e)/(1+e*cos(ang + precission));
      double delta_x = sqrt(r1*r1 + r2*r2 - 2*r1*r2*cos(precission));

      double v = sqrt(mass*G*(2/r1 + (ellipse ? -1 : 1)/a));

      total_distance += delta_x;
      total_time += delta_x/v;
   }
}


int main ()
{
   bool a_i_radial_speed_pos, a_f_radial_speed_pos;   // indicates whether the
                        // indicated radiouses are going towards or
                        // moving away from the body (to distinguish the both
                        // possibilities for each radious)

   double r_i, r_f;     // initial and final radiouses
   double a_i, a_f;     // initial and final angles
   double precission;   // angle diferential
   double mass;         // mass of the body being orbited
   double e, a;         // orbit parameters

   std::string answer = "d";  // stores the answer of the user
                              // (use radiouses or degrees)

   std::cout << "\norbit excentricity (e): ";     std::cin >> e;
   std::cout << "\norbit semi-major axis (a): ";  std::cin >> a;
   std::cout << "\nmain body mass: ";             std::cin >> mass;

   // if the orbit is circular, it doesn't makes sense to use radiouses
   if (e != 0)
   {
      std::cout << "\nuse radiouses or degrees? (r/d): ";  std::cin >> answer;
   }

   if (answer == "r")
   {
      std::string radial_v;

      std::cout << "\ninitial radious: ";
      std::cin >> r_i;

      std::cout << "\nradial speed is positive? (y/n): ";
      std::cin >> radial_v;
      a_i_radial_speed_pos = (radial_v == "y");

      std::cout << "\nfinal radious: ";
      std::cin >> r_f;

      std::cout << "\nradial speed is positive? (y/n): ";
      std::cin >> radial_v;
      a_f_radial_speed_pos = (radial_v == "y");

      a_i = acos(((e < 1 ? 1 : -1) * a*(1-e*e)/r_i - 1)/e);
      a_f = acos(((e < 1 ? 1 : -1) * a*(1-e*e)/r_f - 1)/e);

      // if the object is going towards the mass, change the sign of the angles
      if (not a_i_radial_speed_pos)  a_i *= -1;
      if (not a_f_radial_speed_pos)  a_f *= -1;

      std::cout << "\nangles used: " << a_i << " to " << a_f << "\n\n";
   }
   else
   {
      std::cout << "\n\nThe zero angle is at periapsis and it increases with\n";
      std::cout << "the object's movement. Both formats [pi, -pi) and [0, 2*pi)\n";
      std::cout << "are accepted.\n";

      std::cout << "\ninitial angle: ";  std::cin >> a_i;
      std::cout << "\nfinal angle: ";    std::cin >> a_f;

      // put angles in the correct format
      a_i = correctAngle(a_i);
      a_f = correctAngle(a_f);
   }

   int divisions;

   std::cout << "\nnumber of divisions: "; std::cin >> divisions;

   // get the angle for each division
   precission = angleDiference(a_i, a_f, true) / divisions;

   double total_distance, total_time;

   computeOrbit(a_i, a_f, precission, mass, e, a, total_distance, total_time);


   std::cout << "\n\n\nRESULTS:\n\ndistance: \t" << total_distance;
   std::cout << " m\ntime: \t\t" << total_time << " s\n\n";
}
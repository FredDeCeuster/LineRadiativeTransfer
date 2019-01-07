#include <pybind11/pybind11.h>
#include <math.h>


namespace py = pybind11;

#include <iostream>
using namespace std;



// Constants

const double PI              = 3.141592653589;    // pi
const double FOUR_PI         = 12.56637061436;    // 4*pi
const double INVERSE_SQRT_PI = 0.5641895835478;   // 1/sqrt(pi)

const double CC              = 2.99792458E+8;    // [m/s] speed of light
const double HH              = 6.62607004E-34;   // [J*s] Planck's constant
const double KB              = 1.38064852E-23;   // [J/K] Boltzmann's constant
const double MP              = 1.6726219E-27;    // [kg] proton mass
const double T_CMB           = 2.7254800;        // [K] CMB temperature

const double SECONDS_IN_YEAR = 3.1556926E+7;    // number of seconds in one year

const double C_SQUARED       = 8.98755179E+16;   // [m^2/s^2] speed of light squared

const double v_turb          = 0.12012E3;

const double V_TURB_OVER_C_ALL_SQUARED = v_turb * v_turb / C_SQUARED;   // (v_turb / c)^2
const double TWO_KB_OVER_MP_C_SQUARED  = 2.0 * KB / (MP * C_SQUARED);   // 2.0*Kb/Mp*c^2


// Model Parameters

inline double temperature (
    const double x        )
{
  return 100.0; 
}

inline double velocity (
    const double x     )
{
  return 5.0E-3*x; 
}

inline double abundance (
    const double x      )
{
  return 1.0; 
}


inline double


inline double doppler_shift (
    const double x1,
    const double x2         )
{
  
  return 1.0 + (velocity(x1) - velocity(x2)) / CC;

}

///  profile_width: line profile width due to thermal and turbulent Doppler shifts
///    @param[in] x: position
///    @param[in] freq_line: frequency of the line under consideration
///    @return width of the correpsonding line profile
//////////////////////////////////////////////////////////////////////////////////

inline double profile_width (
    const double x,
    const double freq_line  )
{

  return freq_line * sqrt (TWO_KB_OVER_MP_C_SQUARED*temperature(x) + V_TURB_OVER_C_ALL_SQUARED);

}




///  profile: line profile function
///////////////////////////////////
 
inline double profile      (
    const double nu,
    const double x,
    const double freq_line )
{

  const double inverse_width = 1.0 / profile_width (x, freq_line);
  const double  sqrtExponent = inverse_width * (nu - freq_line);
  const double  exponent     = - sqrtExponent * sqrtExponent;


  return INVERSE_SQRT_PI * inverse_width * exp (exponent);

}


///  optical_depth: line optical depth between start and stop
/////////////////////////////////////////////////////////////

double optical_depth_p (
    const double nu,
    const double chi,
    const double freq_line,
    const double start,
    const double stop,
    const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(xi, stop), xi, freq_line);
  }

  result *= chi;


  return result;

}



///  optical_depth: line optical depth between start and stop
/////////////////////////////////////////////////////////////

double optical_depth_m (
    const double nu,
    const double chi,
    const double freq_line,
    const double start,
    const double stop,
    const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(start, xi), xi, freq_line);
  }

  result *= chi;


  return result;

}

//double optical_depth_m (
//    const double nu,
//    const double chi,
//    const double freq_line,
//    const double x,
//    const double L,
//    const long npoints )
//{
//
//  const double start = x;
//  const double stop  = L;
//
//  const double dx = (stop-start) / npoints;
//
//  double result = 0.0;
//
//  for (double xi = start; xi < stop; xi += dx)
//  {
//    result += profile (nu, xi, freq_line);
//  }
//  
//  result *= chi;
//
//
//  return result;
//
//}
//
//
//
double intensity_p         (
    const double nu,
    const double eta,
    const double chi,
    const double freq_line,
    const double start,
    const double stop,
    const double dx        )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(start, xi), xi, freq_line)
              * exp (-optical_depth_p (nu, chi, freq_line, start, xi, dx));
  }

  result *= eta;


  return result;

}

double intensity_m         (
    const double nu,
    const double eta,
    const double chi,
    const double freq_line,
    const double start,
    const double stop,
    const double dx        )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(xi, stop), xi, freq_line)
              * exp (-optical_depth_p (nu, chi, freq_line, xi, stop, dx));
  }

  result *= eta;


  return result;

}



double mean_intensity      (
    const double nu,
    const double eta,
    const double chi,
    const double freq_line,
    const double zero,
    const double x,
    const double L,
    const double dx        )
{

  return 0.5 * (  intensity_m (nu, eta, chi, freq_line, x,    L, dx)
                + intensity_p (nu, eta, chi, freq_line, zero, x, dx) );

}


double test (const double q)
{
  return 5.0;
}

PYBIND11_MODULE (functions, functions_module)
{
  functions_module.def ("test",            &test,            "test"                       );
  functions_module.def ("profile",         &profile,         "Line profile function"      );
  functions_module.def ("optical_depth_m", &optical_depth_m, "Optical depth (- direction)");
  functions_module.def ("optical_depth_p", &optical_depth_m, "Optical depth (+ direction)");
  functions_module.def ("intensity_m",     &intensity_m,     "Intensity (- direction)"    );
  functions_module.def ("intensity_p",     &intensity_p,     "intensity (+ direction)"    );
  functions_module.def ("mean_intensity",  &mean_intensity,  "Mean intensity"             );
}

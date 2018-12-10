#include <iostream>
#include <math.h>
using namespace std;

#include "linemodel.hpp"
#include "constants.hpp"
#include "linedata.hpp"
#include "model.hpp"


LineModel ::
  LineModel                   (
      const LINEDATA linedata )
  : linedata (linedata)
{

}

inline double LineModel ::
    initialise          (
        const long line )
{

  freq_line = linedata.frequency  (line);
  eta       = linedata.emissivity (line);
  chi       = linedata.opacity    (line);

}

inline double LineModel ::
    doppler_shift       (
        const double x1,
        const double x2 )
{

  return 1.0 + (velocity(x1) - velocity(x2)) / CC;

}

///  profile_width: line profile width due to thermal and turbulent Doppler shifts
///    @param[in] x: position
///    @param[in] freq_line: frequency of the line under consideration
///    @return width of the correpsonding line profile
//////////////////////////////////////////////////////////////////////////////////

inline double LineModel ::
    profile_width      (
        const double x )
{

  return freq_line * sqrt (TWO_KB_OVER_MP_C_SQUARED*temperature(x) + V_TURB_OVER_C_ALL_SQUARED);

}




///  profile: line profile function
///////////////////////////////////

inline double LineModel ::
    profile             (
        const double nu,
        const double x  )
{

  const double inverse_width = 1.0 / profile_width (x);
  const double  sqrtExponent = inverse_width * (nu - freq_line);
  const double  exponent     = - sqrtExponent * sqrtExponent;

  return INVERSE_SQRT_PI * inverse_width * exp (exponent);

}


///  optical_depth: line optical depth between start and stop
/////////////////////////////////////////////////////////////

double optical_depth_p (
    const double nu,
    const double start,
    const double stop,
    const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(xi, stop), xi);
  }

  result *= chi;


  return result;

}



///  optical_depth: line optical depth between start and stop
/////////////////////////////////////////////////////////////

double optical_depth_m (
    const double nu,
    const double start,
    const double stop,
    const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(start, xi), xi);
  }

  result *= chi;


  return result;

}




double intensity_p         (
    const double nu,
    const double start,
    const double stop,
    const double dx        )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(start, xi), xi)
                 * exp (-optical_depth_p (nu, start, xi, dx));
  }

  result *= eta;


  return result;

}

double intensity_m         (
    const double nu,
    const double start,
    const double stop,
    const double dx        )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * profile (nu*doppler_shift(xi, stop), xi)
                 * exp (-optical_depth_p (nu, xi, stop, dx));
  }

  result *= eta;


  return result;

}



double mean_intensity      (
    const double nu,
    const double zero,
    const double x,
    const double L,
    const double dx        )
{

  return 0.5 * (  intensity_m (linedata, nu, x,    L, dx)
                + intensity_p (linedata, nu, zero, x, dx) );

}

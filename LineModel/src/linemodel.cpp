#include <iostream>
#include <math.h>
using namespace std;

#include "linemodel.hpp"
#include "constants.hpp"
#include "model.hpp"


LineModel ::
  LineModel                    (
      const LINEDATA &linedata,
      const long      line,
      const double    x_min,
      const double    x_max,
      const long      npoints  )
  : line      (line)
  , x_min     (x_min)
  , x_max     (x_max)
  , npoints   (npoints)
  , freq_line (linedata.frequency  (line))
  , eta       (linedata.emissivity (line))
  , chi       (linedata.opacity    (line))
{

  dtau.resize (npoints);
     x.resize (npoints);

  dx = (x_max - x_min) / (double) npoints;

  x[0] = x_min;

  for (long n = 1; n < npoints; n++)
  {
    x[n] = x[n-1] + dx;
  }

}


double LineModel ::
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

double LineModel ::
    profile_width      (
        const double x )
{

  return freq_line * sqrt (TWO_KB_OVER_MP_C_SQUARED*temperature(x) + V_TURB_OVER_C_ALL_SQUARED);

}




///  profile: line profile function
///////////////////////////////////

double LineModel ::
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

double LineModel ::
    optical_depth_p        (
        const double nu,
        const double start,
        const double stop,
        const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * abundance (xi)
                 * profile (nu*doppler_shift(xi, stop), xi);
  }

  result *= chi;


  return result;

}

void LineModel ::
    compute_dtau (double x)
{

  for (double xi = ; n < npoints; n++)
  {
    dtau[n] = dx * abundance (xi)
                 * profile (nu*doppler_shift(xi, stop), xi);
  }

}


///  optical_depth: line optical depth between start and stop
/////////////////////////////////////////////////////////////

double LineModel ::
    optical_depth_m        (
        const double nu,
        const double start,
        const double stop,
        const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * abundance (xi)
                 * profile (nu*doppler_shift(start, xi), xi);
  }

  result *= chi;


  return result;

}




double LineModel ::
    intensity_p            (
        const double B,
        const double nu,
        const double start,
        const double stop,
        const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * abundance (xi)
                 * profile (nu*doppler_shift(start, xi), xi)
                 * exp (-optical_depth_p (nu, start, xi, dx));
  }

  result *= eta;
  result += B * exp (-optical_depth_p (nu, start, stop, dx));


  return result;

}

double LineModel ::
    intensity_m            (
        const double B,
        const double nu,
        const double start,
        const double stop,
        const double dx    )
{

  double result = 0.0;

  for (double xi = start; xi < stop; xi += dx)
  {
    result += dx * abundance (xi)
                 * profile (nu*doppler_shift(xi, stop), xi)
                 * exp (-optical_depth_p (nu, xi, stop, dx));
  }

  result *= eta;
  result += B * exp (-optical_depth_p (nu, start, stop, dx));


  return result;

}



double LineModel ::
    mean_intensity        (
        const double B,
        const double nu,
        const double x,
        const double dx   )
{

  compute_dtau ();

  return 0.5 * (  intensity_m (B, nu, x, x_max, dx)
                + intensity_p (B, nu, x_min, x, dx) );

}

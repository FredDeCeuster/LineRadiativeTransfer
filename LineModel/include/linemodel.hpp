// Magritte: Multidimensional Accelerated General-purpose Radiative Transfer
//
// Developed by: Frederik De Ceuster - University College London & KU Leuven
// _________________________________________________________________________


#ifndef __LINEMODEL_HPP_INCLUDED__
#define __LINEMODEL_HPP_INCLUDED__

#include "linedata.hpp"
#include "types.hpp"


struct LineModel
{
  const long line;           ///< line number

  const double x_min;
  const double x_max;

  const double freq_line;   ///< line frequency
  const double eta;         ///< line emissivity
  const double chi;         ///< line opacity

  const long npoints;

  const double dx;

  Double1 dtau;
  Double1 x;


  LineModel                    (
      const LINEDATA &linedata,
      const long      line,
      const double    x_min,
      const double    x_max,
      const long      npoints  );

  void initialise     (
      const long line );

  double doppler_shift (
      const double x1,
      const double x2  );

  double profile_width (
      const double x   );

  double profile      (
      const double nu,
      const double x  );

  double optical_depth_p (
      const double nu,
      const double start,
      const double stop,
      const double dx    );

  double optical_depth_m (
      const double nu,
      const double start,
      const double stop,
      const double dx    );

  double intensity_p     (
      const double B,
      const double nu,
      const double start,
      const double stop,
      const double dx    );

  double intensity_m     (
      const double B,
      const double nu,
      const double start,
      const double stop,
      const double dx    );

  double mean_intensity (
      const double B,
      const double nu,
      const double x,
      const double dx   );

};


#endif // __LINEMODEL_HPP_INCLUDED__

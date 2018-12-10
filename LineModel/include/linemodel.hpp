// Magritte: Multidimensional Accelerated General-purpose Radiative Transfer
//
// Developed by: Frederik De Ceuster - University College London & KU Leuven
// _________________________________________________________________________


#ifndef __LINEMODEL_HPP_INCLUDED__
#define __LINEMODEL_HPP_INCLUDED__

struct LineModel
{
  const LINEDATA linedata;   ///< line data structure

  long line;           ///< line number

  double freq_line;
  double eta;
  double chi;



  LineModel                   (
      const LINEDATA linedata );

  void initialise    (
      const long line);

  inline double doppler_shift (
      const double x1,
      const double x2         );

  inline double profile_width (
      const double x          );

  inline double profile (
      const double nu,
      const double x    );

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
      const double nu,
      const double start,
      const double stop,
      const double dx    );

  double intensity_m     (
      const double nu,
      const double start,
      const double stop,
      const double dx    );

  double mean_intensity (
      const double nu,
      const double zero,
      const double x,
      const double L,
      const double dx   );
}


#endif // __LINEMODEL_HPP_INCLUDED__

#include "model.hpp"


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

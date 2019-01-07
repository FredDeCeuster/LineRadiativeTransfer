#include "model.hpp"


// Model Parameters

double temperature (
    const double x )
{
  return 100.0 + (1.0E-5)*x;
}

double velocity    (
    const double x )
{
  return (5.0E-5)*x;
}

double abundance   (
    const double x )
{
  return (1.0E+4);
}

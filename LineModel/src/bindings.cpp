#include "linemodel.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;


PYBIND11_MODULE (functions, functions_module)
{
  functions_module.def ("profile",         &profile,         "Line profile function"      );
  functions_module.def ("optical_depth_m", &optical_depth_m, "Optical depth (- direction)");
  functions_module.def ("optical_depth_p", &optical_depth_m, "Optical depth (+ direction)");
  functions_module.def ("intensity_m",     &intensity_m,     "Intensity (- direction)"    );
  functions_module.def ("intensity_p",     &intensity_p,     "intensity (+ direction)"    );
  functions_module.def ("mean_intensity",  &mean_intensity,  "Mean intensity"             );
}

#include "linemodel.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;


PYBIND11_MODULE (LineModel, linemodel_module)
{

  // Module docstring
  linemodel_module.doc() = "linemodel module";


  py::class_<LineModel>(linemodel_module, "LineModel")
      // constructor
      .def (py::init<const LINEDATA &, const long, const double, const double>())
      // functions
//      .def ("initialise",      &LineModel::initialise,      "set line number for model"  )
//      .def ("profile",         &LineModel::profile,         "Line profile function"      )
//      .def ("optical_depth_m", &LineModel::optical_depth_m, "Optical depth (- direction)")
//      .def ("optical_depth_p", &LineModel::optical_depth_m, "Optical depth (+ direction)")
//      .def ("intensity_m",     &LineModel::intensity_m,     "Intensity (- direction)"    )
//      .def ("intensity_p",     &LineModel::intensity_p,     "intensity (+ direction)"    )
      .def ("mean_intensity",  &LineModel::mean_intensity,  "Mean intensity"             );
}

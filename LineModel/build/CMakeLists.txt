cmake_minimum_required (VERSION 2.8.12)

# Set project title
project (LineModel)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Point to the include directory
include_directories (../include)

# Link to pybind11
add_subdirectory (/home/frederik/software/pybind11-2.2.4
  ../include/pybind11)

# include linedata module
include_directories (/home/frederik/Dropbox/Astro/Magritte/modules/linedata/include)
link_directories (/home/frederik/Dropbox/Astro/Magritte/modules/linedata/bin)

# Point library binary file to the bin directory
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/../bin)

# pybind1 command to create the module in bin directory
pybind11_add_module (LineModel
  ../src/model.cpp
  ../src/linemodel.cpp
  ../src/bindings.cpp)

# Link Magritte's linedata class
target_link_libraries (LineModel PRIVATE
  lib_linedata.a)

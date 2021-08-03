#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(Simulation)


#----------------------------------------------------------------------------
# Find Geant4 package, no UI and Visualization drivers activated
#
## find_package(Geant4 REQUIRED)
#----------------------------------------------------------------------------
# Find Geant4 package, with UI and Visualization drivers activated
#
find_package(Geant4 REQUIRED ui_all vis_all)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executables, and link it to the Geant4 libraries
#
add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES} )

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(PROJECT_SCRIPTS
  vis.mac
  InrUSource.mac
  source.mac
  spectra.mac
  Cs137_spectra.mac
  spectra_Cs137.mac
  spectra_U238.mac
  spectra_U235.mac
  spectra_Pu239.mac
  )

foreach(_script ${PROJECT_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

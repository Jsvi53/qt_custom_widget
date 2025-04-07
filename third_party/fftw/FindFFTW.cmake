# - Try to find FFTW
# Once done this will define
#  FFTW_FOUND - System has FFTW
#  FFTW_INCLUDE_DIRS - The FFTW include directories
#  FFTW_LIBRARIES - The libraries needed to use FFTW

# Check if we are already done
if(FFTW_LIBRARIES AND FFTW_INCLUDE_DIRS)
  set(FFTW_FOUND TRUE)
  return()
endif()

# Include directory
find_path(FFTW_INCLUDE_DIR
  NAMES fftw3.h
  PATHS "${CMAKE_CURRENT_LIST_DIR}/"
  NO_DEFAULT_PATH
)

# Libraries
find_library(FFTW_LIBRARY
  NAMES libfftw3-3
  PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
  NO_DEFAULT_PATH
)

find_library(FFTWF_LIBRARY
  NAMES libfftw3f-3
  PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
  NO_DEFAULT_PATH
)

find_library(FFTWL_LIBRARY
  NAMES libfftw3l-3
  PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
  NO_DEFAULT_PATH
)

# Handle the QUIETLY and REQUIRED arguments and set FFTW_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFTW DEFAULT_MSG FFTW_INCLUDE_DIR FFTW_LIBRARY FFTWF_LIBRARY FFTWL_LIBRARY)

# Set output variables
if(FFTW_FOUND)
  set(FFTW_INCLUDE_DIRS ${FFTW_INCLUDE_DIR})
  set(FFTW_LIBRARIES ${FFTW_LIBRARY} ${FFTWF_LIBRARY} ${FFTWL_LIBRARY})
endif()

# Hide these variables from the CMake GUI
mark_as_advanced(FFTW_INCLUDE_DIR FFTW_LIBRARY FFTWF_LIBRARY FFTWL_LIBRARY)
# FindFFTW.cmake
# - Find FFTW library
#
# This module defines the following variables:
#  FFTW_INCLUDE_DIRS - Include directories for FFTW
#  FFTW_LIBRARIES - Libraries to link against FFTW

# 设置头文件路径
find_path(FFTW_INCLUDE_DIR fftw3.h
    PATHS "${CMAKE_CURRENT_LIST_DIR}"
    NO_DEFAULT_PATH
)

# 根据操作系统和构建类型选择库文件路径
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        find_library(FFTW_LIBRARY
            NAMES fftw3
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/debug"
            NO_DEFAULT_PATH
        )
        find_library(FFTWF_LIBRARY
            NAMES fftw3f
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/debug"
            NO_DEFAULT_PATH
        )
        find_library(FFTWL_LIBRARY
            NAMES fftw3l
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/debug"
            NO_DEFAULT_PATH
        )
    else()
        find_library(FFTW_LIBRARY
            NAMES fftw3
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
            NO_DEFAULT_PATH
        )
        find_library(FFTWF_LIBRARY
            NAMES fftw3f
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
            NO_DEFAULT_PATH
        )
        find_library(FFTWL_LIBRARY
            NAMES fftw3l
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
            NO_DEFAULT_PATH
        )
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        find_library(FFTW_LIBRARY
            NAMES fftw3
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/debug"
            NO_DEFAULT_PATH
        )
        find_library(FFTWF_LIBRARY
            NAMES fftw3f
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/debug"
            NO_DEFAULT_PATH
        )
        find_library(FFTWL_LIBRARY
            NAMES fftw3l
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/debug"
            NO_DEFAULT_PATH
        )
    else()
        find_library(FFTW_LIBRARY
            NAMES fftw3
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/release"
            NO_DEFAULT_PATH
        )
        find_library(FFTWF_LIBRARY
            NAMES fftw3f
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/release"
            NO_DEFAULT_PATH
        )
        find_library(FFTWL_LIBRARY
            NAMES fftw3l
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/release"
            NO_DEFAULT_PATH
        )
    endif()
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

# 设置变量
set(FFTW_INCLUDE_DIRS ${FFTW_INCLUDE_DIR})
set(FFTW_LIBRARIES
    ${FFTW_LIBRARY}
    ${FFTWF_LIBRARY}
    ${FFTWL_LIBRARY}
)

# 使用FindPackageHandleStandardArgs处理查找结果
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFTW DEFAULT_MSG FFTW_INCLUDE_DIR FFTW_LIBRARY FFTWF_LIBRARY FFTWL_LIBRARY)
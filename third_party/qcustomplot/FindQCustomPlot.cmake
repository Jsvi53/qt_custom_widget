# FindQCustomPlot.cmake
# - Find QCustomPlot library
#
# This module defines the following variables:
#  QCustomPlot_INCLUDE_DIRS - Include directories for QCustomPlot
#  QCustomPlot_LIBRARIES - Libraries to link against QCustomPlot

# 设置头文件路径
find_path(QCustomPlot_INCLUDE_DIR qcustomplot.h
    PATHS "${CMAKE_CURRENT_LIST_DIR}"
    NO_DEFAULT_PATH
)

# 根据操作系统和构建类型选择库文件路径
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        find_library(QCustomPlot_LIBRARY
            NAMES qcustomplotd2
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/debug"
            NO_DEFAULT_PATH
        )
    else()
        find_library(QCustomPlot_LIBRARY
            NAMES qcustomplot2
            PATHS "${CMAKE_CURRENT_LIST_DIR}/windows/release"
            NO_DEFAULT_PATH
        )
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        find_library(QCustomPlot_LIBRARY
            NAMES qcustomplotd
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/debug"
            NO_DEFAULT_PATH
        )
    else()
        find_library(QCustomPlot_LIBRARY
            NAMES qcustomplot
            PATHS "${CMAKE_CURRENT_LIST_DIR}/linux/release"
            NO_DEFAULT_PATH
        )
    endif()
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

# 设置变量
set(QCustomPlot_INCLUDE_DIRS ${QCustomPlot_INCLUDE_DIR})
set(QCustomPlot_LIBRARIES ${QCustomPlot_LIBRARY})

# 使用FindPackageHandleStandardArgs处理查找结果
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QCustomPlot DEFAULT_MSG QCustomPlot_INCLUDE_DIR QCustomPlot_LIBRARY)
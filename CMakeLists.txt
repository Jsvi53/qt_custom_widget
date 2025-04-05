cmake_minimum_required(VERSION 3.5)
project(custom_widget LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 构建类型设置
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release")

# 查找 Qt 库
find_package(Qt5 REQUIRED COMPONENTS
    Widgets
    Charts
    Gui
    Multimedia
    Sql
    Core
    PrintSupport
    3DCore
    DataVisualization
    Quick
    QuickWidgets
)

# 设置CMake模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/qcustomplot")
find_package(QCustomPlot REQUIRED)

# 设置源文件和头文件路径
set(INCLUDE_DIR
    include/
    include/base
    include/base2
    include/gui
    include/gui2
    include/utils
    include/utils2
    include/databasemodule
    include/test
    include/test2
    include/fileapp
    include/test_qmlmerge
    ${QCustomPlot_INCLUDE_DIRS}
)

# 添加 TsFile 目录，并设置 CLEAN_NO_CUSTOM 属性
add_subdirectory(assets/TsFile)

# 添加资源文件
set(RESOURCES
    assets/assets.qrc
)

# 添加源文件
file(GLOB_RECURSE GUISOURCES
    "include/*.h"
    "include/base/*.h"
    "include/base2/*.h"
    "include/utils/*.h"
    "include/gui/*.h"
    "include/gui2/*.h"
    "include/utils2/*.h"
    "include/databasemodule/*.h"
    "include/test/*.h"
    "include/test2/*.h"
    "include/fileapp/*.h"
    "include/test_qmlmerge/*.h"
    "src/*.cpp"
    "src/base/*.cpp"
    "src/utils/*.cpp"
    "src/utils2/*.cpp"
    "src/gui/*.cpp"
    "src/gui2/*.cpp"
    "src/base2/*.cpp"
    "src/databasemodule/*.cpp"
    "src/test/*.cpp"
    "src/test2/*.cpp"
    "src/fileapp/*.cpp"
    "src/test_qmlmerge/*.cpp"
    "src/*.qrc"
    "src/*.ui"
    "src/base/*.ui"
    "src/base2/*.ui"
    "src/utils/*.ui"
    "src/utils2/*.ui"
    "src/gui/*.ui"
    "src/gui2/*.ui"
)

# 设置CMake策略CMP0111
if(POLICY CMP0111)
    cmake_policy(SET CMP0111 NEW)
endif()

# 添加可执行文件
add_executable(jpbalance
    ${RESOURCES}
    ${GUISOURCES}
)

# 设置头文件路径
target_include_directories(jpbalance PRIVATE ${INCLUDE_DIR})

# 链接库
target_link_libraries(jpbalance PRIVATE
    ${QCustomPlot_LIBRARIES}
    Qt5::Widgets
    Qt5::Charts
    Qt5::Gui
    Qt5::Multimedia
    Qt5::Sql
    Qt5::Core
    Qt5::PrintSupport
    Qt5::3DCore
    Qt5::DataVisualization
    Qt5::Quick
    Qt5::QuickWidgets
)

# 设置宏定义
target_compile_definitions(jpbalance PRIVATE QCUSTOMPLOT_USE_LIBRARY)

# 后处理：复制配置文件
add_custom_target(copy_configs ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/config/configs.json"
    "${CMAKE_CURRENT_BINARY_DIR}/configs.json"
    COMMENT "Copying configs.json to binary directory"
)

# 后处理：复制动态库
add_custom_command(TARGET jpbalance POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying qcustomplotd2.dll from ${CMAKE_CURRENT_SOURCE_DIR}/third_party/qcustomplot/windows/debug/qcustomplotd2.dll to $<TARGET_FILE_DIR:jpbalance>"
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/qcustomplot/windows/debug/qcustomplotd2.dll"
    "$<TARGET_FILE_DIR:jpbalance>"
    COMMENT "Copying qcustomplotd2.dll to binary directory"
)
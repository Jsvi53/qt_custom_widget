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

# 添加 TsFile 目录，并设置 CLEAN_NO_CUSTOM 属性
add_subdirectory(assets/TsFile)

# 添加资源文件
set(RESOURCES
    assets/assets.qrc
)

# 添加不带2的源文件
file(GLOB_RECURSE GUISOURCES
    "include/*.h"
    "include/base/*.h"
    "include/utils/*.h"
    "include/gui/*.h"
    "include/databasemodule/*.h"
    "include/test/*.h"
    "include/fileapp/*.h"
    "src/*.cpp"
    "src/base/*.cpp"
    "src/utils/*.cpp"
    "src/gui/*.cpp"
    "src/databasemodule/*.cpp"
    "src/test/*.cpp"
    "src/fileapp/*.cpp"
    "src/*.qrc"
    "src/*.ui"
    "src/base/*.ui"
    "src/utils/*.ui"
    "src/gui/*.ui"
)

# 添加带2的源文件
file(GLOB_RECURSE GUISOURCES2
    "include/base2/*.h"
    "include/gui2/*.h"
    "include/utils2/*.h"
    "include/test2/*.h"
    "include/test_qmlmerge/*.h"
    "src/base2/*.cpp"
    "src/utils2/*.cpp"
    "src/gui2/*.cpp"
    "src/test2/*.cpp"
    "src/test_qmlmerge/*.cpp"
    "src/base2/*.ui"
    "src/utils2/*.ui"
    "src/gui2/*.ui"
)

# 添加不带2的头文件路径
set(INCLUDE_DIR
    include/
    include/base
    include/gui
    include/utils
    include/databasemodule
    include/test
    include/fileapp
    ${QCustomPlot_INCLUDE_DIRS}
)

# 添加带2的头文件路径
set(INCLUDE_DIR2
    include/base2
    include/gui2
    include/utils2
    include/test2
    include/test_qmlmerge
)

list(REMOVE_ITEM GUISOURCES
    ""
)

# 设置CMake策略CMP0111
if(POLICY CMP0111)
    cmake_policy(SET CMP0111 NEW)
endif()

# 添加可执行文件
add_executable(custom_widget
    ${RESOURCES}
    # ${GUISOURCES}
    # ${GUISOURCES2}
    src/main.cpp
    include/gui/resultgraph.h
    include/base/bigraph.h
    include/base2/thememanager.h
    src/base/bigraph.cpp
    src/gui/resultgraph.cpp
    src/base2/thememanager.cpp
    src/gui/resultgraphscreen.ui
    src/tchrt.cpp
    include/tchrt.h
)

# 设置头文件路径
target_include_directories(custom_widget PRIVATE
    #${INCLUDE_DIR}
    #${INCLUDE_DIR2}
    include/base
    include/base2
    include/gui
    third_party/qcustomplot/
    include
)

# 链接库
target_link_libraries(custom_widget PRIVATE
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
target_compile_definitions(custom_widget PRIVATE QCUSTOMPLOT_USE_LIBRARY)

# 后处理：复制配置文件
add_custom_command(TARGET custom_widget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/config/configs.json"
    "${CMAKE_CURRENT_BINARY_DIR}/configs.json"
    COMMENT "Copying configs.json to binary directory"
)

# 后处理：复制主题配置文件
add_custom_command(TARGET custom_widget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/config2/themeconfigs.json"
    "${CMAKE_CURRENT_BINARY_DIR}/themeconfigs.json"
    COMMENT "Copying themeconfigs.json to binary directory"
)

# 后处理：复制动态库
add_custom_command(TARGET custom_widget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying qcustomplotd2.dll from ${CMAKE_CURRENT_SOURCE_DIR}/third_party/qcustomplot/windows/debug/qcustomplotd2.dll to $<TARGET_FILE_DIR:custom_widget>"
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/qcustomplot/windows/debug/qcustomplotd2.dll"
    "$<TARGET_FILE_DIR:custom_widget>"
    COMMENT "Copying qcustomplotd2.dll to binary directory"
)

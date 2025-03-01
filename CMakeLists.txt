cmake_minimum_required(VERSION 3.5)

project(qt_custom_widget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 设置自动处理 Qt 的元对象编译器（MOC）、资源编译器（RCC）和 UI 编译器（UIC）
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt 库
find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

# 设置源文件和头文件路径
set(SRC_DIR src)
set(INCLUDE_DIR include)

# 设置翻译文件（如果有）
set(TS_FILES ${SRC_DIR}/qt_custom_widget_zh_CN.ts)

# 添加可执行文件
add_executable(qt_custom_widget
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/mainwindow.cpp
    ${INCLUDE_DIR}/mainwindow.h
    ${SRC_DIR}/mainwindow.ui


    ${TS_FILES}
)

# 包含头文件目录
target_include_directories(qt_custom_widget PRIVATE ${INCLUDE_DIR})

# 链接 Qt 模块
target_link_libraries(qt_custom_widget PRIVATE Qt5::Widgets)

# 生成翻译文件（如果有）
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

cmake_minimum_required(VERSION 3.5)

project(qt_custom_widget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 构建类型设置
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")     # 打印 CMAKE_BUILD_TYPE

# 查找 Qt 库
find_package(Qt5 REQUIRED COMPONENTS
    Widgets
    Charts
    Multimedia
    Sql
    Core
    PrintSupport
    Quick
    QuickWidgets
    DataVisualization
)

# 设置源文件和头文件路径
set(SRC_DIR src)
set(INCLUDE_DIR include)

# 设置翻译文件路径
# set(TS_FILES ${CMAKE_SOURCE_DIR}/TsFile/qt_custom_widget_zh_CN.ts)

# 添加 TsFile 目录，并设置 CLEAN_NO_CUSTOM 属性
add_subdirectory(TsFile)

# 生成翻译文件
# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# 添加资源文件
qt5_add_resources(RESOURCES assets/assets.qrc)

# 添加子模块
add_subdirectory(src/databasetest)

# 添加可执行文件
add_executable(qt_custom_widget
    ${SRC_DIR}/main.cpp
    # ${INCLUDE_DIR}/mainwindow/mainwindow.h
    # ${SRC_DIR}/mainwindow/mainwindow.cpp
    # ${SRC_DIR}/mainwindow/mainwindow.ui

    # # 添加 QSwitchButton 模块
    # ${INCLUDE_DIR}/qswitchbutton/qswitchbutton.h
    # ${SRC_DIR}/qswitchbutton/qswitchbutton.cpp
    # ${INCLUDE_DIR}/qswitchbutton/switchbuttonshowwindow.h
    # ${SRC_DIR}/qswitchbutton/switchbuttonshowwindow.cpp
    # ${SRC_DIR}/qswitchbutton/switchbuttonshowwindow.ui

    # # 添加 polarchart 模块
    # ${INCLUDE_DIR}/chart/polarchart.h
    # ${SRC_DIR}/chart/polarchart.cpp
    # ${INCLUDE_DIR}/chart/polarchartshowwindow.h
    # ${SRC_DIR}/chart/polarchartshowwindow.cpp
    # ${SRC_DIR}/chart/polarchartshowwindow.ui

    # # 添加 barchart 模块
    # ${INCLUDE_DIR}/chart/barchart.h
    # ${SRC_DIR}/chart/barchart.cpp
    # ${INCLUDE_DIR}/chart/barchartshowwindow.h
    # ${SRC_DIR}/chart/barchartshowwindow.cpp
    # ${SRC_DIR}/chart/barchartshowwindow.ui

    # # 添加 wave 模块
    # ${INCLUDE_DIR}/chart/wavechart.h
    # ${SRC_DIR}/chart/wavechart.cpp
    # ${INCLUDE_DIR}/chart/wavechartshowwindow.h
    # ${SRC_DIR}/chart/wavechartshowwindow.cpp
    # ${SRC_DIR}/chart/wavechartshowwindow.ui

    # # 添加 phasechart 模块
    # ${INCLUDE_DIR}/chart/balancingphasechart.h
    # ${SRC_DIR}/chart/balancingphasechart.cpp
    # ${INCLUDE_DIR}/chart/balancingshowphasechart.h
    # ${SRC_DIR}/chart/balancingshowphasechart.cpp
    # ${SRC_DIR}/chart/balancingshowphasechart.ui

    # # 添加 schenckmain 模块
    # ${INCLUDE_DIR}/schenckmain/schenckmain.h
    # ${SRC_DIR}/schenckmain/schenckmain.cpp
    # ${SRC_DIR}/schenckmain/schenckmain.ui

    # # 添加 test 模块
    # ${INCLUDE_DIR}/test/test.h
    # ${SRC_DIR}/test/test.cpp
    # ${SRC_DIR}/test/mywidget.ui

    # # 添加 manager 模块
    # ${INCLUDE_DIR}/manager/managerwindow.h
    # ${SRC_DIR}/manager/managerwindow.cpp

    # # 添加 login 模块
    # ${INCLUDE_DIR}/fileapp/filetemplatewindow.h
    # ${INCLUDE_DIR}/fileapp/TemplateParams.h
    # ${INCLUDE_DIR}/fileapp/TemplateConfigPage.h
    # ${SRC_DIR}/fileapp/filetemplatewindow.cpp
    # ${SRC_DIR}/fileapp/TemplateConfigPage.cpp
    # ${SRC_DIR}/fileapp/filetemplatewindow.ui

    # # 添加 basemodule 模块
    # ${INCLUDE_DIR}/basemodule/basewidget.h
    # ${SRC_DIR}/basemodule/basewidget.cpp
    # ${SRC_DIR}/basemodule/basewidget.ui

    # # 添加 launchscreen 模块
    # ${INCLUDE_DIR}/jp_mainwindow/jp_mainwindow.h
    # ${SRC_DIR}/jp_mainwindow/jp_mainwindow.cpp
    # ${SRC_DIR}/jp_mainwindow/jp_mainwindow.ui

    # # 添加 launchscreen 模块
    # # ${INCLUDE_DIR}/launchscreen/launchscreen.h
    # # ${SRC_DIR}/launchscreen/launchscreen.cpp
    # # ${SRC_DIR}/launchscreen/launchscreen.ui
    # # 添加 jp_setting 模块
    # ${INCLUDE_DIR}/jp_settingscreen/jp_settingscreen.h
    # ${SRC_DIR}/jp_settingscreen/jp_settingscreen.cpp
    # ${SRC_DIR}/jp_settingscreen/jp_settingscreen.ui

    # # 添加 jp_filemanager 模块
    # ${INCLUDE_DIR}/jp_filemanagerscreen/jp_filemanager.h
    # ${SRC_DIR}/jp_filemanagerscreen/jp_filemanager.cpp
    # ${SRC_DIR}/jp_filemanagerscreen/jp_filemanager.ui

    # # 添加 jp_balancese 模块
    # ${INCLUDE_DIR}/jp_balancesetupscreen/jp_balancesetup.h
    # ${SRC_DIR}/jp_balancesetupscreen/jp_balancesetup.cpp
    # ${SRC_DIR}/jp_balancesetupscreen/jp_balancesetup.ui

    # # 添加 jp_balancerunscreen 模块
    # ${INCLUDE_DIR}/jp_balancerunscreen/jp_balancerun.h
    # ${SRC_DIR}/jp_balancerunscreen/jp_balancerun.cpp
    # ${SRC_DIR}/jp_balancerunscreen/jp_balancerun.ui

    # # 添加 jp_balancerunscreen 模块
    # ${INCLUDE_DIR}/chart/spectrum.h
    # ${SRC_DIR}/chart/spectrum.cpp

    # # 添加 jp_balancerunscreen 模块
    # ${INCLUDE_DIR}/chart/polardiagram.h
    # ${SRC_DIR}/chart/polardiagram.cpp

    # # 添加 qcustomplot 模块
    # # ${INCLUDE_DIR}/chart/qcustomplot.h
    # # ${SRC_DIR}/chart/qcustomplot.cpp

    # # 用动态库方式引入 QCustomPlot
    # ${INCLUDE_DIR}/qtcustomplot/qcustomplot.h

    # 添加 JP_ResultGraph 模块
    # ${INCLUDE_DIR}/jp_resultgraphscreen/jp_resultgraph.h
    # ${SRC_DIR}/jp_resultgraphscreen/jp_resultgraph.cpp
    # ${SRC_DIR}/jp_resultgraphscreen/jp_resultgraph.ui
    # ${INCLUDE_DIR}/chart/bigraph.h
    # ${SRC_DIR}/chart/bigraph.cpp

    # 添加 信号发生器 模块
    # ${INCLUDE_DIR}/utils/signalgenerator.h
    # ${SRC_DIR}/utils/signalgenerator.cpp
    # ${INCLUDE_DIR}/utils/signalgenerator2.h
    # ${SRC_DIR}/utils/signalgenerator2.cpp

    # 界面融合
    # ${INCLUDE_DIR}/onsitebalancer/onsitebalancer.h
    # ${SRC_DIR}/onsitebalancer/onsitebalancer.cpp
    # ${INCLUDE_DIR}/onsitebalancer/home.h
    # ${SRC_DIR}/onsitebalancer/home.cpp
    # ${SRC_DIR}/onsitebalancer/homescreen.ui
    # ${INCLUDE_DIR}/onsitebalancer/settingscreen.h
    # ${SRC_DIR}/onsitebalancer/settingscreen.cpp
    # ${SRC_DIR}/onsitebalancer/settingscreen.ui

    # 3dchart
    ${INCLUDE_DIR}/chart/3dchart.h
    ${SRC_DIR}/chart/3dchart.cpp

    # 路径列表界面
    # ${INCLUDE_DIR}/jp_routesscreen/jp_routes.h
    # ${SRC_DIR}/jp_routesscreen/jp_routes.cpp
    # ${SRC_DIR}/jp_routesscreen/jp_routesscreen.ui

    # test_qmlmerge
    # ${INCLUDE_DIR}/test_qmlmerge/test_qmlmerge.h
    # ${SRC_DIR}/test_qmlmerge/test_qmlmerge.cpp



    # 添加资源文件生成的目标
    ${RESOURCES}
)


# 包含头文件目录
target_include_directories(qt_custom_widget PRIVATE ${INCLUDE_DIR})


# 设置 QCustomPlot 库的名称
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(WIN32)
    set(CUSTOMPLOT_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/qtcustomplot/windows/debug")
    set(CUSTOMPLOT_LIB_NAME "libqcustomplotd2")
  elseif(UNIX)
    set(CUSTOMPLOT_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/qtcustomplot/unix/debug")
    set(CUSTOMPLOT_LIB_NAME "libqcustomplotd2")
  endif()
else()
  if(WIN32)
    set(CUSTOMPLOT_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/qtcustomplot/windows/release")
    set(CUSTOMPLOT_LIB_NAME "libqcustomplot2")
  elseif(UNIX)
    set(CUSTOMPLOT_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/qtcustomplot/unix/release")
    set(CUSTOMPLOT_LIB_NAME "libqcustomplot2")
  endif()
endif()


# 链接 Qt 模块
target_link_libraries(qt_custom_widget PRIVATE
    Qt5::Widgets
    Qt5::Charts
    Qt5::Multimedia
    Qt5::Sql
    Qt5::Core
    Qt5::PrintSupport
    Qt5::Quick
    Qt5::QuickWidgets
    Qt5::DataVisualization
    basemodule_lib
    ${CUSTOMPLOT_LIB_DIR}/${CUSTOMPLOT_LIB_NAME}.a
)


# # 链接 QCustomPlot 动态库
# if(UNIX)
#     target_link_libraries(qt_custom_widget PRIVATE ${UNIX_CUSTOMPLOT_LIB_DIR}/libqcustomplot2.so)
#     add_custom_command(TARGET qt_custom_widget POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${UNIX_CUSTOMPLOT_LIB_DIR}/libqcustomplot2.so
#         $<TARGET_FILE_DIR:qt_custom_widget>)
# endif()

# if(WIN32)
#     # 不需要链接 libqcustomplot2.a，因为使用的是动态库
#     add_custom_command(TARGET qt_custom_widget POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${WIN_CUSTOMPLOT_LIB_DIR}/qcustomplot2.dll
#         $<TARGET_FILE_DIR:qt_custom_widget>)
# endif()
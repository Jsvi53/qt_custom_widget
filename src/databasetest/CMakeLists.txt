
# 设置子模块的库名称
set(BASEMODULE_LIB_NAME basemodule_lib)

# 添加库
add_library(${BASEMODULE_LIB_NAME} basemodule.cpp ${CMAKE_SOURCE_DIR}/include/databasetest/databasetest.h)

# 设置头文件路径
target_include_directories(${BASEMODULE_LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 链接 Qt 库
target_link_libraries(${BASEMODULE_LIB_NAME} Qt5::Core Qt5::Sql)

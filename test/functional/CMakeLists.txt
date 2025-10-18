
# 清除之前的文件列表（可选）
# 添加其他文件
file(GLOB Functional_SOURCES  RELATIVE "${PROJECT_SOURCE_DIR}" "functional/*.cpp")


# 将多个文件列表合并到同一个变量中
list(APPEND test_sources ${Functional_SOURCES})

#
# add_executable(test_all ${test_sources} $<TARGET_OBJECTS:catch_amalgamated>)

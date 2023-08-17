
# 清除之前的文件列表（可选）
# 添加其他文件
file(GLOB PROVIDERS_SOURCE  RELATIVE "${PROJECT_SOURCE_DIR}" "Streams/providers/*.cpp")


# 将多个文件列表合并到同一个变量中
list(APPEND test_sources ${PROVIDERS_SOURCE})

#
# add_executable(test_all ${test_sources} $<TARGET_OBJECTS:catch_amalgamated>)

cmake_minimum_required(VERSION 3.21.1)

project(libsa)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_library(libsa sa.cpp)

set_target_properties(libsa PROPERTIES PUBLIC_HEADER sa.h)

install(TARGETS libsa DESTINATION lib PUBLIC_HEADER DESTINATION include)

add_subdirectory(tests)

if (WIN32)
    target_link_libraries(libsa LINK_PUBLIC wsock32 ws2_32 iphlpapi)
endif ()
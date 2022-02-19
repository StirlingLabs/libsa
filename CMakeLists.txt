cmake_minimum_required(VERSION 3.16)

project(libsa)

enable_testing()

add_library(libsa sa.cpp)

set_target_properties(libsa PROPERTIES PUBLIC_HEADER sa.h)

target_compile_features(libsa PRIVATE cxx_std_17)

install(TARGETS libsa DESTINATION lib PUBLIC_HEADER DESTINATION include)

add_subdirectory(tests)

if (WIN32)
    target_link_libraries(libsa LINK_PUBLIC wsock32 ws2_32 iphlpapi)
endif ()

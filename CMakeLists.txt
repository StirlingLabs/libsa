cmake_minimum_required(VERSION 3.16)

project(sa)

include(CheckStructHasMember)

option(SA_SKIP_TESTS "Skip building tests" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if (NOT WIN32)
    check_struct_has_member("struct sockaddr" sa_len sys/socket.h HAVE_SOCKADDR_SA_LEN LANGUAGE C)
endif ()

if (HAVE_SOCKADDR_SA_LEN)
    add_compile_definitions(HAVE_SOCKADDR_SA_LEN=1)
endif()

add_library(sa sa.c)

set_target_properties(sa PROPERTIES PUBLIC_HEADER sa.h)

target_include_directories(sa PRIVATE .)

include(GNUInstallDirs)

install(TARGETS sa
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (WIN32)
    target_link_libraries(sa LINK_PUBLIC wsock32 ws2_32 iphlpapi)
endif ()

if (SA_SKIP_TESTS)
    MESSAGE(WARNING "Tests skipped!")
else()
    enable_testing()
    add_subdirectory(tests)
endif()
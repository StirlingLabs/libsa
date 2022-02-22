cmake_minimum_required(VERSION 3.16)

project(sa)

include(CheckIPOSupported)
check_ipo_supported(RESULT HAVE_IPO_SUPPORT OUTPUT IPO_SUPPORT_ERROR)

include(CheckStructHasMember)

option(SA_SKIP_TESTS "Skip building tests" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if (NOT WIN32)
    check_struct_has_member("struct sockaddr" sa_len sys/socket.h HAVE_SOCKADDR_SA_LEN LANGUAGE C)
endif ()

if (HAVE_SOCKADDR_SA_LEN)
    add_compile_definitions(HAVE_SOCKADDR_SA_LEN=1)
endif ()

add_library(sa sa.c)

if( HAVE_IPO_SUPPORT )
    message(STATUS "IPO enabled")
    set_property(TARGET sa PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO not supported: <${IPO_SUPPORT_ERROR}>")
endif()

set_property(TARGET sa PROPERTY C_STANDARD 11)
set_property(TARGET sa PROPERTY C_STANDARD_REQUIRED OFF)
set_property(TARGET sa PROPERTY C_VISIBILITY_PRESET hidden)
set_property(TARGET sa PROPERTY VISIBILITY_INLINES_HIDDEN ON)

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
    
    # hack to make debugging shared builds convenient
    if (WIN32 AND BUILD_SHARED_LIBS)
        add_custom_command(TARGET sa POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:sa>"
                "${CMAKE_BINARY_DIR}/bin")
    endif ()

    set_property(TARGET sa PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

if (SA_SKIP_TESTS)
    MESSAGE(WARNING "Tests skipped!")
else ()
    enable_testing()
    add_subdirectory(tests)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/master.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

function(define_gtest test_name)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} sa gtest_main)
    target_include_directories(${test_name} PRIVATE ../include ../src ./)
    if (WIN32)
        add_custom_command(TARGET ${test_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:sa>"
                "$<TARGET_FILE_DIR:${test_name}>")
        set_target_properties(${test_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    endif ()

    # help IDEs recognize changes to sa constitute rebuild of tests
    set_property(
            DIRECTORY
            APPEND
            PROPERTY CMAKE_CONFIGURE_DEPENDS "$<TARGET_FILE:sa>"
    )

    gtest_discover_tests(${test_name})
endfunction()


file(GLOB test_sources CONFIGURE_DEPENDS "test_*.cpp")
foreach (test_source ${test_sources})
    get_filename_component(test_name ${test_source} NAME_WLE)
    define_gtest(${test_name})
endforeach ()

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
    if (WIN32)
        add_custom_command(TARGET ${test_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:sa>"
                "$<TARGET_FILE_DIR:${test_name}>")
        set_target_properties(${test_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    endif ()
    gtest_discover_tests(${test_name})
endfunction()

define_gtest(test_sa_is_unspec)
define_gtest(test_sa_is_ipv4)
define_gtest(test_sa_is_ipv6)
define_gtest(test_sa_unspec)
define_gtest(test_sa_ipv4)
define_gtest(test_sa_ipv6)
define_gtest(test_sa_address_to_str)
define_gtest(test_sa_get_port)
define_gtest(test_sa_set_port)
define_gtest(test_sa_get_scope)
define_gtest(test_sa_set_scope)
define_gtest(test_sa_get_family)
define_gtest(test_sa_set_family)
define_gtest(test_sa_family_offset)
define_gtest(test_sa_has_len_field)
define_gtest(test_sa_get_address_byte)
define_gtest(test_sa_set_address_byte)
define_gtest(test_sa_free)
define_gtest(test_sa_get_size)


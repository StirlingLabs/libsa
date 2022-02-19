set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/master.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

function(define_gtest test_name)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} libsa gtest_main)
    #add_test(${test_name} ${test_name})
    gtest_discover_tests(${test_name})
endfunction()

define_gtest(test_sa_is_ipv4)
define_gtest(test_sa_is_ipv6)
define_gtest(test_sa_ipv4)
define_gtest(test_sa_ipv6)
define_gtest(test_sa_ipv4_to_str)
define_gtest(test_sa_ipv6_to_str)
define_gtest(test_sa_to_str)
define_gtest(test_sa_get_port)
define_gtest(test_sa_set_port)
define_gtest(test_sa_get_scope)
define_gtest(test_sa_set_scope)

function(addTest test_name src)
    add_executable(${test_name} ${src})
    target_link_libraries (${test_name} gtest_main stdc++fs all_utils progresscpp logging exp commandLineParser temporalParser usmt_core)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${WORK_DIR})
endfunction()

message("-- Including test cases...")

set(WORK_DIR ${CMAKE_BINARY_DIR})
set(TEST_DIR ${CMAKE_BINARY_DIR}/../tests)

addTest(languageCompareTests languageCompareTest.cc)
addTest(z3Tests z3Tests.cc)
addTest(gatherPathTests gatherPathTests.cc)

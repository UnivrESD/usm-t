function(addTest test_name src)
    add_executable(${test_name} ${src})
    target_link_libraries (${test_name} gtest_main stdc++fs all_utils progresscpp logging exp commandLineParser temporalParser miner)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${WORK_DIR})
endfunction()

message("-- Including test cases...")

set(WORK_DIR ${CMAKE_BINARY_DIR})
set(TEST_DIR ${CMAKE_BINARY_DIR}/../tests)

addTest("TraceTest" ./traceTests.cc)
addTest("OpeTest" ./opeTests.cc)
addTest("ConvTest" ./conversionTests.cc)
addTest("ConstantsTest" ./constantsTests.cc )
addTest("TemporalExpressionTest" ./temporalExpressionTests.cc )
addTest("TemporalDepthTest" ./temporalDepthTests.cc )


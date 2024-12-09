SET(NAME evaluator)
project(${NAME})



#############################################
# Sources.
#############################################

SET(EVALUATOR_SRC src/expected_vs_mined.cc src/fault_coverage.cc src/assertion_utils.cc src/usmt-evaluator.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${EVALUATOR_SRC})
target_link_libraries(${NAME} PUBLIC usmt_utils ${SPOTLTL_LIB} miner_utils traceReader set_cover)
target_include_directories(${NAME} PUBLIC include ${SPOTLTLCPP_INCLUDE_DIRS} )






SET(NAME evaluator)
project(${NAME})



#############################################
# Sources.
#############################################

SET(EVALUATOR_SRC src/evaluator.cc)

#############################################
# Targets.
#############################################
add_library(${NAME} ${EVALUATOR_SRC})
target_link_libraries(${NAME} PUBLIC usmt_utils ${SPOTLTL_LIB})
target_include_directories(${NAME} PUBLIC include ${SPOTLTLCPP_INCLUDE_DIRS})






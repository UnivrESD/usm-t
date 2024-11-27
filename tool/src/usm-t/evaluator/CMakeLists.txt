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
target_link_libraries(${NAME} PUBLIC usmt_utils)
target_include_directories(${NAME} PUBLIC include)






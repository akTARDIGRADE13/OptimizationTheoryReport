set(SOLVER1_SRC solver_example.cpp)

add_library(solver_example ${SOLVER1_SRC})

target_link_libraries(solver_example common)
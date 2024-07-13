set(SOLVER1_SRC RandomRouteSolver.cpp)

add_library(RandomRouteSolver ${SOLVER1_SRC})

target_link_libraries(RandomRouteSolver common)
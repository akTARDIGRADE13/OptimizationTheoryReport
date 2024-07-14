set(SOLVER1_SRC SimulatedAnnealingSolver.cpp)

add_library(SimulatedAnnealingSolver ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver common)
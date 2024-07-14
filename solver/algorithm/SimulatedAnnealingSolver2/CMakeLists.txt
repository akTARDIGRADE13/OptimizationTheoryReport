set(SOLVER1_SRC SimulatedAnnealingSolver2.cpp)

add_library(SimulatedAnnealingSolver2 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver2 common)
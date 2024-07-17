set(SOLVER1_SRC SimulatedAnnealingSolver8.cpp)

add_library(SimulatedAnnealingSolver8 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver8 common)
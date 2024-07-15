set(SOLVER1_SRC SimulatedAnnealingSolver4.cpp)

add_library(SimulatedAnnealingSolver4 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver4 common)
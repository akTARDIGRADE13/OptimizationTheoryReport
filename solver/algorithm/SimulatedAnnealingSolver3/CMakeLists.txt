set(SOLVER1_SRC SimulatedAnnealingSolver3.cpp)

add_library(SimulatedAnnealingSolver3 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver3 common)
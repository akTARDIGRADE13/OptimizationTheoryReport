set(SOLVER1_SRC SimulatedAnnealingSolver6.cpp)

add_library(SimulatedAnnealingSolver6 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver6 common)
set(SOLVER1_SRC SimulatedAnnealingSolver5.cpp)

add_library(SimulatedAnnealingSolver5 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver5 common)
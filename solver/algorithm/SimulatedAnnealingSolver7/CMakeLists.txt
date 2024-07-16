set(SOLVER1_SRC SimulatedAnnealingSolver7.cpp)

add_library(SimulatedAnnealingSolver7 ${SOLVER1_SRC})

target_link_libraries(SimulatedAnnealingSolver7 common)
cmake_minimum_required(VERSION 3.22)
project(DeliveryRobot)

# インクルードディレクトリの追加
function(add_include_directories)
    include_directories(${ARGN})
endfunction()

add_include_directories(
    include
    algorithm/RandomRouteSolver
    algorithm/SimulatedAnnealingSolver
    algorithm/SimulatedAnnealingSolver2
    algorithm/SimulatedAnnealingSolver3
    algorithm/SimulatedAnnealingSolver4
    algorithm/SimulatedAnnealingSolver5
    algorithm/solver_example
)

# コンパイルオプションの追加
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# ソースファイルの追加
add_library(common 
    src/common.cpp 
    src/problem.cpp 
    src/solution.cpp 
    src/validator.cpp 
    src/random_generator.cpp 
    src/timer.cpp 
    src/CumulativeSumMaxSegmentTree.cpp
    src/SA_base.cpp
    src/BIT.cpp
    src/StarrySkyTree.cpp
)

# サブディレクトリの追加
function(add_algorithm_subdirectories)
    foreach(subdir IN LISTS ARGN)
        add_subdirectory(${subdir})
    endforeach()
endfunction()

add_algorithm_subdirectories(
    algorithm/RandomRouteSolver
    algorithm/SimulatedAnnealingSolver
    algorithm/SimulatedAnnealingSolver2
    algorithm/SimulatedAnnealingSolver3
    algorithm/SimulatedAnnealingSolver4
    algorithm/SimulatedAnnealingSolver5
    algorithm/solver_example
)

# エグゼクタブルの作成
add_executable(DeliveryRobot src/main.cpp)
target_link_libraries(DeliveryRobot 
    common 
    RandomRouteSolver 
    SimulatedAnnealingSolver 
    SimulatedAnnealingSolver2 
    SimulatedAnnealingSolver3 
    SimulatedAnnealingSolver4
    SimulatedAnnealingSolver5
    solver_example
)

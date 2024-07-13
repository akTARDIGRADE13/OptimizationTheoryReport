cmake_minimum_required(VERSION 3.22)
project(DeliveryRobot)

# インクルードディレクトリの追加
include_directories(include)
include_directories(algorithm/RandomRouteSolver)
include_directories(algorithm/solver_example)

# ソースファイルの追加
add_library(common src/common.cpp src/problem.cpp src/solution.cpp src/validator.cpp src/random_generator.cpp src/timer.cpp)

# サブディレクトリの追加
add_subdirectory(algorithm/RandomRouteSolver)
add_subdirectory(algorithm/solver_example)

# エグゼクタブルの作成
add_executable(DeliveryRobot src/main.cpp)
target_link_libraries(DeliveryRobot common RandomRouteSolver solver_example)
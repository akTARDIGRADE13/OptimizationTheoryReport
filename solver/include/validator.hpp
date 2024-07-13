#pragma once

#include "common.hpp"
#include "problem.hpp"
#include "solution.hpp"

// validならコストを返す、invalidなら-1を返す
Cost validate_solution(const Problem &problem, const Operations &operations);
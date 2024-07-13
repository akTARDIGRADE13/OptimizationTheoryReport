#include "common.hpp"

#include <fstream>
#include <sstream>

// ログメッセージを出力する関数
void log_message(LogLevel level, const std::string &message) {
    switch (level) {
    case DEBUG:
        std::cerr << "[DEBUG] " << message << std::endl;
        break;
    case INFO:
        std::cerr << "[INFO] " << message << std::endl;
        break;
    case WARNING:
        std::cerr << "[WARNING] " << message << std::endl;
        break;
    case ERROR:
        std::cerr << "[ERROR] " << message << std::endl;
        break;
    }
}

// ファイルからデータを読み込む関数
std::vector<std::string> read_file_lines(const std::string &filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

// (x1,y1) から (x2,y2) への移動経路を返す関数
Operations get_route(Coordinate start, Coordinate goal) {
    Operations operations;
    int dx = goal.first - start.first;
    int dy = goal.second - start.second;
    if (dy > 0) {
        operations.insert(operations.end(), dy, "R");
    } else if (dy < 0) {
        operations.insert(operations.end(), -dy, "L");
    }

    if (dx > 0) {
        operations.insert(operations.end(), dx, "D");
    } else if (dx < 0) {
        operations.insert(operations.end(), -dx, "U");
    }
    return operations;
}

// 荷物 i を積む操作を返す関数
Operations load_operation(int i) {
    return {"+" + std::to_string(i)};
}

// 荷物 i を降ろす操作を返す関数
Operations unload_operation(int i) {
    return {"-" + std::to_string(i)};
}

// (x1,y1) から (x2,y2) へ行って荷物 i を積む操作を返す関数
Operations load_operation(int i, Coordinate start, Coordinate goal) {
    Operations operations = get_route(start, goal);
    operations.push_back("+" + std::to_string(i));
    return operations;
}

// (x1,y1) から (x2,y2) へ行って荷物 i を降ろす操作を返す関数
Operations unload_operation(int i, Coordinate start, Coordinate goal) {
    Operations operations = get_route(start, goal);
    operations.push_back("-" + std::to_string(i));
    return operations;
}

// (x1,y1) から (x2,y2) へ行って荷物 i を積み、(x2,y2) から (x3,y3) へ行って荷物 i を降ろす操作を返す関数
Operations move_operation(int i, Coordinate start, Coordinate goal, Coordinate next_goal) {
    Operations operations = get_route(start, goal);
    operations.push_back("+" + std::to_string(i));
    Operations next_operations = get_route(goal, next_goal);
    operations.insert(operations.end(), next_operations.begin(), next_operations.end());
    operations.push_back("-" + std::to_string(i));
    return operations;
}
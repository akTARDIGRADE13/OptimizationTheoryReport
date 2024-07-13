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
#pragma once

#include <iostream>
#include <string>
#include <vector>

enum LogLevel { DEBUG, INFO, WARNING, ERROR };

// ログメッセージを出力する関数
void log_message(LogLevel level, const std::string &message);

// ファイルからデータを読み込む関数
std::vector<std::string> read_file_lines(const std::string &filename);

// 共通の型定義
using Grid = std::vector<std::vector<int>>;
using Operation = std::string;
using Operations = std::vector<Operation>;
using Cost = int;
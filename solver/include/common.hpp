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
using Coordinate = std::pair<int, int>;

// (x1,y1) から (x2,y2) への移動経路を返す関数
Operations get_route(Coordinate start, Coordinate goal);

// 荷物 i を積む操作を返す関数
Operations load_operation(int i);

// 荷物 i を降ろす操作を返す関数
Operations unload_operation(int i);

// (x1,y1) から (x2,y2) へ行って荷物 i を積む操作を返す関数
Operations load_operation(int i, Coordinate start, Coordinate goal);

// (x1,y1) から (x2,y2) へ行って荷物 i を降ろす操作を返す関数
Operations unload_operation(int i, Coordinate start, Coordinate goal);

// (x1,y1) から (x2,y2) へ行って荷物 i を積み、(x2,y2) から (x3,y3) へ行って荷物 i を降ろす操作を返す関数
Operations move_operation(int i, Coordinate start, Coordinate goal, Coordinate next_goal);

// 2つの座標のマンハッタン距離を返す関数
int manhattan_distance(Coordinate a, Coordinate b);
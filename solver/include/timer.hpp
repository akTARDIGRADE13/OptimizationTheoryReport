#pragma once

#include <chrono>
#include <string>

struct Timer {
public:
    Timer();
    
    // 計測を開始する
    void start();

    // 計測を停止する
    void stop();

    // 経過時間を取得する（ミリ秒単位）
    double getElapsedMilliseconds() const;

    // 経過時間を取得する（秒単位）
    double getElapsedSeconds() const;

    // 経過時間をフォーマットされた文字列として取得する
    std::string getFormattedElapsedTime() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool running;
};

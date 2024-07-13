#include "timer.hpp"

Timer::Timer() : running(false) {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    running = false;
}

double Timer::getElapsedMilliseconds() const {
    auto end = running ? std::chrono::high_resolution_clock::now() : endTime;
    return std::chrono::duration<double, std::milli>(end - startTime).count();
}

double Timer::getElapsedSeconds() const {
    auto end = running ? std::chrono::high_resolution_clock::now() : endTime;
    return std::chrono::duration<double>(end - startTime).count();
}

std::string Timer::getFormattedElapsedTime() const {
    double milliseconds = getElapsedMilliseconds();
    int hours = static_cast<int>(milliseconds / 3600000);
    milliseconds -= hours * 3600000;
    int minutes = static_cast<int>(milliseconds / 60000);
    milliseconds -= minutes * 60000;
    int seconds = static_cast<int>(milliseconds / 1000);
    milliseconds -= seconds * 1000;

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d.%03d", hours, minutes, seconds, static_cast<int>(milliseconds));
    return std::string(buffer);
}

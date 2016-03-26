#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

class Chrono {
public:

    void start() {
        _start = std::chrono::system_clock::now();
    }

    void stop() {
        _end = std::chrono::system_clock::now();
        _elapsed_seconds += _end - _start;
    }

    double getTime() {
        return _elapsed_seconds.count();
    }
private:
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::time_point<std::chrono::system_clock> _end;
    std::chrono::duration<double> _elapsed_seconds;
};

#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

class Chrono {
public:

    static Chrono &getInstance() {
        static Chrono c;
        return c;
    }

    void start() {
        _start = std::chrono::system_clock::now();
    }

    void end() {
        _end = std::chrono::system_clock::now();
        _elapsed_seconds += _end - _start;
    }

    void display() {
        std::cout << _elapsed_seconds.count() << "s" << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::time_point<std::chrono::system_clock> _end;
    std::chrono::duration<double> _elapsed_seconds;

    Chrono() = default;
    Chrono(const Chrono &other) = delete;
    const Chrono &operator=(const Chrono &other) = delete;
    ~Chrono() {}
};

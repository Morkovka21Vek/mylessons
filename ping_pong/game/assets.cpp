#include "assets.hpp"
#include <chrono>
#include <thread>

static std::chrono::high_resolution_clock::time_point time_start;
static std::chrono::high_resolution_clock::time_point time_end;

static void fps_lock(std::chrono::milliseconds frame_time_ms, size_t fpscount) {
    long timesleep = 1000 / fpscount - frame_time_ms.count();
    if (timesleep > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timesleep));
    }
}

void timer_start() {
    time_start = std::chrono::high_resolution_clock::now();
}

size_t timer_end(size_t MAX_FPS) {
    auto time_middle = std::chrono::high_resolution_clock::now();
    fps_lock(std::chrono::duration_cast<std::chrono::milliseconds>(
                 time_middle - time_start),
             MAX_FPS);
    time_end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(
                     time_end - time_start)
                     .count();
}

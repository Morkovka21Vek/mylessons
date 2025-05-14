#pragma once
#include <chrono>
#include <cstddef>

struct scrsize {
    size_t height;
    size_t width;
};

void fps_lock(std::chrono::milliseconds frame_time, size_t fpscount);

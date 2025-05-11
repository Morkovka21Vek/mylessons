#pragma once
#include <cstddef>
#include <chrono>

struct scrsize {
    size_t height;
    size_t width;
};

void fps_lock(std::chrono::milliseconds frame_time, size_t fpscount);

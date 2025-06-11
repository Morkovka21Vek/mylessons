#pragma once
#include <cmath>

struct Size2D {

    Size2D(size_t width, size_t height): width(width), height(height)
    {}

    Size2D(const Size2D&) = default;

    Size2D(): width(0), height(0) {}

    Size2D& operator=(const Size2D& other) = default;

    size_t width;
    size_t height;
};

struct Vector2D {
    float x, y;

    Vector2D(const Vector2D&) = default;

    Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D() : x(0), y(0) {}

    Vector2D& operator=(const Vector2D& other) = default;

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(float val) const {
        return Vector2D(x * val, y * val);
    }

    Vector2D operator/(float val) const {
        return Vector2D(x / val, y / val);
    }

    Vector2D &operator+=(const Vector2D &obj2) {
        this->x += obj2.x;
        this->y += obj2.y;
        return *this;
    }

    Vector2D &operator-=(const Vector2D &obj2) {
        this->x -= obj2.x;
        this->y -= obj2.y;
        return *this;
    }

    float magnitude() const {
        return std::sqrt(x*x + y*y);
    }

    Vector2D normalized() const {
        float mag = magnitude();
        if (mag > 0) return Vector2D(x/mag, y/mag);
        return Vector2D(0, 0);
    }
};

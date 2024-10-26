#ifndef VECTOR4_HPP
#define VECTOR4_HPP

/// SIMD Vector4 | 128-bit SSE

#include <array>
#include <immintrin.h>

namespace SIMD_OPS {
    class Vector4 {
        public:
        std::array<float, 4> data;

        Vector4() : data{ 0.0f, 0.0f, 0.0f, 0.0f } {}
        Vector4(float x, float y, float z, float w) : data{ x, y, z, w } {}
        Vector4(const std::array<float, 4>& arr) : data(arr) {}
        Vector4(const __m128 a128) { _mm_storeu_ps(this->data.data(), a128); }
        Vector4(const float* arr) { _mm_storeu_ps(this->data.data(), _mm_loadu_ps(arr)); }

        Vector4 operator+(const Vector4& other) const {
            return Vector4(_mm_add_ps(_mm_loadu_ps(this->data.data()), _mm_loadu_ps(other.data.data())));
        }

        Vector4 operator-(const Vector4& other) const {
            return Vector4(_mm_sub_ps(_mm_loadu_ps(this->data.data()), _mm_loadu_ps(other.data.data())));
        }

        Vector4 operator*(const Vector4& other) const {
            return Vector4(_mm_mul_ps(_mm_loadu_ps(this->data.data()), _mm_loadu_ps(other.data.data())));
        }

        Vector4 operator/(const Vector4& other) const {
            return Vector4(_mm_div_ps(_mm_loadu_ps(this->data.data()), _mm_loadu_ps(other.data.data())));
        }

        float& operator[](int index) {
            return this->data[index];
        }

        const float& operator[](int index) const {
            return this->data[index];
        }
    };
}

#endif // VECTOR4_HPP
#ifndef VECTOR16_HPP
#define VECTOR16_HPP

/// SIMD Vector16 | 512-bit AVX-512

#include <array>
#include <immintrin.h>

namespace SIMD_OPS {
    class Vector16 {
        public:
        std::array<float, 16> data;

        Vector16() : data{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f } {}
        Vector16(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) : data{ a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p } {}
        Vector16(const std::array<float, 16>& arr) : data(arr) {}
        Vector16(const __m512 a512) { _mm512_storeu_ps(this->data.data(), a512); }
        Vector16(const float* arr) { _mm512_storeu_ps(this->data.data(), _mm512_loadu_ps(arr)); }

        Vector16 operator+(const Vector16& other) const {
            return Vector16(_mm512_add_ps(_mm512_loadu_ps(this->data.data()), _mm512_loadu_ps(other.data.data())));
        }

        Vector16 operator-(const Vector16& other) const {
            return Vector16(_mm512_sub_ps(_mm512_loadu_ps(this->data.data()), _mm512_loadu_ps(other.data.data())));
        }

        Vector16 operator*(const Vector16& other) const {
            return Vector16(_mm512_mul_ps(_mm512_loadu_ps(this->data.data()), _mm512_loadu_ps(other.data.data())));
        }

        Vector16 operator/(const Vector16& other) const {
            return Vector16(_mm512_div_ps(_mm512_loadu_ps(this->data.data()), _mm512_loadu_ps(other.data.data())));
        }

        float& operator[](int index) {
            return this->data[index];
        }

        const float& operator[](int index) const {
            return this->data[index];
        }
    };
}

#endif // VECTOR16_HPP
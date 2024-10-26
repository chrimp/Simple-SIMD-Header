#ifndef VECTOR8_HPP
#define VECTOR8_HPP

/// SIMD Vector8 | 256-bit AVX

#include <array>
#include <immintrin.h>

namespace SIMD_OPS {
    class Vector8 {
        public:
        std::array<float, 8> data;

        Vector8() : data{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f } {}
        Vector8(float a, float b, float c, float d, float e, float f, float g, float h) : data{ a, b, c, d, e, f, g, h } {}
        Vector8(const std::array<float, 8>& arr) : data(arr) {}
        Vector8(const __m256 a256) { _mm256_storeu_ps(this->data.data(), a256); }
        Vector8(const float* arr) { _mm256_storeu_ps(this->data.data(), _mm256_loadu_ps(arr)); }

        Vector8 operator+(const Vector8& other) const {
            return Vector8(_mm256_add_ps(_mm256_loadu_ps(this->data.data()), _mm256_loadu_ps(other.data.data())));
        }

        Vector8 operator-(const Vector8& other) const {
            return Vector8(_mm256_sub_ps(_mm256_loadu_ps(this->data.data()), _mm256_loadu_ps(other.data.data())));
        }

        Vector8 operator*(const Vector8& other) const {
            return Vector8(_mm256_mul_ps(_mm256_loadu_ps(this->data.data()), _mm256_loadu_ps(other.data.data())));
        }

        Vector8 operator/(const Vector8& other) const {
            return Vector8(_mm256_div_ps(_mm256_loadu_ps(this->data.data()), _mm256_loadu_ps(other.data.data())));
        }

        float& operator[](int index) {
            return this->data[index];
        }

        const float& operator[](int index) const {
            return this->data[index];
        }
    };
}

#endif // VECTOR8_HPP
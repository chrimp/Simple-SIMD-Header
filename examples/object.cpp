#include <algorithm>
#include <immintrin.h>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <ratio>
#include <vector>
#include <iostream>
#include <thread>
#include "../headers/Vector4.hpp"
#include "../headers/Vector8.hpp"
#include "../headers/Vector16.hpp"


using namespace std;
using namespace SIMD_OPS;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

const int NUM_ARRS = 1000;
const int ARR_SIZE = 300000;

void add_vec4(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 3; i += 4) {
        Vector4 vec_a(&a[i]);
        Vector4 vec_b(&b[i]);

        Vector4 result = vec_a + vec_b;
        move(result.data.data(), result.data.data() + 4, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] += b[i];
    }
}

void add_vec8(vector<float>& a, vector<float>& b) {
    int i = 0;

    __m256 result = _mm256_setzero_ps();
    for (; i < ARR_SIZE - 7; i += 8) {
        Vector8 vec_a(&a[i]);
        Vector8 vec_b(&b[i]);

        Vector8 result = vec_a + vec_b;

        move(result.data.data(), result.data.data() + 8, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] += b[i];
    }
} 

void add_vec16(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 15; i += 16) {
        Vector16 vec_a(&a[i]);
        Vector16 vec_b(&b[i]);

        Vector16 result = vec_a + vec_b;

        move(result.data.data(), result.data.data() + 16, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] += b[i];
    }
}

void mul_vec4(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 3; i += 4) {
        Vector4 vec_a(&a[i]);
        Vector4 vec_b(&b[i]);

        Vector4 result = vec_a * vec_b;

        move(result.data.data(), result.data.data() + 4, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] *= b[i];
    }
}

void mul_vec8(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 7; i += 8) {
        Vector8 vec_a(&a[i]);
        Vector8 vec_b(&b[i]);

        Vector8 result = vec_a * vec_b;

        move(result.data.data(), result.data.data() + 8, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] *= b[i];
    }
} 

void mul_vec16(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 15; i += 16) {
        Vector16 vec_a(&a[i]);
        Vector16 vec_b(&b[i]);

        Vector16 result = vec_a * vec_b;

        move(result.data.data(), result.data.data() + 16, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] *= b[i];
    }
}

void sub_vec4(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 3; i += 4) {
        Vector4 vec_a(&a[i]);
        Vector4 vec_b(&b[i]);

        Vector4 result = vec_a - vec_b;

        move(result.data.data(), result.data.data() + 4, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] -= b[i];
    }
}

void sub_vec8(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 7; i += 8) {
        Vector8 vec_a(&a[i]);
        Vector8 vec_b(&b[i]);

        Vector8 result = vec_a - vec_b;

        move(result.data.data(), result.data.data() + 8, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] -= b[i];
    }
} 

void sub_vec16(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 15; i += 16) {
        Vector16 vec_a(&a[i]);
        Vector16 vec_b(&b[i]);

        Vector16 result = vec_a - vec_b;

        move(result.data.data(), result.data.data() + 16, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] -= b[i];
    }
}

void div_vec4(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 3; i += 4) {
        Vector4 vec_a(&a[i]);
        Vector4 vec_b(&b[i]);

        Vector4 result = vec_a / vec_b;

        move(result.data.data(), result.data.data() + 4, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] /= b[i];
    }
}

void div_vec8(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 7; i += 8) {
        Vector8 vec_a(&a[i]);
        Vector8 vec_b(&b[i]);

        Vector8 result = vec_a / vec_b;

        move(result.data.data(), result.data.data() + 8, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] /= b[i];
    }
} 

void div_vec16(vector<float>& a, vector<float>& b) {
    int i = 0;

    for (; i < ARR_SIZE - 15; i += 16) {
        Vector16 vec_a(&a[i]);
        Vector16 vec_b(&b[i]);

        Vector16 result = vec_a / vec_b;

        move(result.data.data(), result.data.data() + 16, &a[i]);
    }

    for (; i < ARR_SIZE; i++) {
        a[i] /= b[i];
    }
}

void scalar_add(vector<float>& a, vector<float>& b) {
    for (int i = 0; i < a.size(); i++) {
        a[i] += b[i];
    }
}

void scalar_sub(vector<float>& a, vector<float>& b) {
    for (int i = 0; i < a.size(); i++) {
        a[i] -= b[i];
    }
}

void scalar_mul(vector<float>& a, vector<float>& b) {
    for (int i = 0; i < a.size(); i++) {
        a[i] *= b[i];
    }
}

void scalar_div(vector<float>& a, vector<float>& b) {
    for (int i = 0; i < a.size(); i++) {
        a[i] /= b[i];
    }
}

void add_vec4_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        add_vec4(arrs[i], arrs[i + 1]);
    }
}

void add_vec8_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        add_vec8(arrs[i], arrs[i + 1]);
    }
}

void add_vec16_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        add_vec16(arrs[i], arrs[i + 1]);
    }
}

void mul_vec4_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        mul_vec4(arrs[i], arrs[i + 1]);
    }
}

void mul_vec8_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        mul_vec8(arrs[i], arrs[i + 1]);
    }
}

void mul_vec16_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        mul_vec16(arrs[i], arrs[i + 1]);
    }
}

void sub_vec4_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        sub_vec4(arrs[i], arrs[i + 1]);
    }
}

void sub_vec8_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        sub_vec8(arrs[i], arrs[i + 1]);
    }
}

void sub_vec16_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        sub_vec16(arrs[i], arrs[i + 1]);
    }
}

void div_vec4_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        div_vec4(arrs[i], arrs[i + 1]);
    }
}

void div_vec8_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        div_vec8(arrs[i], arrs[i + 1]);
    }
}

void div_vec16_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        div_vec16(arrs[i], arrs[i + 1]);
    }
}

void scalar_add_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        scalar_add(arrs[i], arrs[i + 1]);
    }
}

void scalar_sub_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        scalar_sub(arrs[i], arrs[i + 1]);
    }
}

void scalar_mul_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        scalar_mul(arrs[i], arrs[i + 1]);
    }
}

void scalar_div_threadWorker(vector<vector<float>>& arrs, int start, int end) {
    for (int i = start; i < end; i++) {
        scalar_div(arrs[i], arrs[i + 1]);
    }
}

const int NUM_THREADS = 1;
const int CHUNK_SIZE = NUM_ARRS / NUM_THREADS;

vector<duration<double, milli>> bench_adds(vector<vector<float>>& arrs) {
    vector<thread> threads(NUM_THREADS);

    auto vector4_add_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(add_vec4_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector4_add_end = high_resolution_clock::now();
    auto vector4_add_duration = duration_cast<milliseconds>(vector4_add_end - vector4_add_start);
    duration<double, milli> vector4_add_ms = vector4_add_duration;

    auto vector8_add_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(add_vec8_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector8_add_end = high_resolution_clock::now();
    auto vector8_add_duration = duration_cast<milliseconds>(vector8_add_end - vector8_add_start);
    duration<double, milli> vector8_add_ms = vector8_add_duration;

    auto vector16_add_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(add_vec16_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector16_add_end = high_resolution_clock::now();
    auto vector16_add_duration = duration_cast<milliseconds>(vector16_add_end - vector16_add_start);
    duration<double, milli> vector16_add_ms = vector16_add_duration;

    auto scalar_add_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(scalar_add_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto scalar_add_end = high_resolution_clock::now();
    auto scalar_add_duration = duration_cast<milliseconds>(scalar_add_end - scalar_add_start);
    duration<double, milli> scalar_add_ms = scalar_add_duration;

    vector<duration<double, milli>> ret = {scalar_add_ms, vector4_add_ms, vector8_add_ms, vector16_add_ms};

    return ret;
}

vector<duration<double, milli>> bench_muls(vector<vector<float>>& arrs) {
    vector<thread> threads(NUM_THREADS);

    auto vector4_mul_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(mul_vec4_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector4_mul_end = high_resolution_clock::now();
    auto vector4_mul_duration = duration_cast<milliseconds>(vector4_mul_end - vector4_mul_start);
    duration<double, milli> vector4_mul_ms = vector4_mul_duration;

    auto vector8_mul_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(mul_vec8_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector8_mul_end = high_resolution_clock::now();
    auto vector8_mul_duration = duration_cast<milliseconds>(vector8_mul_end - vector8_mul_start);
    duration<double, milli> vector8_mul_ms = vector8_mul_duration;

    auto vector16_mul_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(mul_vec16_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector16_mul_end = high_resolution_clock::now();
    auto vector16_mul_duration = duration_cast<milliseconds>(vector16_mul_end - vector16_mul_start);
    duration<double, milli> vector16_mul_ms = vector16_mul_duration;

    auto scalar_mul_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(scalar_mul_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto scalar_mul_end = high_resolution_clock::now();
    auto scalar_mul_duration = duration_cast<milliseconds>(scalar_mul_end - scalar_mul_start);
    duration<double, milli> scalar_mul_ms = scalar_mul_duration;

    vector<duration<double, milli>> ret = {scalar_mul_ms, vector4_mul_ms, vector8_mul_ms, vector16_mul_ms};

    return ret;
}

vector<duration<double, milli>> bench_subs(vector<vector<float>>& arrs) {
    vector<thread> threads(NUM_THREADS);

    auto vector4_sub_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(sub_vec4_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector4_sub_end = high_resolution_clock::now();
    auto vector4_sub_duration = duration_cast<milliseconds>(vector4_sub_end - vector4_sub_start);
    duration<double, milli> vector4_sub_ms = vector4_sub_duration;

    auto vector8_sub_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(sub_vec8_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector8_sub_end = high_resolution_clock::now();
    auto vector8_sub_duration = duration_cast<milliseconds>(vector8_sub_end - vector8_sub_start);
    duration<double, milli> vector8_sub_ms = vector8_sub_duration;

    auto vector16_sub_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(sub_vec16_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector16_sub_end = high_resolution_clock::now();
    auto vector16_sub_duration = duration_cast<milliseconds>(vector16_sub_end - vector16_sub_start);
    duration<double, milli> vector16_sub_ms = vector16_sub_duration;

    auto scalar_sub_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(scalar_sub_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto scalar_sub_end = high_resolution_clock::now();
    auto scalar_sub_duration = duration_cast<milliseconds>(scalar_sub_end - scalar_sub_start);
    duration<double, milli> scalar_sub_ms = scalar_sub_duration;

    vector<duration<double, milli>> ret = {scalar_sub_ms, vector4_sub_ms, vector8_sub_ms, vector16_sub_ms};

    return ret;
}

vector<duration<double, milli>> bench_divs(vector<vector<float>>& arrs) {
    vector<thread> threads(NUM_THREADS);

    auto vector4_div_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(div_vec4_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector4_div_end = high_resolution_clock::now();
    auto vector4_div_duration = duration_cast<milliseconds>(vector4_div_end - vector4_div_start);
    duration<double, milli> vector4_div_ms = vector4_div_duration;

    auto vector8_div_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(div_vec8_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector8_div_end = high_resolution_clock::now();
    auto vector8_div_duration = duration_cast<milliseconds>(vector8_div_end - vector8_div_start);
    duration<double, milli> vector8_div_ms = vector8_div_duration;

    auto vector16_div_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(div_vec16_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto vector16_div_end = high_resolution_clock::now();
    auto vector16_div_duration = duration_cast<milliseconds>(vector16_div_end - vector16_div_start);
    duration<double, milli> vector16_div_ms = vector16_div_duration;

    auto scalar_div_start = high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(scalar_div_threadWorker, ref(arrs), i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE - 1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    auto scalar_div_end = high_resolution_clock::now();
    auto scalar_div_duration = duration_cast<milliseconds>(scalar_div_end - scalar_div_start);
    duration<double, milli> scalar_div_ms = scalar_div_duration;

    vector<duration<double, milli>> ret = {scalar_div_ms, vector4_div_ms, vector8_div_ms, vector16_div_ms};

    return ret;
}

int main() {
    //srand(chrono::system_clock::now().time_since_epoch().count());
    srand(100);

    vector<vector<float>> arrs(NUM_ARRS, vector<float>(ARR_SIZE));

    for (int i = 0; i < NUM_ARRS; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {
            arrs[i][j] = static_cast<float>(i);
            //arrs[i][j] = static_cast<float>(rand());
        }
    }

    duration<double, milli> scalar_add_ms = duration<double, milli>::zero();
    duration<double, milli> vector4_add_ms = duration<double, milli>::zero();
    duration<double, milli> vector8_add_ms = duration<double, milli>::zero();
    duration<double, milli> vector16_add_ms = duration<double, milli>::zero();

    for (int i = 0; i < 3; i++) {
        vector<duration<double, milli>> add_times = bench_adds(arrs);
        scalar_add_ms += add_times[0];
        vector4_add_ms += add_times[1];
        vector8_add_ms += add_times[2];
        vector16_add_ms += add_times[3];
    }

    duration<double, milli> scalar_mul_ms = duration<double, milli>::zero();
    duration<double, milli> vector4_mul_ms = duration<double, milli>::zero();
    duration<double, milli> vector8_mul_ms = duration<double, milli>::zero();
    duration<double, milli> vector16_mul_ms = duration<double, milli>::zero();

    for (int i = 0; i < 3; i++) {
        vector<duration<double, milli>> mul_times = bench_muls(arrs);
        scalar_mul_ms += mul_times[0];
        vector4_mul_ms += mul_times[1];
        vector8_mul_ms += mul_times[2];
        vector16_mul_ms += mul_times[3];
    }

    duration<double, milli> scalar_sub_ms = duration<double, milli>::zero();
    duration<double, milli> vector4_sub_ms = duration<double, milli>::zero();
    duration<double, milli> vector8_sub_ms = duration<double, milli>::zero();
    duration<double, milli> vector16_sub_ms = duration<double, milli>::zero();

    for (int i = 0; i < 3; i++) {
        vector<duration<double, milli>> sub_times = bench_subs(arrs);
        scalar_sub_ms += sub_times[0];
        vector4_sub_ms += sub_times[1];
        vector8_sub_ms += sub_times[2];
        vector16_sub_ms += sub_times[3];
    }

    duration<double, milli> scalar_div_ms = duration<double, milli>::zero();
    duration<double, milli> vector4_div_ms = duration<double, milli>::zero();
    duration<double, milli> vector8_div_ms = duration<double, milli>::zero();
    duration<double, milli> vector16_div_ms = duration<double, milli>::zero();

    for (int i = 0; i < 3; i++) {
        vector<duration<double, milli>> div_times = bench_divs(arrs);
        scalar_div_ms += div_times[0];
        vector4_div_ms += div_times[1];
        vector8_div_ms += div_times[2];
        vector16_div_ms += div_times[3];
    }

    cout << "Scalar add - Total: " << scalar_add_ms.count() << "ms, " << "avg: " << scalar_add_ms.count() / 3 << "ms" << endl;
    cout << "Vector4 add - Total: " << vector4_add_ms.count() << "ms, " << "avg: " << vector4_add_ms.count() / 3 << "ms" << endl;
    cout << "Vector8 add - Total: " << vector8_add_ms.count() << "ms, " << "avg: " << vector8_add_ms.count() / 3 << "ms" << endl;
    cout << "Vector16 add - Total: " << vector16_add_ms.count() << "ms, " << "avg: " << vector16_add_ms.count() / 3 << "ms" << endl;
    cout << endl;

    cout << "Scalar mul - Total: " << scalar_mul_ms.count() << "ms, " << "avg: " << scalar_mul_ms.count() / 3 << "ms" << endl;
    cout << "Vector4 mul - Total: " << vector4_mul_ms.count() << "ms, " << "avg: " << vector4_mul_ms.count() / 3 << "ms" << endl;
    cout << "Vector8 mul - Total: " << vector8_mul_ms.count() << "ms, " << "avg: " << vector8_mul_ms.count() / 3 << "ms" << endl;
    cout << "Vector16 mul - Total: " << vector16_mul_ms.count() << "ms, " << "avg: " << vector16_mul_ms.count() / 3 << "ms" << endl;
    cout << endl;

    cout << "Scalar sub - Total: " << scalar_sub_ms.count() << "ms, " << "avg: " << scalar_sub_ms.count() / 3 << "ms" << endl;
    cout << "Vector4 sub - Total: " << vector4_sub_ms.count() << "ms, " << "avg: " << vector4_sub_ms.count() / 3 << "ms" << endl;
    cout << "Vector8 sub - Total: " << vector8_sub_ms.count() << "ms, " << "avg: " << vector8_sub_ms.count() / 3 << "ms" << endl;
    cout << "Vector16 sub - Total: " << vector16_sub_ms.count() << "ms, " << "avg: " << vector16_sub_ms.count() / 3 << "ms" << endl;
    cout << endl;

    cout << "Scalar div - Total: " << scalar_div_ms.count() << "ms, " << "avg: " << scalar_div_ms.count() / 3 << "ms" << endl;
    cout << "Vector4 div - Total: " << vector4_div_ms.count() << "ms, " << "avg: " << vector4_div_ms.count() / 3 << "ms" << endl;
    cout << "Vector8 div - Total: " << vector8_div_ms.count() << "ms, " << "avg: " << vector8_div_ms.count() / 3 << "ms" << endl;
    cout << "Vector16 div - Total: " << vector16_div_ms.count() << "ms, " << "avg: " << vector16_div_ms.count() / 3 << "ms" << endl;

    return 0;
}

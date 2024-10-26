# Simple SIMD header
Use these header files for hardware-accelerated basic arithmetic operations with FP32 data.

- **Vector4.hpp**  
Use this for SSE operations (FP32 * 4, 128-bit)
- **Vector8.hpp**  
Use this for AVX operations (FP32 * 8, 256-bit)
- **Vector16.hpp**  
Use this for AVX512 operations (FP32 * 16, 512-bit)

## How to use
Simply include hpp in your code. (#include "Vector*.hpp")  
You can create instance with:
```C++
using namespace SIMD_OPS
Vector4 a; // Creates zero-filled instance {0, 0, 0, 0}
Vector4 b = {0, 0, 0, 0}; // Create instance from values

// Create instance from float std::array
std::array<float, 4> myArr = { 1.0, 2.0, 3.0, 4.0 };
Vector4 c(myArr);

// Creates instance from array-like objects. Pass the address of the start element.
std::vector<float> myVec = { 1, 2, 3, 4, 5, 6, 7, 8 };
Vector4 d(&myVec[1]); // Contains 2, 3, 4, 5

// Create instance from __m128
__m128 myIntrinData = _mm_set_ps(1.0, 2.0, 3.0, 4.0);
Vector4 e(myIntrinData);
```
**Be careful when passing the address of an element.** It does not check for out-of-bounds. If ( (size - starting index) < size of class (4/8/16) ) then it will cause undefined behavior.

Also you can get the value and reference of the elements by index:
```C++
// Get value
Vector4 vec; // { 0, 0, 0, 0 }
float val = vec[0]; // 0
val = 1; // vec is still { 0, 0, 0, 0 }

// Get Reference
float& ref = vec[0]; // 0
ref = 1; // vec is now { 1, 0, 0, 0 }
const float& constRef = vec[0]; // constRef is const, read-only
```

## Use cases
Generally you don't need these, compilers with optimization enabled will automatically vectorize/unroll loops for you.  
However in some cases compiler misses possible vectorization points:
```C++
(Original Code)
void SecondOrderIIRFilter::ProcessBuffer(vector<vector<float>>& buffer) {
    int numOfChannles = min(m_NumChannels, (int)buffer.size());

    for (int channel = 0; channel < numOfChannles; channel++) {
        vector<float>& samples = buffer[channel];

        for (int i = 0; i < buffer[channel].size(); i++) {
            float inVal = samples[i];

            float factorForB0 = inVal - m_A1 * m_Z1[channel] - m_A2 * m_Z2[channel];
            float outVal = m_B0 * factorForB0 + m_B1 * m_Z1[channel] + m_B2 * m_Z2[channel];

            m_Z2[channel] = m_Z1[channel];
            m_Z1[channel] = factorForB0;

            samples[i] = outVal;
        }
    }
}
```
(Above is conversion to C++ from xuan25's [R128Normalization](https://github.com/xuan25/R128Normalization/blob/master/R128Normalization/R128Normalization/R128/Lufs/SecondOrderIIRFilter.cs), under [GPL-3.0 license](https://github.com/xuan25/R128Normalization/blob/master/LICENSE))

```C++
(Vectorized with SSE)
void AVX_Filter::processVector(vector<vector<float>>& samples) {
    int size = samples.size();

    Z1Vec = {0, 0, 0, 0};
    Z2Vec = {0, 0, 0, 0};

    array<float, 2> factorForB0_Pre = {samples[0][0], samples[1][0]};
    array<float, 2> B0Pre_2 = {B0_Pre, B0_Pre};
    array<float, 2> outVal_Pre = {factorForB0_Pre[0] * B0Pre_2[0], factorForB0_Pre[1] * B0Pre_2[1]};

    Vector4 calc = {samples[0][1], samples[1][1], outVal_Pre[0], outVal_Pre[1]};

    Z1Vec[0] = samples[0][0];
    Z1Vec[1] = samples[1][0];

    int i = 2;

    for (; i < size; i++) {
        Vector4 factorForB0 = calc - A1Vec * Z1Vec - A2Vec * Z2Vec;
        Vector4 outVal = B0Vec * factorForB0 + B1Vec * Z1Vec + B2Vec * Z2Vec;

        Z2Vec = Z1Vec;
        Z1Vec = factorForB0;

        samples[0][i - 1] = outVal[2];
        samples[1][i - 1] = outVal[3];

        calc[2] = outVal[0];
        calc[3] = outVal[1];
        calc[0] = samples[0][i];
        calc[1] = samples[1][i];
    }

    Vector4 factorForB0 = calc - A1Vec * Z1Vec - A2Vec * Z2Vec;
    Vector4 outVal = B0Vec * factorForB0 + B1Vec * Z1Vec + B2Vec * Z2Vec;

    samples[0][i - 1] = outVal[2];
    samples[1][i - 1] = outVal[3];
    
    return;
}
```
(Above is my original work, under MIT License)

Using original code (scalar) takes 15.284 seconds in average, while SSE version took 12.032 seconds in average.  
Benchmark was done by measuring LUFS of 504 audio files which includes above functions' processing on each file. Iterated three times, averaged.

## Requirements
Target platform should support according instruction set (SSE/AVX/AVX512), these header files **do not** include runtime feature check.

## Compile Options
**!!Use this with optimization enabled!!** Instance creation is expensive--especially over a large iteration.  
When optimization is enabled, there is no difference between creating instance and directly calling intrinsics.

Below is benchmark without optimization enabled, directly calling intrinsics without using header files:
```
Scalar add - Total: 2035ms, avg: 678.333ms
SSE add - Total: 1421ms, avg: 473.667ms
AVX2 add - Total: 767ms, avg: 255.667ms
AVX512 add - Total: 610ms, avg: 203.333ms

Scalar mul - Total: 3316ms, avg: 1105.33ms
SSE mul - Total: 1430ms, avg: 476.667ms
AVX2 mul - Total: 753ms, avg: 251ms
AVX512 mul - Total: 590ms, avg: 196.667ms

Scalar sub - Total: 3447ms, avg: 1149ms
SSE sub - Total: 1445ms, avg: 481.667ms
AVX2 sub - Total: 772ms, avg: 257.333ms
AVX512 sub - Total: 631ms, avg: 210.333ms

Scalar div - Total: 3442ms, avg: 1147.33ms
SSE div - Total: 1586ms, avg: 528.667ms
AVX2 div - Total: 823ms, avg: 274.333ms
AVX512 div - Total: 632ms, avg: 210.667ms
```
Below is benchmark with the same configuration, except this time using header files' classes:
```
Scalar add - Total: 3522ms, avg: 1174ms
Vector4 add - Total: 7288ms, avg: 2429.33ms
Vector8 add - Total: 4145ms, avg: 1381.67ms
Vector16 add - Total: 2513ms, avg: 837.667ms

Scalar mul - Total: 3448ms, avg: 1149.33ms
Vector4 mul - Total: 5648ms, avg: 1882.67ms
Vector8 mul - Total: 4158ms, avg: 1386ms
Vector16 mul - Total: 2680ms, avg: 893.333ms

Scalar sub - Total: 3527ms, avg: 1175.67ms
Vector4 sub - Total: 6271ms, avg: 2090.33ms
Vector8 sub - Total: 4196ms, avg: 1398.67ms
Vector16 sub - Total: 2640ms, avg: 880ms

Scalar div - Total: 3495ms, avg: 1165ms
Vector4 div - Total: 7807ms, avg: 2602.33ms
Vector8 div - Total: 4431ms, avg: 1477ms
Vector16 div - Total: 2711ms, avg: 903.667ms
```
As can be seen when compiler optimization is disabled the overhead is significant.
Ran basic operations on 1,000 of 300,000-large float arrays, three iterations on each operation. Refer to [these codes](https://github.com/chrimp/Simple-SIMD-Header/tree/main/examples).  
Benchmark performed on 7800X3D with 16x2GB of 6000/CL30 DDR5 memory sticks. Expect memory bandwidth bottleneck anywhere between AVX2 and AVX512 with 16 threads.
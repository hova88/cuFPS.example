#pragma once
#include <cuda_runtime.h>
void furthest_point_sampling(int a , int n , int m,
    const float* data , float* temp , int* idx , cudaStream_t stream);

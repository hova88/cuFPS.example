#include <stdio.h>
#include "utils.cc"
#include "src/fps.h"


int main() 
{

    std::string file_name = "../nuscenes_10sweeps_points.txt";
    float* cloud;
    float* temp;

    int n = LoadCloud(cloud , temp ,file_name , 5);
    int m = 5000;

    float* dev_cloud;
    float* dev_temp;
    int* dev_idx;
    cudaMalloc(reinterpret_cast<void**>(&dev_cloud), n * 3 * sizeof(float));
    cudaMalloc(reinterpret_cast<void**>(&dev_temp), n * sizeof(float));
    cudaMalloc(reinterpret_cast<void**>(&dev_idx), m * sizeof(int));
    
    cudaMemcpy(dev_cloud , cloud ,n * 3 * sizeof(float) , cudaMemcpyHostToDevice);
    cudaMemcpy(dev_temp , temp ,n * sizeof(float) , cudaMemcpyHostToDevice);


    cudaStream_t stream;
    cudaStreamCreate(&stream);

    furthest_point_sampling(1,n,m,dev_cloud,dev_temp,dev_idx,stream);

    cudaDeviceSynchronize();


    int host_idx[m] = {};
    cudaMemcpy(reinterpret_cast<void**>(&host_idx) , dev_idx , m * sizeof(int) , cudaMemcpyDeviceToHost);

    for (int i = 0 ; i < m ; ++i)
    {
        printf("%f %f %f \n",cloud[host_idx[i]*3 + 0],cloud[host_idx[i]*3 + 1],cloud[host_idx[i]*3 + 2]);
    }
    
    cudaStreamDestroy(stream);
    cudaFree(dev_temp);
    cudaFree(dev_cloud);
    cudaFree(dev_idx);
    return 0;
}
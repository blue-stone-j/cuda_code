
#include <iostream>


#include "common/myutility.h"

#include "func/addition.h"
#include "func/matrix_cuda.h"
#include "func/cloud_normal.h"
#include "func/reduction.h"
#include "func/cloud_change.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "cuda_code_node");

  //***** 设置日志 *****//
  FLAGS_log_dir          = std::string(getenv("HOME")) + "/bag/perception_test/log";
  FLAGS_colorlogtostderr = true;
  FLAGS_alsologtostderr  = true; // shouldbe false
  FLAGS_logbuflevel      = -1;
  // todo: use CLog from common
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "cuda_code node starts";


  int dev = 0, driverVersion = 0, runtimeVersion = 0;
  cudaDeviceProp deviceProp;
  printf("cuda device properties: %d\n", cudaGetDeviceProperties(&deviceProp, dev));
  cudaDriverGetVersion(&driverVersion);
  cudaRuntimeGetVersion(&runtimeVersion);
  printf("  CUDA Driver Version / Runtime Version         %d.%d  /  %d.%d\n",
         driverVersion / 1000, (driverVersion % 100) / 10,
         runtimeVersion / 1000, (runtimeVersion % 100) / 10);
  printf("  CUDA Capability Major/Minor version number:   %d.%d\n",
         deviceProp.major, deviceProp.minor);
  printf("  Total amount of global memory:                %.2f MBytes (%llu bytes)\n",
         (float)deviceProp.totalGlobalMem / pow(1024.0, 3));
  printf("  GPU Clock rate:                               %.0f MHz (%0.2f GHz)\n",
         deviceProp.clockRate * 1e-3f, deviceProp.clockRate * 1e-6f);
  printf("  Memory Bus width:                             %d-bits\n",
         deviceProp.memoryBusWidth);
  if (deviceProp.l2CacheSize)
  {
    printf("  L2 Cache Size:                            	%d bytes\n",
           deviceProp.l2CacheSize);
  }
  printf("  Max Texture Dimension Size (x,y,z)            1D=(%d),2D=(%d,%d),3D=(%d,%d,%d)\n",
         deviceProp.maxTexture1D, deviceProp.maxTexture2D[0], deviceProp.maxTexture2D[1], deviceProp.maxTexture3D[0], deviceProp.maxTexture3D[1], deviceProp.maxTexture3D[2]);
  printf("  Max Layered Texture Size (dim) x layers       1D=(%d) x %d,2D=(%d,%d) x %d\n",
         deviceProp.maxTexture1DLayered[0], deviceProp.maxTexture1DLayered[1],
         deviceProp.maxTexture2DLayered[0], deviceProp.maxTexture2DLayered[1],
         deviceProp.maxTexture2DLayered[2]);
  printf("  Total amount of constant memory               %lu bytes\n",
         deviceProp.totalConstMem);
  printf("  Total amount of shared memory per block:      %lu bytes\n",
         deviceProp.sharedMemPerBlock);
  printf("  Total number of registers available per block:%d\n",
         deviceProp.regsPerBlock);
  printf("  Wrap size:                                    %d\n", deviceProp.warpSize);
  printf("  Maximun number of thread per multiprocesser:  %d\n",
         deviceProp.maxThreadsPerMultiProcessor);
  printf("  Maximun number of thread per block:           %d\n",
         deviceProp.maxThreadsPerBlock);
  printf("  Maximun size of each dimension of a block:    %d x %d x %d\n",
         deviceProp.maxThreadsDim[0], deviceProp.maxThreadsDim[1], deviceProp.maxThreadsDim[2]);
  printf("  Maximun size of each dimension of a grid:     %d x %d x %d\n",
         deviceProp.maxGridSize[0],
         deviceProp.maxGridSize[1],
         deviceProp.maxGridSize[2]);
  printf("  Maximu memory pitch                           %lu bytes\n", deviceProp.memPitch);
  std::cout << "  使用GPU device " << dev << ": " << deviceProp.name << std::endl;
  std::cout << "  SM的数量: " << deviceProp.multiProcessorCount << std::endl;
  std::cout << "  每个线程块的共享内存大小: " << deviceProp.sharedMemPerBlock / 1024.0 << " KB" << std::endl;
  std::cout << "  每个EM的最大线程数: " << deviceProp.maxThreadsPerMultiProcessor << std::endl;
  std::cout << "  每个SM的最大线程束数: " << deviceProp.maxThreadsPerMultiProcessor / 32 << std::endl;
  std::cout << std::endl
            << std::endl;

  NumAdd num_add;

  Matrix mat;
  mat.matrixMul(mat.A, mat.B, mat.C);
  mat.matrixAdd(mat.A, mat.B, mat.C);

  Reduction reduction;

  CloudChange cloud_change;
  ;

  // CloudNormal cloud_normal;

  std::cout << "cuda node finish" << std::endl;

  return 0;
}
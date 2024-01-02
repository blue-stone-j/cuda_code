cmake_minimum_required(VERSION 3.10)
project(cuda_code)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -DMY_DEF=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMY_DEF=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMY_DEF=1")

find_package(catkin REQUIRED COMPONENTS
  roscpp

  # CUDA
  PCL

  # pcl_conversions
)

find_package(CUDA REQUIRED)
find_package(PCL 1.10.1 REQUIRED)

catkin_package(
  INCLUDE_DIRS include # The exported include paths

  DEPENDS PCL # Non-catkin CMake projects

  LIBRARIES cuda_code # The exported libraries from the project
  CATKIN_DEPENDS
  std_msgs
  sensor_msgs

  # truck_msgs
  # comm_lib
)

# include directories
include_directories(
  include

  ${PCL_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${CUDA_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

set(srcs
  src/func/addition.cu
  src/func/matrix_cuda.cu
  src/func/reduction.cu
  src/func/cloud_change.cu
  src/func/cloud_normal.cu

  src/cuda_code_node.cpp
)

set(incs
  include/common/cuda_base.h
  include/func/addition.h
  include/func/matrix_cuda.h

  include/func/cloud_normal.h
  include/common/myutility.h
)

# cuda_add_library(cuda_code_lib ${srcs} ${incs})
cuda_add_executable(cuda_code_node ${srcs})

target_link_libraries(cuda_code_node
  ${CUDA_LIBRARIES}
  ${CUDA_CUBLAS_LIBRARIES}
  ${CUDA_curand_LIBRARY}

  ${PCL_LIBRARY_DIRS}
  ${YAML_CPP_LIBRARIES}
  ${catkin_LIBRARIES}
  glog gflags
)

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
install(TARGETS cuda_code_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/cuda_code/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY
  launch
  config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

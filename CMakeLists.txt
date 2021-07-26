cmake_minimum_required(VERSION 3.10)

add_compile_options( -pthread)
project(FPS)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RELEASE")
endif ()
find_package(Threads)
find_package(CUDA REQUIRED)

file(GLOB SRC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/)
include_directories( . ${SRC_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
list(APPEND LINK_LIBRARY
            ${CUDA_cusparse_LIBRARY}
            ${CUDA_LIBRARIES}
            ${CUDA_CUBLAS_LIBRARIES}
            ${CUDA_curand_LIBRARY}
            ${CMAKE_THREAD_LIBS_INIT}    
            )
add_subdirectory(src)

add_executable(fps_test main.cc )
target_link_libraries(fps_test fps)
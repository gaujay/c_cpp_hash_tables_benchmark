cmake_minimum_required(VERSION 3.5)

project(htables_bench LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
  add_compile_options(/W3)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /GL")
else()
  add_compile_options(-Wall)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -static -march=native -mtune=native")
endif()

add_executable(htables_bench
               main.cpp)

target_include_directories(htables_bench PUBLIC ${PROJECT_SOURCE_DIR})

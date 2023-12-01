cmake_minimum_required(VERSION 3.0)
project(openaicpp)

set(CMAKE_PROGRAM_PATH "../")

include_directories("include/curl")
include_directories("include/openai")
#include_directories("include/openai/nlohmann")

add_subdirectory(src)


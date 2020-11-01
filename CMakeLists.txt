cmake_minimum_required(VERSION 3.10)
project(dsp_team_project)

set(CMAKE_CXX_STANDARD 14)

file(GLOB source_files src/*.cpp)
file(GLOB header_files src/*.h)

add_executable(dsp_team_project ${source_files} ${header_files})

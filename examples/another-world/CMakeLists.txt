cmake_minimum_required(VERSION 3.1)
project (another-world)
include (../../32blit.cmake)
blit_executable (another-world another-world.cpp virtual-machine.cpp resource.cpp)

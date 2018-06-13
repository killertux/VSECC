cmake_minimum_required(VERSION 3.2)
project(ECC)

set(CMAKE_CXX_STANDARD 14)

add_executable(ECC main.cpp app/ECurve/ECurve.cpp app/ECurve/ECurve.hpp app/EPoint/EPoint.cpp app/EPoint/EPoint.hpp app/Exception/Exception.cpp app/Exception/Exception.hpp app/ECC.cpp app/ECC.hpp)

target_link_libraries(ECC -lntl -lpthread)
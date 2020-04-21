cmake_minimum_required (VERSION 3.12)

project (KokkosAntiPatterns)

cmake_policy(SET CMP0074 NEW)
find_package(Kokkos REQUIRED)

add_subdirectory(implicit-this-capture)



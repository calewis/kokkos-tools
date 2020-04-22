add_executable(basic-example basic-example.cpp)
target_link_libraries(basic-example Kokkos::kokkos)

add_executable(explicit-host explicit-host.cpp)
target_link_libraries(explicit-host Kokkos::kokkos)

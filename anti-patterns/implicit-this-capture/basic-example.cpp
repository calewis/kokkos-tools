#include <Kokkos_Core.hpp>

struct MyStruct {
  void operator()() {
    Kokkos::parallel_for(
        50, KOKKOS_LAMBDA(int i) { 
          printf("%d\n", N + i); 
        });
  }

  int N = 1000;
};

int main(int argc, char** argv) {
  Kokkos::initialize(argc, argv);
  {
    MyStruct{}();
  }
  Kokkos::finalize();

  return 0;
}

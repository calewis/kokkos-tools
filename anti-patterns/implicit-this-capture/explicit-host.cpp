#include <Kokkos_Core.hpp>

KOKKOS_FUNCTION void do_something(int i, int j) {
  printf("Hello{%i} from j = %i\n", i, j);
}

struct GoodClass {
  int foo;

  KOKKOS_INLINE_FUNCTION GoodClass(int f) : foo(f) {}
  KOKKOS_INLINE_FUNCTION void method() {
    Kokkos::parallel_for(
        Kokkos::RangePolicy<Kokkos::DefaultHostExecutionSpace>(0, 42),
        KOKKOS_LAMBDA(int i) { do_something(foo, i); });
  }
};

int main(int argc, char **argv) {
  Kokkos::initialize(argc, argv);
  { GoodClass{5}.method(); }
  Kokkos::finalize();

  return 0;
}

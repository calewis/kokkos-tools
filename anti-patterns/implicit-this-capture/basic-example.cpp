#include <Kokkos_Core.hpp>

using TeamMember = Kokkos::TeamPolicy<>::member_type;

KOKKOS_FUNCTION void do_something(int member, int i) {
  printf("Hello{%i} from i = %i\n", member, i);
}

struct GoodClass {
  int foo;
  TeamMember member;

  KOKKOS_INLINE_FUNCTION GoodClass(int f, TeamMember m) : foo(f), member(m) {}
  KOKKOS_INLINE_FUNCTION void method() {
    Kokkos::parallel_for(Kokkos::TeamThreadRange(member, 15),
                         [&](int i) { do_something(foo, i); });
  }
};

struct BadClass {
  int foo = 1;
  KOKKOS_INLINE_FUNCTION void method() {
    Kokkos::parallel_for(
        15, KOKKOS_LAMBDA(const int i) { do_something(foo, i); });
  }
};

int main(int argc, char **argv) {
  Kokkos::initialize(argc, argv);
  {
    BadClass{}.method();
    Kokkos::parallel_for(
        Kokkos::TeamPolicy<>(1, 15), KOKKOS_LAMBDA(TeamMember const &member) {
          GoodClass(5, member).method();
        });
  }
  Kokkos::finalize();

  return 0;
}

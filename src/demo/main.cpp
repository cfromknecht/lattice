#include <lattice/PolyRingMatrix.h>

#include <cstdlib>
#include <iostream>
#include <sys/time.h>

const size_t ITERATIONS = 10000;
const size_t SPREAD = 100;

int main() {
  srand( time( NULL ) );

  // Polynomial Multiplication
  auto ring = lattice::PolyRingMatrix{1, 8, 256, 8};
  auto ring2 = lattice::PolyRingMatrix{8, 8, 256, 8};
  auto ring3 = lattice::PolyRingMatrix{1, 8, 256, 8};
  ring.uniformInit();
  ring2.uniformInit();

  struct timeval t1, t2;
  gettimeofday( &t1, 0 );
  ring * ring2;
  gettimeofday( &t2, 0 );

  std::cout << "time: " << (t2.tv_usec - t1.tv_usec 
      + 1000000*(t2.tv_sec - t1.tv_sec))
      << std::endl;

  gettimeofday( &t1, 0 );
  ring += ring3;
  gettimeofday( &t2, 0 );

  std::cout << "time: " << (t2.tv_usec - t1.tv_usec 
      + 1000000*(t2.tv_sec - t1.tv_sec))
      << std::endl;

  return 0;
}

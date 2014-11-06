#include <lattice/DiscreteGaussianSampler.h>
#include <lattice/Constants.h>

#include <cstdlib>
#include <iostream>
#include <sys/time.h>

const size_t ITERATIONS = 10000;
const size_t SPREAD = 100;

int main() {
  srand( time( NULL ) );

  auto sampler = lattice::DiscreteGaussianSampler{SPREAD, 63, 1024};
  for ( size_t i = 0; i < ITERATIONS; ++i )
    sampler.sample();

  // Polynomial Multiplication
  auto ring = lattice::PolyRing{256, 14};
  auto ring2 = lattice::PolyRing{256, 14};
  ring.uniformInit();
  ring2.uniformInit();

  struct timeval t1, t2;
  gettimeofday( &t1, 0 );
#pragma omp parallel for
  for ( size_t i = 0; i < ITERATIONS; ++i )
    ring * ring2;
  gettimeofday( &t2, 0 );
  
  std::cout << "*=: " << 
    double(t2.tv_usec - t1.tv_usec + 1000000*(t2.tv_sec - t1.tv_sec))/double(ITERATIONS)
    << std::endl;

  gettimeofday( &t1, 0 );
#pragma omp parallel for
  for ( size_t i = 0; i < ITERATIONS; ++i )
    ring *= ring2;
  gettimeofday( &t2, 0 );

  std::cout << "*: " << 
    double(t2.tv_usec - t1.tv_usec + 1000000*(t2.tv_sec - t1.tv_sec))/double(ITERATIONS)
    << std::endl;

  return 0;
}

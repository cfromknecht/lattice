#include <lattice/DiscreteGaussianSampler.h>
#include <lattice/PolyRingFLINT.h>

#include <cstdlib>
#include <iostream>

const size_t ITERATIONS = 1000;
const size_t SPREAD = 100;

int main() {
  srand( time( NULL ) );

  auto sampler = lattice::DiscreteGaussianSampler{SPREAD, 63, 1024};
  for ( size_t i = 0; i < ITERATIONS; ++i )
    sampler.sample();

  auto ring = lattice::PolyRingFLINT{256, 8};
  auto ring2 = lattice::PolyRingFLINT{256, 8};
  ring *= ring2;
  ring += ring2;
  ring2 -= ring2;
  ring2 = ring;

  std::cout << "degree: " << ring.degree() << std::endl;
  std::cout << "degree2: " << ring2.degree() << std::endl;

  return 0;
}

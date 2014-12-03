#include <lattice/PolyRingMatrix.h>
#include <lattice/Trapdoor.h>

#include <cstdlib>
#include <iostream>
#include <sys/time.h>

const size_t N = 256;
const size_t K = 8;

const size_t ITERATIONS = 25;
const size_t SPREAD = 100;

double millsBetween( struct timeval tv1, struct timeval tv2 ) {
  return tv2.tv_usec - tv1.tv_usec + 1000000.0*(tv2.tv_sec - tv1.tv_sec);
}

int main() {
  srand( time( NULL ) );

  double encrypt_time = 0;
  struct timeval t1, t2;

  auto A = lattice::PolyRingMatrix{2*K, 1, N, K};
  auto s = lattice::PolyRingMatrix{1, 1, N, K};
  auto e = lattice::PolyRingMatrix{2*K, 1, N, K};
  auto G = lattice::PolyRingMatrix{K, 1, N, K};
  auto m = lattice::PolyRingMatrix{2*K, 1, N, K};

  A.uniformInit();
  m.uniformInit();

  for ( size_t i = 0; i < 8; ++i )
    G.setCoeff( i, 0, 0, size_t(1) << i );

  // trapdoor for G
  auto TG = lattice::PolyRingMatrix{8, 8, 256, 8};
  for ( size_t i = 0; i < 8; ++i ) {
    TG.setCoeff( i, i, 0, 2 );
    if ( i < 7 )
      TG.setCoeff( i, i + 1, 0, -1 );
  }

  for ( size_t i = 0; i < ITERATIONS; ++i ) {
    gettimeofday( &t1, 0 );
    auto y = A * s + e + G *m; // error correcting encryption
    gettimeofday( &t2, 0 );
    encrypt_time += millsBetween( t1, t2 );
  }

  std::cout << "encrypt time: " << (encrypt_time/double(ITERATIONS)) << std::endl;

  return 0;
}


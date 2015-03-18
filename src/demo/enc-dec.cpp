#include <lattice/PolyRingMatrix.h>

#include <cstdlib>
#include <iostream>
#include <sys/time.h>

const size_t N = 256;
const size_t K = 8;

const size_t ITERATIONS = 100;
const size_t SPREAD = 100;

double microsecondsBetween( struct timeval tv1, struct timeval tv2 ) {
  return tv2.tv_usec - tv1.tv_usec + 1000000.0*(tv2.tv_sec - tv1.tv_sec);
}

int main() {
  srand( time( NULL ) );

  double encrypt_time = 0;
  double decrypt_time = 0;
  struct timeval t1, t2;

  auto A = lattice::PolyRingMatrix{K, 1, N, K};
  auto s = lattice::PolyRingMatrix{1, 1, N, K};
  auto e = lattice::PolyRingMatrix{K, 1, N, K};
  auto G = lattice::PolyRingMatrix{K, 1, N, K};
  auto m = lattice::PolyRingMatrix{1, 1, N, K};

  A.uniformInit();

  // initialize G
  for ( size_t i = 0; i < K; ++i )
    G.setCoeff( i, 0, 0, size_t(1) << i );

  // trapdoor for G
  auto TG = lattice::PolyRingMatrix{K, K, 256, K};
  for ( size_t i = 0; i < K; ++i ) {
    TG.setCoeff( i, i, 0, 2 );
    if ( i < 7 )
      TG.setCoeff( i, i + 1, 0, -1 );
  }

  for ( size_t i = 0; i < ITERATIONS; ++i ) {
    gettimeofday( &t1, 0 );
    m.uniformInit();
    s.uniformInit();
    e.ternaryInit();
    auto y = A * s + G * m + e; // error correcting encryption
    gettimeofday( &t2, 0 );
    encrypt_time += microsecondsBetween( t1, t2 );

    gettimeofday( &t1, 0 );
    auto TGe = TG * (y - A * s);
    gettimeofday( &t2, 0 );
    decrypt_time += microsecondsBetween( t1, t2 );

    if ( i == ITERATIONS - 1 ) {
      std::cout << "TGe: " << std::endl;
      for ( size_t j = 0; j < K; ++j  ) {
        fmpz_mod_poly_print( *TGe.polys()[j].poly() );
        std::cout << std::endl;
      }
      std::cout << std::endl;

      std::cout << "error: " << std::endl;
      fmpz_mod_poly_print( *e.polys()[K-1].poly() );
      std::cout << std::endl;
      std::cout << std::endl;

      auto ePrime = *TG.gaussianElimination( TGe );
      std::cout << "recovered error: " << std::endl;
      fmpz_mod_poly_print( *ePrime.polys()[0].poly() );
      std::cout << std::endl;
    }
  }

  std::cout << "total time: " << encrypt_time + decrypt_time << std::endl;
  std::cout << "encrypt time: " << (encrypt_time/double(ITERATIONS)) << std::endl;
  std::cout << "decrypt time: " << (decrypt_time/double(ITERATIONS)) << std::endl;

  return 0;
}


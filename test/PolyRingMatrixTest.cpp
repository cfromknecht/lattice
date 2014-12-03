#include <lattice/PolyRingMatrix.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>

constexpr std::size_t operator "" _sz ( unsigned long long int x ) {
  return x;
}

TEST( PolyRingMatrixTest, parameters ) {
  size_t n = 2;
  size_t m = 3;
  size_t degree = 256;
  size_t k = 8;
  auto matrix = lattice::PolyRingMatrix{n, m, degree, k};

  ASSERT_EQ( matrix.n(), n );
  ASSERT_EQ( matrix.m(), m );
  ASSERT_EQ( matrix.degree(), degree );
  ASSERT_EQ( matrix.k(), k );
}

TEST( PolyRingMatrixTest, gMatrix ) {
  size_t degree = 256;
  size_t k = 8;
  auto G = lattice::PolyRingMatrix{1, k, degree, k};
  for ( size_t i = 0; i < k; ++i )
    G[i].set( 0, 1_sz << i );
  
  // bit decomposition of 15
  auto xPrime = lattice::PolyRingMatrix{k, 1, degree, k};
  xPrime[0].set( 0, 1 );
  xPrime[1].set( 0, 1 );
  xPrime[2].set( 0, 1 );
  xPrime[3].set( 0, 1 );

  auto x = G * xPrime;

  ASSERT_EQ( 15_sz, x[0].get( 0 ) );
}

TEST( PolyRingMatrixTest, copy ) {
  size_t degree = 256;
  size_t k = 8;
  auto matrix = lattice::PolyRingMatrix{1, 1, degree, k};
  matrix.uniformInit();

  lattice::PolyRingMatrix matrixCopy{matrix};
  for ( size_t i = 0; i < degree; ++i )
    ASSERT_EQ( matrix.polys()[0].get( i ), matrixCopy.polys()[0].get( i ) );
}

TEST( PolyRingMatrixTest, assingment ) {
  size_t degree = 256;
  size_t k = 8;
  auto matrix = lattice::PolyRingMatrix{1, 1, degree, k};
  matrix.uniformInit();

  auto matrixCopy = matrix;
  for ( size_t i = 0; i < degree; ++i )
    ASSERT_EQ( matrix.polys()[0].get( i ), matrixCopy.polys()[0].get( i ) );
}


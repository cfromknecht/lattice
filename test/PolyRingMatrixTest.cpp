#include <lattice/PolyRingMatrix.h>
#include <gtest/gtest.h>

#include <cstdlib>

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


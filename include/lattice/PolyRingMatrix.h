#ifndef _POLY_RING_MATRIX_
#define _POLY_RING_MATRIX_

#include <lattice/PolyRing.hpp>

#include <vector>

namespace lattice {

  class PolyRingMatrix {
    std::vector<PolyRing> _polys;
    size_t _n;
    size_t _m;
    size_t _degree;
    size_t _k;

    PolyRingMatrix() = delete;
  public:
    PolyRingMatrix( size_t nn, size_t mm, size_t deg, size_t kk );
    PolyRingMatrix( const PolyRingMatrix& other );
    PolyRingMatrix& operator=( const PolyRingMatrix& rhs );
    ~PolyRingMatrix();

    PolyRingMatrix& operator+=( const PolyRingMatrix& rhs );
    PolyRingMatrix& operator-=( const PolyRingMatrix& rhs );
    PolyRingMatrix& operator*=( const PolyRingMatrix& rhs );
    PolyRingMatrix operator+( const PolyRingMatrix& rhs );
    PolyRingMatrix operator-( const PolyRingMatrix& rhs );
    PolyRingMatrix operator*( const PolyRingMatrix& rhs );
    const PolyRing operator[]( size_t i ) const;
    PolyRing& operator[]( size_t i );

    size_t n() const { return _n; }
    size_t m() const { return _m; }
    size_t degree() const { return _degree; }
    size_t k() const { return _k; }

    void uniformInit(); 
    void ternaryInit(); 

    const std::vector<PolyRing> polys() const { return _polys; }
  };

}

#endif


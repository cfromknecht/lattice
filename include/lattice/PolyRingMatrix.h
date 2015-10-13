#ifndef LATTICE_POLY_RING_MATRIX
#define LATTICE_POLY_RING_MATRIX

#include <lattice/PolyRing.hpp>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace lattice {

  class PolyRingMatrix {
  protected:
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
    PolyRing& operator[]( size_t i );
    const PolyRing operator[]( size_t i ) const;

    size_t n() const { return _n; }
    size_t m() const { return _m; }
    size_t degree() const { return _degree; }
    size_t k() const { return _k; }

    void setPoly( size_t row, size_t col, const PolyRing& ring );
    void setCoeff( size_t row, size_t col, size_t i, size_t val );

    std::vector<PolyRing>& polys() { return _polys; }
    const std::vector<PolyRing>& polys() const { return _polys; }

    void uniformInit(); 
    void uniformInit( size_t i ); 
    void ternaryInit(); 
    void ternaryInit( size_t i ); 

    PolyRingMatrix* gaussianElimination( const PolyRingMatrix& target ) const;

    std::string toString();

  };

  inline bool operator==( const PolyRingMatrix& lhs, const PolyRingMatrix& rhs ) {
    // same object?
    if ( &lhs == &rhs ) return true;
    // are params equal?
    auto checkParams = lhs.n() == rhs.n() && 
                       lhs.m() == rhs.m() && 
                       lhs.degree() == rhs.degree() && 
                       lhs.k() == rhs.k() &&
                       lhs.polys().size() == rhs.polys().size();
    if ( !checkParams ) return false;
    // check all polynomials
    for ( size_t i = 0; i < lhs.polys().size(); ++i )
      if ( lhs.polys()[i] != rhs.polys()[i] )
        return false;
    // must be equal
    return true;
  }

  typedef std::unique_ptr<PolyRingMatrix> PolyRingMatrixPtr;

}

#endif


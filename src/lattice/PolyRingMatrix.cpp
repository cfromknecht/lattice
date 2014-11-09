#include <lattice/PolyRingMatrix.h>

#include <cassert>

namespace lattice {

  PolyRingMatrix::PolyRingMatrix( size_t nn, size_t mm, size_t deg, size_t kk ) : 
      _polys(std::vector<PolyRing>(nn*mm, PolyRing{deg, kk})), _n{nn}, _m{mm}, 
      _degree(deg), _k(kk) {}

  PolyRingMatrix::PolyRingMatrix( const PolyRingMatrix& o ) :
      _polys(std::vector<PolyRing>(o.n()*o.m(), PolyRing{o.degree(), o.k()})), 
      _n(o.n()), _m(o.m()), _degree(o.degree()), _k(o.k()) {}

  PolyRingMatrix& PolyRingMatrix::operator=( const PolyRingMatrix& rhs ) {
    if ( this != &rhs ) {
      _n = rhs.n();
      _m = rhs.m();
      _polys = std::vector<PolyRing>(_n*_m, PolyRing{_degree, _k});
      for ( size_t i = 0; i < _n*_m; ++i )
        _polys[i] = rhs[i];
    }
    return *this;
  }

  PolyRingMatrix::~PolyRingMatrix() {}

  PolyRingMatrix& PolyRingMatrix::operator+=( const PolyRingMatrix& rhs ) {
    assert( _n == rhs.n() );
    assert( _m == rhs.m() );
    for ( size_t i = 0; i < _n*_m; ++i )
      _polys[i] += rhs[i];
    return *this;
  }

  PolyRingMatrix& PolyRingMatrix::operator-=( const PolyRingMatrix& rhs ) {
    assert( _n == rhs.n() );
    assert( _m == rhs.m() );
    for ( size_t i = 0; i < _n*_m; ++i )
      _polys[i] -= rhs[i];
    return *this;
  }

  PolyRingMatrix& PolyRingMatrix::operator*=( const PolyRingMatrix& rhs ) {
    *this = *this * rhs;
    return *this;
  }

  PolyRingMatrix PolyRingMatrix::operator+( const PolyRingMatrix& rhs ) {
    PolyRingMatrix matrix = *this;
    matrix += rhs;
    return matrix;
  }

  PolyRingMatrix PolyRingMatrix::operator-( const PolyRingMatrix& rhs ) {
    PolyRingMatrix matrix = *this;
    matrix -= rhs;
    return matrix;
  }

  PolyRingMatrix PolyRingMatrix::operator*( const PolyRingMatrix& rhs ) {
    assert( _m == rhs.n() );
    PolyRingMatrix matrix{_n, rhs.m(), _degree, _k};
    for ( size_t r = 0; r < _n; ++r )
      for ( size_t s = 0; s < rhs.m(); ++s )
        for ( size_t t = 0; t < _m; ++t )
          matrix[r*rhs.m() + s] += _polys[r*_m + t] * rhs[t*rhs.m() + s];
        
    return matrix;
  }

  PolyRing& PolyRingMatrix::operator []( size_t i ) {
    assert( i < _n*_m );
    return _polys[i];
  }

  const PolyRing PolyRingMatrix::operator []( size_t i ) const {
    assert( i < _n*_m );
    return _polys[i];
  }

  void PolyRingMatrix::uniformInit() {
    for ( size_t i = 0; i < _n*_m; ++i )
      _polys[i].uniformInit();
  }

  void PolyRingMatrix::ternaryInit() {
    for ( size_t i = 0; i < _n*_m; ++i )
      _polys[i].ternaryInit();
  }

}


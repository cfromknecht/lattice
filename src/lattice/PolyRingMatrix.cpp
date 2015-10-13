#include <lattice/PolyRingMatrix.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace lattice {

  PolyRingMatrix::PolyRingMatrix( size_t nn, size_t mm, size_t deg, size_t kk ) : 
      _polys( std::vector<PolyRing>{nn*mm, PolyRing{deg, kk}} ), 
      _n( nn ), 
      _m( mm ), 
      _degree( deg ), 
      _k( kk ) {}

  PolyRingMatrix::PolyRingMatrix( const PolyRingMatrix& o ) :
      _polys( std::vector<PolyRing>{o.n()*o.m(), PolyRing{o.degree(), o.k()}} ), 
      _n( o.n() ),
      _m( o.m() ),
      _degree( o.degree() ),
      _k( o.k() ) {
    // copy polynomials
#pragma omp parallel for
    for ( size_t i = 0; i < _n*_m; ++i )
      _polys[i] = o.polys()[i];
   }

  PolyRingMatrix& PolyRingMatrix::operator=( const PolyRingMatrix& rhs ) {
    std::cout << "copying PolyRingMatrix" << std::endl;
    if ( this != &rhs ) {
      _n = rhs.n();
      _m = rhs.m();
      _polys = std::vector<PolyRing>(_n*_m, PolyRing{_degree, _k});

      std::cout << "initial: " << _polys[0].toString() << std::endl;
      std::cout << "rhs: " << rhs._polys[0].toString() << std::endl;

#pragma omp parallel for
      for ( size_t i = 0; i < _n*_m; ++i )
        _polys[i] = rhs._polys[i];

      std::cout << "after: " << _polys[0].toString() << std::endl;
    }
    return *this;
  }

  PolyRingMatrix::~PolyRingMatrix() {}

  PolyRingMatrix& PolyRingMatrix::operator+=( const PolyRingMatrix& rhs ) {
    if ( _n != rhs.n() || _m != rhs.m() ) 
      throw std::runtime_error{"matrices must be same size"};
#pragma omp parallel for
    for ( size_t i = 0; i < _n*_m; ++i )
      _polys[i] += rhs[i];
    return *this;
  }

  PolyRingMatrix& PolyRingMatrix::operator-=( const PolyRingMatrix& rhs ) {
    if ( _n != rhs.n() || _m != rhs.m() ) 
      throw std::runtime_error{"matrices must be same size"};
#pragma omp parallel for
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
    if ( _m != rhs.n() ) 
      throw std::runtime_error{"matrices do not align"};
    PolyRingMatrix matrix{_n, rhs.m(), _degree, _k};
#pragma omp parallel for
    for ( size_t r = 0; r < _n; ++r )
#pragma omp parallel for
      for ( size_t s = 0; s < rhs.m(); ++s )
        for ( size_t t = 0; t < _m; ++t )
          matrix[r*rhs.m() + s] += _polys[r*_m + t] * rhs[t*rhs.m() + s];
    return matrix;
  }

  PolyRing& PolyRingMatrix::operator []( size_t i ) {
    assert( i < _n*_m );
    if ( i >= _n*_m ) throw std::runtime_error{"array bounds error"};
    return _polys[i];
  }

  const PolyRing PolyRingMatrix::operator []( size_t i ) const {
    assert( i < _n*_m );
    return _polys[i];
  }

  void PolyRingMatrix::setPoly( size_t row, size_t col, const PolyRing& ring ) {
    _polys[row*_m + col] = ring;
  }

  void PolyRingMatrix::setCoeff( size_t row, size_t col, size_t i, size_t val ) {
    _polys[row*_m + col].set( i, val );
  }

  void PolyRingMatrix::uniformInit( size_t i ) {
    _polys[i].uniformInit();
  }

  void PolyRingMatrix::uniformInit() {
#pragma omp parallel for
    for ( size_t i = 0; i < _n*_m; ++i )
      this->uniformInit( i );
  }

  void PolyRingMatrix::ternaryInit( size_t i ) {
    _polys[i].ternaryInit();
  }

  void PolyRingMatrix::ternaryInit() {
#pragma omp parallel for
    for ( size_t i = 0; i < _n*_m; ++i )
      this->ternaryInit( i );
  }

  PolyRingMatrix*
  PolyRingMatrix::gaussianElimination( const PolyRingMatrix& target ) const {
    if ( target.m() != 1 || _n != target.n() || _n != _m ) 
      throw "Cannot compute Gaussian Elimination";
    
    auto solution = new PolyRingMatrix{_m, 1, _degree, _k};
    //auto A = new PolyRingMatrix{*this};
    //auto b = new PolyRingMatrix{target};

    return solution;
  }

  std::string PolyRingMatrix::toString() {
    std::stringstream ss;

    ss << _n << " " << _m << " " << _degree << " " << _k << std::endl;

    for ( size_t i = 0; i < _polys.size(); ++i )
      ss << _polys[i].toString();

    return ss.str();
  }

}


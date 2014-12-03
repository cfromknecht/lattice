#include <lattice/PolyRingFLINT.h>

#include <iostream>

namespace lattice {

  PolyRingFLINT::PolyRingFLINT( size_t nn, size_t kk ) :
    PolyRingBase<PolyRingFLINT>{}, _degree(nn), _k(kk),
    _modulus(size_t(1) << kk), _poly(new ring_t[1]), _F(new ring_t[1]) {
    initPoly();
    initF();
  }

  PolyRingFLINT::PolyRingFLINT( const PolyRingFLINT& other ) :
      PolyRingBase<PolyRingFLINT>{}, _degree(other._degree), _k(other._k),
      _modulus(other._modulus), _poly(new ring_t[1]), _F(new ring_t[1]) {
    copyPoly( other.poly() );
    initF();
  }

  PolyRingFLINT::~PolyRingFLINT() {
    clearPoly();
    clearF();
  }

  // PolyRingBase implementation
  PolyRingFLINT& PolyRingFLINT::operator=( const PolyRingFLINT& rhs ) {
    if ( this != &rhs ) {
      _degree = rhs._degree;
      _k = rhs._k;
      _modulus = rhs._modulus;
      fmpz_mod_poly_set( _poly[0], rhs._poly[0] );
    }
    return *this;
  }

  PolyRingFLINT& PolyRingFLINT::operator+=( const PolyRingFLINT& rhs ) {
    fmpz_mod_poly_add( _poly[0], _poly[0], rhs._poly[0] );
    return *this;
  }

  PolyRingFLINT& PolyRingFLINT::operator-=( const PolyRingFLINT& rhs ) {
    fmpz_mod_poly_sub( _poly[0], _poly[0], rhs._poly[0] );
    return *this;
  }

  PolyRingFLINT& PolyRingFLINT::operator*=( const PolyRingFLINT& rhs ) {
    fmpz_mod_poly_mulmod( _poly[0], _poly[0], rhs._poly[0], _F[0] );
    return *this;
  }

  PolyRingFLINT PolyRingFLINT::operator+( const PolyRingFLINT& rhs ) {
    PolyRingFLINT lhs = PolyRingFLINT{*this};
    lhs += rhs;
    return lhs;
  }

  PolyRingFLINT PolyRingFLINT::operator-( const PolyRingFLINT& rhs ) {
    PolyRingFLINT lhs = PolyRingFLINT{*this};
    lhs -= rhs;
    return lhs;
  }

  PolyRingFLINT PolyRingFLINT::operator*( const PolyRingFLINT& rhs ) {
    PolyRingFLINT lhs = PolyRingFLINT{*this};
    lhs *= rhs;
    return lhs;
  }

  bool PolyRingFLINT::operator==( const PolyRingFLINT& rhs ) const {
    return this == &rhs;
  }

  bool PolyRingFLINT::operator!=( const PolyRingFLINT& rhs ) const {
    return this != &rhs;
  }

  size_t PolyRingFLINT::get( size_t i ) const {
    fmpz_t coeff_z;
    fmpz_init( coeff_z );
    fmpz_mod_poly_get_coeff_fmpz( coeff_z, _poly[0], i );
    return fmpz_get_ui( coeff_z );
  }

  void PolyRingFLINT::set( size_t i, size_t coeff ) {
    fmpz_mod_poly_set_coeff_ui( _poly[0], i, coeff );
  }

  void PolyRingFLINT::uniformInit() {
    for ( size_t i = 0; i < _degree; ++i )
      fmpz_mod_poly_set_coeff_ui( _poly[0], i, rand() );
  }

  void PolyRingFLINT::ternaryInit() {
    auto bernoulliDist = BernoulliSampler{};
    for ( size_t i = 0; i < _degree; ++i ) {
      if ( bernoulliDist.sample() ) // 0 with probability 1/2
        fmpz_mod_poly_set_coeff_ui( _poly[0], i, 0 );
      else {
        if ( bernoulliDist.sample() ) // 1 with probability 1/4
          fmpz_mod_poly_set_coeff_ui( _poly[0], i, 1 );
        else
          fmpz_mod_poly_set_coeff_ui( _poly[0], i, _modulus - 1 );
      }
    }
  }

  // Initialization helper methods
  void PolyRingFLINT::initPoly() {
    fmpz_t q_z;
    fmpz_init_set_ui( q_z, _modulus );

    fmpz_mod_poly_init2( _poly[0], q_z, _degree );

    fmpz_clear( q_z );
  }

  void PolyRingFLINT::copyPoly( ring_t* r ) {
    initPoly();
    fmpz_mod_poly_set( _poly[0], r[0] );
  }

  void PolyRingFLINT::clearPoly() {
    fmpz_mod_poly_clear( _poly[0] );
    delete [] _poly;
  }

  void PolyRingFLINT::initF() {
    fmpz_t q_z;
    fmpz_init_set_ui( q_z, _modulus );

    fmpz_mod_poly_init2( _F[0], q_z, _degree );
    fmpz_mod_poly_set_coeff_ui( _F[0], 0, 1 );
    fmpz_mod_poly_set_coeff_ui( _F[0], _degree, 1 );

    fmpz_clear( q_z );
  }

  void PolyRingFLINT::clearF() {
    fmpz_mod_poly_clear( _F[0] );
    delete [] _F;
  }

}


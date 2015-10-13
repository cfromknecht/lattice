#include <lattice/PolyRingFLINT.h>

#include <iostream>
#include <string>
#include <sstream>

namespace lattice {

  PolyRingFLINT::PolyRingFLINT( size_t nn, size_t kk ) :
      PolyRingBase<PolyRingFLINT>{}, 
      _degree(nn), 
      _k(kk),
      _modulus(size_t(1) << kk), 
      _poly(initPoly()),
      _F(initF()) {}

  PolyRingFLINT::PolyRingFLINT( const PolyRingFLINT& other ) :
      PolyRingBase<PolyRingFLINT>{}, 
      _degree(other._degree), 
      _k(other._k),
      _modulus(other._modulus), 
      _poly(other.copyPoly()),
      _F(initF()) {}

  PolyRingFLINT::~PolyRingFLINT() {}

  // PolyRingBase implementation
  PolyRingFLINT& PolyRingFLINT::operator=( const PolyRingFLINT& rhs ) {
    if ( this != &rhs ) {
      _degree = rhs._degree;
      _k = rhs._k;
      _modulus = rhs._modulus;
      fmpz_mod_poly_set( _poly.get(), rhs._poly.get() );
    }
    return *this;
  }

  PolyRingFLINT& PolyRingFLINT::operator+=( const PolyRingFLINT& rhs ) {
    fmpz_mod_poly_add( _poly.get(), _poly.get(), rhs._poly.get() );
    return *this;
  }

  PolyRingFLINT& PolyRingFLINT::operator-=( const PolyRingFLINT& rhs ) {
    fmpz_mod_poly_sub( _poly.get(), _poly.get(), rhs._poly.get() );
    return *this;
  }

  PolyRingFLINT& PolyRingFLINT::operator*=( const PolyRingFLINT& rhs ) {
    fmpz_mod_poly_mulmod( _poly.get(), _poly.get(), rhs._poly.get(), _F.get() );
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
    fmpz_mod_poly_get_coeff_fmpz( coeff_z, _poly.get(), i );
    return fmpz_get_ui( coeff_z );
  }

  void PolyRingFLINT::set( size_t i, size_t coeff ) {
    char buf[256];
    char format[] = "%zu %zu"; 
    log( sprintf( buf, format, i, coeff) );
    fmpz_mod_poly_set_coeff_ui( _poly.get(), i, coeff );
  }

  void PolyRingFLINT::uniformInit() {
    for ( size_t i = 0; i < _degree; ++i )
      fmpz_mod_poly_set_coeff_ui( _poly.get(), i, rand() );
  }

  void PolyRingFLINT::ternaryInit() {
    BernoulliSampler bernoulliDist{};

    for ( size_t i = 0; i < _degree; ++i ) {
      if ( bernoulliDist.sample() ) // 0 with probability 1/2
        fmpz_mod_poly_set_coeff_ui( _poly.get(), i, 0 );
      else {
        if ( bernoulliDist.sample() ) // 1 with probability 1/4
          fmpz_mod_poly_set_coeff_ui( _poly.get(), i, 1 );
        else
          fmpz_mod_poly_set_coeff_ui( _poly.get(), i, _modulus - 1 );
      }
    }
  }


  PolyRingFLINT* PolyRingFLINT::halveEntries() const {
    size_t mod = size_t(1) << _k;
    size_t threshold = mod/2;
    auto halvedPoly = new PolyRingFLINT{_degree, _k};
    std::cout << "degree: " << _degree << std::endl;
    for ( size_t i = 0; i < _degree; ++i ) {
      size_t coeff = get( i );
      std::cout << coeff << " ";
      if ( coeff < threshold )
        halvedPoly->set( i, coeff/2 );
      else
        halvedPoly->set( i, (int(coeff) - mod)/2 + mod );
    }
    std::cout << std::endl;
    return halvedPoly;
  }

  // Initialization helper methods
  ring_handler PolyRingFLINT::initPoly() {
    auto r = ring_handler{new ring_t, &deleteRingT};

    fmpz_t q_z;
    fmpz_init_set_ui( q_z, _modulus );

    fmpz_mod_poly_init2( r.get(), q_z, _degree );

    fmpz_clear( q_z );

    return r;
  }

  ring_handler PolyRingFLINT::initF() {
    auto r = ring_handler{new ring_t, &deleteRingT};

    fmpz_t q_z;
    fmpz_init_set_ui( q_z, _modulus );

    fmpz_mod_poly_init2( r.get(), q_z, _degree );
    fmpz_mod_poly_set_coeff_ui( r.get(), 0, 1 );
    fmpz_mod_poly_set_coeff_ui( r.get(), _degree, 1 );

    fmpz_clear( q_z );

    return r;
  }

  ring_handler PolyRingFLINT::copyPoly() const {
    auto r = ring_handler{new ring_t, &deleteRingT};

    fmpz_t q_z;
    fmpz_init_set_ui( q_z, _modulus );

    fmpz_mod_poly_init2( r.get(), q_z, _degree );
    fmpz_mod_poly_set( r.get(), _poly.get() );

    fmpz_clear( q_z );

    return r;
  }

  void PolyRingFLINT::deleteRingT( ring_t* r ) {
    fmpz_mod_poly_clear( r );
    delete r;
  }

  std::string PolyRingFLINT::toString() const {
    std::stringstream ss;

    ss << _degree << " " << _k << std::endl;
    for ( size_t i = 0; i < _degree; ++i ) {
      if ( i > 0 ) ss << " ";
      ss << get( i );
    }
    ss << std::endl;

    return ss.str();
  }

}


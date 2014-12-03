#include <lattice/Trapdoor.h>

#include <iostream>

namespace lattice {

  Trapdoor::Trapdoor( size_t deg, size_t kk ) : 
      PolyRingMatrix(2*kk, kk, deg, kk), 
      _parityCheck{new PolyRingMatrix{1, 2*kk, deg, kk}} {
    buildTrapdoorWithParityCheck();
  }

  Trapdoor::Trapdoor( const Trapdoor& other ) : 
      PolyRingMatrix( other ), _parityCheck{new PolyRingMatrix{*other.parityCheck()}} {}

  Trapdoor& Trapdoor::operator=( const Trapdoor& rhs ) {
    if ( this != &rhs ) {
      auto oldParityCheck = _parityCheck;
      _parityCheck = new PolyRingMatrix{*rhs.parityCheck()};
      delete oldParityCheck;
    }
    return *this;
  }

  Trapdoor::~Trapdoor() { delete _parityCheck; }
  
  void Trapdoor::buildTrapdoorWithParityCheck() {
    // initialize A|0 and R|0
    for ( size_t i = 0; i < k()*k(); ++i )
      ternaryInit( i );
    for ( size_t i = 0; i < k(); ++i )
      _parityCheck->uniformInit( i );

    // compute AR
    auto AR = *_parityCheck * *this;

    // subtract AR from G, leaving A|G-AR
    PolyRing gVector{degree(), k()};
    for ( size_t i = 0; i < k(); ++i ) {
      gVector.set( 0, size_t(1) << i );
      _parityCheck->setPoly( 0, k() + i, gVector - AR[i] );
    }

    // fill in identity matrix, leaving R|I
    for ( size_t i = 0; i < k(); ++i )
      setCoeff( k() + i, i, 0, 1 );
  }

} // namespace lattice


#include <lattice/StreamState.h>

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

#include <cassert>
#include <memory>

namespace lattice {

  StreamState::StreamState( bool isInitialUse_ ) : 
      _prevToken( nullptr ),
      _r0( nullptr ),
      _r1( nullptr ),
      _isInitialUse( isInitialUse_ ) {}

  StreamState::StreamState( const StreamState& other ) :
      _prevToken( nullptr ),
      _r0( nullptr ),
      _r1( nullptr ),
      _isInitialUse( other.isInitialUse() ) {
    _prevToken = new PolyRingMatrix( other.prevToken() );
    _r0 = new PolyRingMatrix( other.r0() );
    _r1 = new PolyRingMatrix( other.r1() );
  }

  StreamState& StreamState::operator=( const StreamState& rhs ) {
    if ( this != &rhs ) {
      _prevToken = new PolyRingMatrix( rhs.prevToken() );
      _r0 = new PolyRingMatrix( rhs.r0() );
      _r1 = new PolyRingMatrix( rhs.r1() );
      _isInitialUse = rhs.isInitialUse();
    }

    return *this;
  }

  void StreamState::setPrevToken( const PolyRingMatrix& newPrevToken) {
    _prevToken = new PolyRingMatrix( newPrevToken );
  }

  void StreamState::setR0( const PolyRingMatrix& newR0) {
    _r0 = new PolyRingMatrix( newR0 );
  }

  void StreamState::setR1( const PolyRingMatrix& newR1) {
    _r1 = new PolyRingMatrix( newR1 );
  }

} // namespace lattice


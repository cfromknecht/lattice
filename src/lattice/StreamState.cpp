#include <lattice/StreamState.h>

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  StreamState::StreamState( bool isInitialUse_ ) : 
      prevToken( nullptr ),
      r0( nullptr ),
      r1( nullptr ),
      isInitialUse( isInitialUse_ ) {}

  StreamState::StreamState( const StreamState& other ) :
      prevToken( make_unique<PolyRingMatrix>( *other.prevToken ) ),
      r0( make_unique<PolyRingMatrix>( *other.r0) ),
      r1( make_unique<PolyRingMatrix>( *other.r1) ),
      isInitialUse( other.isInitialUse ) {}

  StreamState& StreamState::operator=( const StreamState& other ) {
    prevToken.reset( new PolyRingMatrix{*other.prevToken} );
    r0.reset( new PolyRingMatrix{ *other.r0 } );
    r1.reset( new PolyRingMatrix{ *other.r1 } );
    isInitialUse = other.isInitialUse;

    return *this;
  }

  StreamState& StreamState::operator=( StreamState& other ) {
    prevToken = std::move( other.prevToken );
    r0 = std::move( other.r0 );
    r1 = std::move( other.r1 );
    isInitialUse = other.isInitialUse;

    return *this;
  }

} // namespace lattice


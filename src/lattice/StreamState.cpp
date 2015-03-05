#include <lattice/StreamState.h>

#include <memory>

namespace lattice {

  StreamState::StreamState( bool isInitialUse ) : isInitialUse{isInitialUse} {}

  StreamState::StreamState( const StreamState& other ) :
      prevToken{std::make_unique<PolyRingMatrix>(*other.prevToken)},
      r0{std::make_unique<PolyRingMatrix>(*other.r0)},
      r1{std::make_unique<PolyRingMatrix>(*other.r1)},
      isInitialUse{other.isInitialUse} {}

  StreamState& StreamState::operator=( const StreamState& other ) {
    prevToken.reset( new PolyRingMatrix{*other.prevToken} );
    r0.reset( new PolyRingMatrix{*other.r0} );
    r1.reset( new PolyRingMatrix{*other.r1} );
    isInitialUse{other.isInitialUse};

    return *this;
  }

  StreamState& StreamState::operator=( StreamState& other ) {
    prevToken = std::move( other.prevToken );
    r0 = std::move( other.r0 );
    r1 = std::move( other.r1 );
    isInitialUse{other.isInitialUse};

    return *this;
  }

} // namespace lattice


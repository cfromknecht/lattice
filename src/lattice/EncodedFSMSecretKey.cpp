#include <lattice/EncodedFSMSecretKey.h>

#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  EncodedFSMSecretKey::EncodedFSMSecretKey( size_t lambda_, size_t k_ ) :
      EncodedFSMPublicKey{ lambda_, k_ },
      _start( make_unique<PolyRingMatrix>( 1, 1, lambda_, k_ ) ),
      _accept( make_unique<PolyRingMatrix>( 1, 1, lambda_, k_ ) ), 
      _reject( make_unique<PolyRingMatrix>( 1, 1, lambda_, k_ ) ) {
    _start->uniformInit();
    _accept->uniformInit();
    _reject->uniformInit();
  }

  EncodedFSMSecretKey::EncodedFSMSecretKey( const EncodedFSMSecretKey& other ) : 
      EncodedFSMPublicKey{ other.lambda(), other.k() },
      _start( make_unique<PolyRingMatrix>( *other.start() ) ),
      _accept( make_unique<PolyRingMatrix>( *other.accept() ) ),
      _reject( make_unique<PolyRingMatrix>( *other.reject() ) ) {}

} // namespace lattice


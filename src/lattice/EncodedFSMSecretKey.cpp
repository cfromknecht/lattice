#include <lattice/EncodedFSMSecretKey.h>

#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  EncodedFSMSecretKey::EncodedFSMSecretKey( size_t lambda, size_t k ) :
      EncodedFSMPublicKey{lambda, k},
      _start{new PolyRingMatrix{1, 1, lambda, k}},
      _accept{new PolyRingMatrix{1, 1, lambda, x}}, 
      _reject{new PolyRingMatrix{1, 1, lambda, x}} {
    _start.uniformInit();
    _accept.uniformInit();
    _reject.uniformInit();
  }

  EncodedFSMSecretKey::EncodedFSMSecretKey( const EncodedFSMSecretKey& other ) : 
      EncodedFSMPublicKey{other.lambda(), other.k()},
      _start{new PolyRingMatrix{other.start()}},
      _accept{new PolyRingMatrix{other.accept()}},
      _reject{new PolyRingMatrix{other.reject()}} {}

} // namespace lattice


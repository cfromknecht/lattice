#include <lattice/EncryptedFSMSecretKey.h>

namespace lattice {

  EncryptedFSMSecretKey::EncryptedFSMSecretKey( size_t lambda, size_t k ) :
      _start{new PolyRingMatrix{1, 1, lambda, k}},
      _accept{new PolyRingMatrix{1, 1, lambda, x}}, 
      _reject{new PolyRingMatrix{1, 1, lambda, x}},
      _publicKey{new EncryptedFSMPublicKey{lambda, k}},
      _lambda{lambda},
      _k{k} {
    _start.uniformInit();
    _accept.uniformInit();
    _reject.uniformInit();
  }

  EncryptedFSMSecretKey::EncryptedFSMSecretKey( const EncryptedFSMSecretKey
  other ) : 
      _start{new PolyRingMatrix{other.start()}},
      _accept{new PolyRingMatrix{other.accept()}},
      _reject{new PolyRingMatrix{other.reject()}},
      _publicKey{new EncryptedFSMSecretKey{other.publicKey()}},
      _lambda{other.lambda()},
      _k{other.k()} {}

} // namespace lattice


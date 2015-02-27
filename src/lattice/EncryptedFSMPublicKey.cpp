#include <lattice/EncryptedFSMPublicKey.h>

namespace lattice {

  EncryptedFSMPublicKey::EncryptedFSMPublicKey( size_t lambda, size_t k ) :
      _At{new PolyRingMatrix{k, 1, lambda, k}},
      _A0{new PolyRingMatrix{k, 1, lambda, k}},
      _A1{new PolyRingMatrix{k, 1, lambda, k}},
      _lambda{lambda}, 
      _k{k} {
    _At.uniformInit();
    _A0.uniformInit();
    _A1.uniformInit();
  }

  EncryptedFSMPublicKey::EncryptedFSMPublicKey( const EncryptedFSMPublicKey
  other ) :
      _At{new PolyRingMatrix{other.At()}},
      _A0{new PolyRingMatrix{other.A0()}},
      _A1{new PolyRingMatrix{other.A1()}},
      _lambda{other.lambda()},
      _k{other.k()} {}

} // namespace lattice

